/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoTagMap.h													 *
*  @brief    ʵʱ��Map��													 *
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
#ifndef  GEOSYS_RTDB_TAG_MAP_H__
#define  GEOSYS_RTDB_TAG_MAP_H__

#include"geoBasicType.h"
#include "geoStringMap.hh"

class GeoTagPro;
/**
* @class GeoTagMap
*
* @brief ��ǩ������ID��ӳ��
*
*
*/
class GeoTagMap:public GeoStringMap
{

	friend GeoTagPro;
public:
	GeoTagMap();
	GeoTagMap(geoUInt32 size);

	///��������ȡ��ID
	geoUInt32 GetId(geoChar * pTagName);
	///��������ȡ��ID
	geoAPIStatus GetId(geoChar * pTagName,geoUInt32 &unTagId);
	///��������ȡ��ID
	geoAPIStatus GetIdList(geoStringList *pTagNameList, geoTagIdList * pTagIdList);
private:




};
#endif
