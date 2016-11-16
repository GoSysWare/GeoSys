#ifndef _NICSYS_FUNCTION_H__
#define _NICSYS_FUNCTION_H__

#include "geoBasicType.h"
#include "geoError.hh"
#include "geoAssert.hh"
__inline geoAPIStatus NewMemory(void** ppDest, geoUInt32 nSize)
{
	GEO_ASSERT(ppDest !=geoNULL);
	GEO_ASSERT(nSize>0);

	*ppDest = geoNULL;

	*ppDest = malloc(nSize);
	if (*ppDest==geoNULL)
	{
		return geoERR_COMMON_NO_MEMORY;
	}
	return geoRET_SUCC;
}

__inline geoAPIStatus NewAndClear(void** ppDest, geoUInt32 nSize)
{
	if (geoErr(NewMemory(ppDest,nSize)))
	{
		return geoERR_COMMON_NO_MEMORY;
	}
	memset(*ppDest,0,nSize);
	return geoRET_SUCC;
}

__inline void FreeAndNull(void** ppDest)
{
	if (ppDest==geoNULL)
	{
		return;
	}
	if (*ppDest!=geoNULL)
	{
		free(*ppDest);
		*ppDest = geoNULL;
	}
}

__inline void FreeStr(geoStr* geotr)
{
	FreeAndNull((void**)geotr);
}

__inline void ClearStr(geoStr* geotr)
{
	GEO_ASSERT(geotr!=geoNULL);
	if (*geotr!=geoNULL)
	{
		free(*geotr);
	}
	*geotr = geoNULL;
}

__inline void ClearStr(geoStr geotr)
{
	ClearStr(&geotr);
}

__inline geoAPIStatus NewAndCopyStr(geoStr* geotrDest,const geoChar * strSource)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(NewMemory((geoVoid**)geotrDest,
		(geoUInt32)(strlen(strSource)+1)*sizeof(geoChar)));  
	strcpy(*geotrDest,strSource);
	return geoRET_SUCC;
}

__inline geoAPIStatus NewAndCopyUStr(geoWStr* geotrDest,const geoWChar * strSource)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(NewMemory((geoVoid**)geotrDest,
		(geoUInt32)(wcslen((const geoWChar *)strSource)+1)*sizeof(geoWChar)));  /*修改原因:定义unique情况下申请空间长度不够*/
	wcscpy((geoWChar *)*geotrDest,(const geoWChar *)strSource);
	return geoRET_SUCC;
}

__inline geoAPIStatus geoStrRplace (geoStr* geotrDest,geoStr strSource)
{
	geoAPIStatus nRet = geoRET_SUCC;
	GEO_ASSERT(geotrDest!=geoNULL);
	if ( IsNotNull(*geotrDest) )
	{
		ClearStr(geotrDest);
	}
	if (strSource)
	{
		RET_ERR(NewAndCopyStr(geotrDest,strSource));
	}
	return geoRET_SUCC;
}

__inline geoBool IsVariantVariable(geoVariant* pVariant)
{
	return (pVariant->vType == vTypeAString ||
		pVariant->vType == vTypeWString ||
		pVariant->vType == vTypeString ||
		pVariant->vType == vTypeBlob);
}

__inline geoBool IsVariantFixed(geoVariant* pVariant)
{
	return (!IsVariantVariable(pVariant));
}

__inline void ClearVariant(geoVariant* pVariant)
{
	GEO_ASSERT(pVariant!=geoNULL);
	if (IsVariantVariable(pVariant) && (pVariant->vBlob.Length!=0))
	{
		GEO_ASSERT(pVariant->vBlob.Data!=geoNULL);
		free(pVariant->vBlob.Data);
	}
	memset(pVariant,0,sizeof(geoVariant));
}

__inline void FreeVariant(geoVariant** ppVariant)
{
	if (ppVariant==geoNULL)
	{
		return;
	}
	if (*ppVariant==geoNULL)
	{
		return;
	}
	ClearVariant(*ppVariant);
	FreeAndNull((void**)ppVariant);
}



