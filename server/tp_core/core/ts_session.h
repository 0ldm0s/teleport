#ifndef __TS_SESSION_H__
#define __TS_SESSION_H__

#include "../common/ts_const.h"
#include "../common/protocol_interface.h"

#include <ex.h>

typedef struct TS_CONNECT_INFO
{
	ex_astr sid;

	// ���������Ϣ��ص�����Ҫ�ص�ID
	int user_id;
	int host_id;
	int account_id;

	ex_astr user_name;// ���뱾�����ӵ��û���

	ex_astr real_remote_host_ip;// ������Զ������IP�������ֱ������ģʽ������remote_host_ip��ͬ��
	ex_astr remote_host_ip;// Ҫ���ӵ�Զ��������IP������Ƕ˿�ӳ��ģʽ����Ϊ·��������IP��
	int remote_host_port;// Ҫ���ӵ�Զ�������Ķ˿ڣ�����Ƕ˿�ӳ��ģʽ����Ϊ·�������Ķ˿ڣ�
	ex_astr client_ip;

	ex_astr account_name;	// Զ���������˺�
	ex_astr account_secret;// Զ�������˺ŵ����루����˽Կ��
	ex_astr account_param;

	int protocol_type;
	int protocol_sub_type;
	int auth_type;
	int sys_type;
	
	int ref_count;// ���������Ϣ�����ü��������������������Ϣ����δ��ʹ�ã��򳬹�30����Զ�����
	ex_u64 ticket_start;// ��������Ϣ�Ĵ���ʱ�䣨���ڳ�ʱδʹ�þ����ٵĹ��ܣ�
}TS_CONNECT_INFO;

typedef std::map<ex_astr, TS_CONNECT_INFO*> ts_connections;

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
	bool get_connect_info(const ex_astr& sid, TS_CONNECT_INFO& info);

protected:
	// �߳�ѭ��
	void _thread_loop(void);
	// ����ֹͣ��־�����߳��ܹ���������
	void _set_stop_flag(void);

private:
	void _gen_session_id(ex_astr& sid, const TS_CONNECT_INFO* info, int len);
	bool _add_connect_info(ex_astr& sid, TS_CONNECT_INFO* info);
	void _check_connect_info(void);

private:
	ExThreadLock m_lock;
	ts_connections m_connections;
};

extern TsSessionManager g_session_mgr;

#endif // __TS_SESSION_H__

