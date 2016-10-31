/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoStdio.h                                                     *
*  @brief    平台相关的io操作API                                                      *
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
#ifndef  GEOSYS_UTILS_STDIO_H__
#define  GEOSYS_UTILS_STDIO_H__

#include <stdio.h>

#include"geoUtils.h"

GEO_UITLS_API
int geo_fprintf(FILE *fp, const char *format, ...);

GEO_UITLS_API
int geo_sprintf(char *buf, const char *format, ...);

GEO_UITLS_API
int geo_snprintf(char *buf, size_t maxlen, const char *format, ...);

GEO_UITLS_API
int geo_vprintf(const char *format, va_list argptr);

GEO_UITLS_API
int geo_vfprintf(FILE *fp, const char *format, va_list argptr);


GEO_UITLS_API
int geo_vsprintf(char *buffer, const char *format, va_list argptr);


GEO_UITLS_API
int geo_vsnprintf(char *buffer, size_t maxlen, const char *format, va_list argptr);


GEO_UITLS_API
int geo_fprintf(FILE *fp, const wchar_t *format, ...);

GEO_UITLS_API
int geo_sprintf(wchar_t *buf, const wchar_t *format, ...);


GEO_UITLS_API
int geo_snprintf(wchar_t *buf, size_t maxlen, const wchar_t *format, ...);

GEO_UITLS_API
int geo_vprintf(const wchar_t *format, va_list argptr);

GEO_UITLS_API
int geo_vfprintf(FILE *fp, const wchar_t *format, va_list argptr);

GEO_UITLS_API
int geo_vsprintf(wchar_t *buffer, const wchar_t *format, va_list argptr);

GEO_UITLS_API
int geo_vsnprintf(wchar_t *buffer, size_t maxlen, const wchar_t *format, va_list argptr);




#endif