//=========================================================================
// 
// StrList结构体的序列化、反序列化等功能定义
// 字段串列表
// 
//=========================================================================

__inline void ClearStrList(geoStringList* geotrList)
{
	if (geotrList==geoNULL)
	{
		return ;
	}

	geoUInt32 i;
	geoStr* p;
	if (geotrList->Count>0)
	{
		for (i=0;i<geotrList->Count;++i)
		{
			p = geotrList->List+i;
			ClearStr(p);
		}
		free(geotrList->List);
	}

	memset(geotrList,0,sizeof(geoStringList));
}
//ce
__inline void FreeStrList(geoStringList** pgeotrList)
{
	if (pgeotrList==geoNULL)
	{
		return;
	}
	if (*pgeotrList==geoNULL)
	{
		return;
	}
	ClearStrList(*pgeotrList);
	free(*pgeotrList);
	*pgeotrList = geoNULL;
}

__inline geoAPIStatus NewStrList(geoStringList** pgeotrList)
{
	return NewAndClear((geoVoid**)pgeotrList,(geoUInt32)sizeof(geoStringList));
}

__inline geoAPIStatus NewStrListEx(geoStringList **pgeotrList,geoUInt32 nCount)
{

	GEO_ASSERT(pgeotrList!=geoNULL);
	GEO_ASSERT(*pgeotrList==geoNULL);
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(NewAndClear((geoVoid**)pgeotrList,sizeof(geoStringList)));
	geoStringList* geotrList = *pgeotrList;
	geotrList->Count = nCount;
	nRet=(NewAndClear((geoVoid**)&(geotrList->List),sizeof(geoStr)*nCount));
	if (geoErr(nRet))
	{
		FreeStrList(pgeotrList);
		return nRet;
	}
	return nRet;
}

//
//
////=========================================================================
//// 
//// PropValue结构体的序列化、反序列化等功能定义
//// 单个属性的值
//// 
////=========================================================================
//
//__inline void ClearPropValue(geoPropValue* pPropValue)
//{
//	if (pPropValue==geoNULL)
//	{
//		return ;
//	}
//
//	ClearVariant(&(pPropValue->Value));
//
//	memset(pPropValue,0,sizeof(geoPropValue));
//}
//
//__inline void FreePropValue(geoPropValue** ppPropValue)
//{
//	if (ppPropValue==geoNULL)
//	{
//		return;
//	}
//	if (*ppPropValue==geoNULL)
//	{
//		return;
//	}
//	ClearPropValue(*ppPropValue);
//	free(*ppPropValue);
//	*ppPropValue = geoNULL;
//}
//
//__inline geoAPIStatus NewPropValue(geoPropValue** ppPropValue)
//{
//	return NewAndClear((geoVoid**)ppPropValue,(geoUInt32)sizeof(geoPropValue));
//}
//
//
////=========================================================================
//// 
//// PropValueList结构体的序列化、反序列化等功能定义
//// 属性值列表
//// 
////=========================================================================
//
//__inline void ClearPropValueList(geoPropValueList* pPropValueList)
//{
//	if (pPropValueList==geoNULL)
//	{
//		return ;
//	}
//
//	geoUInt16 i;
//	geoPropValue* p;
//	if (pPropValueList->PropCount>0)
//	{
//		for (i=0;i<pPropValueList->PropCount;++i)
//		{
//			p = pPropValueList->PropValueList+i;
//			ClearPropValue(p);
//		}
//		free(pPropValueList->PropValueList);
//	}
//
//	memset(pPropValueList,0,sizeof(geoPropValueList));
//}
////ce
//__inline void FreePropValueList(geoPropValueList** ppPropValueList)
//{
//	if (ppPropValueList==geoNULL)
//	{
//		return;
//	}
//	if (*ppPropValueList==geoNULL)
//	{
//		return;
//	}
//	ClearPropValueList(*ppPropValueList);
//	free(*ppPropValueList);
//	*ppPropValueList = geoNULL;
//}
//
//__inline geoAPIStatus NewPropValueList(geoPropValueList** ppPropValueList)
//{
//	return NewAndClear((geoVoid**)ppPropValueList,(geoUInt32)sizeof(geoPropValueList));
//}
////ce
//__inline geoAPIStatus NewPropValueListEx(geoPropValueList **ppPropValueList,geoUInt16 nCount)
//{
//	geoAPIStatus nRet = geoRET_SUCC;
//
//	GEO_ASSERT(ppPropValueList!=geoNULL);
//	GEO_ASSERT(*ppPropValueList==geoNULL);
//
//	RET_ERR(NewAndClear((geoVoid**)ppPropValueList,sizeof(geoPropValueList)));
//	geoPropValueList* pPropValueList = *ppPropValueList;
//	pPropValueList->PropCount = nCount;
//	nRet = NewAndClear((geoVoid**)&(pPropValueList->PropValueList),sizeof(geoPropValue)*nCount);
//	if(geoErr(nRet))
//	{
//		FreePropValueList(ppPropValueList);
//	}
//	return nRet;
//}


