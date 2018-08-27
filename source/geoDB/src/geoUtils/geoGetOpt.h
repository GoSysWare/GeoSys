/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoGetOpt.h                                                     *
*  @brief    Argc Argv参数解析                                                   *
*																			 *
*  此为linux的源码改写  
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



#ifndef GEOSYS_UTILS_GETOPT_H__
#define GEOSYS_UTILS_GETOPT_H__

#include "geoUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

extern GEO_UITLS_API int opterr;		//是否打印输出错误信息
extern GEO_UITLS_API int optind;		//再次调用 getopt() 时的下一个 argv 指针的索引。
extern GEO_UITLS_API int optopt;		//最后一个已知选项。可以重复调用 getopt()，直到其返回 - 1 为止.
extern GEO_UITLS_API int optreset;		/* reset getopt */
extern GEO_UITLS_API char *optarg;		//指向当前选项参数（如果有）的指针（optarg不需要定义，在getopt.h中已经有定义）。

struct option
{
  const char *name; //name表示的是长参数名
  int has_arg; //has_arg有3个值，no_argument(或者是0)，表示该参数后面不跟参数值
				//required_argument(或者是1),表示该参数后面一定要跟个参数值 
				//optional_argument(或者是2),表示该参数后面可以跟，也可以不跟参数值 
  int *flag;  //用来决定，getopt_long()的返回值到底是什么。如果flag是null，则函数会返回与该项option匹配的val值 
  int val;//和flag联合决定返回值 
};

//struct option long_options[] = {
//	{ "a123", required_argument, 0, 'a' },getopt_long
//	{ "c123", no_argument, 0, 'c' },
//}
//现在，如果命令行的参数是 - a 123，那么调用()将返回字符'a', 
//并且将字符串123由optarg返回(注意注意！字符串123由optarg带回！optarg不需要定义，在getopt.h中已经有定义)，
//那么，如果命令行参数是 - c，那么调用getopt_long()将返回字符'c', 
//而此时，optarg是null。
//最后，当getopt_long()将命令行所有参数全部解析完成后，返回 - 1。
//getopt_long在遇到 -name时，会拆解成 -n -a -m -e到optstring中进行匹配
#define no_argument       0
#define required_argument 1
#define optional_argument 2

GEO_UITLS_API int GEO_CALL getopt(int, char**, const char*);
GEO_UITLS_API int GEO_CALL getopt_long(int, char**, const char*, const struct option*, int*);

#ifdef __cplusplus
}
#endif

#endif /* __GETOPT_H__ */


//实例用法:
/*
#include <stdio.h>
#include <getopt.h>
char *l_opt_arg;
char* const short_options = "nbl:";
struct option long_options[] = {
	{ "name", 0, NULL, 'n' },
	{ "bf_name", 0, NULL, 'b' },
	{ "love", 1, NULL, 'l' },
	{ 0, 0, 0, 0 },
};
int main(int argc, char *argv[])
{
	int c;
	while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
	{
		switch (c)
		{
		case 'n':
			printf("My name is XL./n");
			break;
		case 'b':
			printf("His name is ST./n");
			break;
		case 'l':
			l_opt_arg = optarg;
			printf("Our love is %s!/n", l_opt_arg);
			break;
		}
	}



	return 0;
}
[root@localhost wyp]# gcc -o getopt getopt.c
[root@localhost wyp]# . / getopt -n -b -l forever
My name is XL.
His name is ST.
Our love is forever!
[root@localhost liuxltest]#
[root@localhost liuxltest]# . / getopt -nb -l forever
My name is XL.
His name is ST.
Our love is forever!
[root@localhost liuxltest]# . / getopt -nbl forever
My name is XL.
His name is ST.
Our love is forever!
*/