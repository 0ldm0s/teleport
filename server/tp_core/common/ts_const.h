#ifndef __TS_ERRNO_H__
#define __TS_ERRNO_H__

//#include "ts_types.h"

#define TS_RDP_PROXY_PORT		52089
#define TS_RDP_PROXY_HOST		"0.0.0.0"

#define TS_SSH_PROXY_PORT		52189
#define TS_SSH_PROXY_HOST		"0.0.0.0"

#define TS_TELNET_PROXY_PORT	52389
#define TS_TELNET_PROXY_HOST	"0.0.0.0"

#define TS_HTTP_RPC_PORT		52080
//#define TS_HTTP_RPC_HOST		"127.0.0.1"
#define TS_HTTP_RPC_HOST		"localhost"


#define TS_RDP_PROTOCOL_RDP          0
#define TS_RDP_PROTOCOL_TLS          1
#define TS_RDP_PROTOCOL_HYBRID       2
#define TS_RDP_PROTOCOL_RDSTLS       4
#define TS_RDP_PROTOCOL_HYBRID_EX    8

// #define TS_AUTH_MODE_NONE			0
// #define TS_AUTH_MODE_PASSWORD		1
// #define TS_AUTH_MODE_PRIVATE_KEY	2
// 
// #define TS_PROXY_PROTOCOL_RDP		1
// #define TS_PROXY_PROTOCOL_SSH		2
// #define TS_PROXY_PROTOCOL_TELNET	3

// #define TSR_OK						0x0000
// #define TSR_INVALID_DATA			0x0001
// #define TSR_SEND_ERROR				0x0002
// #define TSR_NEED_MORE_DATA			0x0005
// #define TSR_FAILED					0x0006
// #define TSR_DATA_LEN_ZERO			0x0007
// 
// #define TSR_MAX_CONN_REACHED		0x0010
// #define TSR_MAX_HOST_REACHED		0x0011
// 
// #define TSR_INVALID_REQUEST			0x1000
// #define TSR_INVALID_URI				0x1001
// #define TSR_INVALID_URL_ENCODE		0x1002
// #define TSR_NO_SUCH_METHOD			0x1003
// #define TSR_INVALID_JSON_FORMAT		0x1004
// #define TSR_INVALID_JSON_PARAM		0x1005
// #define TSR_GETAUTH_INFO_ERROR		0x1006
// #define TSR_HOST_LOCK_ERROR			0x1007
// #define TSR_ACCOUNT_LOCK_ERROR		0x1008

//================================================
// #define SESS_STAT_RUNNING				0		// �Ự��ʼ�ˣ���δ����
// #define SESS_STAT_END					9999	// �Ự�ɹ�����
// #define SESS_STAT_ERR_AUTH_DENIED		1		// �Ự��������Ϊ��֤ʧ��
// #define SESS_STAT_ERR_CONNECT			2		// �Ự��������Ϊ�޷����ӵ�Զ������
// #define SESS_STAT_ERR_BAD_SSH_KEY		3		// �Ự��������Ϊ�޷�ʶ��SSH˽Կ
// #define SESS_STAT_ERR_INTERNAL			4		// �Ự��������Ϊ�ڲ�����
// #define SESS_STAT_ERR_UNSUPPORT_PROTOCOL	5	// �Ự��������ΪЭ�鲻֧��(RDP)
// #define SESS_STAT_ERR_BAD_PKG			6		// �Ự��������Ϊ�յ�����ı���
// #define SESS_STAT_ERR_RESET				7		// �Ự��������Ϊteleport���ķ���������
// #define SESS_STAT_ERR_IO				8		// �Ự��������Ϊ�����ж�
// #define SESS_STAT_ERR_SESSION			9		// �Ự��������Ϊ��Ч�ĻỰID


#endif // __TS_ERRNO_H__