//=========================================================================
// 
// APIStatusList结构体的序列化、反序列化等功能定义
// 返回状态列表
// 
//=========================================================================

__inline void ClearAPIStatusList(geoAPIStatusList* pAPIStatusList)
{
	if (pAPIStatusList==geoNULL)
	{
		return ;
	}

	free(pAPIStatusList->List);


	memset(pAPIStatusList,0,sizeof(geoAPIStatusList));
}

__inline void FreeAPIStatusList(geoAPIStatusList** ppAPIStatusList)
{
	if (ppAPIStatusList==geoNULL)
	{
		return;
	}
	if (*ppAPIStatusList==geoNULL)
	{
		return;
	}
	ClearAPIStatusList(*ppAPIStatusList);
	free(*ppAPIStatusList);
	*ppAPIStatusList = geoNULL;
}

__inline geoAPIStatus NewAPIStatusList(geoAPIStatusList** ppAPIStatusList)
{
	return NewAndClear((geoVoid**)ppAPIStatusList,(geoUInt32)sizeof(geoAPIStatusList));
}

__inline geoAPIStatus NewAPIStatusListEx(geoAPIStatusList **ppAPIStatusList,geoUInt32 nCount)
{
	geoAPIStatus nRet = geoRET_SUCC;

	GEO_ASSERT(ppAPIStatusList!=geoNULL);
	GEO_ASSERT(*ppAPIStatusList==geoNULL);

	RET_ERR(NewAndClear((geoVoid**)ppAPIStatusList,sizeof(geoAPIStatusList)));
	geoAPIStatusList* pAPIStatusList = *ppAPIStatusList;
	pAPIStatusList->Count = nCount;
	nRet = NewAndClear((geoVoid**)&(pAPIStatusList->List),sizeof(geoAPIStatus)*nCount);
	if (geoErr(nRet))
	{
		FreeAPIStatusList(ppAPIStatusList);
	}
	return nRet;
}
//
//
////=========================================================================
//// 
//// TagIdList结构体的序列化、反序列化等功能定义
//// 测点ID列表
//// 
////=========================================================================
//
//__inline void ClearTagIdList(geoTagIdList* pTagIdList)
//{
//	if (pTagIdList==geoNULL)
//	{
//		return ;
//	}
//
//	free(pTagIdList->TagIdList);
//
//
//	memset(pTagIdList,0,sizeof(geoTagIdList));
//}
////ce
//__inline void FreeTagIdList(geoTagIdList** ppTagIdList)
//{
//	if (ppTagIdList==geoNULL)
//	{
//		return;
//	}
//	if (*ppTagIdList==geoNULL)
//	{
//		return;
//	}
//	ClearTagIdList(*ppTagIdList);
//	free(*ppTagIdList);
//	*ppTagIdList = geoNULL;
//}
////ce
//__inline geoAPIStatus NewTagIdList(geoTagIdList** ppTagIdList)
//{
//	return NewAndClear((geoVoid**)ppTagIdList,(geoUInt32)sizeof(geoTagIdList));
//}
////ce
//__inline geoAPIStatus NewTagIdListEx(geoTagIdList **ppTagIdList,geoUInt32 nCount)
//{
//	geoAPIStatus nRet = geoRET_SUCC;
//
//	GEO_ASSERT(ppTagIdList!=geoNULL);
//	GEO_ASSERT(*ppTagIdList==geoNULL);
//
//	RET_ERR(NewAndClear((geoVoid**)ppTagIdList,sizeof(geoTagIdList)));
//	geoTagIdList* pTagIdList = *ppTagIdList;
//	pTagIdList->TagCount = nCount;
//	nRet = NewAndClear((geoVoid**)&(pTagIdList->TagIdList),sizeof(geoUInt32)*nCount);
//	if (geoErr(nRet))
//	{
//		FreeTagIdList(ppTagIdList);
//	}
//	return nRet;
//}
//
//
//
////=========================================================================
//// 
//// PropIdList结构体的序列化、反序列化等功能定义
//// 属性ID列表
//// 
////=========================================================================
//
//__inline void ClearPropIdList(geoPropIdList* pPropIdList)
//{
//	if (pPropIdList==geoNULL)
//	{
//		return ;
//	}
//
//	free(pPropIdList->PropIdList);
//
//
//	memset(pPropIdList,0,sizeof(geoPropIdList));
//}
//
//__inline void FreePropIdList(geoPropIdList** ppPropIdList)
//{
//	if (ppPropIdList==geoNULL)
//	{
//		return;
//	}
//	if (*ppPropIdList==geoNULL)
//	{
//		return;
//	}
//	ClearPropIdList(*ppPropIdList);
//	free(*ppPropIdList);
//	*ppPropIdList = geoNULL;
//}
//
//__inline geoAPIStatus NewPropIdList(geoPropIdList** ppPropIdList)
//{
//	return NewAndClear((geoVoid**)ppPropIdList,(geoUInt32)sizeof(geoPropIdList));
//}
//
//__inline geoAPIStatus NewPropIdListEx(geoPropIdList **ppPropIdList,geoUInt16 nCount)
//{
//	geoAPIStatus nRet = geoRET_SUCC;
//
//	GEO_ASSERT(ppPropIdList!=geoNULL);
//	GEO_ASSERT(*ppPropIdList==geoNULL);
//
//	RET_ERR(NewAndClear((geoVoid**)ppPropIdList,sizeof(geoPropIdList)));
//	geoPropIdList* pPropIdList = *ppPropIdList;
//	pPropIdList->PropCount = nCount;
//	nRet = NewAndClear((geoVoid**)&(pPropIdList->PropIdList),sizeof(geoUInt16)*nCount);
//	if (geoErr(nRet))
//	{
//		FreePropIdList(ppPropIdList);
//	}
//	return nRet;
//}

