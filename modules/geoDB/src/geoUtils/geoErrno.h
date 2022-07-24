/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                      *
*                                                                            *
*  @file     geoErrno.h                                                     *
*  @brief    系统错误号处理接口                              *
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
*  Remark         :									                         *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/09/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_UTILS_ERRNO_H__
#define  GEOSYS_UTILS_ERRNO_H__
#include"geoBasicType.h"


#include"geoUtils.h"

GEO_UITLS_API int GEO_CALL last_error(void);

GEO_UITLS_API void GEO_CALL set_last_error(int error);

GEO_UITLS_API int GEO_CALL set_errno_to_last_error(void);

GEO_UITLS_API int GEO_CALL set_errno_to_wsa_last_error(void);


#endif
