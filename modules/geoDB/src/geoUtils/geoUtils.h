/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoUtils.h														 *
*  @brief    GeoSys的通用库处理                                          *
*																			 *
*			本库涵盖：
					线程
					时间
					事件
					互斥量
					文件操作
					GUID
					Error
					输入输出
					字符处理
					Arg Options
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
#ifndef  GEOSYS_DB_UTILS_H__
#define  GEOSYS_DB_UTILS_H__


#include"geoConfig.h"
#include "geoWchar.h"
#include "geoBasicType.h"

#include <fstream>

#	if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__CODEGEARC__)
#		ifdef LIB_UTILS_EXPORTS
#			define GEO_UITLS_API      __declspec(dllexport)
#		else
#			define GEO_UITLS_API      __declspec(dllimport)
#		endif
#	else
		#define GEO_UITLS_API
#	endif

#ifdef _WIN32
#include<Windows.h>
extern GEO_OSVERSIONINFO  win32_versioninfo_;
extern HINSTANCE win32_resource_module_;
#endif // _WIN32

 extern	std::ostream * g_log_output;


GEO_UITLS_API geoUInt32 geo_log2(geoUInt32 num);

#endif
