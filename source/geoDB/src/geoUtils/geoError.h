/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                      *
*                                                                            *
*  @file     geoError.h                                                     *
*  @brief    GeoSys ƽ̨�����봦��                             *
*
*	�������������
*	������̬����-40000 ~ -39500	HMI����������	-39500~ -39000
*	����ͼ��ʾ	-39000~ -38500	������ʾģ��	-38500~ -38000
*	I&C������ʾ	-38000~ -37500	��־ģ��	-37500~ -37000
*	���ģ��	-37000~ -36500	����ģ��	-36500~ -36000
*	����ģ��	-36000~ -35500	��ǰֵģ��	-35500~ -35000
*	����ģ��	-35000~ -34500	��ӡģ��	-34500~ -34000
*	Ȩ��ģ��	-34000~ -33500	����ģ��	-33500~ -33000
*	״̬�б�ģ��	-33000~ -32500	���߼��±�	-32500~ -32000
*	POPģ��	-32000~ -31500	���߰���	-31500~ -31000
*	����Ա����	-31000~ -30500	ϵͳ����ģ��	-30500~ -30000
*	�˵�ר�й���ģ��	-30000~ -29500	HMIԤ��	-29500~ -20000
*	ʵʱ���ں�	-20000~ -19500	��ʷ���ں�	-19500~ -19000
*	��ʷ�洢	-19000~ -18500	Ȩ�޷���	-18500~ -18000
*	��������	-18000~ -17500	�¼���¼	-17500~ -17000
*	�����ں�	-17000~ -16500	�������	-16500~ -16000
*	���Ʒ���	-16000~ -15500	IOSS	-15500~ -15000
*	���ݿ�Ԥ��	-10000~ -5000
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(�汾��)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         :									                         *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/10/14 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_UTILS_ERROR_H__
#define  GEOSYS_UTILS_ERROR_H__


typedef enum
{
	geoERR_COMMON_MIN = -5000,					// ���򳣼��Ĵ�����ʼ��
	geoERR_COMMON_NO_MEMORY,
	geoERR_COMMON_DATATYPE,
	geoERR_COMMON_DATACHANGE_FAIL,
	geoERR_COMMON_PARAMETER_INVALID,
	geoERR_COMMON_FILE_NOT_EXIST,
	geoERR_COMMON_MAX = -4000,					// ���򳣼��Ĵ��������
} geoErrorCode_COMMON;



typedef enum
{
	geoERR_DB_MIN = -10000,						// ���ݿ�ͨ����ʼ������
	geoERR_DB_VERSION_DIFFRENT,					// ���ݿ�汾��һ��

	geoERR_DB_MAX = -5000,						// ���ݿ�ͨ����������
} geoErrorCode_DB;


