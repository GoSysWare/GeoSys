/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoTagValue.h													 *
*  @brief    ʵʱ��ʵʱֵ����												*
*																			 *
*  ������ID�Ĺ�����
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
*  2016/10/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_RTDB_TAG_VALUE_H__
#define  GEOSYS_RTDB_TAG_VALUE_H__

#include"geoBasicType.h"
#include"geoRTDBMacro.h"

class GeoTagValue
{
public:
	GeoTagValue();
	GeoTagValue(geoChar * strPathName,
		geoUInt32 nCapacity = TAG_DEFUALT_CAPACITY);
	~GeoTagValue();

};



#endif

