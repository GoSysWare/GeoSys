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
	explicit GeoTagVector(geoChar * strPathName ,
					geoUInt32 nCapacity = TAG_DEFUALT_CAPACITY,
					geoChar * strAuthor = TAG_INFO_DEFAULT_AUTHOR,
					geoChar * strOEM = TAG_INFO_DEFAULT_OEM
				);
	~GeoTagVector();
	geoAPIStatus Init();
	geoAPIStatus UnInit();

	///	标签数组核心存储
	geoTagBase * mData;

	///增加标签，系统自动分配ID
	geoAPIStatus AddTag(geoUInt32 * tagId );

	///删除标签
	geoAPIStatus DelTag(geoUInt32 tagId);

	///初始化标签
	geoAPIStatus InitTag(geoUInt32 tagId);

	///清空标签
	geoAPIStatus ClearTag(geoUInt32 tagId);

	///把修改的标签Id推入至ChangedList，保存配置时只需保存这些Id
	///在SaveFile没有调用期间，反复操作会带来重复Id的问题，
	///比如新建一个Id，然后再删除它，会计数两次,这个影响不大
	geoAPIStatus PushToChangedList(geoUInt32 tagId);
	///同步配置信息
	///配置文件已经存在
	geoAPIStatus SyncTagToFile();
	///是否被删除
	inline	geoBool  IsDeleted(geoUInt32 id)
	{
		return (mData[id].Flag.Deleted == 1);
	}
	///是否存在
	inline	geoBool  IsExist(geoUInt32 tagId)
	{
		return (tagId >= 0 && tagId < mDataBaseInfo.CurrentIndex && !IsDeleted(tagId));
	}
	///是否存在
	inline	geoBool  IsChanged(geoUInt32 tagId)
	{
		return (mData[tagId].Flag.Changed == 1 && !IsDeleted(tagId));
	}
	///得到当前有效标签数
	inline geoUInt32 GetValidCount() const
	{
		return mDataBaseInfo.ValidCount;
	}
	///得到当前标签索引
	inline geoUInt32 GetCurrentIndex() const
	{
		return mDataBaseInfo.CurrentIndex;
	}
	///得到当前系统容量
	inline geoUInt32 GetCapacity() const
	{
		return mDataBaseInfo.Capacity;
	}
	///根据TagId，得到数据
	inline geoTagBase * GetData(geoUInt32 tagId)
	{
		GEO_ASSERT(IsExist(tagId));
		return mData + tagId;
	}
	///	设置标签已改变，应该保存
	inline geoVoid SetChangedFlag(geoUInt32 tagId)
	{
		GEO_ASSERT(tagId<mDataBaseInfo.CurrentIndex);
		mData[tagId].Flag.Changed = 1;
	}
	///设置标签已保存完毕，应该清除改变标识
	inline geoVoid ClearChangedFlag(geoUInt32 tagId)
	{
		GEO_ASSERT(tagId<mDataBaseInfo.CurrentIndex);
		mData[tagId].Flag.Changed = 0;
	}
private:
	///
	geoAPIStatus LoadDataFile(geoChar* strFileFullName);

	///
	geoAPIStatus SaveDataFile(geoChar* strFileFullName);
	///
	vector<geoUInt32> mChangedList;
	///文件路径
	geoChar  mStrPathName[PATH_MAX];
	

	///数据库信息
	struct geoDataBaseInfo {
		//版本
		geoUInt32 Version;
		/// 标签实际容量
		geoUInt32  Capacity;
		///有效的标签数
		geoUInt32  ValidCount;
		///当前标签索引,永远只增加，直到接近mCapacity
		geoUInt32 CurrentIndex;
		///作者
		geoChar   Author[TAG_AUTHOR_SIZE];	
		///单位
		geoChar	  OEM[TAG_OEM_SIZE];	
		//校验
		geoUInt32 Check;
	};
	geoDataBaseInfo mDataBaseInfo;




};
#endif