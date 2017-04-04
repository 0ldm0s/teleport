#ifndef __TS_WEB_RPC_H__
#define __TS_WEB_RPC_H__

#include "ts_session.h"

#include <json/json.h>

// ����log��־״̬
bool ts_web_rpc_register_core();

// ������֤ID��ȡ��֤��Ϣ������������IP���˿ڣ��û����������˽Կ��Э����RDP��SSH�ȵȣ�
bool ts_web_rpc_get_auth_info(int auth_id, Json::Value& jret);

// ��¼�Ự�Ŀ�ʼ
bool ts_web_rpc_session_begin(TS_SESSION_INFO& info, int& record_id);
//session ����
bool ts_web_rpc_session_end(int id, int ret_code);


#endif // __TS_WEB_RPC_H__
