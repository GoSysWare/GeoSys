/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoObject.h                                                     *
*  @brief    ����Object����                                                *
*																			 *
*			 ���Ԥ���ŷ�������չ���������԰��ո��ֱ�����Ե�Object			 *
*			 ��Ӹ������߰������õĶ���										 *
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

#ifndef  GEOSYS_OBJECT_H__
#define  GEOSYS_OBJECT_H__

#include "geoBasicType.h"



#define G_OBJECT_TYPE_DEFUAL	0u
#define G_OBJECT_TYPE_NET		1u << 1


#define G_OBJECT_NAME			"GeoSysObject"

/**
* @clasa GeoObject
* @brief GeoSys�Ļ����� 
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
	* @brief ���ض�������
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
	* @brief ���ض������ͣ�����������һ���ַ���
	* @return ��Ӧ�������ͱ��е�ֵ
	*/
	const geoUInt16	getType();

	geoVoid		dump();

private:
	geoUInt16	mObjectType;
	geoUInt16	mObjectTag;
	geoStdString	mObjectName;
};



#endif

