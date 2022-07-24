/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoProp.h														*
*  @brief    ʵʱ���ǩ�����Դ���											*
*																			*
*  
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
#ifndef  GEOSYS_RTDB_PROP_H__
#define  GEOSYS_RTDB_PROP_H__
#include "geoBasicType.h"
#include "geoRTDBMacro.h"
#include "geoTagVector.h"

class GeoTagMap;

class GeoBaseTagProp:GeoTagVector
{

public:

	explicit GeoBaseTagProp(GeoTagMap * hashNameMap);

	explicit GeoBaseTagProp(GeoTagMap * hashNameMap,
			geoChar * strPathName,
			geoUInt32 nCapacity,
			geoChar * strAuthor,
			geoChar * strOEM);
private:
	GeoTagMap * mHash;
protected:
	geoVoid InitTagBasePropList();
	geoAPIStatus InitNameHash();
public:

	geoAPIStatus Init();
	geoAPIStatus UnInit();

	///	�����Ժ���
	typedef geoAPIStatus(GeoBaseTagProp::* GetPropFunction) (geoUInt32, geoVariant*);

	///	д���Ժ���
	typedef geoAPIStatus(GeoBaseTagProp::*SetPropFunction) (geoUInt32, geoVariant*);

	///	�������Ժ���
	typedef geoAPIStatus(GeoBaseTagProp::*FilterPropFunction) (geoUInt32, geoVariant*);



	typedef struct
	{
		GetPropFunction			GetFunction;
		SetPropFunction			SetFunction;
		FilterPropFunction		FilterFunction;
		geoVarTypeEnum			DataType;
	}psPropProcess;

	psPropProcess m_pTagBasePropProcess[geoProp_TagBase_Max];

	geoAPIStatus GetProp_Id(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_TagType(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_TagType(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus FilterProp_TagType(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_Name(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_Name(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus FilterProp_Name(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_DataType(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_DataType(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus FilterProp_DataType(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_Description(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_Description(geoUInt32 unTagId, geoVariant *pValue);
	
	geoAPIStatus FilterProp_Description(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_Unit(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_Unit(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus FilterProp_Unit(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_InitValue(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_InitValue(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus FilterProp_InitValue(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_ParentId(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_NextId(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_PrevId(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_FirstChildId(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_CreateTime(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_CreateTime(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus FilterProp_CreateTime(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus GetProp_LastModifyTime(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus SetProp_LastModifyTime(geoUInt32 unTagId, geoVariant *pValue);

	geoAPIStatus FilterProp_LastModifyTime(geoUInt32 unTagId, geoVariant *pValue);

	//�õ���չ��ǩ����+ ��չID
	geoAPIStatus GetExtend(geoUInt32 unTagId, geoUInt8* pnTagType, geoUInt32* pnExtendId);
	//�õ���չ��չID
	geoAPIStatus GetExtendId(geoUInt32 unTagId, geoUInt32* pnExtendId);
	//������չID
	geoAPIStatus SetExtendId(geoUInt32 unTagId, geoUInt32 unExtendID);

	//�ж��Ƿ�Ϊ��������
	static  geoBool IsTagBaseProp(geoUInt16 nPropId);

public:
	geoAPIStatus AddTag(
		geoPropValueList *pPropValueList,
		geoUInt32 *pnNewTagId,
		geoAPIStatus* pAPIStatusList);

	geoAPIStatus DelTag(geoUInt32 nDelTagId);

	///	�õ���ǩ�ĵ�������
	geoAPIStatus GetProperty(
		geoUInt32 unTagId,
		geoUInt16 nPropId,
		geoVariant *pValue);

	geoAPIStatus GetTagBasePropList(geoUInt32 unTagId, geoTagPropList * pTagPropList);
	geoAPIStatus SetTagBasePropList(geoUInt32 unTagId, geoTagPropList * pTagPropList);

	///	���ñ�ǩ�ĵ�������
	geoAPIStatus SetProperty(
		geoUInt32 unTagId,
		geoUInt16 nPropId,
		geoVariant *pValue);


	///	�õ���ǩ��һ������
	geoAPIStatus GetPropList(
		geoUInt32 unTagId,
		geoPropIdList *pPropIdList,
		geoPropValueList* pValueList);

	geoAPIStatus GetPropList(
		geoUInt32 unTagId,
		geoTagPropList * pTagPropList);

	///	���ñ�ǩ��һ������
	geoAPIStatus SetPropList(
		geoUInt32 unTagId,
		geoTagPropList * pTagPropList);

	///����ID ȡ���������� 
	inline geoUInt8 GetDataType(geoUInt32 unTagId);
	///��������ȡ��ID
	///geoUInt32 GetId(geoChar * pTagName);
	///����IDȡ�ñ�ǩ���� 
	inline geoUInt32 GetTagType(geoUInt32 unTagId);
};
#endif