/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoNet.h														 *
*  @brief    GeoSys的网络处理模块                                            *
*																			 *
*  集合TCP UDP通用网络处理，
*   TCP	 支持采用libevent实现同步Reactor模式 带事务模型
*        支持用asio实现异步模式，无事务模型
*   UDP  支持用asio实现无阻塞的异步模式，无事务模型
		 支持用asio实现阻塞的同步模式，无事务模型	
*   多播 支持用asio实现无阻塞的异步模式，无事务模型
*		 支持用asio实现无阻塞的同步模式，无事务模型
*  串口通信  支持同步串口
*			 支持异步串口
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
#ifndef  GEOSYS_DB_NET_H__
#define  GEOSYS_DB_NET_H__


#include"geoConfig.h"

#include "geoBasicType.h"




#if defined(GEO_HEADER_INLINE)
#	define GEO_NET_API inline
#else 
#	if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__CODEGEARC__)
#		ifdef LIB_NET_EXPORTS
#			define GEO_NET_API      __declspec(dllexport)
#		else
#			define GEO_NET_API      __declspec(dllimport)
#		endif
#	else
#define GEO_NET_API
#	endif

#endif



#endif