//=========================================================================
// 
// ValueList结构体的序列化、反序列化等功能定义
// 值列表
// 
//=========================================================================

__inline void ClearValueList(geoValueList* pValueList)
{
	if (pValueList==geoNULL)
	{
		return ;
	}

	geoUInt32 i;
	geoVariant* p;
	if (pValueList->ValueCount>0)
	{
		for (i=0;i<pValueList->ValueCount;++i)
		{
			p = pValueList->ValueList+i;
			ClearVariant(p);
		}
		free(pValueList->ValueList);
	}

	memset(pValueList,0,sizeof(geoValueList));
}

__inline void FreeValueList(geoValueList** ppValueList)
{
	if (ppValueList==geoNULL)
	{
		return;
	}
	if (*ppValueList==geoNULL)
	{
		return;
	}
	ClearValueList(*ppValueList);
	free(*ppValueList);
	*ppValueList = geoNULL;
}

__inline geoAPIStatus NewValueList(geoValueList** ppValueList)
{
	return NewAndClear((geoVoid**)ppValueList,(geoUInt32)sizeof(geoValueList));
}

__inline geoAPIStatus NewValueListEx(geoValueList **ppValueList,geoUInt32 nCount)
{
	geoAPIStatus nRet = geoRET_SUCC;

	GEO_ASSERT(ppValueList!=geoNULL);
	GEO_ASSERT(*ppValueList==geoNULL);

	RET_ERR(NewAndClear((geoVoid**)ppValueList,sizeof(geoValueList)));
	geoValueList* pValueList = *ppValueList;
	pValueList->ValueCount = nCount;
	nRet = NewAndClear((geoVoid**)&(pValueList->ValueList),sizeof(geoVariant)*nCount);
	if(geoErr(nRet))
	{
		FreeValueList(ppValueList);
	}
	return nRet;
}

