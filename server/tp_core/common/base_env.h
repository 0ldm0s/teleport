#ifndef __TS_BASE_ENV_H__
#define __TS_BASE_ENV_H__

#include "protocol_interface.h"

class TppEnvBase
{
public:
	TppEnvBase();
	virtual ~TppEnvBase();

	bool init(TPP_INIT_ARGS* args);

public:
	ex_wstr exec_path;
	ex_wstr etc_path;	// �����ļ���SSH��������˽Կ�ļ��Ĵ��·��
	ex_wstr replay_path;

	TPP_TAKE_SESSION_FUNC take_session;
	TPP_FREE_SESSION_FUNC free_session;
	TPP_SESSION_BEGIN_FUNC session_begin;
	TPP_SESSION_END_FUNC session_end;

protected:
	virtual bool _on_init(TPP_INIT_ARGS* args) = 0;
};

#endif // __TS_BASE_ENV_H__
