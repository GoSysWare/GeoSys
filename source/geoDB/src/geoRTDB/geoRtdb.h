/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRtdb.h                                            *
*  @brief    实时数据库的数据定义，API接口函数                                             *
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

#ifndef  GEOSYS_RTDB_H__
#define  GEOSYS_RTDB_H__

#include"geoBasicType.h"








#include <pshpack4.h>
typedef enum __tag_RTDB_EVENT {
	EV_AddTag = 0,
	EV_DropTag = 1,
	EV_ModifyTag = 2,
	EV_AddNode = 3,
	EV_DropNode = 4,
	EV_Max= 4,
}GEO_Rtdb_Event;

// RTDB PNP hooking support
typedef struct __tag_RTDB_DISPATCH_TABLE {
	void(*OnAddTag)(PRTK_TAG pTag);
	void(*OnDropTag)(PRTK_TAG pTag);
	void(*OnModifyTag)(PRTK_TAG);
	void(*OnAddNode)(PRTK_NODE pnode);
	void(*OnDropNode)(PRTK_NODE pnode);
}RTDB_DISPATCH_TABLE, *PRTDB_DISPATCH_TABLE;
#include <poppack.h>

RTDB_API __bool PMC_API hook_rtdb_events(
	PRTDB_DISPATCH_TABLE table
);
RTDB_API __bool PMC_API unhook_rtdb_events(
	PRTDB_DISPATCH_TABLE table
);
RTDB_API void PMC_API fire_rtdb_event(
	RTDB_EVENT id,
	void * p1 DEFAULT_PARAM(0),
	void * p2 DEFAULT_PARAM(0)
);



#endif