typedef enum
{
	geoERR_RTDB_MIN = -20000,						// ʵʱ����ʼ������
	geoERR_RTDB_COMMON = geoERR_RTDB_MIN,			// ʵʱ��ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
	///
	geoERR_TAG_MIN = -19900,						//��ǩ��صĴ�����
	geoERR_TAG_COMMON = geoERR_TAG_MIN,				//��ǩȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
	geoERR_TAG_DATAFILE_CREATE,						//��ǩ���������ļ�����ʧ��
	geoERR_TAG_DATAFILE_OPEN,						//��ǩ���������ļ���ʧ��
	geoERR_TAG_DATAFILE_SAVE,						//��ǩ���������ļ�����д��ʧ��
	geoERR_TAG_DATAFILE_NOTEXIST,
	geoERR_TAG_INFOFILE_CLOSE,
	geoERR_TAG_COUNT_OVERFLOW,
	geoERR_TAG_NOT_EXIST,
	geoERR_TAG_NAME_REDUPLICATE,
	geoERR_TAG_NAME_NOT_EXIST,
	geoERR_DEVICE_ID_REDUPLICATE,
	geoERR_TAG_NAMEHASH_FAILTURE,
	geoERR_SYSTEM_PROP_GET,
	geoERR_SYSTEM_PROP_SET,
	geoERR_DEVICE_ADD,
	geoERR_DEIVCE_PROP_GET,
	geoERR_DEIVCE_PROP_SET,
	geoERR_TAG_LACK_PROP,
	geoERR_TAG_WRONG_NAME,
	geoERR_SYSTEM_NOT_EXIST,
	geoERR_SYSTEM_ROOT_DELETE,
	geoERR_TAG_PROP_FILTER,
	geoERR_TAG_PROP_CANNOT_CHANGE,
	geoERR_TAG_PROP_NOT_CHANGED,
	geoERR_TAG_DATATYPE,
	geoERR_TAG_DATATYPE_HAS_SET,
	geoERR_TAG_UNITNO_OVERFLOW,
	geoERR_TAG_COMPRESS_OVERRUN,
	geoERR_TAG_CREATETIME_HAS_SET,
	geoERR_TAG_PROP_GET,
	geoERR_TAG_PROP_SET,
	geoERR_TAG_PROP_REDUPLICATE,
	geoERR_FAIL_IN_BATCH,
	geoERR_TAG_RETRIEVAL_TYPE,
	geoERR_TAG_RETRIEVAL,
	geoERR_TAG_CONFIGFILE_SAVE,
	geoERR_TAG_HAS_DELETED,
	geoERR_DB_ANAPROP_NOT_CHANGED,
	geoERR_TAGEXTEND_PROP_NOT_EXIST,
	geoERR_DB_ANAPROP_CANNOT_CHANGE,
	geoERR_DB_DIGPROP_CANNOT_CHANGE,
	geoERR_DB_RESTRAINPROP_NOT_CHANGED,
	geoERR_COMMON_STARTDB_FAIL,
	geoERR_TAG_FLAG,
	geoERR_TAG_CANNOT_COPY,
	geoERR_RTDB_PROXY_MIN = -19900,					//ʵʱ��ӿڴ�����صĴ�����

	geoERR_RTDB_MAX = -19500,						//ʵʱ����������
}geoErrorCode_RTDB;

typedef enum
{
	geoERR_HISD_MIN = -19500,						// ��ʷ����ʼ������
	geoERR_HISD_COMMON = geoERR_HISD_MIN,			// ��ʷ��ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													//
													geoERR_HISD_MAX = -19000,						//��ʷ����������

}geoErrorCode_HISD;

