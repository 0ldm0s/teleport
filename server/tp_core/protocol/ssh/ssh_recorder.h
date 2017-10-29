#ifndef __TPP_SSH_RECORDER_H__
#define __TPP_SSH_RECORDER_H__

#include "../../common/base_record.h"

#define TS_RECORD_TYPE_SSH_TERM_SIZE		0x01		// �ն˴�С��������������
#define TS_RECORD_TYPE_SSH_DATA				0x02		// ����չʾ����������

#pragma pack(push,1)

// ¼���ļ�ͷ
// typedef struct TS_RECORD_HEADER
// {
// 	ex_u32 magic;		// "TPPR" ��־ TelePort Protocol Record
// 	ex_u64 timestamp;	// ����¼�����ʼʱ�䣨UTCʱ�����
// 	ex_u32 packages;	// �ܰ���
// 	ex_u32 time_ms;		// �ܺ�ʱ�����룩
// 	ex_u16 width;		// ��ʼ��Ļ�ߴ磺��
// 	ex_u16 height;		// ��ʼ��Ļ�ߴ磺��
// 	ex_u16 file_count;	// �����ļ�����
// 	ex_u32 file_size;	// ���������ļ����ܴ�С��������ÿ�������ļ���ͷ����4�ֽڵ�ÿ�ļ���С��
// 	char account[16];	// teleport�˺�
// 	char username[16];	// Զ�������û���
// 	char ip[18];
// 	ex_u16 port;
// 
// 	ex_u8 reserve[128 - 4 - 8 - 4 - 4 - 2 - 2 - 2 - 4 - 16 - 16 - 18 - 2];	// ����
// }TS_RECORD_HEADER;
// 
// // һ�����ݰ���ͷ
// typedef struct TS_RECORD_PKG
// {
// 	ex_u8 type;			// ������������
// 	ex_u32 size;		// ��������ܴ�С��������ͷ��
// 	ex_u32 time_ms;		// ���������ʼʱ���ʱ�����룬��ζ��һ�����Ӳ��ܳ�������49�죩
// 	ex_u8 reserve[3];	// ����
// }TS_RECORD_PKG;

// ��¼���ڴ�С�ı�����ݰ�
typedef struct TS_RECORD_WIN_SIZE
{
	ex_u16 width;
	ex_u16 height;
}TS_RECORD_WIN_SIZE;

#pragma pack(pop)

class TppSshRec : public TppRecBase
{
public:
	TppSshRec();
	virtual ~TppSshRec();

	void record(ex_u8 type, const ex_u8* data, size_t size);
	void record_win_size_startup(int width, int height);
	void record_win_size_change(int width, int height);
	void record_command(const ex_astr& cmd);

    void flush_record();

protected:
	bool _on_begin(const TPP_CONNECT_INFO* info);
	bool _on_end();

	bool _save_to_data_file();
	bool _save_to_cmd_file();

protected:
	TS_RECORD_HEADER m_head;

	MemBuffer m_cmd_cache;

    bool m_save_full_header;

    FILE* m_file_info;
    FILE* m_file_data;
    FILE* m_file_cmd;
};

#endif // __TPP_SSH_RECORDER_H__
