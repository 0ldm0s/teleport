#ifndef __TS_SESSION_H__
#define __TS_SESSION_H__

#include "../common/ts_const.h"
#include "../common/protocol_interface.h"

#include <ex.h>

typedef struct TS_SESSION_INFO
{
	ex_astr sid;
	ex_astr account_name;	// ���뱾�����ӵ��û���

	//int auth_id;
	ex_astr host_ip;
	int host_port;
	int protocol;
	ex_astr user_name;
	ex_astr user_auth;
	ex_astr user_param;
	int auth_mode;
	int sys_type;

	int ref_count;
	ex_u64 ticket_start;
}TS_SESSION_INFO;

typedef std::map<ex_astr, TS_SESSION_INFO*> ts_sessiones;

class TsSessionManager : public ExThreadBase
{
public:
	TsSessionManager();
	~TsSessionManager();

	// ����һ��session-id��
	ex_rv request_session(
		ex_astr& sid,	// ���ص�session-id
		ex_astr account_name,
		int auth_id,
		const ex_astr& host_ip, // Ҫ���ӵ�����IP
		int host_port,  // Ҫ���ӵ������˿�
		int sys_type,   // ��������ϵͳ����
		int protocol,  // Ҫʹ�õ�Э�飬1=rdp, 2=ssh
		const ex_astr& user_name, // ��֤��Ϣ�е��û���
		const ex_astr& user_auth, // ��֤��Ϣ�������˽Կ
		const ex_astr& user_param, //
		int auth_mode // ��֤��ʽ��1=password��2=private-key
	);

	// ����sid�õ�session��Ϣ
	bool get_session(const ex_astr& sid, TS_SESSION_INFO& info);

protected:
	// �߳�ѭ��
	void _thread_loop(void);
	// ����ֹͣ��־�����߳��ܹ���������
	void _set_stop_flag(void);

private:
	bool _add_session(ex_astr& sid, TS_SESSION_INFO* info);
	void _gen_session_id(ex_astr& sid, const TS_SESSION_INFO* info, int len);
	void _check_sessions(void);

private:
	ExThreadLock m_lock;
	ts_sessiones m_sessions;
};

extern TsSessionManager g_session_mgr;

#endif // __TS_SESSION_H__

