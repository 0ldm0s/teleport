"""
"""

# Created on 2016.07.08
#
# Author: Giovanni Cannata
#
# Copyright 2016 - 2018 Giovanni Cannata
#
# This file is part of ldap3.
#
# ldap3 is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ldap3 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with ldap3 in the COPYING and COPYING.LESSER files.
# If not, see <http://www.gnu.org/licenses/>.

try:
    from queue import Empty
except ImportError:  # Python 2
    # noinspection PyUnresolvedReferences
    from Queue import Empty

from ...core.exceptions import LDAPExtensionError
from ...protocol.persistentSearch import persistent_search_control
from ... import SEQUENCE_TYPES
from ...utils.dn import safe_dn


class PersistentSearch(object):
    def __init__(self,
                 connection,
                 search_base,
                 search_filter,
                 search_scope,
                 dereference_aliases,
                 attributes,
                 size_limit,
                 time_limit,
                 controls,
                 changes_only,
                 events_type,
                 notifications,
                 streaming,
                 callback
                 ):
        if connection.strategy.sync:
            raise LDAPExtensionError('Persistent Search needs an asynchronous streaming connection')

        if connection.check_names and search_base:
            search_base = safe_dn(search_base)

        self.connection = connection
        self.changes_only = changes_only
        self.notifications = notifications
        self.message_id = None
        self.base = search_base
        self.filter = search_filter
        self.scope = search_scope
        self.dereference_aliases = dereference_aliases
        self.attributes = attributes
        self.size_limit = size_limit
        self.time_limit = time_limit
        self.connection.strategy.streaming = streaming
        if callback and callable(callback):
            self.connection.strategy.callback = callback
        elif callback:
            raise LDAPExtensionError('callback is not callable')

        if not isinstance(controls, SEQUENCE_TYPES):
            self.controls = []
        else:
            self.controls = controls

        self.controls.append(persistent_search_control(events_type, changes_only, notifications))
        self.start()

    def start(self):
        if self.message_id:  # persistent search already started
            return

        if not self.connection.bound:
            self.connection.bind()

        with self.connection.strategy.async_lock:
            self.message_id = self.connection.search(search_base=self.base,
                                                     search_filter=self.filter,
                                                     search_scope=self.scope,
                                                     dereference_aliases=self.dereference_aliases,
                                                     attributes=self.attributes,
                                                     size_limit=self.size_limit,
                                                     time_limit=self.time_limit,
                                                     controls=self.controls)
            self.connection.strategy.persistent_search_message_id = self.message_id

    def stop(self):
        self.connection.abandon(self.message_id)
        self.connection.unbind()
        if self.message_id in self.connection.strategy._responses:
            del self.connection.strategy._responses[self.message_id]
        if hasattr(self.connection.strategy, '_requests') and self.message_id in self.connection.strategy._requests:  # asynchronous strategy has a dict of request that could be returned by get_response()
            del self.connection.strategy._requests[self.message_id]
        self.connection.strategy.persistent_search_message_id = None
        self.message_id = None

    def next(self):
        if not self.connection.strategy.streaming and not self.connection.strategy.callback:
            try:
                return self.connection.strategy.events.get_nowait()
            except Empty:
                return None

        raise LDAPExtensionError('Persistent search is not accumulating events in queue')
