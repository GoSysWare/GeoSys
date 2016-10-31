/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                      *
*                                                                            *
*  @file     geoDll.h                                                     *
*  @brief    dll或so 动态或者静态链接库处理类                                *
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
#ifndef  GEOSYS_UTILS_DLL_H__
#define  GEOSYS_UTILS_DLL_H__

#include "geoBasicType.h"
#include "geoUtils.h"
#include <signal.h>
#include <mutex>
#include<vector>
#if defined (_WIN32)
#include <windows.h>
typedef HINSTANCE SHLIB_HANDLE;
#else
typedef void * SHLIB_HANDLE;

#endif // 

class GEO_UITLS_API std::mutex;

class GEO_UITLS_API GeoDll
{
public:
	explicit GeoDll();
	explicit GeoDll(const geoTChar  *dll_name,int open_mode DEFAULT_PARAM(0));

	~GeoDll();
	int open(geoTChar * dll_filename, int open_mode DEFAULT_PARAM(0), SHLIB_HANDLE handle DEFAULT_PARAM(0));
	int close();
	void * symbol(const geoTChar *sym_name);


private:
	void getDllNames(const geoTChar *dll_name,std::vector<geoStdTString>  &try_names);
	sig_atomic_t mRefcount;
	SHLIB_HANDLE mHandle;
	int mOpenMode;
	geoTChar mDllName[_MAX_PATH];
	static sig_atomic_t mOpenCalled;
	std::mutex mMutex;
};


#endif