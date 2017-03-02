#ifndef __TS_HTTP_RPC_H__
#define __TS_HTTP_RPC_H__

#include "mongoose.h"

#include <ex.h>
#include <json/json.h>


/*
//=================================================================
�ӿ�ʹ��˵����

�����������󣬼��� 127.0.0.1:52080������http���������ʽҪ�����£�

GET ��ʽ
http://127.0.0.1:52080/method/json_param
����json_param��ʹ��url_encode���б�����json��ʽ�ַ���

POST ��ʽ
http://127.0.0.1:52080/method
post������������json_param

���У�URI��Ϊ�������֣�
method			����ִ�е����񷽷���
json_param		�����񷽷��ĸ��Ӳ��������û�и��Ӳ������ⲿ�ֿ���ʡ�ԡ�

���ظ�ʽ��ִ�н����󣬷���һ��json��ʽ���ַ����������ߣ���ʽ���£�

{"code":0,"data":varb}

���У�code�Ǳ��еģ���ֵ��һ��������룬0��ʾ�ɹ������ʧ�ܣ������û��data�򡣲����ɹ�ʱ��data�����
�����ķ������ݣ����ʽ���ݾ���ִ�е����񷽷���ͬ����ͬ��

*/

class TsHttpRpc : public ExThreadBase
{
public:
	TsHttpRpc();
	~TsHttpRpc();

	bool init(void);

protected:
	void _thread_loop(void);
	void _set_stop_flag(void);

private:
	ex_rv _parse_request(struct http_message* req, ex_astr& func_cmd, Json::Value& json_param);
	void _process_request(const ex_astr& func_cmd, const Json::Value& json_param, ex_astr& buf);

	//void _create_json_ret(ex_astr& buf, Json::Value& jr_root);
	void _create_json_ret(ex_astr& buf, int errcode, const Json::Value& jr_data);
	void _create_json_ret(ex_astr& buf, int errcode);
	void _create_json_ret(ex_astr& buf, int errcode, const char* message);

	// ����һ���ỰID
	void _rpc_func_request_session(const Json::Value& json_param, ex_astr& buf);
	// ����һ���ַ��������ص������ĵ�BASE64���룩
	void _rpc_func_enc(const Json::Value& json_param, ex_astr& buf);
	// Ҫ���������ķ����˳�
	void _rpc_func_exit(const Json::Value& json_param, ex_astr& buf);

	static void _mg_event_handler(struct mg_connection *nc, int ev, void *ev_data);

private:
	ex_astr m_host_ip;
	int m_host_port;

	struct mg_mgr m_mg_mgr;
};

#endif // __TS_HTTP_RPC_H__
