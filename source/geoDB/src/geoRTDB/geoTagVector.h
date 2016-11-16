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
	///�Ƿ�ɾ��
	inline	geoBool  IsDeleted(geoUInt32 id)
	{
		return (mData[id].Flag.Deleted == 1);
	}
	///�Ƿ����
	inline	geoBool  IsExist(geoUInt32 tagId)
	{
		return (tagId >= 0 && tagId < mCurrentIndex && !IsDeleted(tagId));
	}
	///�õ���ǰ��Ч��ǩ��
	inline geoUInt32 GetValidCount() const
	{
		return mValidCount;
	}
	///�õ���ǰ��ǩ����
	inline geoUInt32 GetCurrentIndex() const
	{
		return mValidCount;
	}
	///�õ���ǰϵͳ����
	inline geoUInt32 GetCapacity() const
	{
		return mCapacity;
	}
	///����TagId���õ�����
	inline geoTagBase * GetData(geoUInt32 tagId)
	{
		GEO_ASSERT(IsExist(tagId));
		return mData + tagId;
	}
private:
	///�ļ�·��
	geoChar  mStrPathName[PATH_MAX];
	///	��ǩ������Ĵ洢
	geoTagBase * mData;

	/// ��ǩʵ������
	geoUInt32  mCapacity;

	///��Ч�ı�ǩ��
	geoUInt32  mValidCount;

	///��ǰ��ǩ����,��Զֻ���ӣ�ֱ���ӽ�mCapacity
	geoUInt32 mCurrentIndex;
	///����
	geoChar   mAuthor[TAG_AUTHOR_SIZE];	
	///��λ
	geoChar	  mOEM[TAG_OEM_SIZE];		





};
#endif