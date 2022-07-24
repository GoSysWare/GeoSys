/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoTagMap.h													 *
*  @brief    实时库Map表													 *
*																			 *
*  名字与ID的关联层
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
*  2016/10/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_RTDB_TAG_MAP_H__
#define  GEOSYS_RTDB_TAG_MAP_H__

#include"geoBasicType.h"
#include "geoStringMap.hh"

class GeoTagPro;
/**
* @class GeoTagMap
*
* @brief 标签名字与ID的映射
*
*
*/
class GeoTagMap:public GeoStringMap
{

	friend GeoTagPro;
public:
	GeoTagMap();
	GeoTagMap(geoUInt32 size);

	///根据名字取得ID
	geoUInt32 GetId(geoChar * pTagName);
	///根据名字取得ID
	geoAPIStatus GetId(geoChar * pTagName,geoUInt32 &unTagId);
	///根据名字取得ID
	geoAPIStatus GetIdList(geoStringList *pTagNameList, geoTagIdList * pTagIdList);
private:




};
#endif
