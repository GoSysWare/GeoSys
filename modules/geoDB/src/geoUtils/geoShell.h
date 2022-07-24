/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoShell.h														*
*  @brief    Shell运行控制台，可以在控制台模式下输入一些终端命令            *
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
*  2016/12/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_UTILS_SHELL_H__
#define  GEOSYS_UTILS_SHELL_H__

#include <string.h>
#include "geoBasicType.h"

#include "geoUtils.h"

typedef void * geoShell;


struct shell_command {
	char * name;
	char * brief_description;
	int(*shell_proc)(char * arglist, void * pv);
};



class GEO_UITLS_API variable{
public:
	geoShell *s;
	char name[256];
	enum v_type{
		vt_int,
		vt_float,
		vt_char_,	//char *
		vt_object,
	}type;
	union{
		int i_val;
		double f_val;
		char c_val[256];
		void * o_val;
	};
	variable(){
		type=vt_char_;
		*c_val=0;
		strcpy(name,"unknown_variable");
	}
	variable(int v, const char * n=0){
		type=vt_int;
		i_val=v;
		if(n) {
			strncpy(name,n,sizeof(name));
			name[sizeof(name) - 1] = 0;
		}
	};
	variable(const char *v, const char *n=0){
		type=vt_char_;
		strncpy(c_val,v,sizeof(c_val));
		c_val[sizeof(c_val) - 1] = 0;
		if(n) {
			strncpy(name,n,sizeof(name));
			name[sizeof(name) - 1] = 0;
		}
	}
	variable(double v, const char *n=0){
		type=vt_float;
		f_val=v;
		if(n) {
			strncpy(name,n,sizeof(name));
			name[sizeof(name) - 1] = 0;
		}
	}
	variable(void *v, const char *n=0){
		type=vt_object;
		o_val=v;
		if(n) {
			strncpy(name,n,sizeof(name));
			name[sizeof(name) - 1] = 0;
		}
	};
	virtual ~variable(){
	};
	void show();
	int set(const char * value);
	void get(char * buffer, int length);
};



GEO_UITLS_API void GEO_CALL shell_add_v(geoShell, variable * v);
GEO_UITLS_API void GEO_CALL shell_del_v(geoShell, variable * v);
GEO_UITLS_API int GEO_CALL shell_set_v(geoShell,
	const char * name,
	const char * value,
	variable ::v_type vt = variable::vt_char_
	);

GEO_UITLS_API variable * GEO_CALL shell_get_v(geoShell, const char * name);
GEO_UITLS_API int GEO_CALL shell_get_v(geoShell, const char * name,int * value);
GEO_UITLS_API int GEO_CALL shell_get_v(geoShell, const char * name,char ** value);
GEO_UITLS_API int GEO_CALL shell_get_v(geoShell, const char * name,float * value);
GEO_UITLS_API int GEO_CALL shell_get_v(geoShell, const char * name,void ** value);




	GEO_UITLS_API geoShell GEO_CALL shell_create(
	const shell_command * valid_cmds
	);

		GEO_UITLS_API int GEO_CALL shell_execute(
	geoShell, 
	const char * lbuffer,
	void * pv
	);

		GEO_UITLS_API bool GEO_CALL shell_execute_ex(
	geoShell, 
	const char * lbuffer,
	void * pv,
	int * code
	);


GEO_UITLS_API void GEO_CALL shell_destroy(geoShell);


#endif
