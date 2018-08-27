/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoTagValue.h													 *
*  @brief    实时库实时值处理												*
*																			 *
*  名字与ID的关联层
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
#ifndef  GEOSYS_RTDB_TAG_VALUE_H__
#define  GEOSYS_RTDB_TAG_VALUE_H__

#include"geoBasicType.h"
#include"geoRTDBMacro.h"

class GeoTagValue
{
public:
	GeoTagValue();
	GeoTagValue(geoChar * strPathName,
		geoUInt32 nCapacity = TAG_DEFUALT_CAPACITY);
	~GeoTagValue();

};



#endif

