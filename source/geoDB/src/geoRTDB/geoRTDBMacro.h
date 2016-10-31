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


#define geoQueryLevel_ALL	0xFFFF				// 查询结点下的所有内容，用于geoQueryArea


#define TAG_NAME_SIZE   32
#define TAG_DESC_SIZE   64
#define TAG_DEVICE_NAME_SIZE   16
#define TAG_DEVICE_ADDR_SIZE   128

#include <pshpack1.h>

///  数据记录定义
typedef struct
{
	geoTime				Time;				// 时间戳
	geoVariant			Value;				// 值
	geoUInt8			Quality;			// 质量戳
} geoData;

///	 数据记录列表
typedef struct
{
	geoUInt32			DataCount;			// 数据记录个数
	geoData*			DataList;			// 数据记录列表
} geoDataList;

///	查询范围
typedef struct
{
	geoUInt32			RootTagId;			// 查询的起始结点（包括它本身）
	geoUInt16			QueryLevel;			// 查询的树深度，0查本身，geoQueryLevel_ALL查所有，1、2、3...查相关深度
	geoBool				QuerySelf;			// 当查询的深度超过0时，是否查起始结点本身
} geoQueryArea;
struct iter_info {
	geoUInt32 curr_tag;
	geoUInt16 level;			// 遍历深度
	geoUInt16 curr_level;
	geoUInt32 iter_root;
	geoUInt32 iter_last;
};
typedef struct
{
	geoUInt8		Deleted : 1;			/// 是否已删除标志
	//	psUInt8		Dirty:1;				/// 是否已脏标志
	geoUInt8		IsNode : 1;				/// 是否是结点
	geoUInt8		Unused : 6;				/// 未使用
}geoTagBaseFlag;
typedef struct
{
	//基本属性

	geoUInt16	TagType;					/// 点类型
	geoChar		Name[TAG_NAME_SIZE];					/// 点短名
	geoChar		Description[TAG_DESC_SIZE];			/// 点描述
	geoUInt8     DataType;					///数据类型
	geoUInt8	 Unit;						///单位
	geoVariant	InitValue;					///初始值
	geoUInt64	SecurityArea;				/// 点的安全区
	//内置属性
	geoUInt32	Id;								/// 结点ID号
	geoUInt32	ExtendId;					/// 点在扩充属性数组中的编号
	geoTagBaseFlag Flag;						/// 状态标志
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
	geoBool		IsControl;								///是否下行
	geoUInt32	Peroid;									///周期刷新时间
	RTK_LIST_ENTRY	DeviceLink;							// 设备驱动链表，内部使用
	RTK_LIST_ENTRY	RefreshLink;						// 刷新链表，内部使用
}geoTagRecordBase;


#include <poppack.h>

#define	geoTagId_Unused	0xFFFFFFFF				// 无效的测点ID
#define	geoTagId_Root	0x00000000				// 根测点ID



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