#ifndef __TS_HTTP_RPC_H__
#define __TS_HTTP_RPC_H__

#include "ts_const.h"

#include <vector>
#include <string>
#include <map>

#include <ex.h>
#include <json/json.h>

#include "../../external/mongoose/mongoose.h"


// typedef ex_u32 ts_rv;

// #define TSR_OK						0x0000
// #define TSR_INVALID_DATA			0x0001
// #define TSR_SEND_ERROR				0x0002
// #define TSR_NEED_MORE_DATA			0x0005
// #define TSR_FAILED					0x0006
// #define TSR_PING_OK					0x0007
// #define TSR_PING_ERROR				0x0008
// 
// #define TSR_INVALID_REQUEST			0x1000
// #define TSR_INVALID_URI				0x1001
// #define TSR_INVALID_URL_ENCODE		0x1002
// #define TSR_NO_SUCH_METHOD			0x1003
// #define TSR_INVALID_JSON_FORMAT		0x1004
// #define TSR_INVALID_JSON_PARAM		0x1005
// #define TSR_CREATE_PROCESS_ERROR	0x1006
// #define TSR_OPENFILE_ERROR			0x1007
// #define TSR_GETTEMPPATH_ERROR		0x1007

/*
//=================================================================
�ӿ�ʹ��˵����

�����������󣬼��� 127.0.0.1:50022������http���������ʽҪ�����£�

GET ��ʽ
http://127.0.0.1:50022/method/json_param
����json_param��ʹ��url_encode���б�����json��ʽ�ַ���

POST ��ʽ
http://127.0.0.1:50022/method
post������������json_param

���У�URI��Ϊ�������֣�
method			����ִ�е����񷽷���
json_param		�����񷽷��ĸ��Ӳ��������û�и��Ӳ������ⲿ�ֿ���ʡ�ԡ�

���ظ�ʽ��ִ�н����󣬷���һ��json��ʽ���ַ����������ߣ���ʽ���£�

{"code":0,"data":varb}

���У�code�Ǳ��еģ���ֵ��һ��������룬0��ʾ�ɹ������ʧ�ܣ������û��data�򡣲����ɹ�ʱ��data�����
�����ķ������ݣ����ʽ���ݾ���ִ�е����񷽷���ͬ����ͬ��

*/

void http_rpc_main_loop(void);
void http_rpc_stop(void);

typedef std::map<ex_astr, ex_astr> content_type_map;

// struct sid_info
// {
// 	ex_astr host_ip;
// 	ex_astr s_id;
// 	bool update;
// };
// typedef std::map<DWORD, sid_info> PidSidMap;

class TsHttpRpc
{
public:
	TsHttpRpc();
	~TsHttpRpc();

	bool init(const char* ip, int port);
	void run(void);
	void stop(void);

	ex_astr get_content_type(ex_astr file_suffix)
	{
		content_type_map::iterator it = m_content_type_map.find(file_suffix);
		if (it != m_content_type_map.end())
		{
			return it->second;
		}
		else
		{
			return "application/octet-stream";
		}
	};

private:
	int _parse_request(struct http_message* req, ex_astr& func_cmd, ex_astr& func_args);
	void _process_js_request(const ex_astr& func_cmd, const ex_astr& func_args, ex_astr& buf);
	void _create_json_ret(ex_astr& buf, int errcode);
	void _create_json_ret(ex_astr& buf, Json::Value& jr_root);

	void _rpc_func_create_ts_client(const ex_astr& func_args, ex_astr& buf);
	void _rpc_func_ts_check(const ex_astr& func_args, ex_astr& buf);
	void _rpc_func_ts_rdp_play(const ex_astr& func_args, ex_astr& buf);
	void _rpc_func_get_config(const ex_astr& func_args, ex_astr& buf);
	void _rpc_func_set_config(const ex_astr& func_args, ex_astr& buf);
	void _rpc_func_file_action(const ex_astr& func_args, ex_astr& buf);
	void _rpc_func_get_version(const ex_astr& func_args, ex_astr& buf);

	static void _mg_event_handler(struct mg_connection *nc, int ev, void *ev_data);

private:
	content_type_map m_content_type_map;
	struct mg_mgr m_mg_mgr;
	bool m_stop;
};

#endif // __TS_HTTP_RPC_H__
