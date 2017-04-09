#ifndef __TS_BASE_RECORD_H__
#define __TS_BASE_RECORD_H__

#include "base_env.h"
#include "ts_membuf.h"
#include "protocol_interface.h"

#include <ex.h>

#define MAX_SIZE_PER_FILE 4194304  // 4M = 1024*1024*4
//#define MAX_SIZE_PER_FILE 40*1024
// #define SSH_DATA		 1
// #define SSH_WINDOWS_SIZE 2

#if 0
#pragma pack(push,1)

struct ts_replay_data_header
{
	ex_u8  action;
	ex_u32 time;
	ex_u32 size;
	//char* buf;
};
struct ts_replay_header
{
	char   ID[16];
	char   version[16];
	ex_u8  total_size;
	ex_u8  total_file_count;
	ex_u32 total_time;
	//���飬ÿ������Ԫ�ص�������ÿ���ļ��Ĳ���ʱ��
};
struct ssh_terms_data_header
{
	char   ID[16];
	char   version[16];
	ex_u32  term_count;
	//���飬ÿ������Ԫ�ص�������ÿ���ļ��Ĳ���ʱ��
};
struct ssh_terms_data {
	//char term[16];
	ex_u32 time;
	ex_u32 w;
	ex_u32 h;
	//ex_u32 px;
	//ex_u32 py;
};
#pragma pack(pop)
typedef std::vector<ex_u32> file_time_list;

typedef std::vector<ssh_terms_data> windows_size_list;

class base_record
{
public:
	base_record();
	~base_record();
public:
	void begin(int record_id, int record_type);
	void record(unsigned char* buf, int len, int cmd);
	void windows_size(ssh_terms_data size_info);
	void end();
	ex_astr get_replay_path() {
		return m_current_path;
	}
protected:
	bool open_next_file();
	bool cached_buffer(ts_replay_data_header* header, unsigned char* buf,int len);
	bool save_buffer_to_file(int internal_time);
	bool save_to_file(int internal_time, ts_replay_data_header* header, unsigned char* buf, int len);
protected:
	ex_u64 m_begin_time;
	ex_u64 m_last_time;

	int m_file_current_index;

	ex_astr m_current_path;
	FILE* m_current_file;
	unsigned char* m_buf;
	int m_buf_offset;

	file_time_list m_timelist;
	windows_size_list m_windows_size_list;

	int m_totol_size;
	//Json::Value m_ts_replay;

};
#endif

//====================================================
// NEW INTERFACE
//====================================================

// #define TS_RECORD_TYPE_RDP_CURSOR_POS		0x10		// �������λ�øı䣬���ڻ����������
// #define TS_RECORD_TYPE_RDP_SERVER_PKG		0x11		// ����˷��ص����ݰ�������չʾ

// #pragma pack(push,1)
// 
// // ¼���ļ�ͷ
// typedef struct TS_RECORD_HEADER
// {
// 	ex_u32 magic;		// "TPPR" ��־ TelePort Protocol Record
// 	ex_u32 timestamp;	// ����¼�����ʼʱ�䣨UTCʱ�����
// 	ex_u32 packages;	// �ܰ���
// 	ex_u32 time_ms;		// �ܺ�ʱ�����룩
// 	ex_u16 width;		// ��ʼ��Ļ�ߴ磺��
// 	ex_u16 height;		// ��ʼ��Ļ�ߴ磺��
// 	ex_u8 security;		// 0 = RDP, 1 = SSL
// 	ex_u16 file_count;	// �����ļ�����
// 	ex_u32 file_size;	// ���������ļ����ܴ�С��������ÿ�������ļ���ͷ����4�ֽڵ�ÿ�ļ���С��
// 	char account[16];	// teleport�˺�
// 	char username[16];	// Զ�������û���
// 	char ip[18];
// 	ex_u16 port;
// 
// 	ex_u8 reserve[128 - 20 - 1 - 2 - 4 - 16 - 16 - 18 - 2];	// ����
// }TS_RECORD_HEADER;
// 
// // һ�����ݰ���ͷ
// typedef struct TS_RECORD_PKG
// {
// 	ex_u8 type;			// �����������ͣ�Ŀǰ��ʱ����δʹ�ã�����Ϊ0��
// 	ex_u32 size;		// ��������ܴ�С
// 	ex_u32 time_ms;		// ���������ʼʱ���ʱ�����룬��ζ��һ�����Ӳ��ܳ�������49�죩
// 	ex_u8 reserve[3];	// ����
// }TS_RECORD_PKG;
// 
// RDP����ƶ�
// typedef struct TS_RECORD_RDP_MOUSE_POS
// {
// 	ex_u16 x;
// 	ex_u16 y;
// }TS_RECORD_RDP_MOUSE_POS;

// #pragma pack(pop)

class TppRecBase
{
public:
	TppRecBase();
	virtual ~TppRecBase();

	void begin(const wchar_t* base_path, const wchar_t* base_fname, int record_id, const TPP_SESSION_INFO* info);
	void end(void);

	virtual void record(ex_u8 type, const ex_u8* data, size_t size) = 0;

protected:
	virtual void _on_begin(const TPP_SESSION_INFO* info) = 0;
	virtual void _on_end(void) = 0;

protected:
	int m_protocol;

	ex_wstr m_base_path;		// ¼���ļ�����·�������� /usr/local/eom/teleport/data/replay/ssh/123�����ֱ�����ڲ����ӵģ���Ϊ���λỰ¼���ļ���Ŀ¼����
	ex_wstr m_base_fname;		// ¼���ļ����ļ�����������չ�����֣��ڲ����Դ�Ϊ�����ϳ��ļ�ȫ��������¼���ļ������ m_base_path ָ���Ŀ¼��

	ex_u64 m_start_time;
	ex_u64 m_last_time;

	MemBuffer m_cache;
};

#endif // __TS_BASE_RECORD_H__
