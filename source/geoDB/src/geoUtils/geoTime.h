/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoEvent.h                                                     *
*  @brief    线程处理类                                                      *
*																			 *
*  其中包含了事件封装
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
*  2016/08/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef  GEOSYS_UTILS_TIME_H__
#define  GEOSYS_UTILS_TIME_H__


#include <chrono>
#include "geoBasicType.h"
#include "geoTime.h"

using namespace std::chrono;


//时间戳零点
 extern   const  geoTimeStamp  geoTime_Zero;


#include "geoUtils.h"
#include "geoStdio.h"
#include "geoUnistd.h"


//以毫秒为计量单位
//此计时以系统启动时间为基准，
//此时间可以得到系统启动后CPU的tick计数，表示系统启动了多少毫秒
//主要用在程序内部定时，调节系统时间对程序无影响的地方
 GEO_UITLS_API geoTime   GEO_CALL geo_get_steady_time();
//以毫秒为计量单位
//此时间可以得到当前系统时间
//主要用在时间戳上
GEO_UITLS_API geoTimeStamp  GEO_CALL geo_get_system_time();

//毫秒的geoTime转换为CPU的tick时间
//为标准函数和系统函数所用
GEO_UITLS_API steady_clock::time_point   GEO_CALL geo_geotime_to_steadytime(geoTime absTime);

// Returns the given timestamp in the form
// "hour:minute:second:microsecond."  The month, day, and year are
// also stored in the beginning of the date_and_time array
// using ISO-8601 format.
// 012345678901234567890123456
// 2010-12-02 12:56:00.123456<nul>

GEO_UITLS_API geoTChar * GEO_CALL geo_timestamp(const geoTimeStamp& time_value,
	geoTChar date_and_time[],
	size_t date_and_timelen,
	bool return_pointer_to_first_digit DEFAULT_PARAM(false));


#endif