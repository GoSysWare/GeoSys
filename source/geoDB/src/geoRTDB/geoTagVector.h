/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoTagVector.h                                            *
*  @brief    实时库内核数据的数组结构                                       *
*																			 *
*    属于实时库的物理存储层 Model
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
#ifndef  GEOSYS_RTDB_TAG_VECTOR_H__
#define  GEOSYS_RTDB_TAG_VECTOR_H__

#include"geoBasicType.h"
#include "geoRTDBMacro.h"
#include "preCompile.h"



/**
* @class GeoTagVector
*
* @brief 
*
*
*/
class GeoTagVector
{
public:
	GeoTagVector();
	GeoTagVector(geoUInt32 nCapacity = TAG_DEFUALT_CAPACITY,
					geoChar * strPathName = geoNULL,
					geoChar * strAuthor = TAG_INFO_DEFAULT_AUTHOR,
					geoChar * strOEM = TAG_INFO_DEFAULT_OEM
				);
	~GeoTagVector();
	geoAPIStatus Init();
	geoAPIStatus UnInit();
	///
	geoAPIStatus LoadInfoFile(geoChar* strFileFullName);
	///
	geoAPIStatus LoadDataFile(geoChar* strFileFullName);
	///
	geoAPIStatus SaveInfoFile(geoChar* strFileFullName);
	///
	geoAPIStatus SaveDataFile(geoChar* strFileFullName);

	///
	geoAPIStatus AddTag(geoUInt32 * tagId );
	///
	geoAPIStatus DelTag(geoUInt32 * tagId);
	///
	geoAPIStatus InitTag(geoUInt32 tagId);
	///是否被删除
	inline	geoBool  IsDeleted(geoUInt32 id)
	{
		return (mData[id].Flag.Deleted == 1);
	}
	///是否存在
	inline	geoBool  IsExist(geoUInt32 tagId)
	{
		return (tagId >= 0 && tagId < mCurrentIndex && !IsDeleted(tagId));
	}
	///得到当前有效标签数
	inline geoUInt32 GetValidCount() const
	{
		return mValidCount;
	}
	///得到当前标签索引
	inline geoUInt32 GetCurrentIndex() const
	{
		return mValidCount;
	}
	///得到当前系统容量
	inline geoUInt32 GetCapacity() const
	{
		return mCapacity;
	}
	///根据TagId，得到数据
	inline geoTagBase * GetData(geoUInt32 tagId)
	{
		GEO_ASSERT(IsExist(tagId));
		return mData + tagId;
	}
private:
	///文件路径
	geoChar  mStrPathName[PATH_MAX];
	///	标签数组核心存储
	geoTagBase * mData;

	/// 标签实际容量
	geoUInt32  mCapacity;

	///有效的标签数
	geoUInt32  mValidCount;

	///当前标签索引,永远只增加，直到接近mCapacity
	geoUInt32 mCurrentIndex;
	///作者
	geoChar   mAuthor[TAG_AUTHOR_SIZE];	
	///单位
	geoChar	  mOEM[TAG_OEM_SIZE];		





};
#endif