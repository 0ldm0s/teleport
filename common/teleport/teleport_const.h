#ifndef __TELEPORT_CONST_H__
#define __TELEPORT_CONST_H__

// ���ļ��趨teleport����ģ��֮��ͨѶʱ�Ĵ���ֵ��JSON���ݣ���������
//  - WEB����������
//  - WEB������WEB��̨
//  - WEB��̨��CORE���ķ���

// �ɹ�
#define TPE_OK			0

//-------------------------------------------------------
// ͨ�ô���ֵ
//-------------------------------------------------------
#define TPE_NEED_MORE_DATA			1	// ��Ҫ�������ݣ���һ���Ǵ���


// 100~299��ͨ�ô���ֵ

#define TPE_FAILED					100	// �ڲ�����
#define TPE_NETWORK					101	// �������

// HTTP������ش���
#define TPE_HTTP_METHOD				120	// ��Ч�����󷽷�������GET/POST�ȣ������ߴ�������󷽷���������ҪPOST��ȴʹ��GET��ʽ����
#define TPE_HTTP_URL_ENCODE			121	// URL��������޷����룩
//#define TPE_HTTP_URI				122	// ��Ч��URI

#define TPE_UNKNOWN_CMD				124	// δ֪������
#define TPE_JSON_FORMAT				125	// �����JSON��ʽ����ҪJSON��ʽ���ݣ�����ȴ�޷���JSON��ʽ���룩
#define TPE_PARAM					126	// ��������
#define TPE_DATA					127	// ���ݴ���




// #define TPE_OPENFILE_ERROR			0x1007	// �޷����ļ�
// #define TPE_GETTEMPPATH_ERROR		0x1007
#define TPE_OPENFILE				300

//-------------------------------------------------------
// ���ֳ���ר�ô���ֵ
//-------------------------------------------------------
#define TPE_NO_ASSIST				100000	// δ�ܼ�⵽���ֳ���
#define TPE_OLD_ASSIST				100001	// ���ֳ���汾̫��
#define TPE_START_CLIENT			100002	// �޷������ͻ��˳����޷��������̣�



//-------------------------------------------------------
// ���ķ���ר�ô���ֵ
//-------------------------------------------------------
#define TPE_NO_CORE_SERVER			200000	// δ�ܼ�⵽���ķ���



#endif // __TELEPORT_CONST_H__
