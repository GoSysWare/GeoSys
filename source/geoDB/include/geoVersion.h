

/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                   *
*                                                                            *
*  @file     geoVersion.h                                                     *
*  @brief    线程处理类                                                      *
*																			 *
*  GeoSys的编码版本
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
#ifndef GEOSYS_VERSIONED_H
#define GEOSYS_VERSIONED_H


#define GEOSYS_MAJOR_VERSION 1
#define GEOSYS_MINOR_VERSION 0
#define GEOSYS_BETA_VERSION  1
#define GEOSYS_VERSION_STR "1.0.1"
#define GEOSYS_VERSION 0x010001

#define GEOSYS_DEFAULT_NAME		"GeoSysWare"
#define GEOSYS_AUTHOR			"George Kuo"
#define GEOSYS_BUILD_TIME		"2016/06/01"
#define GEOSYS_OEM				"G.O.G"

#define GEOSYS_RTDB_MAJOR_VERSION 1
#define GEOSYS_RTDB_MINOR_VERSION 0
#define GEOSYS_RTDB_BETA_VERSION  1

#define GEOSYS_RTDB_VERSION_STR "1.0.1"

#define GEOSYS_RTDB_VERSION 0x010001



/**
*@brief NICSYS当前的版本比较
可以采用如 #if (GEOSYS_VERSION >= GEOSYS_VERSION_CHECK(4, 4, 0))
*/
#define GEOSYS_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

/**
*@brief GEOSYS的虚拟实时多播总线版本
*/
#define GEOSYS_VBUS_VERSION 0x0201

#define GEOSYS_VBUS_VERSION_STR "2.1"

#endif