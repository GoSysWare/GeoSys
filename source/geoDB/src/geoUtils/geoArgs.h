/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoArgs.h                                                     *
*  @brief    字符串截断分割处理  ，将字符串以指定的字符分割成多个子字符串      *
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
*  2016/10/30 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef  GEOSYS_UTILS_ARGS_H__
#define  GEOSYS_UTILS_ARGS_H__


#include "geoUtils.h"

#define MAX_ARGC 128
#define MAX_LINE_LENGTH 2048

typedef struct __tag_CArgsA
{
	int argc;
	char * argv[MAX_ARGC];
	int arg_idx[MAX_ARGC];
	char args[MAX_LINE_LENGTH];
}CArgsA;

typedef struct __tag_CArgsW
{
	int argc;
	wchar_t * argv[MAX_ARGC];
	int arg_idx[MAX_ARGC];
	wchar_t args[MAX_LINE_LENGTH];
}CArgsW;

#ifdef UNICODE
#define CArgs CArgsW
#define CArgsEx CArgsExW
#define parse_arg_ex parse_arg_exW
#define parse_arg_ey parse_arg_eyW
#else
#define CArgs CArgsA
#define CArgsEx CArgsExA
#define parse_arg_ex parse_arg_exA
#define parse_arg_ey parse_arg_eyA
#endif

CDECL_BEGIN
struct GEO_UITLS_API CArgsExA {
	int		argc;
	char	**argv;
	int		*arg_idx;
	char	*args;

	CArgsExA();
	CArgsExA(const char * src,
		const char * delimiter = ",",
		int maxArgc = MAX_ARGC,
		int maxlen = MAX_LINE_LENGTH,
		bool ignore_empty_fields = true
	);
	virtual ~CArgsExA();

	int parse(
		const char * src,
		const char * delimiter = ",",
		int maxArgc = MAX_ARGC,
		int maxlen = MAX_LINE_LENGTH,
		bool ignore_empty_fields = true
	);
	inline const char * operator[](int i)
	{
		return argv[i];
	}

	int		arg_len;
	int		len;
	void destroy();
	bool create(int arglen, int len);
};

struct GEO_UITLS_API CArgsExW {
	int		argc;
	wchar_t	**argv;
	int		*arg_idx;
	wchar_t	*args;

	CArgsExW();
	CArgsExW(
		const wchar_t * src,
		const wchar_t * delimiter = L",",
		int maxArgc = MAX_ARGC,
		int maxlen = MAX_LINE_LENGTH,
		bool ignore_empty_fields = true
	);
	virtual ~CArgsExW();

	int parse(
		const wchar_t * src,
		const wchar_t * delimiter = L",",
		int maxArgc = MAX_ARGC,
		int maxlen = MAX_LINE_LENGTH,
		bool ignore_empty_fields = true
	);
	inline const wchar_t * operator[](int i)
	{
		return argv[i];
	}
protected:
	int		arg_len;
	int		len;
	void destroy();
	bool create(int arglen, int len);
};




GEO_UITLS_API int GEO_CALL
parse_arg_exA(
	const char * arg_str,
	CArgsA *,
	char * delimiter = NULL
);
GEO_UITLS_API int GEO_CALL
parse_arg_exW(
	const wchar_t * arg_str,
	CArgsW *,
	wchar_t * delimiter = NULL
);

/*
parse_arg_ey 和 parse_arg_ex 不同，在于它将连续出现的分割符号的处理方式不同
举例来说：
parse_arg_ex(",,,,,",&args,",");
得到零个参数，因为strtok将所有的‘,’都忽略了
而parse_arg_ey(",,,,,",&args,",");
则得到5个参数，每个参数都是空字符串
*/
GEO_UITLS_API int GEO_CALL
parse_arg_eyA(
	const char * arg_str,
	CArgsA * args,
	char * delimiter
);

GEO_UITLS_API int GEO_CALL
parse_arg_eyW(
	const wchar_t * arg_str,
	CArgsW * args,
	wchar_t * delimiter
);

CDECL_END












#endif