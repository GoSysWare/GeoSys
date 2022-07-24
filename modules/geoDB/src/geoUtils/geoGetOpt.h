/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoGetOpt.h                                                     *
*  @brief    Argc Argv��������                                                   *
*																			 *
*  ��Ϊlinux��Դ���д  
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(�汾��)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : ������֧��C++11�����±���ͨ��                            *
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

extern GEO_UITLS_API int opterr;		//�Ƿ��ӡ���������Ϣ
extern GEO_UITLS_API int optind;		//�ٴε��� getopt() ʱ����һ�� argv ָ���������
extern GEO_UITLS_API int optopt;		//���һ����֪ѡ������ظ����� getopt()��ֱ���䷵�� - 1 Ϊֹ.
extern GEO_UITLS_API int optreset;		/* reset getopt */
extern GEO_UITLS_API char *optarg;		//ָ��ǰѡ�����������У���ָ�루optarg����Ҫ���壬��getopt.h���Ѿ��ж��壩��

struct option
{
  const char *name; //name��ʾ���ǳ�������
  int has_arg; //has_arg��3��ֵ��no_argument(������0)����ʾ�ò������治������ֵ
				//required_argument(������1),��ʾ�ò�������һ��Ҫ��������ֵ 
				//optional_argument(������2),��ʾ�ò���������Ը���Ҳ���Բ�������ֵ 
  int *flag;  //����������getopt_long()�ķ���ֵ������ʲô�����flag��null�������᷵�������optionƥ���valֵ 
  int val;//��flag���Ͼ�������ֵ 
};

//struct option long_options[] = {
//	{ "a123", required_argument, 0, 'a' },getopt_long
//	{ "c123", no_argument, 0, 'c' },
//}
//���ڣ���������еĲ����� - a 123����ô����()�������ַ�'a', 
//���ҽ��ַ���123��optarg����(ע��ע�⣡�ַ���123��optarg���أ�optarg����Ҫ���壬��getopt.h���Ѿ��ж���)��
//��ô����������в����� - c����ô����getopt_long()�������ַ�'c', 
//����ʱ��optarg��null��
//��󣬵�getopt_long()�����������в���ȫ��������ɺ󣬷��� - 1��
//getopt_long������ -nameʱ������� -n -a -m -e��optstring�н���ƥ��
#define no_argument       0
#define required_argument 1
#define optional_argument 2

GEO_UITLS_API int GEO_CALL getopt(int, char**, const char*);
GEO_UITLS_API int GEO_CALL getopt_long(int, char**, const char*, const struct option*, int*);

#ifdef __cplusplus
}
#endif

#endif /* __GETOPT_H__ */


//ʵ���÷�:
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