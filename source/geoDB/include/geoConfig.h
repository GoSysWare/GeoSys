/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.												*
*                                                                            *
*  @file     geoConfig.h                                                   *
*  @brief		GeoSys的一些系统业务相关的配置和设置都在此					                                      *
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
*  2016/08/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef  GEOSYS_OS_CONFIG_H__
#define  GEOSYS_OS_CONFIG_H__




#include "geoVersion.h"
#include "geoVersionNameSpace.h"

#define rtkm_node_key_length   16


////如果编译器不支持C++11编译自动失败
//#if __cplusplus < 20131103L  
//#error "should use C++ 11 implementation"  
//#endif  


#ifdef _WIN32
#pragma warning(disable:4996) //全部关掉
#endif // _WIN32


#endif