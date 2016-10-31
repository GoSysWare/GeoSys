/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoUnistd.h                                                     *
*  @brief    平台相关的操作API                                                      *
*																			 *
*  封装 access getpagesize chdir rmdir  close execv 等API
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
#ifndef  GEOSYS_UTILS_UNISTD_H__
#define  GEOSYS_UTILS_UNISTD_H__
#include <errno.h>
#include <io.h>
#include<time.h>
#include"geoWchar.h"
#include"geoUtils.h"


 //R_OK 4 /* Test for read permission. */
 //W_OK 2 /* Test for write permission. */
 //X_OK 1 /* Test for execute permission. */
 //F_OK 0 /* Test for existence. */
GEO_UITLS_API
int GEO_CALL geo_access(const char *path, int amode);

#if defined (_UNICODE)
GEO_UITLS_API
int GEO_CALL geo_access(const wchar_t *path, int amode);
#endif 

GEO_UITLS_API
struct tm * GEO_CALL geo_localtime_r(const time_t *t, struct tm *res);

GEO_UITLS_API
pid_t GEO_CALL geo_getpid(void);

#endif