//=========================================================================
// 
// Data结构体的序列化、反序列化等功能定义
// 数据记录定义
// 
//=========================================================================

__inline void ClearData(geoData* pData)
{
	if (pData==geoNULL)
	{
		return ;
	}

	ClearVariant(&(pData->Value));

	memset(pData,0,sizeof(geoData));
}

__inline void FreeData(geoData** ppData)
{
	if (ppData==geoNULL)
	{
		return;
	}
	if (*ppData==geoNULL)
	{
		return;
	}
	ClearData(*ppData);
	free(*ppData);
	*ppData = geoNULL;
}

__inline geoAPIStatus NewData(geoData** ppData)
{
	return NewAndClear((geoVoid**)ppData,(geoUInt32)sizeof(geoData));
}



//=========================================================================
// 
// DataList结构体的序列化、反序列化等功能定义
// 数据记录列表
// 
//=========================================================================

__inline void ClearDataList(geoDataList* pDataList)
{
	if (pDataList==geoNULL)
	{
		return ;
	}

	geoUInt32 i;
	geoData* p;
	if (pDataList->DataCount>0)
	{
		for (i=0;i<pDataList->DataCount;++i)
		{
			p = pDataList->DataList+i;
			ClearData(p);
		}
		free(pDataList->DataList);
	}

	memset(pDataList,0,sizeof(geoDataList));
}
//free字符串有问题
__inline void FreeDataList(geoDataList** ppDataList)
{
	if (ppDataList==geoNULL)
	{
		return;
	}
	if (*ppDataList==geoNULL)
	{
		return;
	}
	ClearDataList(*ppDataList);
	free(*ppDataList);
	*ppDataList = geoNULL;
}

__inline geoAPIStatus NewDataList(geoDataList** ppDataList)
{
	return NewAndClear((geoVoid**)ppDataList,(geoUInt32)sizeof(geoDataList));
}

__inline geoAPIStatus NewDataListEx(geoDataList **ppDataList,geoUInt32 nCount)
{
	geoAPIStatus nRet = geoRET_SUCC;

	GEO_ASSERT(ppDataList!=geoNULL);
	GEO_ASSERT(*ppDataList==geoNULL);

	RET_ERR(NewAndClear((geoVoid**)ppDataList,sizeof(geoDataList)));
	geoDataList* pDataList = *ppDataList;
	pDataList->DataCount = nCount;
	nRet = NewAndClear((geoVoid**)&(pDataList->DataList),sizeof(geoData)*nCount);
	if(geoErr(nRet))
	{
		FreeDataList(ppDataList);
	}
	return nRet;
}


