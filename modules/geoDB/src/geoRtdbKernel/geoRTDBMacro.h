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
#define TAG_DESC_SIZE   128    //64���֣�128Ӣ��
#define TAG_DEVICE_NAME_SIZE   16
#define TAG_DEVICE_ADDR_SIZE   128


///��ǩ�������20W
#define TAG_MAX_CAPACITY   1000*100*2 
///Ĭ�ϵı�ǩ����4W
#define TAG_DEFUALT_CAPACITY   1000*10*4

///�����ַ�����
#define TAG_AUTHOR_SIZE   32
///��˾�ַ�����
#define TAG_OEM_SIZE	64

/// ��Ч�ı�ǩID
#define	geoTagId_Unused	0xFFFFFFFF				
// ����ǩID
#define	geoTagId_Root	0x00000000				
#define geoQueryLevel_ALL	0xFFFF				// ��ѯ����µ��������ݣ�����geoQueryArea


#include <pshpack1.h>

/// ��ǩID�б�
typedef struct __tag_TagIdList
{
	geoUInt32			TagCount;			// ���Ը���
	geoUInt32*			TagIdList;		// ����ID�б�
} geoTagIdList;

/// ����ID�б�
typedef struct __tag_PropIdList
{
	geoUInt16			PropCount;			// ���Ը���
	geoUInt16*			PropIdList;		// ����ID�б�
} geoPropIdList;


///	�������Ե�ֵ
typedef struct __tag_PropValue
{
	geoUInt16			PropId;			// ����ID
	geoVariant			Value;			// ����ֵ
} geoPropValue;

/// ����ֵ����
typedef struct __tag_PropValueList
{
	geoUInt16			PropCount;			// ���Ը���
	geoPropValue*		PropValueList;		// ����ֵ�б�
} geoPropValueList;


/// �����б�
typedef struct
{
	geoUInt16		PropCount;
	geoVariant**		Value;
	geoAPIStatus**	APIStatus;
}geoTagPropList;


///	��ѯ��Χ
typedef struct __tag_QueryArea
{
	geoUInt32			RootTagId;			// ��ѯ����ʼ��㣨����������
	geoUInt16			QueryLevel;			// ��ѯ������ȣ�0�鱾��geoQueryLevel_ALL�����У�1��2��3...��������
	geoBool				QuerySelf;			// ����ѯ����ȳ���0ʱ���Ƿ����ʼ��㱾��
} geoQueryArea;

struct iter_info {
	geoUInt32 curr_tag;
	geoUInt16 level;					// �������
	geoUInt16 curr_level;
	geoUInt32 iter_root;
	geoUInt32 iter_last;
};


typedef enum  __tag_TagTypeEnum
{
	TagType_Invalid = 0,
	//��ͨ��
	TagType_Comm ,
	//��ͨ���ص�
	TagType_Digit,
	//��ͨģ���
	TagType_Ana,
	//�������Ŀ��ص�
	TagType_ADigit,
	//��������ģ���
	TagType_AAna,
	//�Ѿ��Ǳ�����Ŀ��ص㣬������������
	TagType_Alarm,
	//�����
	TagType_Calc,
	//���Ƶ�
	TagType_TAG ,
	//��ǩ���������չ֧��64��
	TagType_Max = 64,
}geoTagTypeEnum;

