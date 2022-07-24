/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRTDBMacro.h                                            *
*  @brief    实时数据库相关的宏                                              *
*																			 *
*
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : 必须在支持C++11环境下编译通过                            *
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

//配置文件目录 "工作目录\config\rtdb\"
#define TAG_DEFAULT_CONFIG_DIR     \
	DIRECTORY_SEPARATOR_STR_A \
	GEO_TEXT("config")	\
	DIRECTORY_SEPARATOR_STR_A \
	GEO_TEXT("rtdb")	\
	DIRECTORY_SEPARATOR_STR_A

#define TAG_NAME_SIZE   32
#define TAG_DESC_SIZE   128    //64汉字，128英文
#define TAG_DEVICE_NAME_SIZE   16
#define TAG_DEVICE_ADDR_SIZE   128


///标签最大容量20W
#define TAG_MAX_CAPACITY   1000*100*2 
///默认的标签容量4W
#define TAG_DEFUALT_CAPACITY   1000*10*4

///作者字符长度
#define TAG_AUTHOR_SIZE   32
///公司字符长度
#define TAG_OEM_SIZE	64

/// 无效的标签ID
#define	geoTagId_Unused	0xFFFFFFFF				
// 根标签ID
#define	geoTagId_Root	0x00000000				
#define geoQueryLevel_ALL	0xFFFF				// 查询结点下的所有内容，用于geoQueryArea


#include <pshpack1.h>

/// 标签ID列表
typedef struct __tag_TagIdList
{
	geoUInt32			TagCount;			// 属性个数
	geoUInt32*			TagIdList;		// 属性ID列表
} geoTagIdList;

/// 属性ID列表
typedef struct __tag_PropIdList
{
	geoUInt16			PropCount;			// 属性个数
	geoUInt16*			PropIdList;		// 属性ID列表
} geoPropIdList;


///	单个属性的值
typedef struct __tag_PropValue
{
	geoUInt16			PropId;			// 属性ID
	geoVariant			Value;			// 属性值
} geoPropValue;

/// 属性值链表
typedef struct __tag_PropValueList
{
	geoUInt16			PropCount;			// 属性个数
	geoPropValue*		PropValueList;		// 属性值列表
} geoPropValueList;


/// 属性列表
typedef struct
{
	geoUInt16		PropCount;
	geoVariant**		Value;
	geoAPIStatus**	APIStatus;
}geoTagPropList;


///	查询范围
typedef struct __tag_QueryArea
{
	geoUInt32			RootTagId;			// 查询的起始结点（包括它本身）
	geoUInt16			QueryLevel;			// 查询的树深度，0查本身，geoQueryLevel_ALL查所有，1、2、3...查相关深度
	geoBool				QuerySelf;			// 当查询的深度超过0时，是否查起始结点本身
} geoQueryArea;

struct iter_info {
	geoUInt32 curr_tag;
	geoUInt16 level;					// 遍历深度
	geoUInt16 curr_level;
	geoUInt32 iter_root;
	geoUInt32 iter_last;
};


typedef enum  __tag_TagTypeEnum
{
	TagType_Invalid = 0,
	//普通点
	TagType_Comm ,
	//普通开关点
	TagType_Digit,
	//普通模拟点
	TagType_Ana,
	//带报警的开关点
	TagType_ADigit,
	//带报警的模拟点
	TagType_AAna,
	//已经是报警点的开关点，给报警服务用
	TagType_Alarm,
	//计算点
	TagType_Calc,
	//挂牌点
	TagType_TAG ,
	//标签类型最大扩展支持64种
	TagType_Max = 64,
}geoTagTypeEnum;

