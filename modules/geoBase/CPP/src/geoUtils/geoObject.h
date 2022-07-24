/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoObject.h                                                     *
*  @brief    基本Object对象，                                                *
*																			 *
*			 这个预留着方便做扩展，这样可以按照各种编程语言的Object			 *
*			 添加各种乱七八糟有用的东西										 *
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

#ifndef  GEOSYS_OBJECT_H__
#define  GEOSYS_OBJECT_H__

#include "geoBasicType.h"



#define G_OBJECT_TYPE_DEFUAL	0u
#define G_OBJECT_TYPE_NET		1u << 1


#define G_OBJECT_NAME			"GeoSysObject"

/**
* @clasa GeoObject
* @brief GeoSys的基础类 
*
*   
*/

class GeoObject
{
public:
	GeoObject();
	GeoObject(char * name,geoUInt16 type, geoUInt16 tag);
	virtual	~GeoObject();
	/**
	* @brief 返回对象名字
	* @return std::string
	*/
	virtual  geoStdString toString();
	/**
	* @brief 
	* @return 
	*/
	void	setClassName(geoStdString cname) ;
	/**
	* @brief 
	* @return 
	*/
	void	setType(geoUInt16 type);
	/**
	* @brief 返回对象类型，对象类型是一个字符，
	* @return 对应对象类型表中的值
	*/
	const geoUInt16	getType();

	geoVoid		dump();

private:
	geoUInt16	mObjectType;
	geoUInt16	mObjectTag;
	geoStdString	mObjectName;
};



#endif

