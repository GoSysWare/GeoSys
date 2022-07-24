
/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.                    *
*                                                                            *
*  @file     geoGUID.h                                                     *
*  @brief    UUID或者GUID生成器                                                     *
*																			 *
*    利用操作系统的GUID区别生成
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

#ifndef		GEOSYS_UTILS_GUID_H__
#define		GEOSYS_UTILS_GUID_H__
#include "geoBasicType.h"

#include "geoUtils.h"

/**
* @class geoGUID
* @brief GUID类
*
* 
* @warning
*/
class GEO_UITLS_API GeoGUID{
public:
	geoUInt8	data[16];
	geoVoid create();
	inline geoInt32 name_size() const{return 43;}
	geoInt32 to_string(geoChar * buffer) const;
};

/**
*   当map里GUID作为Key时的排序用的重载操作                                                   
*/
inline bool operator < (const GeoGUID & g1, const GeoGUID & g2)
{
	return memcmp(g1.data, g2.data, sizeof(g1.data))<0? true : false;
}
inline bool operator == (const GeoGUID & g1, const GeoGUID & g2)
{
	return memcmp(g1.data, g2.data, sizeof(g1.data))==0? true : false;
}

#endif