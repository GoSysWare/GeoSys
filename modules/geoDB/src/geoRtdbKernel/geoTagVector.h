/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoTagVector.h                                            *
*  @brief    ʵʱ���ں����ݵ�����ṹ                                       *
*																			 *
*    ����ʵʱ�������洢�� Model
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

	///	��ǩ������Ĵ洢
	geoTagBase * mData;

	///���ӱ�ǩ��ϵͳ�Զ�����ID
	geoAPIStatus AddTag(geoUInt32 * tagId );

	///ɾ����ǩ
	geoAPIStatus DelTag(geoUInt32 tagId);

	///��ʼ����ǩ
	geoAPIStatus InitTag(geoUInt32 tagId);

	///��ձ�ǩ
	geoAPIStatus ClearTag(geoUInt32 tagId);

	///���޸ĵı�ǩId������ChangedList����������ʱֻ�豣����ЩId
	///��SaveFileû�е����ڼ䣬��������������ظ�Id�����⣬
	///�����½�һ��Id��Ȼ����ɾ���������������,���Ӱ�첻��
	geoAPIStatus PushToChangedList(geoUInt32 tagId);
	///ͬ��������Ϣ
	///�����ļ��Ѿ�����
	geoAPIStatus SyncTagToFile();
	///�Ƿ�ɾ��
	inline	geoBool  IsDeleted(geoUInt32 id)
	{
		return (mData[id].Flag.Deleted == 1);
	}
	///�Ƿ����
	inline	geoBool  IsExist(geoUInt32 tagId)
	{
		return (tagId >= 0 && tagId < mDataBaseInfo.CurrentIndex && !IsDeleted(tagId));
	}
	///�Ƿ����
	inline	geoBool  IsChanged(geoUInt32 tagId)
	{
		return (mData[tagId].Flag.Changed == 1 && !IsDeleted(tagId));
	}
	///�õ���ǰ��Ч��ǩ��
	inline geoUInt32 GetValidCount() const
	{
		return mDataBaseInfo.ValidCount;
	}
	///�õ���ǰ��ǩ����
	inline geoUInt32 GetCurrentIndex() const
	{
		return mDataBaseInfo.CurrentIndex;
	}
	///�õ���ǰϵͳ����
	inline geoUInt32 GetCapacity() const
	{
		return mDataBaseInfo.Capacity;
	}
	///����TagId���õ�����
	inline geoTagBase * GetData(geoUInt32 tagId)
	{
		GEO_ASSERT(IsExist(tagId));
		return mData + tagId;
	}
	///	���ñ�ǩ�Ѹı䣬Ӧ�ñ���
	inline geoVoid SetChangedFlag(geoUInt32 tagId)
	{
		GEO_ASSERT(tagId<mDataBaseInfo.CurrentIndex);
		mData[tagId].Flag.Changed = 1;
	}
	///���ñ�ǩ�ѱ�����ϣ�Ӧ������ı��ʶ
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
	///�ļ�·��
	geoChar  mStrPathName[PATH_MAX];
	

	///���ݿ���Ϣ
	struct geoDataBaseInfo {
		//�汾
		geoUInt32 Version;
		/// ��ǩʵ������
		geoUInt32  Capacity;
		///��Ч�ı�ǩ��
		geoUInt32  ValidCount;
		///��ǰ��ǩ����,��Զֻ���ӣ�ֱ���ӽ�mCapacity
		geoUInt32 CurrentIndex;
		///����
		geoChar   Author[TAG_AUTHOR_SIZE];	
		///��λ
		geoChar	  OEM[TAG_OEM_SIZE];	
		//У��
		geoUInt32 Check;
	};
	geoDataBaseInfo mDataBaseInfo;




};
#endif