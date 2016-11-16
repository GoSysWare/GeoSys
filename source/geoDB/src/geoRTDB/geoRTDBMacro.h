/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRTDBMacro.h                                            *
*  @brief    ʵʱ���ݿ���صĺ�                                              *
*																			 *
*
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(�汾��)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : ������֧��C++11�����±���ͨ��                            *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/10/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_RTDB_MACRO_H__
#define  GEOSYS_RTDB_MACRO_H__

#include"geoListEntry.h"
#include"geoBasicType.h"




#define TAG_DATA_FILENAME GEO_TEXT("rtdb_tag.gf")
#define TAG_INFO_FILENAME GEO_TEXT("rtdbi_tag.gf")

#define TAG_INFO_DEFAULT_AUTHOR  GEOSYS_AUTHOR
#define TAG_INFO_DEFAULT_OEM	 GEOSYS_OEM

//�����ļ�Ŀ¼ "����Ŀ¼\config\rtdb\"
#define TAG_DEFAULT_CONFIG_DIR     \
	DIRECTORY_SEPARATOR_STR_A \
	GEO_TEXT("config")	\
	DIRECTORY_SEPARATOR_STR_A \
	GEO_TEXT("rtdb")	\
	DIRECTORY_SEPARATOR_STR_A

#define TAG_NAME_SIZE   32
#define TAG_DESC_SIZE   64
#define TAG_DEVICE_NAME_SIZE   16
#define TAG_DEVICE_ADDR_SIZE   128


///��ǩ�������20W
#define TAG_MAX_CAPACITY   1000*100*2 
///Ĭ�ϵı�ǩ����4W
#define TAG_DEFUALT_CAPACITY   1000*10*4

#define TAG_AUTHOR_SIZE   32
#define TAG_OEM_SIZE	64

#include <pshpack1.h>

typedef struct __tag_RtdbInfo
{
	geoUInt32 Version;		//�汾
	geoUInt32 Capacity;		//����
	geoUInt32 ValidCount;	//��Ч����
	geoUInt32 CurrentIndex;
	geoChar   Author[TAG_AUTHOR_SIZE];	//����
	geoChar	  OEM[TAG_OEM_SIZE];		//��λ
	geoUInt32  Check;					//У��
} geoRtdbInfo;


///	��ѯ��Χ
typedef struct __tag_QueryArea
{
	geoUInt32			RootTagId;			// ��ѯ����ʼ��㣨����������
	geoUInt16			QueryLevel;			// ��ѯ������ȣ�0�鱾��geoQueryLevel_ALL�����У�1��2��3...��������
	geoBool				QuerySelf;			// ����ѯ����ȳ���0ʱ���Ƿ����ʼ��㱾��
} geoQueryArea;
struct iter_info {
	geoUInt32 curr_tag;
	geoUInt16 level;			// �������
	geoUInt16 curr_level;
	geoUInt32 iter_root;
	geoUInt32 iter_last;
};
typedef struct
{
	geoUInt8		Deleted : 1;			/// �Ƿ���ɾ����־
	//	psUInt8		Dirty:1;				/// �Ƿ������־
	geoUInt8		IsNode : 1;				/// �Ƿ��ǽ��
	geoUInt8		Unused : 6;				/// δʹ��
}geoTagBaseFlag;

#define geoQueryLevel_ALL	0xFFFF				// ��ѯ����µ��������ݣ�����geoQueryArea
typedef struct __tag_geoTagBase
{
	//��������

	geoUInt16	TagType;					/// ������
	geoChar		Name[TAG_NAME_SIZE];					/// �����
	geoChar		Description[TAG_DESC_SIZE];			/// ������
	geoUInt8     DataType;					///��������
	geoUInt8	 Unit;						///��λ
	geoVariant	InitValue;					///��ʼֵ
	geoUInt64	SecurityArea;				/// ��İ�ȫ��
	//��������
	geoUInt8	NodeId;						///�ڵ�ID��
	geoUInt32	Id;							/// ��ǩID��
	geoUInt32	ExtendId;					/// �����������������еı��
	geoTagBaseFlag Flag;						/// ״̬��־
	geoUInt32	ParentId;					/// �����
	geoUInt32	NextId;						/// ͬһ����һ���
	geoUInt32	PrevId;						/// ͬһ��ǰһ���
	geoUInt32	FirstChildId;				/// �ӽ��
	geoTimeStamp		CreateTime;					/// ����ʱ��
	geoTimeStamp		LastModifyTime;				/// ����޸�ʱ��
	//��ʷ����
	geoBool		IsSave;								///�Ƿ����ʷ��
	geoUInt8	CompressModel;					///ѹ��ģʽ
	geoUInt8	CompressRate;					///ѹ����
	geoUInt32	SaveMaxPeroid;					///�洢������ڣ�Ҳ�������ڴ洢
	//IO����
	geoChar	    IODeviceName[TAG_DEVICE_NAME_SIZE];		/// IO�豸��
	geoChar		IODeviceAddr[TAG_DEVICE_ADDR_SIZE];		/// IO�豸��ַ
	geoBool		IsPeriodUpdate;							///�Ƿ������ϴ�
	geoBool		IsControl;								///�Ƿ�����
	geoUInt32	Peroid;									///����ˢ��ʱ��
	RTK_LIST_ENTRY	DeviceLink;							// �豸���������ڲ�ʹ��
	RTK_LIST_ENTRY	RefreshLink;						// ˢ�������ڲ�ʹ��
}geoTagBase;


#include <poppack.h>

#define	geoTagId_Unused	0xFFFFFFFF				// ��Ч�Ĳ��ID
#define	geoTagId_Root	0x00000000				// �����ID



typedef enum
{
	Iter_SameLayer = 0,
	//Iter_NextLayer=1,
	Iter_Done = 2,
};



#define MAX_HANDLERS 8

extern PRTDB_DISPATCH_TABLE	g_Handlers[MAX_HANDLERS];
extern __int				g_iHandlers;

#define FIRE_EVENT(__field__, __parameters__)\
do{\
	for(int i=0; i<g_iHandlers; i++){\
		if(g_Handlers[i] -> __field__){\
			g_Handlers[i] -> __field__ __parameters__;\
		}\
	}\
}while(0)


#endif