//
////=========================================================================
//// 
//// TagRealData结构体的序列化、反序列化等功能定义
//// 测点实时值
//// 
////=========================================================================
//
//__inline void ClearTagRealData(geoRealData* pTagRealData)
//{
//	if (pTagRealData==geoNULL)
//	{
//		return ;
//	}
//
//	ClearData(&(pTagRealData->RealData));
//
//	memset(pTagRealData,0,sizeof(geoRealData));
//}
//
//__inline void FreeTagRealData(geoRealData** ppTagRealData)
//{
//	if (ppTagRealData==geoNULL)
//	{
//		return;
//	}
//	if (*ppTagRealData==geoNULL)
//	{
//		return;
//	}
//	ClearTagRealData(*ppTagRealData);
//	free(*ppTagRealData);
//	*ppTagRealData = geoNULL;
//}
//
//__inline geoAPIStatus NewTagRealData(geoRealData** ppTagRealData)
//{
//	return NewAndClear((geoVoid**)ppTagRealData,(geoUInt32)sizeof(geoRealData));
//}
//
//
//
////=========================================================================
//// 
//// TagListRealData结构体的序列化、反序列化等功能定义
//// 多个测点值列表
//// 
////=========================================================================
//
//__inline void ClearRealDataList(geoRealDataList* pTagListRealData)
//{
//	if (pTagListRealData==geoNULL)
//	{
//		return ;
//	}
//
//	geoUInt32 i;
//	geoRealData* p;
//	if (pTagListRealData->TagCount>0)
//	{
//		for (i=0;i<pTagListRealData->TagCount;++i)
//		{
//			p = pTagListRealData->TagListRealData+i;
//			ClearTagRealData(p);
//		}
//		free(pTagListRealData->TagListRealData);
//	}
//
//	memset(pTagListRealData,0,sizeof(geoRealDataList));
//}
//
//__inline void FreeRealDataList(geoRealDataList** ppTagListRealData)
//{
//	if (ppTagListRealData==geoNULL)
//	{
//		return;
//	}
//	if (*ppTagListRealData==geoNULL)
//	{
//		return;
//	}
//	ClearRealDataList(*ppTagListRealData);
//	free(*ppTagListRealData);
//	*ppTagListRealData = geoNULL;
//}
//
//__inline geoAPIStatus NewRealDataList(geoRealDataList** ppTagListRealData)
//{
//	return NewAndClear((geoVoid**)ppTagListRealData,(geoUInt32)sizeof(geoRealDataList));
//}
//
//__inline geoAPIStatus NewRealDataListEx(geoRealDataList **ppTagListRealData,geoUInt32 nCount)
//{
//	geoAPIStatus nRet = geoRET_SUCC;
//
//	GEO_ASSERT(ppTagListRealData!=geoNULL);
//	GEO_ASSERT(*ppTagListRealData==geoNULL);
//
//	RET_ERR(NewAndClear((geoVoid**)ppTagListRealData,sizeof(geoRealDataList)));
//	geoRealDataList* pTagListRealData = *ppTagListRealData;
//	pTagListRealData->TagCount = nCount;
//	nRet = NewAndClear((geoVoid**)&(pTagListRealData->TagListRealData),sizeof(geoRealData)*nCount);
//	if(geoErr(nRet))
//	{
//		FreeRealDataList(ppTagListRealData);
//	}
//
//	return nRet;
//}


//=========================================================================
// 
// ReconList结构体的序列化、反序列化等功能定义
// 测点ID列表
// 
//=========================================================================

