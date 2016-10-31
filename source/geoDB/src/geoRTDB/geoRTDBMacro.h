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


#define geoQueryLevel_ALL	0xFFFF				// ��ѯ����µ��������ݣ�����geoQueryArea


#define TAG_NAME_SIZE   32
#define TAG_DESC_SIZE   64
#define TAG_DEVICE_NAME_SIZE   16
#define TAG_DEVICE_ADDR_SIZE   128

#include <pshpack1.h>

///  ���ݼ�¼����
typedef struct
{
	geoTime				Time;				// ʱ���
	geoVariant			Value;				// ֵ
	geoUInt8			Quality;			// ������
} geoData;

///	 ���ݼ�¼�б�
typedef struct
{
	geoUInt32			DataCount;			// ���ݼ�¼����
	geoData*			DataList;			// ���ݼ�¼�б�
} geoDataList;

///	��ѯ��Χ
typedef struct
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
typedef struct
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
	geoUInt32	Id;								/// ���ID��
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
}geoTagRecordBase;


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