///常规属性ID定义
typedef enum __tag_TagPropEnum
{
	geoProp_TagBase_Min = 0,

	//基本属性
	geoProp_Id = geoProp_TagBase_Min,
	geoProp_TagType,	// 1 标签类型
	geoProp_Name,		// 2 标签名
	geoProp_Description,// 3 标签描述
	geoProp_DataType,	// 4 数据类型
	geoProp_Unit,		// 5 单位
	geoProp_InitValue,		// 6 初始值
	geoProp_ParentId,   // 7 父节点
	geoProp_FirstChildId,// 8 子节点
	geoProp_PrevId,			// 9 前节点
	geoProp_NextId,			// 10 后节点
	geoProp_LastModifyTime,	// 11 最后修改时间
	geoProp_CreateTime,		// 12 创建时间
	geoProp_TagBase_Max,

	//历史相关属性
	geoProp_His_Min = 30,
	geoProp_His_IsSave = geoProp_His_Min,	//是否保存开关
	geoProp_His_MaxSaveTime,		//最大保存时间
	geoProp_His_CompressRate,		//压缩率
	geoProp_His_CompressMode,		//压缩模式
	geoProp_His_Max,

	//IOSS属性
	geoProp_IOSS_Min,
	geoProp_IOSS_DeviceName = geoProp_IOSS_Min,
	geoProp_IOSS_Addr,
	geoProp_IOSS_IsPeroidUpdate,
	geoProp_IOSS_Peroid,
	geoProp_IOSS_Max,
	// 扩展属性最小值
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

	////模拟点
	//geoProp_EnableLLAlarm,		   ///低低限
	//geoProp_EnableLOAlarm,		   ///低限
	//geoProp_EnableHIAlarm,		   ///高限
	//geoProp_EnableHHAlarm,		   ///高高限

	//geoProp_EnableRateAlarm,		   ///变化率报警限值
	//geoProp_EnableDevAlarm,		   ///偏差报警限值


	//geoProp_LowLowAlarmNeedRespond,	   ///低低限是否需要应答
	//geoProp_LowAlarmNeedRespond,		   ///低限是否需要应答
	//geoProp_HighAlarmNeedRespond,		   ///高限是否需要应答
	//geoProp_HighHighAlarmNeedRespond,	   ///高高限是否需要应答
	//geoProp_RateAlarmNeedRespond,		   ///变化率报警是否需要应答
	//geoProp_DevAlarmNeedRespond,	           ///偏差报警是否需要应答


	//geoProp_LowLowAlarm,		   ///低低限
	//geoProp_LowAlarm,		   ///低限
	//geoProp_HighAlarm,		   ///高限
	//geoProp_HighHighAlarm,		   ///高高限
	//geoProp_Rate,		   ///变化率报警限值
	//geoProp_RatePeriod,     ///变化率周期
	//geoProp_Dev,		   ///偏差报警限值
	//geoProp_SP,           ///目标值
	//geoProp_DeadBand,     ///报警死区

	//geoProp_LowLowAlarmPriority,	   ///低低限报警优先级
	//geoProp_LowAlarmPriority,		   ///低限报警优先级
	//geoProp_HighAlarmPriority,		   ///高限报警优先级
	//geoProp_HighHighAlarmPriority,		   ///高高限报警优先级
	//geoProp_RateAlarmPriority,		   ///变化率报警优先级
	//geoProp_DevAlarmPriority,	          ///偏差报警优先级

	//geoPropFlag_Max_Analog,

	geoPropFlag_Extend_Max,
} psTagPropEnum;




//标签的内部状态标识
typedef struct __tag_TagBaseFlag
{
	geoUInt8		Deleted: 1;				/// 是否已删除标志
	geoUInt8		Changed: 1;				/// 是否已修改标志
	geoUInt8		IsNode : 1;				/// 是否是结点
	geoUInt8		Unused : 5;				/// 未使用
}geoTagBaseFlag;


typedef struct __tag_geoTagBase
{
	//基本属性
	geoUInt8	TagType;					/// 点类型
	geoChar		Name[TAG_NAME_SIZE];				/// 点名，必须数字、字母开头
	geoChar		Description[TAG_DESC_SIZE];			/// 点描述
	geoUInt8     DataType;					///数据类型
	geoUInt8	 Unit;						///单位
	geoDouble	InitValue;					///初始值
	//geoUInt64	SecurityArea;				/// 点的安全区，64位掩码方式，扩展属性来
	//内置属性
	geoUInt32	Id;							/// 标签ID号
	geoUInt32	ExtendId;					/// 点在扩充属性数组中的编号
	geoTagBaseFlag Flag;					/// 状态标志
	geoUInt32	ParentId;					/// 父结点
	geoUInt32	NextId;						/// 同一级后一结点
	geoUInt32	PrevId;						/// 同一级前一结点
	geoUInt32	FirstChildId;				/// 子结点
	geoTimeStamp		CreateTime;					/// 建立时间
	geoTimeStamp		LastModifyTime;				/// 最后修改时间
	//历史属性
	geoBool		IsSave;								///是否进历史库
	geoUInt8	CompressModel;					///压缩模式
	geoUInt8	CompressRate;					///压缩率
	geoUInt32	SaveMaxPeroid;					///存储最大周期，也就是周期存储
	//IO属性
	geoChar	    IODeviceName[TAG_DEVICE_NAME_SIZE];		/// IO设备名
	geoChar		IODeviceAddr[TAG_DEVICE_ADDR_SIZE];		/// IO设备地址
	geoBool		IsPeriodUpdate;							///是否周期上传
	geoUInt32	Peroid;									///周期刷新时间
	RTK_LIST_ENTRY	DeviceLink;							// 设备驱动链表，内部使用
	RTK_LIST_ENTRY	RefreshLink;						// 刷新链表，内部使用
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