__inline void ClearReconList(geoRecnoList * pReconList)
{
	if (pReconList==geoNULL)
	{
		return ;
	}

	free(pReconList->RecnoList);


	memset(pReconList,0,sizeof(geoRecnoList));
}
//ce
__inline void FreeReconList(geoRecnoList** ppReconList)
{
	if (ppReconList==geoNULL)
	{
		return;
	}
	if (*ppReconList==geoNULL)
	{
		return;
	}
	ClearReconList(*ppReconList);
	free(*ppReconList);
	*ppReconList = geoNULL;
}
//ce
__inline geoAPIStatus NewReconList(geoRecnoList** ppReconList)
{
	return NewAndClear((geoVoid**)ppReconList,(geoUInt32)sizeof(geoRecnoList));
}
//ce
__inline geoAPIStatus NewReconListEx(geoRecnoList **ppReconList,geoUInt32 nCount)
{
	geoAPIStatus nRet = geoRET_SUCC;

	GEO_ASSERT(ppReconList!=geoNULL);
	GEO_ASSERT(*ppReconList==geoNULL);

	RET_ERR(NewAndClear((geoVoid**)ppReconList,sizeof(geoRecnoList)));
	geoRecnoList* pReconList = *ppReconList;
	pReconList-> RecnoCount= nCount;
	nRet = NewAndClear((geoVoid**)&(pReconList->RecnoList),sizeof(geoUInt32)*nCount);
	if (geoErr(nRet))
	{
		FreeReconList(ppReconList);
	}
	return nRet;
}

//
////=========================================================================
//// 
//// NameId结构体的序列化、反序列化等功能定义
//// 
////=========================================================================
//
//__inline void ClearNameId(geoNameId* pNameId)
//{
//	if (pNameId==geoNULL)
//	{
//		return ;
//	}
//
//	ClearStr(&(pNameId->TagName));
//
//	memset(pNameId,0,sizeof(geoNameId));
//}
//
//__inline void FreeNameId(geoNameId** ppNameId)
//{
//	if (ppNameId==geoNULL)
//	{
//		return;
//	}
//	if (*ppNameId==geoNULL)
//	{
//		return;
//	}
//	ClearNameId(*ppNameId);
//	free(*ppNameId);
//	*ppNameId = geoNULL;
//}
//
//__inline geoAPIStatus NewNameId(geoNameId** ppNameId)
//{
//	return NewAndClear((geoVoid**)ppNameId,(geoUInt32)sizeof(geoNameId));
//}
//
////=========================================================================
//// 
//// NameIdList结构体的序列化、反序列化等功能定义
//// 
////=========================================================================
//
//__inline void ClearNameIdList(geoNameIdList* pNameIdList)
//{
//	if (pNameIdList==geoNULL)
//	{
//		return ;
//	}
//
//	geoUInt32 i;
//	geoNameId* p;
//	if (pNameIdList->NameCount>0)
//	{
//		for (i=0;i<pNameIdList->NameCount;++i)
//		{
//			p = pNameIdList->NameList+i;
//			ClearNameId(p);
//		}
//		free(pNameIdList->NameList);
//	}
//
//	memset(pNameIdList,0,sizeof(geoNameIdList));
//}
//
//__inline void FreeNameIdList(geoNameIdList** ppNameIdList)
//{
//	if (ppNameIdList==geoNULL)
//	{
//		return;
//	}
//	if (*ppNameIdList==geoNULL)
//	{
//		return;
//	}
//	ClearNameIdList(*ppNameIdList);
//	free(*ppNameIdList);
//	*ppNameIdList = geoNULL;
//}
//
//__inline geoAPIStatus NewNameIdList(geoNameIdList** ppNameIdList)
//{
//	return NewAndClear((geoVoid**)ppNameIdList,(geoUInt32)sizeof(geoNameIdList));
//}
////ce
//__inline geoAPIStatus NewNameIdListEx(geoNameIdList **ppNameIdList,geoUInt32 nCount)
//{
//	geoAPIStatus nRet = geoRET_SUCC;
//
//	GEO_ASSERT(ppNameIdList!=geoNULL);
//	GEO_ASSERT(*ppNameIdList==geoNULL);
//
//	RET_ERR(NewAndClear((geoVoid**)ppNameIdList,sizeof(geoNameIdList)));
//	geoNameIdList* pNameIdList = *ppNameIdList;
//	pNameIdList->NameCount = nCount;
//	nRet = NewAndClear((geoVoid**)&(pNameIdList->NameList),sizeof(geoNameId)*nCount);
//	if(geoErr(nRet))
//	{
//		FreeNameIdList(ppNameIdList);
//	}
//	return nRet;
//}


#endif