typedef enum
{
	geoERR_RECD_MIN = -19000,						// ��ʷ�洢��ʼ������
	geoERR_RECD_COMMON = geoERR_RECD_MIN,			// ��ʷ�洢ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
													geoERR_RECD_MAX = -18500,						//��ʷ�洢��������

}geoErrorCode_Record;
typedef enum
{
	geoERR_USERS_MIN = -18500,						// �û�Ȩ����ʼ������
	geoERR_USERS_COMMON = geoERR_USERS_MIN,			// �û�Ȩ��ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
													geoERR_USERS_MAX = -18000,						//�û�Ȩ����������

}geoErrorCode_UERS;
typedef enum
{
	geoERR_ALARM_MIN = -18000,						// ������ʼ������
	geoERR_ALARM_COMMON = geoERR_ALARM_MIN,			// ����ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
	geoERR_ALARM_MAX = -17500,						//������������

}geoErrorCode_Alarm;
typedef enum
{
	geoERR_LOG_MIN = -17500,						// �¼���ʼ������
	geoERR_LOG_COMMON = geoERR_LOG_MIN,				// �¼�ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
	geoERR_LOG_MAX = -17000,						//�¼���������

}geoErrorCode_LOG;
typedef enum
{
	geoERR_CALC_MIN = -17000,						// ������ʼ������
	geoERR_CALC_COMMON = geoERR_CALC_MIN,			// ����ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
	geoERR_CALC_MAX = -16500,						//������������

}geoErrorCode_CALC;
typedef enum
{
	geoERR_NET_MIN = -16500,						// ���������ʼ������
	geoERR_NET_COMMON = geoERR_NET_MIN,				// �������ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
	geoERR_VBUS_COMMON = -16400,						// VBUSȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����

																										///
	geoERR_TCP_CLIENT_NEED_RESET = -16322,
	geoERR_TCP_NEW_SEND_THREAD = -16321,
	geoERR_TCP_RECVN_FAILED = -16320,
	geoERR_TCP_SENDN_ERR = -16319,
	geoERR_TCP_CONNECT_FAILED = -16318,
	geoERR_TCP_SYS_STATUS_ERR = -16317,
	geoERR_TCP_MAPUNBIND = -16316,
	geoERR_TCP_MQ_SHUTDOWN = -16315,
	geoERR_TCP_GETQ_TIMEOUT = -16314,
	geoERR_TCP_CALLBACK_FUNCTION_SEND = -16313,
	geoERR_TCP_REGISTER_CALLBACK_FAIL = -16312,
	geoERR_TCP_NO_MQ = -16311,
	geoERR_TCP_CONNECTING = -16310,
	geoERR_TCP_API_CONNECT_NOT_FOUND = -16309,
	geoERR_TCP_CONNECT_NOT_FOUND = -16308,
	geoERR_TCP_MAX_CONNECTION = -16307,
	geoERR_TCP_NOHANDLE_FIND = -16306,
	geoERR_TCP_CONNECT_HASHMAP_ERROR = -16305,		//���ӵ�HASH_MAP�󶨡�������Ҵ���
	geoERR_TCP_CONNECTMGR_STOPED = -16304,				//
	geoERR_TCP_PARA_FILE_FAIL = -16303,				//RPC����˿ͻ�ID�����ļ�����
	geoERR_TCP_START_ERROR = -16302,
	geoERR_TCP_STATUS_BUSY = -16301,					//�ӿڷ���æ
	geoERR_TCP_COMMON = -16300,						// TCPȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����


	geoERR_NET_MAX = -16000,						//���������������

}geoErrorCode_NET;
typedef enum
{
	geoERR_HANG_MIN = -16000,						// ������ʼ������
	geoERR_HANG_COMMON = geoERR_HANG_MIN,			// ����ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
													geoERR_HANG_MAX = -15500,						//������������

}geoErrorCode_HANG;
typedef enum
{
	geoERR_IOSS_MIN = -15500,						// IOSS��ʼ������
	geoERR_IOSS_COMMON = geoERR_IOSS_MIN,			// IOSSȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
	///
	geoERR_IOSS_OBJECT_NOT_FOUND,
	geoERR_IOSS_DEVICE_NOT_STARTED,
	geoERR_IOSS_DRIVER_NOT_LOADED,

	geoERR_IOSS_DPU_COMMON = -15400,				//DPU����������
	geoERR_IOSS_SETTYPE_NOT_SUPPORTED,
	geoERR_IOSS_CURSOR_NOT_FOUND,
	geoERR_IOSS_SENDBUF_NOT_FOUND,
	geoERR_IOSS_DEVICE_NOT_CONNECTED,
	geoERR_IOSS_NO_VALID_HANDLE,
	geoERR_IOSS_SOCKET_SEND_FAIL,
	geoERR_IOSS_SEND_LENGTH_NOT_MATCH,

	geoERR_IOSS_MAX = -15000,						//IOSS��������

}geoErrorCode_IOSS;