///��������ID����
typedef enum __tag_TagPropEnum
{
	geoProp_TagBase_Min = 0,

	//��������
	geoProp_Id = geoProp_TagBase_Min,
	geoProp_TagType,	// 1 ��ǩ����
	geoProp_Name,		// 2 ��ǩ��
	geoProp_Description,// 3 ��ǩ����
	geoProp_DataType,	// 4 ��������
	geoProp_Unit,		// 5 ��λ
	geoProp_InitValue,		// 6 ��ʼֵ
	geoProp_ParentId,   // 7 ���ڵ�
	geoProp_FirstChildId,// 8 �ӽڵ�
	geoProp_PrevId,			// 9 ǰ�ڵ�
	geoProp_NextId,			// 10 ��ڵ�
	geoProp_LastModifyTime,	// 11 ����޸�ʱ��
	geoProp_CreateTime,		// 12 ����ʱ��
	geoProp_TagBase_Max,

	//��ʷ�������
	geoProp_His_Min = 30,
	geoProp_His_IsSave = geoProp_His_Min,	//�Ƿ񱣴濪��
	geoProp_His_MaxSaveTime,		//��󱣴�ʱ��
	geoProp_His_CompressRate,		//ѹ����
	geoProp_His_CompressMode,		//ѹ��ģʽ
	geoProp_His_Max,

	//IOSS����
	geoProp_IOSS_Min,
	geoProp_IOSS_DeviceName = geoProp_IOSS_Min,
	geoProp_IOSS_Addr,
	geoProp_IOSS_IsPeroidUpdate,
	geoProp_IOSS_Peroid,
	geoProp_IOSS_Max,
	// ��չ������Сֵ
	geoPropFlag_Extend_Min = 37,
	//geoProp_PV = geoPropFlag_Extend_Min,
	//geoProp_LastPV,
	//geoProp_PV_Time,
	//geoProp_PV_Quality,
	//geoProp_LastPV_Time,
	//geoProp_LastPV_Quality,
	//geoProp_OffMessage,
	//geoProp_OnMessage,
	//geoProp_InitValue,
	//geoProp_SaveAsInitValue,
	//geoProp_EnableAlarm,
	//geoProp_EnableValueAlarm,
	//geoProp_NormalValue,
	//geoProp_ValueAlarmNeedRespond,
	//geoProp_EnableQualityAlarm,
	//geoProp_QualityAlarmNeedRespond,
	//geoProp_DelayAlarm,
	//geoProp_ValueAlarmClass,
	//geoProp_QualityAlarmClass,

	//geoPropFlag_Max_Digital,

	////ģ���
	//geoProp_EnableLLAlarm,		   ///�͵���
	//geoProp_EnableLOAlarm,		   ///����
	//geoProp_EnableHIAlarm,		   ///����
	//geoProp_EnableHHAlarm,		   ///�߸���

	//geoProp_EnableRateAlarm,		   ///�仯�ʱ�����ֵ
	//geoProp_EnableDevAlarm,		   ///ƫ�����ֵ


	//geoProp_LowLowAlarmNeedRespond,	   ///�͵����Ƿ���ҪӦ��
	//geoProp_LowAlarmNeedRespond,		   ///�����Ƿ���ҪӦ��
	//geoProp_HighAlarmNeedRespond,		   ///�����Ƿ���ҪӦ��
	//geoProp_HighHighAlarmNeedRespond,	   ///�߸����Ƿ���ҪӦ��
	//geoProp_RateAlarmNeedRespond,		   ///�仯�ʱ����Ƿ���ҪӦ��
	//geoProp_DevAlarmNeedRespond,	           ///ƫ����Ƿ���ҪӦ��


	//geoProp_LowLowAlarm,		   ///�͵���
	//geoProp_LowAlarm,		   ///����
	//geoProp_HighAlarm,		   ///����
	//geoProp_HighHighAlarm,		   ///�߸���
	//geoProp_Rate,		   ///�仯�ʱ�����ֵ
	//geoProp_RatePeriod,     ///�仯������
	//geoProp_Dev,		   ///ƫ�����ֵ
	//geoProp_SP,           ///Ŀ��ֵ
	//geoProp_DeadBand,     ///��������

	//geoProp_LowLowAlarmPriority,	   ///�͵��ޱ������ȼ�
	//geoProp_LowAlarmPriority,		   ///���ޱ������ȼ�
	//geoProp_HighAlarmPriority,		   ///���ޱ������ȼ�
	//geoProp_HighHighAlarmPriority,		   ///�߸��ޱ������ȼ�
	//geoProp_RateAlarmPriority,		   ///�仯�ʱ������ȼ�
	//geoProp_DevAlarmPriority,	          ///ƫ������ȼ�

	//geoPropFlag_Max_Analog,

	geoPropFlag_Extend_Max,
} psTagPropEnum;




//��ǩ���ڲ�״̬��ʶ
typedef struct __tag_TagBaseFlag
{
	geoUInt8		Deleted: 1;				/// �Ƿ���ɾ����־
	geoUInt8		Changed: 1;				/// �Ƿ����޸ı�־
	geoUInt8		IsNode : 1;				/// �Ƿ��ǽ��
	geoUInt8		Unused : 5;				/// δʹ��
}geoTagBaseFlag;


typedef struct __tag_geoTagBase
{
	//��������
	geoUInt8	TagType;					/// ������
	geoChar		Name[TAG_NAME_SIZE];				/// �������������֡���ĸ��ͷ
	geoChar		Description[TAG_DESC_SIZE];			/// ������
	geoUInt8     DataType;					///��������
	geoUInt8	 Unit;						///��λ
	geoDouble	InitValue;					///��ʼֵ
	//geoUInt64	SecurityArea;				/// ��İ�ȫ����64λ���뷽ʽ����չ������
	//��������
	geoUInt32	Id;							/// ��ǩID��
	geoUInt32	ExtendId;					/// �����������������еı��
	geoTagBaseFlag Flag;					/// ״̬��־
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
	geoUInt32	Peroid;									///����ˢ��ʱ��
	RTK_LIST_ENTRY	DeviceLink;							// �豸���������ڲ�ʹ��
	RTK_LIST_ENTRY	RefreshLink;						// ˢ�������ڲ�ʹ��
}geoTagBase;


#include <poppack.h>





enum
{
	Iter_SameLayer = 0,
	//Iter_NextLayer=1,
	Iter_Done = 2,
};

//
//
//#define MAX_HANDLERS 8
//
//extern PRTDB_DISPATCH_TABLE	g_Handlers[MAX_HANDLERS];
//extern __int				g_iHandlers;
//
//#define FIRE_EVENT(__field__, __parameters__)\
//do{\
//	for(int i=0; i<g_iHandlers; i++){\
//		if(g_Handlers[i] -> __field__){\
//			g_Handlers[i] -> __field__ __parameters__;\
//		}\
//	}\
//}while(0)


#endif