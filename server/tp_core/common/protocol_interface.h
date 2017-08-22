#ifndef __TP_PROTOCOL_INTERFACE_H__
#define __TP_PROTOCOL_INTERFACE_H__

#include "ts_const.h"
#include <ex.h>

#ifdef EX_OS_WIN32
#	ifdef TPP_EXPORTS
#		define TPP_API __declspec(dllexport)
#	else
#		define TPP_API __declspec(dllimport)
#	endif
#else
#	define TPP_API
#endif

typedef struct TPP_CONNECT_INFO
{
	char* sid;

	// ���������Ϣ��ص�����Ҫ�ص�ID
	int user_id;
	int host_id;
	int account_id;

	char* user_name;		// ���뱾�����ӵ��û���

	char* real_remote_host_ip;	// ������Զ������IP�������ֱ������ģʽ������remote_host_ip��ͬ��
	char* remote_host_ip;	// Ҫ���ӵ�Զ��������IP������Ƕ˿�ӳ��ģʽ����Ϊ·��������IP��
	int remote_host_port;	// Ҫ���ӵ�Զ�������Ķ˿ڣ�����Ƕ˿�ӳ��ģʽ����Ϊ·�������Ķ˿ڣ�
	char* client_ip;

	char* account_name;		// Զ���������˺�
	char* account_secret;	// Զ�������˺ŵ����루����˽Կ��
	//char* account_param;
	char* username_prompt;	// for telnet
	char* password_prompt;	// for telnet

	int protocol_type;
	int protocol_sub_type;
	int auth_type;
	int connect_flag;
}TPP_CONNECT_INFO;

typedef TPP_CONNECT_INFO* (*TPP_GET_CONNNECT_INFO_FUNC)(const char* sid);
typedef void(*TPP_FREE_CONNECT_INFO_FUNC)(TPP_CONNECT_INFO* info);
typedef bool(*TPP_SESSION_BEGIN_FUNC)(const TPP_CONNECT_INFO* info, int* db_id);
typedef bool(*TPP_SESSION_END_FUNC)(const char* sid, int db_id, int ret);


typedef struct TPP_INIT_ARGS
{
	ExLogger* logger;
	ex_wstr exec_path;
	ex_wstr etc_path;
	ex_wstr replay_path;
	ExIniFile* cfg;

	TPP_GET_CONNNECT_INFO_FUNC func_get_connect_info;
	TPP_FREE_CONNECT_INFO_FUNC func_free_connect_info;
	TPP_SESSION_BEGIN_FUNC func_session_begin;
	TPP_SESSION_END_FUNC func_session_end;
}TPP_INIT_ARGS;



#ifdef __cplusplus
extern "C"
{
#endif

	TPP_API ex_rv tpp_init(TPP_INIT_ARGS* init_args);
	TPP_API ex_rv tpp_start(void);
	TPP_API ex_rv tpp_stop(void);

#ifdef __cplusplus
}
#endif

typedef ex_rv (*TPP_INIT_FUNC)(TPP_INIT_ARGS* init_args);
typedef ex_rv (*TPP_START_FUNC)(void);
typedef ex_rv (*TPP_STOP_FUNC)(void);

#endif // __TP_PROTOCOL_INTERFACE_H__