typedef enum
{
	geoERR_SOUND_MIN = -15000,						// ������ʼ������
	geoERR_SOUND_COMMON = geoERR_SOUND_MIN,			// ����ȫ��ͨ�ô����룬������嶨��Ĵ��󶼿����ô˴�����
													///
	geoERR_SOUND_MAX = -14500,						//������������

}geoErrorCode_SOUND;
//
//typedef enum
//{
//	geoERR_DB_MIN = -20000 ,						// ʵʱ����������ʼ��ַ
//
//	geoERR_COMMON_BASE = -20000 ,				// ʵʱ��ͨ�ô���
//
//	geoERR_DB_CANNOT_START_BASE,                 //ʵʱ���������ģ���޷�����
//	geoERR_DB_CANNOT_START_DIGITAL,            //ʵʱ�⿪����ģ���޷�����
//	geoERR_DB_CANNOT_START_ANALOG,				//ʵʱ��ģ����ģ���޷�����
//	geoERR_DB_CANNOT_START_REAL,					//ʵʱ��ʵʱֵ�����޷�����
//	geoERR_DB_CANNOT_START_NOTIFY,				//ʵʱ��֪ͨģ���޷�����
//
//	geoERR_DB_CANNOT_STOP,                            //ʵʱ���޷�����ֹͣ
//	geoERR_DB_CANNOT_STOP_BASE,					//ʵʱ���������ģ��ֹͣ����
//	geoERR_DB_CANNOT_STOP_DIGITAL,              //ʵʱ�⿪����ģ��ֹͣ����
//	geoERR_DB_CANNOT_STOP_ANALOG,              //ʵʱ��ģ����ģ��ֹͣ����
//	geoERR_DB_CANNOT_STOP_REAL,                  //ʵʱ��ʵʱֵ����ֹͣ����
//	geoERR_DB_CANNOT_STOP_NOTIFY,			   //ʵʱ��֪ͨģ��ֹͣ����
//
//
//	geoERR_TAG_COUNT_OVERFLOW,					//ʵʱ���ǩ��Ŀ�������
//	geoERR_TAG_INFOFILE_NOTEXIST,				//ʵʱ��ϵͳ��Ϣ�ĵ�������
//	geoERR_TAG_DATAFILE_NOTEXIST,				//ʵʱ���ǩ��������Ϣ�ĵ�������
//
//
//
//	geoERR_TCP_CALLBACK_FUNCTION_SEND ,				// ����δʵ��
//	geoERR_COMMON_PARAMETER_INVALID ,					// ��������
//	geoERR_FAIL_IN_BATCH ,						// ���������в��ֲ����������ֳɹ�
//	geoERR_COMMON_NO_MEMORY ,							// ���㹻�ڴ�ռ�
//	geoERR_COMMON_NO_AUHTORITY,							// �޲���Ȩ��
//	geoERR_COMMON_STRING_TOO_LONG,						// �ַ���̫��
//	geoERR_COMMON_DATACHANGE_FAIL,                       // ����ת������
//	geoERR_TCP_NO_MQ,									// ͬ������û�з��������Ϣ����
//
//	geoERR_INTERFACE_BASE = -19900 ,						// �ӿڶ�̬����ش���
//
//	geoERR_TCP_REGISTER_CALLBACK_FAIL,				// �ص�����ע��ʧ��
//
//	geoERR_NET_BASE = -19800 ,					// ͨѶ��ش���
//
//	geoERR_TCP_GETQ_TIMEOUT,						// ������Ϣ���г�ʱ
//	geoERR_TCP_MQ_SHUTDOWN,						// ��Ϣ���йر�
//	geoERR_TCP_MAPUNBIND,						// ������Ϣ�����ʧ��
//	geoERR_TCP_SYS_STATUS_ERR,						// ��������״̬����ʧ��,û�ж�Ӧ��״̬��Ϣ����
//	geoERR_TCP_CONNECT_FAILED,					// ����ʧ��
//	geoERR_NET_SEndID_N_ERR,						// ����ʧ��
//	geoERR_TCP_RECVN_FAILED,                     // ����ʧ��
//	geoERR_NET_NEWTHREAD_SEndID_,					// �߳�ʧ��
//	geoERR_NET_NO_CONNECTED,						// û������
//	geoERR_NET_NOHANDLE_FIND,					// û�б����handle��Ϣ
//	geoERR_TCP_MAX_CONNECTION,					// ���������
//	geoERR_TCP_CLIENT_NEED_RESET,						// ���������Ѿ��������ͻ�����Ҫ����
//	geoERR_TCP_CONNECTING,					//��������������
//
//	geoERR_SCHUDULER_BASE = -19700 ,				// ��������ش���
//
//	geoERR_SCHUDULER_STATUS_ERROR,				// ���������ڴ���״̬
//	geoERR_SCHUDULER_STATUS_STOP,				// ����������ֹͣ״̬
//	geoERR_SCHUDULER_STATUS_BUSY,				// ������������æ״̬
//	geoERR_TCP_PARA_FILE_FAIL,				// ����ģ���ȡ�����ļ�ʧ��
//	geoERR_TCP_CONNECT_HASHMAP_ERROR, 		// ��ȡhash��ʧ��
//	geoERR_SCHEDULER_StartID__ERROR,				// ����ģ������ʧ��
//	geoERR_TCP_CONNECT_NOT_FOUND,  		// ����ģ����δ����������Ϣ
//	geoERR_TCP_API_CONNECT_NOT_FOUND,		// ����ģ����δ����Ӧ������
//	geoERR_TCP_CONNECT_NOT_FOUND,		// ����ģ����δ������������
//	geoERR_TCP_CONNECTMGR_STOPED,					// ���ӹ������Ѿ�ֹͣ
//
//	geoERR_TAGTYPEMANAGER_BASE = -19600 ,		// ���������ش���
//
//	geoERR_TAGTYPEMANAGER_CANNOT_StartID_,			// ������͹���ģ�鲻������
//	geoERR_TAGTYPEMANAGER_MANAGER_FILE_NOT_FOUND,	// ������͹����ļ�������
//	geoERR_TAGTYPEMAMAGER_MAMAGER_FILE_FAIL,		// ������͹����ļ�����
//	geoERR_TAGTYPEMANAGER_TOTAL_PROP_FILE_NOT_FOUND,	// ����������������ļ�������
//	geoERR_TAGTYPEMANAGER_TOTAL_PROP_FILE_FAIL,		// ����������������ļ�����
//
//	geoERR_TAGTYPE_BASE = -19500 ,				// ���������ش���
//
//	geoERR_TAGTYPE_CANNOT_SRART,					// ������Ͷ�̬�ⲻ������
//	geoERR_TAGTYPE_HAVE_StartID_ED,					// ������Ͷ�̬���Ѿ�����
//	geoERR_TAGTYPE_INFO_FILE_FAIL,				// ���������Ϣ�ļ�����
//	geoERR_TAGTYPE_PROP_FILE_FAIL,				// ������������ļ�����
//
//	geoERR_TAG_BASE = -19400 ,					// �����ش���
//
//	geoERR_TAG_HAS_PARENT,						//
//	geoERR_TAG_WRONG_NAME,						//��������ַ����Ϸ�
//	geoERR_TAG_ADD,								// 
//	geoERR_TAG_NAME,								// 
//	geoERR_TAGTREE_DEL,							// 
//	geoERR_TAG_GET_ID,							// 
//	geoERR_TAG_NAMEHASH_UNBIND,					// 
//	geoERR_TAG_GETLONGNAME,						// 
//	geoERR_TAG_NAMEHASH,							// 
//	geoERR_TAG_NAME_TOOLONG,						// 
//	geoERR_TAG_GETSHORTNAME,						// 
//	geoERR_TAGTREE_TRAVERSE,						// 
//	geoERR_TAG_ISANCESTOR,						// 
//	geoERR_TAG_INFOFILE,							// ���ܴ򿪲����Ϣ�ļ�
//	geoERR_TAG_DATAFILE,							// ���ܴ򿪲�������ļ�
//	geoERR_TAG_DELETE_ROOT,						// 
//	geoERR_TAG_HAVE_DELETED,						// ����Ѿ���ɾ��
//	geoERR_TAG_HAVE_CHILD,							//������ӽڵ㣬���ܱ�ɾ��
//	geoERR_TAG_PROP_REDUPLICATE,					// �����ظ�
//	geoERR_TAG_NAME_REDUPLICATE,					// ��������ظ�
//	geoERR_TAG_NAME_NOT_EXIST,					// �����������
//	geoERR_TAG_NAMEHASH_FAILURE,					// ����HASH�����
//	geoERR_TAG_NOT_NODE,							// ָ���ĵ㲻�ǽ������
//	geoERR_TAG_CANNOT_MOVE,						// ��㲻���ƶ�
//	geoERR_TAG_CANNOT_COPY,						// ��㲻�ܸ���
//	geoERR_TAG_NOT_EXIST,						// ��㲻����
//	geoERR_TAG_PROP_NOT_EXIST,					// ���Բ�����
//	geoERR_TAG_PROP_NOT_CHANGED,					// ���ֵδ����
//	geoERR_TAG_PROP_FILTER,						// ���ֵ������
//	geoERR_TAG_CANNOT_GETPROP,					// ���ܶ�����
//	geoERR_TAG_CANNOT_SETPROP,					// ����д����		
//	geoERR_TAG_LACK_PROP,						// ���Ӳ��ʱȱ�ٱ�Ҫ����
//
//	geoERR_DATATYPE,								// �������ʹ���
//	geoERR_DATATYPE_NOT_MATCH,
//	geoERR_TAG_NOT_SAVE_HIS,
//
//	geoERR_TAGNOTIFY_BASE = -19300,
//
//	geoERR_TAGNOTIFY_SUBCRIBE_FAILED,			// ע��ʧ��
//	geoERR_TAGNOTIFY_CANNOT_StartID_,				// ��㶩�ķ���ģ�鲻������
//	geoERR_TAGNOTIFY_SUBSCRIBE_MAP_ERROR,		// ��㶩�ķ���ģ��Ķ��ı����
//	geoERR_TAGNOTIFY_PBULISH_MAP_ERROR,			// ��㶩�ķ���ģ��ķ����߱����
//	geoERR_TAGNOTIFY_TAG_NOT_SUBSCRIBED,			// ���δ������
//	geoERR_TAGNOTIFY_CONNECT_NOT_FOUND,			// ���Ӳ�����
//
//	geoERR_REAL_BASE = -19200 ,					// ʵʱ��ش���
//
//	geoERR_REAL_CANNOT_READ,						// ���ܶ�ʵʱֵ
//	geoERR_REAL_CANNOT_WRITE,					// ����дʵʱֵ
//	geoERR_REAL_DATA_FILE_FAIL,					// ʵʱ���ݱ����ļ�����
//
//	geoERR_REALNOTIFY_BASE = -19100 ,			// ʵʱ��ش���
//
//	geoERR_REALNOTIFY_CANNOT_StartID_,				// ʵʱ���ķ���ģ�鲻������
//	geoERR_REALNOTIFY_SUBSCRIBE_MAP_ERROR,		// ʵʱ���ķ���ģ��Ķ��ı����
//	geoERR_REALNOTIFY_PUBLISH_MAP_ERROR,			// ʵʱ���ķ���ģ��ķ����߱����
//	geoERR_REALNOTIFY_TAG_NOTSUBSCRIBED,			// ʵʱδ������
//	geoERR_REALNOTIFY_CONNECT_NOT_FOUND,			// ���Ӳ�����
//
//	geoERR_AUTHORITY_BASE = -19000,				// Ȩ����ش���
//
//	geoERR_AUTHORITY_SECURITY_AREA_NOT_MATCH,	// ��ȫ����ƥ��
//	geoERR_AUTHORITY_WRITE_READONLY_PROPERTY,	// дֻ������
//	geoERR_TAG_BEYOND_MAX,						// �ܵ���������Ȩ
//	geoERR_LICENSE_UPDATA_ERROR,					// ����License��Ϣʧ�ܣ�ֹͣ���У����Ա�����
//	geoERR_LICENSE_TYPE_NO,						// û���κ����֤��Serverֹͣ���С������Ա�����
//	geoERR_LICENSE_DEMO_RUN_TIMEOUT,				// ��ʾ��Ϳ������ð����г�ʱ��Serverֹͣ���С������Ա�����
//	geoERR_LICENSE_NOT_PSPACE5,					// û�л�ȡpSpace 5.x�汾��License��Serverֹͣ���С������Ա�����
//	geoERR_LICENSE_NOT_SIMPLIFIED_CHINESE,		// û�л�ȡ�������İ汾��License��Serverֹͣ���С������Ա�����
//	geoERR_LICENSE_SITRAP_StartID_,					// SITrap�����������Ա�����
//	geoERR_LICENSE_CONNECT_BEYOND_USERAPP_MAX,	//�û��Ա�д��Ӧ�ó���ͻ�����������������ֵ�������ٽ������ӡ������Ա�����
//	geoERR_LICENSE_CONNECT_BEYOND_VIEW_MAX,		//View�ͻ�������������������ֵ�������ٽ������ӡ������Ա�����
//	geoERR_LICENSE_CONNECT_BEYOND_NETVIEW_MAX,	//NetView�ͻ�������������������ֵ�������ٽ������ӡ������Ա�����
//	geoERR_LICENSE_CONNECT_BEYOND_IO_MAX,		//NetView�ͻ�������������������ֵ�������ٽ������ӡ������Ա�����
//	geoERR_AUTHORITY_StartID__LICENSE_FAIL,			//����Licenseʧ�ܣ����Ա�����
//	geoERR_LICENSE_EVALUATION_TIMEOUT,			//���������г�ʱ�����Ա�����
//	geoERR_LICENSE_NO_EX_LICENSE,				//��չ���û��License��Ȩ�����Ա�����
//
//	geoERR_HIS_BASE = -18900 ,					// ��ʷ����ʷ�ļ���ش���
//
//	geoERR_HIS_NO_DISK_SPACE,					// ���㹻���̿ռ�
//	geoERR_HIS_CACHE_OPENED,					    // �������Ѿ���
//	geoERR_HIS_CACHE_CLOSED,						// ������û�д�
//	// ��ʷ�����ļ�ģ������
//	geoERR_HIS_NOT_INI_PATH,						// û�г�ʼ��·��
//	geoERR_HIS_MANAGER_FILE_OPENED,				// ��ʷ�����ļ��Ѿ���
//	geoERR_HIS_MANAGER_FILE_CLOSED,				// ��ʷ�����ļ�û�д�
//	geoERR_HIS_DATA_FILE_IN_LIST,				// �ļ�������ʷ�����ļ��б����ܱ�ע��
//	geoERR_HIS_MANAGER_FILE_VERSION,				// �����ļ��ļ��汾��Ч
//	geoERR_HIS_MANAGER_FILE_LABEL,				// �����ļ��ļ���ʶ��Ч
//	geoERR_HIS_MANAGER_FILE_INVALID,				// �����ļ��ļ���ʽ����
//	geoERR_HIS_UNREGIST_CURRENT_FILE,			// ����ע����ǰ�ļ�
//	geoERR_HIS_BACKUP_CURRENT_FILE,				// ���ܱ��ݵ�ǰ�ļ�
//	geoERR_HIS_DATA_FILE_NO_DATA,				// �����ļ������ݣ����ܱ���
//	geoERR_HIS_DATA_FILE_TIME_BEYOND,			// �ָ������ļ�ʱ���ļ�ʱ��ȵ�ǰʱ�仹�󣬳���
//	geoERR_HIS_DATA_FILE_TIME_OVERLAP,			// �ָ������ļ�ʱ���ļ�ʱ���������ļ��б��ص�
//	geoERR_HIS_DATA_FILE_COUNT_LESS,				// ���滻ģʽ�£���ʷ�����ļ�����������
//	geoERR_HIS_CAN_NOT_REGIST,					// ����ע��
//	// ��ʷ�����ļ�ģ������
//	geoERR_HIS_DATA_FILE_VERSION,				// �����ļ��ļ��汾��Ч
//	geoERR_HIS_DATA_FILE_LABEL,					// �����ļ��ļ���ʶ��Ч
//	geoERR_HIS_CRC,					 		    // У�����
//	geoERR_HIS_PAGE_FULL,				 		// ҳ����������
//	geoERR_HIS_DATA_PAGE_BEYOND_MIN,				// ����ʱ��ʱ�������ҳ����Сʱ�仹С
//	geoERR_HIS_EndID__OF_INDEX_PAGE,					
//	geoERR_HIS_FILE_NOT_IN_LIST,					// �ļ�ID������ʷ�����ļ��������ļ��б����Ҳ���
//	geoERR_HIS_SOME_DATA_NOT_SAVED,				// ����һ����������Ϊû�пռ䣬���ܲ���
//	geoERR_HIS_NEED_PACK_DATA,					// ����һ���ֿռ䣬��Ҫѹ����ʷ����
//	// �α�ģ������
//	geoERR_HIS_FIND_ERROR,						// ��ѯ�����쳣���
//	geoERR_HIS_BEYOND_MIN,					 	// �ȵ�һ�����ݵ�ʱ�仹С
//	geoERR_HIS_BEYOND_MAX, 			 			// �����һ�����ݵ�ʱ�仹��
//	geoERR_HIS_NO_EQUAL,							// ����ȷƥ��
//	geoERR_HIS_PAGE_EMPTY,						// ҳ��
//	geoERR_HIS_DATA_FILE_NOT_EXIST,				// ����ѯ������λ�����Ƴ�ϵͳ���ļ���
//	geoERR_HIS_NO_DATA_FILE,						// û����ʷ�����ļ�
//	geoERR_HIS_BEYOND_COMPRESS,					// ʱ���ѹ���ṹ������ʱ�仹Ҫ��
//	geoERR_HIS_EQUAL_COMPRESS,					// ������ѹ���ṹ������ʱ����ͬ
//	geoERR_HIS_PAGE_NOT_OPEN,					// ҳδ��
//	geoERR_HIS_NO_DATA,							// ������ļ����޶�Ӧ������
//	geoERR_HIS_NO_DATA_IN_INDEX_PAGE,			// ����ҳ������
//	geoERR_HIS_NO_DATA_IN_DATA_PAGE,				// ����ҳ������
//	// ��ģ������
//	geoERR_HIS_NEED_ADJUST_EndID_,					// ��Ҫ�������һ������
//	geoERR_HIS_NEED_FOUND_COMPRESS,				// ��Ҫ��ѹ���ṹ�в�ѯ����	
//	geoERR_HIS_BEYOND_MAX_READ_COUNT,			// ��ȡ���ݵĸ���������������	
//	//ɾ�����������
//	geoERR_HIS_DELTIME_LESSTHAN_MIN,   			//ɾ��������ָ��ʱ��αȸò����Сʱ�仹С
//	geoERR_HIS_DELTIME_MORETHAN_MAX,   			//ɾ��������ָ��ʱ��αȸò�����ʱ�仹��
//	geoERR_HIS_BEYOND_NUMBER,					// ͳ�Ƽ������Ӧ����100      
//
//	geoERR_EVENT_BASE = -18800 ,					// �¼���ش���
//
//	geoERR_EVENTNOTIFY_BASE = -18700 ,			// �¼�������ش���
//
//	geoERR_EVENTNOTIFY_CANNOT_StartID_,				// �¼����ķ���ģ�鲻������
//	geoERR_EVENTNOTIFY_SUBSCRIBE_MAP_ERROR,		// �¼����ķ���ģ��Ķ��ı����
//	geoERR_EVENTNOTIFY_PUBLISH_MAP_ERROR,		// �¼����ķ���ģ��ķ����߱����
//	geoERR_EVENTNOTIFY_CONNECT_NOT_FOUND,		// ���Ӳ�����
//
//	geoERR_USER_BASE = -18600 ,					// �û����û�����ش���
//
//	geoERR_USER_GROUPNAME_CONFLICT,              //�û�������ͻ
//	geoERR_USER_USERNAME_CONFLICT,               //�û�����ͻ
//	geoERR_USER_USER_IN_GROUP,                   //���û���������д��ڵ��û�
//	geoERR_USER_USER_NOT_IN_GROUP,               //���û���ɾ�������ڵ��û�
//	geoERR_USER_REIGISTE_USERNAME_FAIL,          //��ϵͳע���û�������
//	geoERR_USER_REIGISTE_GROUPNAME_FAIL,         //��ϵͳע���û���������
//	geoERR_USER_USERGROUP_NOT_EXIST,             //���������ڵ��û���
//	geoERR_USER_USER_NOT_EXIST,                  //���������ڵ��û�
//	geoERR_USER_USERNAME_OR_PASSWORD_NOTMATCH,   //�û��������벻ƥ��
//	geoERR_USER_READ_PSUSERCONF_FAIL,            //�û����û��������ļ�������
//	geoERR_USER_WRITE_PSUSERCONF_FAIL,           //�û����û��������ļ�д����
//	geoERR_USER_USERGROUP_ONLYREAD,              //�û���ֻ��
//	geoERR_USER_USER_ONLYREAD,                   //�û�ֻ��
//	geoERR_USER_LOST_VITAL_DATA ,               //ȱʧ�����ֶ�
//	geoERR_USER_NAME_LENGTH_WRONG,              //�û������û��������ȴ���
//	geoERR_USER_NAME_ILLEGAL,                   //�û������û������Ƿ�
//	geoERR_USER_CONF_DESTROY,                   //�û������ļ����ƻ�
//	geoERR_USER_CONF_BACKUP_FAIL,               //�û������ļ�����ʧ��
//
//	geoERR_IOSS_BASE = -18500 ,					// IOSS��ش����
//	geoERR_IOSS_OBJECT_NOT_FOUND,
//	geoERR_IOSS_DEVICE_NOT_STARTED,
//	geoERR_IOSS_DRIVER_NOT_LOADED,
//
//	geoERR_MAX = -10000 , 						// �ӿڷ����������
//} geoErrorCodeEnum;


#endif
