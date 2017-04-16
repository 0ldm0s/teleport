#ifndef __TS_BASE_RECORD_H__
#define __TS_BASE_RECORD_H__

#include "base_env.h"
#include "ts_membuf.h"
#include "protocol_interface.h"

#include <ex.h>

#define MAX_SIZE_PER_FILE 4194304  // 4M = 1024*1024*4

#pragma pack(push,1)

// ¼���ļ�ͷ
typedef struct TS_RECORD_HEADER
{
	ex_u32 magic;		// "TPPR" ��־ TelePort Protocol Record
	ex_u16 ver;			// ¼���ļ��汾��ĿǰΪ2
	ex_u16 protocol;	// Э�飺1=RDP, 2=SSH, 3=Telnet
	ex_u64 timestamp;	// ����¼�����ʼʱ�䣨UTCʱ�����
	ex_u32 packages;	// �ܰ���
	ex_u32 time_ms;		// �ܺ�ʱ�����룩
	ex_u16 width;		// ��ʼ��Ļ�ߴ磺��
	ex_u16 height;		// ��ʼ��Ļ�ߴ磺��
	ex_u16 file_count;	// �����ļ�����
	ex_u32 file_size;	// ���������ļ����ܴ�С��������ÿ�������ļ���ͷ����4�ֽڵ�ÿ�ļ���С��
	char account[16];	// teleport�˺�
	char username[16];	// Զ�������û���
	char ip[18];
	ex_u16 port;

	// RDPר��
	ex_u8 rdp_security;	// 0 = RDP, 1 = TLS

	ex_u8 reserve[128 - 4 - 2 - 2 - 8 - 4 - 4 - 2 - 2 - 2 - 4 - 16 - 16 - 18 - 2 - 1];	// ����
}TS_RECORD_HEADER;

// һ�����ݰ���ͷ
typedef struct TS_RECORD_PKG
{
	ex_u8 type;			// ������������
	ex_u32 size;		// ��������ܴ�С��������ͷ��
	ex_u32 time_ms;		// ���������ʼʱ���ʱ�����룬��ζ��һ�����Ӳ��ܳ�������49�죩
	ex_u8 reserve[3];	// ����
}TS_RECORD_PKG;

#pragma pack(pop)

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
