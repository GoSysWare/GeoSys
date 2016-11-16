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


GEO_UITLS_API
int GEO_CALL geo_chdir(const char *path);

GEO_UITLS_API
int GEO_CALL geo_rmdir(const char *path);

GEO_UITLS_API
char * GEO_CALL geo_getcwd(char *buf, size_t size);

GEO_UITLS_API
int GEO_CALL geo_hostname(char name[], size_t maxnamelen);

GEO_UITLS_API
HANDLE GEO_CALL geo_open(const char *filename,
	int mode,
	mode_t perms = DEFAULT_FILE_PERMS,
	LPSECURITY_ATTRIBUTES sa = 0);

GEO_UITLS_API
int GEO_CALL geo_truncate(const geoTChar *filename, off_t offset);
GEO_UITLS_API
int GEO_CALL geo_mkdir(const char *path, mode_t mode);

GEO_UITLS_API
int GEO_CALL geo_stat(const char *file, Geo_stat *stp);

#if defined (_UNICODE)
GEO_UITLS_API
int GEO_CALL geo_access(const wchar_t *path, int amode);
GEO_UITLS_API
int GEO_CALL geo_chdir(const wchar_t *path);
GEO_UITLS_API
int GEO_CALL geo_rmdir(const wchar_t *path);
GEO_UITLS_API
wchar_t * GEO_CALL geo_getcwd(wchar_t *buf, size_t size);
GEO_UITLS_API
int GEO_CALL geo_hostname(wchar_t name[], size_t maxnamelen);

GEO_UITLS_API
HANDLE GEO_CALL geo_open(const wchar_t *filename,
	int mode,
	mode_t perms = DEFAULT_FILE_PERMS,
	LPSECURITY_ATTRIBUTES sa = 0 );
GEO_UITLS_API
int GEO_CALL geo_mkdir(const wchar_t *path, mode_t mode);

GEO_UITLS_API
int  GEO_CALL geo_stat(const wchar_t *file, Geo_stat *stp);
#endif 
GEO_UITLS_API
int GEO_CALL geo_close(HANDLE handle);

GEO_UITLS_API
HANDLE GEO_CALL geo_dup(HANDLE handle);

GEO_UITLS_API
HANDLE GEO_CALL geo_dup(HANDLE handle, pid_t pid);

GEO_UITLS_API
int GEO_CALL geo_fsync(HANDLE handle);

GEO_UITLS_API
int GEO_CALL geo_ftruncate(HANDLE handle, off_t offset);

GEO_UITLS_API
off_t GEO_CALL geo_lseek(HANDLE handle, off_t offset, int whence);

GEO_UITLS_API
off_t GEO_CALL geo_llseek(HANDLE handle, off_t offset, int whence);

GEO_UITLS_API
ssize_t GEO_CALL geo_read(HANDLE handle, void *buf, size_t len);

GEO_UITLS_API
ssize_t GEO_CALL geo_write(HANDLE handle, const void *buf, size_t nbyte);

GEO_UITLS_API
int GEO_CALL geo_pipe(HANDLE fds[]);

GEO_UITLS_API
int GEO_CALL geo_sleep(u_int mseconds);

GEO_UITLS_API
int GEO_CALL geo_fstat(HANDLE handle, Geo_stat *stp);
GEO_UITLS_API
off_t GEO_CALL geo_filesize(HANDLE handle);

GEO_UITLS_API
off_t  GEO_CALL geo_filesize(const geoTChar *filename);

GEO_UITLS_API
struct tm * GEO_CALL geo_localtime_r(const time_t *t, struct tm *res);




GEO_UITLS_API
pid_t GEO_CALL geo_getpid(void);

#endif