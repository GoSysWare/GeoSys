#ifndef	LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif
#include <assert.h>
#include "preCompile.h"
#include "geoVariant.h"
#include "geoError.h"
#include "geoBasicType.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//
#define  DOUBLE_EXCEPTION			0.0001
#define  PSVARIANT_SIZE				sizeof(geoVariant)
#define  UINT32_SIZE				sizeof(geoUInt32)
#define  DOUBLE_SIZE				sizeof(geoDouble)
#define  FLOAT_SIZE					sizeof(geoFloat)
typedef geoBool (*PSVAEIANT_EQUAL)(geoVariant*,geoVariant*);
typedef geoAPIStatus (*VARIANT_CHANGETYPE)(geoVariant*);
#pragma warning(disable:4244 4996)



geoAPIStatus NewMemory(void** ppDest, geoUInt32 nSize)
{

	*ppDest = geoNULL;
	*ppDest = malloc(nSize);
	if (*ppDest==geoNULL)
	{
		return geoERR_COMMON_NO_MEMORY;
	}
	return geoRET_SUCC;
}

 geoAPIStatus NewAndClear(void** ppDest, geoUInt32 nSize)
{
	if (geoErr(NewMemory(ppDest,nSize)))
	{
		return geoERR_COMMON_NO_MEMORY;
	}
	memset(*ppDest,0,nSize);
	return geoRET_SUCC;
}

 void FreeAndNull(void** ppDest)
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

 void FreeStr(geoStr* pStr)
{
	FreeAndNull((void**)pStr);
}

 void ClearStr(geoStr* pStr)
{
	if (*pStr!=geoNULL)
	{
		free(*pStr);
	}
	*pStr = geoNULL;
}

 void ClearStr(geoStr pStr)
{
	ClearStr(&pStr);
}

 geoAPIStatus NewAndCopyStr(geoStr* geotrDest,const geoChar * strSource)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(NewMemory((geoVoid**)geotrDest,
		(geoUInt32)(strlen(strSource)+1)*sizeof(geoChar)));  /*修改原因:定义unique情况下申请空间长度不够*/
	strcpy(*geotrDest,strSource);
	return geoRET_SUCC;
}

 geoAPIStatus NewAndCopyUStr(geoWStr* geotrDest,const geoWChar * strSource)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(NewMemory((geoVoid**)geotrDest,
		(geoUInt32)(strlen((const geoChar *)strSource)+1)*sizeof(geoWChar)));  /*修改原因:定义unique情况下申请空间长度不够*/
	wcscpy((wchar_t *)*geotrDest,(const wchar_t *)strSource);
	return geoRET_SUCC;
}

 geoAPIStatus geoStrRplace (geoStr* geotrDest,geoStr strSource)
{
	geoAPIStatus nRet = geoRET_SUCC;
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

 geoBool IsVariantVariable(geoVariant* pVariant)
{
	return (pVariant->vType == vTypeAString ||
		pVariant->vType == vTypeWString ||
		pVariant->vType == vTypeString ||
		pVariant->vType == vTypeBlob);
}

 geoBool IsVariantFixed(geoVariant* pVariant)
{
	return (!IsVariantVariable(pVariant));
}

 void ClearVariant(geoVariant* pVariant)
{
	if (IsVariantVariable(pVariant) && (pVariant->vBlob.Length!=0))
	{
	//	ACE_ASSERT(pVariant->vBlob.Data!=geoNULL);
		free(pVariant->vBlob.Data);
	}
	memset(pVariant,0,sizeof(geoVariant));
}

 void FreeVariant(geoVariant** ppVariant)
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





//////////////////////////////////////////////////////////////////////////
///以下为内部函数
//////////////////////////////////////////////////////////////////////////

static  geoBool  Bool_Equal(geoVariant *pFirst, geoVariant *pSecond)
{

	return ((pFirst->vBool) == (pSecond->vBool)) ? geoTRUE : geoFALSE;
}

static  geoBool  Int8_Equal(geoVariant *pFirst, geoVariant *pSecond)
{

	return ((pFirst->vInt8) == (pSecond->vInt8)) ? geoTRUE : geoFALSE;
}

static  geoBool  UInt8_Equal(geoVariant *pFirst, geoVariant *pSecond)
{
	// 与上面一样
	return ((pFirst->vUInt8) == (pSecond->vUInt8)) ? geoTRUE : geoFALSE;
}

static  geoBool  Int16_Equal(geoVariant *pFirst, geoVariant *pSecond)
{
	return (pFirst->vInt16 == pSecond->vInt16) ? geoTRUE : geoFALSE;
}

static  geoBool  UInt16_Equal(geoVariant *pFirst, geoVariant *pSecond)
{
	return (pFirst->vUInt16 == pSecond->vUInt16) ? geoTRUE : geoFALSE;
}

static  geoBool  Int32_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return (pFirst->vInt32==pSecond->vInt32) ? geoTRUE : geoFALSE;
}

static  geoBool  UInt32_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return (pFirst->vUInt32 == pSecond->vUInt32) ? geoTRUE : geoFALSE;
}

static  geoBool  Int64_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return (pFirst->vInt64==pSecond->vInt64) ? geoTRUE : geoFALSE;
}

static  geoBool  UInt64_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return (pFirst->vUInt64==pSecond->vUInt64) ? geoTRUE : geoFALSE;
}

static  geoBool  Float_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return fabs(pFirst->vFloat - pSecond->vFloat)<DOUBLE_EXCEPTION ? geoTRUE : geoFALSE;
}

static geoBool  Double_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return fabs(pFirst->vDouble - pSecond->vDouble) <DOUBLE_EXCEPTION ? geoTRUE : geoFALSE;
}

static geoBool  AnsiString_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return (pFirst->vAString.Length == pSecond->vAString.Length
		&& !strcmp(pFirst->vAString.Data,pSecond->vAString.Data)
		) ? geoTRUE : geoFALSE;
}

static geoBool  String_Equal(geoVariant*pFirst, geoVariant *pSecond)
{
	return(
		pFirst->vString.Length == pSecond->vString.Length
		&& !strcmp(pFirst->vString.Data,pSecond->vString.Data)
		) ? geoTRUE : geoFALSE;
}

static geoBool  UgeoodeString_Equal(geoVariant*pFirst, geoVariant *pSecond)
{

	return (
		pFirst->vWString.Length == pSecond->vWString.Length
		&&!wcscmp((wchar_t*)(pFirst->vWString.Data),
		(wchar_t*)(pSecond->vWString.Data))
		) ? geoTRUE : geoFALSE;

}

static geoBool  Time_Equal(geoVariant*pFirst, geoVariant *pSecond)
{

	return (pFirst->vTimeStamp == pSecond->vTimeStamp) ? geoTRUE : geoFALSE;
}
static geoBool  Blob_Equal(geoVariant *pFirst, geoVariant *pSecond)
{
	return (
		pFirst->vBlob.Length == pSecond->vBlob.Length
		&&memcmp(pFirst->vBlob.Data,pSecond->vBlob.Data,pFirst->vBlob.Length)
		) ? geoTRUE : geoFALSE;
}

// 此函数是防止转移表中出现空指针而设立的，没有实际功能
static geoBool  Equal_ErrorType(geoVariant *pFirst, geoVariant *pSecond)
{
	GEO_UNUSED_ARG(pFirst);
	GEO_UNUSED_ARG(pSecond);
	return geoFALSE;
}
//此函数是防止转移表中出现空指针而设立的，没有实际功能
static geoAPIStatus changto_ErrorType(geoVariant* var)
{
	GEO_UNUSED_ARG(var);
	return geoERR_COMMON_DATATYPE;
}
static geoAPIStatus changto_Bool(geoVariant* var)
{
	geoBool tempbool=geoTRUE;
	switch (var->vType)
	{
	case vTypeBool: 
		return geoRET_SUCC;
	case vTypeInt8 :
		tempbool=var->vInt8 !=0;
		break;
	case vTypeUInt8 :
		tempbool=var->vUInt8 !=0;
		break;
	case vTypeInt16 :
		tempbool=var->vInt16!=0;
		break;
	case vTypeUInt16 :
		tempbool=var->vUInt16!=0;
		break;
	case vTypeInt32 :
		tempbool=var->vInt32!=0;
		break;
	case vTypeUInt32 :	
		tempbool=var->vUInt32!=0;
		break;
	case vTypeInt64 :
		tempbool=var->vInt64!=0;
		break;
	case vTypeUInt64 :	
		tempbool=var->vUInt64!=0;
		break;
	case vTypeFloat :
		tempbool=var->vFloat!=0;
		break;
	case vTypeDouble :	
		tempbool=var->vDouble!=0;
		break;
	case vTypeTimeStamp :
		tempbool=var->vTimeStamp !=0;
		break;
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vBool=tempbool;
	var->vType=vTypeBool;
	return geoRET_SUCC;
}

static geoAPIStatus changto_Int8(geoVariant* var)
{
	geoInt8 tempint8=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempint8=var->vBool;
		break;
	case vTypeInt8 :
		tempint8=var->vInt8 ;
		break;
	case vTypeUInt8 :
		if (var->vUInt8>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vUInt8;
		break;
	case vTypeInt16 :
		if (var->vInt16<SCHAR_MIN||var->vInt16>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vInt16;
		break;
	case vTypeUInt16 :
		if (var->vUInt16<SCHAR_MIN||var->vUInt16>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vUInt16;
		break;
	case vTypeInt32 :
		if (var->vInt32<SCHAR_MIN||var->vInt32>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vInt32;
		break;
	case vTypeUInt32 :	
		if (var->vUInt32<SCHAR_MIN||var->vUInt32>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vUInt32;
		break;
	case vTypeInt64 :
		if (var->vInt64<SCHAR_MIN||var->vInt64>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vInt64;
		break;
	case vTypeUInt64 :	
		if (var->vUInt64<SCHAR_MIN||var->vUInt64>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vUInt64;
		break;
	case vTypeFloat :
		if (var->vFloat<SCHAR_MIN||var->vFloat>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<SCHAR_MIN||var->vDouble>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vInt8=tempint8;
	var->vType=vTypeInt8;
	return geoRET_SUCC;
}

static geoAPIStatus changto_UInt8(geoVariant* var)
{
	geoUInt8 tempint8=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempint8=var->vBool;
		break;
	case vTypeInt8 :
		if (var->vInt8<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vInt8;
		break;
	case vTypeUInt8 :
		return geoRET_SUCC;
	case vTypeInt16 :
		if (var->vInt16<0||var->vInt16>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vInt16;
		break;
	case vTypeUInt16 :
		if (var->vUInt16>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vUInt16;
		break;
	case vTypeInt32 :
		if (var->vInt32<0||var->vInt32>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vInt32;
		break;
	case vTypeUInt32 :	
		if (var->vUInt32>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vUInt32;
		break;
	case vTypeInt64 :
		if (var->vInt64<0||var->vInt64>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vInt64;
		break;
	case vTypeUInt64 :	
		if (var->vUInt64>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vUInt64;
		break;
	case vTypeFloat :
		if (var->vFloat<0||var->vFloat>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<0||var->vDouble>UCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint8=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vUInt8=tempint8;
	var->vType=vTypeUInt8;
	return geoRET_SUCC;
}
static geoAPIStatus changto_Int16(geoVariant* var)
{
	geoInt16 tempint16=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempint16=var->vBool;
		break;
	case vTypeInt8 :
		tempint16=var->vInt8 ;
		break;
	case vTypeUInt8 :
		tempint16=var->vUInt8;
		break;
	case vTypeInt16 :
		return geoRET_SUCC;
	case vTypeUInt16 :
		if (var->vUInt16>SHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint16=var->vUInt16;
		break;
	case vTypeInt32 :
		if (var->vInt32<SHRT_MIN||var->vInt32>SHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint16=var->vInt32;
		break;
	case vTypeUInt32 :	
		if (var->vUInt32>SHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint16=var->vUInt32;
		break;
	case vTypeInt64 :
		if (var->vInt64<SCHAR_MIN||var->vInt64>SCHAR_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint16=var->vInt64;
		break;
	case vTypeUInt64 :	
		if (var->vUInt64<SHRT_MIN||var->vUInt64>SHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint16=var->vUInt64;
		break;
	case vTypeFloat :
		if (var->vFloat<SHRT_MIN||var->vFloat>SHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint16=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<SHRT_MIN||var->vDouble>SHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint16=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vInt16=tempint16;
	var->vType=vTypeInt16;
	return geoRET_SUCC;
}
static geoAPIStatus changto_UInt16(geoVariant* var)
{
	geoUInt16 tempuint16=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempuint16=var->vBool;
		break;
	case vTypeInt8 :
		if (var->vInt8<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vInt8;
		break;
	case vTypeUInt8 :
		tempuint16=var->vUInt8;
		break;
	case vTypeInt16 :
		if (var->vInt16<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vInt16;
		break;
	case vTypeUInt16 :
		return geoRET_SUCC;
	case vTypeInt32 :
		if (var->vInt32<0||var->vInt32>SHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vInt32;
		break;
	case vTypeUInt32 :	
		if (var->vUInt32>USHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vUInt32;
		break;
	case vTypeInt64 :
		if (var->vInt64<0||var->vInt64>USHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vInt64;
		break;
	case vTypeUInt64 :	
		if (var->vUInt64>USHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vUInt64;
		break;
	case vTypeFloat :
		if (var->vFloat<0||var->vFloat>USHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<0||var->vDouble>USHRT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint16=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vUInt16=tempuint16;
	var->vType=vTypeUInt16;
	return geoRET_SUCC;
}


static geoAPIStatus changto_Int32(geoVariant* var)
{
	geoInt32 tempint32=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempint32=var->vBool;
		break;
	case vTypeInt8 :
		tempint32=var->vInt8 ;
		break;
	case vTypeUInt8 :
		tempint32=var->vUInt8;
		break;
	case vTypeInt16 :
		tempint32=var->vInt16;
		break;
	case vTypeUInt16 :
		tempint32=var->vUInt16;
		break;
	case vTypeInt32 :
		return geoRET_SUCC;
	case vTypeUInt32 :	
		if (var->vUInt32>INT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint32=var->vUInt32;
		break;
	case vTypeInt64 :
		if (var->vInt64<INT_MIN||var->vInt64>INT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint32=var->vInt64;
		break;
	case vTypeUInt64 :	
		if (var->vUInt64>INT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint32=var->vUInt64;
		break;
	case vTypeFloat :
		if (var->vFloat<INT_MIN||var->vFloat>INT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint32=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<INT_MIN||var->vDouble>INT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint32=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vInt32=tempint32;
	var->vType=vTypeInt32;
	return geoRET_SUCC;
}
static geoAPIStatus changto_UInt32(geoVariant* var)
{
	geoUInt32 tempuint32=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempuint32=var->vBool;
		break;
	case vTypeInt8 :
		if (var->vInt8<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint32=var->vInt8;
		break;
	case vTypeUInt8 :
		tempuint32=var->vUInt8;
		break;
	case vTypeInt16 :
		if (var->vInt16<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint32=var->vInt16;
		break;
	case vTypeUInt16 :
		tempuint32=var->vUInt16;
		break;
	case vTypeInt32 :
		if (var->vInt32<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint32=var->vInt32;
		break;
	case vTypeUInt32 :	
		return geoRET_SUCC;
	case vTypeInt64 :
		if (var->vInt64<0||var->vInt64>UINT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint32=var->vInt64;
		break;
	case vTypeUInt64 :	
		if (var->vUInt64>UINT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint32=var->vUInt64;
		break;
	case vTypeFloat :
		if (var->vFloat<0||var->vFloat>UINT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint32=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<0||var->vDouble>UINT_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint32=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vUInt32=tempuint32;
	var->vType=vTypeUInt32;
	return geoRET_SUCC;
}

static geoAPIStatus changto_Int64(geoVariant* var)
{
	geoInt64 tempint64=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempint64=var->vBool;
		break;
	case vTypeInt8 :
		tempint64=var->vInt8 ;
		break;
	case vTypeUInt8 :
		tempint64=var->vUInt8;
		break;
	case vTypeInt16 :
		tempint64=var->vInt16;
		break;
	case vTypeUInt16 :
		tempint64=var->vUInt16;
		break;
	case vTypeInt32 :
		tempint64=var->vInt32;
		break;
	case vTypeUInt32 :	
		tempint64=var->vUInt32;
		break;
	case vTypeInt64 :
		return geoRET_SUCC;
	case vTypeUInt64 :	
		if (var->vUInt64>LLONG_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint64=var->vUInt64;
		break;
	case vTypeFloat :
		if (var->vFloat<LLONG_MIN||var->vFloat>LLONG_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint64=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<LLONG_MIN||var->vDouble>LLONG_MAX)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempint64=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vInt64=tempint64;
	var->vType=vTypeInt64;
	return geoRET_SUCC;
}
static geoAPIStatus changto_UInt64(geoVariant* var)
{
	geoUInt64 tempuint64=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempuint64=var->vBool;
		break;
	case vTypeInt8 :
		if (var->vInt8<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint64=var->vInt8;
		break;
	case vTypeUInt8 :
		tempuint64=var->vUInt8;
		break;
	case vTypeInt16 :
		if (var->vInt16<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint64=var->vInt16;
		break;
	case vTypeUInt16 :
		tempuint64=var->vUInt16;
		break;
	case vTypeInt32 :
		if (var->vInt32<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint64=var->vInt32;
		break;
	case vTypeUInt32 :	
		tempuint64=var->vUInt32;
		break;
	case vTypeInt64 :
		if (var->vInt64<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint64=var->vInt64;
		break;
	case vTypeUInt64 :	
		return geoRET_SUCC;
	case vTypeFloat :
		if (var->vFloat<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint64=var->vFloat;
		break;
	case vTypeDouble :
		if (var->vDouble<0)
		{
			return geoERR_COMMON_DATACHANGE_FAIL;
		}
		tempuint64=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vUInt64=tempuint64;
	var->vType=vTypeUInt64;
	return geoRET_SUCC;
}


static geoAPIStatus changto_Float(geoVariant* var)
{
	geoFloat	 tempdata=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempdata=var->vBool;
		break;
	case vTypeInt8 :
		tempdata=var->vInt8;
		break;
	case vTypeUInt8 :
		tempdata=var->vUInt8;
		break;
	case vTypeInt16 :
		tempdata=var->vInt16;
		break;
	case vTypeUInt16 :
		tempdata=var->vUInt16;
		break;
	case vTypeInt32 :
		tempdata=var->vInt32;
		break;
	case vTypeUInt32 :	
		tempdata=var->vUInt32;
		break;
	case vTypeInt64 :
		tempdata=var->vInt64;
		break;
	case vTypeUInt64 :	
		tempdata=var->vUInt64;
		break;
	case vTypeFloat :
		return geoRET_SUCC;
	case vTypeDouble :
		tempdata=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :		
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vFloat=tempdata;
	var->vType=vTypeFloat;
	return geoRET_SUCC;
}
static geoAPIStatus changto_Double(geoVariant* var)
{
	geoFloat	 tempdata=0;
	switch (var->vType)
	{
	case vTypeBool: 
		tempdata=var->vBool;
		break;
	case vTypeInt8 :
		tempdata=var->vInt8;
		break;
	case vTypeUInt8 :
		tempdata=var->vUInt8;
		break;
	case vTypeInt16 :
		tempdata=var->vInt16;
		break;
	case vTypeUInt16 :
		tempdata=var->vUInt16;
		break;
	case vTypeInt32 :
		tempdata=var->vInt32;
		break;
	case vTypeUInt32 :	
		tempdata=var->vUInt32;
		break;
	case vTypeInt64 :
		tempdata=var->vInt64;
		break;
	case vTypeUInt64 :	
		tempdata=var->vUInt64;
		break;
	case vTypeFloat :
		return geoRET_SUCC;
	case vTypeDouble :
		tempdata=var->vDouble;
		break;
	case vTypeTimeStamp :
	case vTypeAString :
	//	tempdata=(geoDouble)atof();
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	var->vDouble=tempdata;
	var->vType=vTypeDouble;
	return geoRET_SUCC;
}

static geoAPIStatus changto_Time(geoVariant *var)
{
	geoTimeStamp	 tempdata=0;
	switch (var->vType)
	{
	case vTypeBool: 
	case vTypeInt8 :
	case vTypeUInt8 :
	case vTypeInt16 :
	case vTypeUInt16 :
	case vTypeInt32 :
	case vTypeUInt32 :	
	case vTypeInt64 :
	case vTypeUInt64 :	
	case vTypeFloat :
	case vTypeDouble :
		return geoERR_COMMON_DATACHANGE_FAIL;
	case vTypeTimeStamp :
		return geoRET_SUCC;
	case vTypeAString :
	case vTypeWString :				
	case vTypeString :						
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
// 	var->Time=tempdata;
// 	var->vType=vTypeTimeStamp;
	return geoRET_SUCC;	

}
static geoAPIStatus changto_AnsiString(geoVariant *var)
{
	geoChar temp[32]={'0'};
	struct tm * ptm=NULL;
	geoStr pch=NULL;
	int a=0;
	geoTimeStamp t = (var->vTimeStamp / 1000);
	switch (var->vType)
	{
	case vTypeBool: 
		strcpy(temp,var->vBool==geoTRUE? "geoTRUE":"geoTRUE");
		break;
	case vTypeInt8 :
		sprintf(temp,"%d",var->vUInt8);
		break;
	case vTypeUInt8 :	
		sprintf(temp,"%d",var->vUInt8);
		break;
	case vTypeInt16 :
		sprintf(temp,"%d",var->vInt16);
		break;
	case vTypeUInt16 :
		sprintf(temp,"%d",var->vUInt16);
		break;
	case vTypeInt32 :	
		sprintf(temp,"%d",var->vInt32);
		break;
	case vTypeUInt32 :
		sprintf(temp,"%d",var->vUInt32);
		break;

	case vTypeInt64 :
		sprintf(temp,"%lld",var->vInt64);
	case vTypeUInt64 :
		sprintf(temp,"%lld",var->vUInt64);
		break;
	case vTypeFloat :
	case vTypeDouble :
		sprintf(temp,"%f",var->vDouble);
		break;
	case vTypeTimeStamp :
		ptm=localtime((time_t*)(&t));
		sprintf(temp,"%04d-%02d-%02d %02d:%02d:%02d.%03d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec,(geoUInt16)var->vTimeStamp % 1000);
		break;
	case vTypeAString :
		return geoRET_SUCC;
	case vTypeWString :	
	 a = wcslen((wchar_t*)var->vWString.Data);
		pch=(geoStr)alloca( a+1);
		for (int i=0;i<a;i++)
		{
			pch[i]=wctob(var->vWString.Data[i]);
		}
		Variant_AStrToVariant(pch,var);
		return geoRET_SUCC;
	case vTypeString :
#ifdef ___UNICODE
		a = wcslen((wchar_t*)var->vWString.Data);
		pch=(geoStr)alloca( a+1);
		for (int i=0;i<a;i++)
		{
			pch[i]=wctob(var->vWString.Data[i]);
		}
		Variant_AStrToVariant(pch,var);
		return geoRET_SUCC;
#else if
		return geoRET_SUCC;
#endif
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	Variant_AStrToVariant(temp,var);
	return geoRET_SUCC;
}
static geoAPIStatus changto_UgeoodeString(geoVariant *var)
{
	geoWChar temp[32]={'0'};
	struct tm * ptm=NULL;
	geoWStr pch=NULL;
	int a=0;
	geoTimeStamp t = (var->vTimeStamp / 1000);
	switch (var->vType)
	{
#define TEMP (wchar_t*)  temp
	case vTypeBool: 
		wcscpy(TEMP,var->vBool==geoTRUE? L"geoTRUE":L"geoFALSE");
		break;
	case vTypeInt8 :
		swprintf(TEMP,L"%d",var->vUInt8);
		break;
	case vTypeUInt8 :	
		swprintf(TEMP,L"%d",var->vUInt8);
		break;
	case vTypeInt16 :
		swprintf(TEMP,L"%d",var->vInt16);
		break;
	case vTypeUInt16 :
		swprintf(TEMP,L"%d",var->vUInt16);
		break;
	case vTypeInt32 :	
		swprintf(TEMP,L"%d",var->vInt32);
		break;
	case vTypeUInt32 :
		swprintf(TEMP,L"%d",var->vUInt32);
		break;
	case vTypeInt64 :
		swprintf(TEMP,L"%lld",var->vInt64);
	case vTypeUInt64 :
		swprintf(TEMP,L"%lld",var->vUInt64);
		break;
	case vTypeFloat :
	case vTypeDouble :
		swprintf(TEMP,L"%f",var->vDouble);
		break;
	case vTypeTimeStamp :		
		ptm=localtime((time_t*)(&t));
		swprintf(TEMP,L"%04d-%02d-%02d %02d:%02d:%02d.%03d",ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec, (geoUInt16)var->vTimeStamp % 1000);
		break;
	case vTypeAString :
astr:	 a = wcslen((wchar_t*)var->vWString.Data);
		pch=(geoWStr)alloca( a+1);
		for (int i=0;i<a;i++)
		{
			pch[i]=btowc(var->vWString.Data[i]);
		}
		Variant_UStrToVariant(pch,var);		
	case vTypeWString :	
		goto end;
	case vTypeString :
#ifdef ___UNICODE
		goto end;
#endif
		goto astr;	
	case vTypeBlob :
	default:
		return geoERR_COMMON_DATACHANGE_FAIL;
	}
	Variant_UStrToVariant(temp,var);
end:	return geoRET_SUCC;
}

static geoAPIStatus changto_String(geoVariant *var)
{
	geoAPIStatus nRet=geoRET_SUCC;
#ifdef ___UNICODE
	nRet =changto_UgeoodeString(var);
#else	
	nRet =changto_AnsiString(var);
#endif
	var->vType=vTypeString;
	return nRet;
}
static geoAPIStatus  changto_Blob(geoVariant *var)
{
return  geoERR_COMMON_DATACHANGE_FAIL;
}

/// 拷贝块数据到通用点类型内部指针指向的数据块
/// 如果结构体内部指针不空，其指向的内存将被释放
static  geoAPIStatus Copy_blockData_to_Variant ( geoVariant *pVariant,void *sdata,const unsigned length)
{
	char *p=NULL;
	char* PtempMem =(char*) malloc(length);
	if (NULL ==PtempMem)
	{
		return geoERR_COMMON_NO_MEMORY;
	}

	memcpy(PtempMem,sdata,length);

	p=pVariant->vAString.Data;  //保持指针
	if (p)
	{       //如果不空，释放内存
		free(p);
	}
	//使内部指针指向数据
	pVariant->vAString.Data=PtempMem;
	return geoRET_SUCC;
}

//////////////////////////////////////////////////////////////////////////
/// 内部函数结束
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
///函数转移表
//////////////////////////////////////////////////////////////////////////

static PSVAEIANT_EQUAL  is_same_value[]=
{
	Equal_ErrorType,
	Bool_Equal,
	Int8_Equal,
	UInt8_Equal,
	Int16_Equal,
	UInt16_Equal,
	Int32_Equal,
	UInt32_Equal,
	Int64_Equal,
	UInt64_Equal,
	Float_Equal,
	Double_Equal,
	Time_Equal,
	String_Equal,
	AnsiString_Equal,
	UgeoodeString_Equal,
	Blob_Equal,
	Equal_ErrorType,
};

static VARIANT_CHANGETYPE Variant_changeType[]={
	changto_ErrorType,
	changto_Bool,
	changto_Int8,
	changto_UInt8,
	changto_Int16,
	changto_UInt16,
	changto_Int32,
	changto_UInt32,
	changto_Int64,
	changto_UInt64,
	changto_Float,
	changto_Double,
	changto_Time,
	changto_String,
	changto_AnsiString,
	changto_UgeoodeString,
	changto_Blob,
	changto_ErrorType,
};


///	 为geoVariant变量申请空间并初始化,但不设置类型

geoAPIStatus GEO_CALL NEW_Variant(geoVariant **ppVariant)
{
    	//申请空间的指针，避免直接使用二级指针
	geoVariant *pVariant = NULL;
	//参数校验
	if (NULL == ppVariant)
	{
		return geoERR_COMMON_PARAMETER_INVALID;
	}

	pVariant = (geoVariant *) malloc( PSVARIANT_SIZE );
	if (NULL == pVariant)
	{
		return geoERR_COMMON_NO_MEMORY;
	}

	memset(pVariant,0,PSVARIANT_SIZE);
	*ppVariant = pVariant ;
	return geoRET_SUCC;
}

///		[API] 为geoVariant变量申请空间并初始化

/// 	调用前，geoVariant_New函数不释放*ppVariant所指向的空间，
///		如果需要释放，应先调用geoVariant_Free函数。
///		调用后，DataType = nDataType , Value = 0(geoNULL) ;

geoAPIStatus   GEO_CALL Variant_New(PIN geoVarTypeEunm nDataType,
						 POUT geoVariant **ppVariant)
{
    geoAPIStatus ret = NEW_Variant(ppVariant);
	if (ret != geoRET_SUCC)
	{
	   return ret;
	}
	(*ppVariant)->vType= nDataType;

	return geoRET_SUCC;
}


///		释放已申请的geoVariant变量空间
geoAPIStatus  GEO_CALL Variant_Free(PIN POUT geoVariant **ppVariant)
{
	if (NULL == ppVariant)
	{
		return geoERR_COMMON_PARAMETER_INVALID;
	}

	Variant_Clear(*ppVariant);    //清空内部数据
	free(*ppVariant);             //释放variant结构体
	*ppVariant=NULL;
	return geoRET_SUCC;
}


/// 清空geoVariant变量
/// 调用后，DataType不变化 , Value = 0(geoNULL)，必要时会释放Value内存;
///

geoAPIStatus GEO_CALL Variant_Clear(PIN POUT geoVariant *pVariant)

{
	geoUInt8  type;
	if( NULL == pVariant )
	{
		return geoERR_COMMON_PARAMETER_INVALID;
	}


	type = pVariant->vType;
	if (vTypeAString == type
		|| vTypeWString == type
		|| vTypeString == type
		|| vTypeBlob == type)
	{
		char* pref = pVariant->vAString.Data;

		if (pref)
		{
			free(pref);
			pVariant->vAString.Data = NULL;
		}

	}
	memset(pVariant, 0, PSVARIANT_SIZE);
	pVariant->vType=vTypeEmpty;
	return geoRET_SUCC;
}


///		将字符串赋给geoVariant变量

geoAPIStatus GEO_CALL Variant_StrToVariant(    PIN geoStr strStr,
								  PIN POUT geoVariant *pVariant)
{
	assert(pVariant!=geoNULL);
	Variant_Clear(pVariant);
	pVariant->vType = vTypeString;
	pVariant->vString.Length = (geoUInt32)strlen(strStr);
	return NewAndCopyStr(&(pVariant->vString.Data),strStr);
}

///		将ANSI字符串赋给geoVariant变量
geoAPIStatus GEO_CALL Variant_AStrToVariant(    PIN geoStr strAStr,
								  PIN POUT geoVariant *pVariant)
{
	assert(pVariant!=geoNULL);
	Variant_Clear(pVariant);
	pVariant->vType = vTypeAString;
	pVariant->vAString.Length = (geoUInt32)strlen(strAStr);
	return NewAndCopyStr(&(pVariant->vAString.Data),strAStr);
}


///		将UNICODE字符串赋给geoVariant变量
geoAPIStatus GEO_CALL Variant_UStrToVariant(PIN geoWStr strUStr,
								   PIN POUT geoVariant *pVariant)
{
	assert(pVariant!=geoNULL);
	Variant_Clear(pVariant);
	pVariant->vType = vTypeWString;
	pVariant->vWString.Length = 
		(geoUInt32)wcslen((const wchar_t *)strUStr);
	return NewAndCopyUStr(&(pVariant->vWString.Data),strUStr);
}

///		将二进制串赋给geoVariant变量
geoAPIStatus GEO_CALL Variant_BlobToVariant(	PIN geoByte *pByteList,
								   PIN geoUInt32 nLength,
								   PIN POUT geoVariant *pVariant)
{
	geoAPIStatus nRet = geoRET_SUCC;
	assert(pVariant!=geoNULL);
	Variant_Clear(pVariant);
	pVariant->vType = vTypeBlob;
	pVariant->vBlob.Length = nLength;
	RET_ERR(NewMemory((geoVoid**)&(pVariant->vBlob.Data),nLength));
	memcpy(pVariant->vBlob.Data,pByteList,nLength);
	return geoRET_SUCC;
}

///		复制geoVariant变量
geoAPIStatus GEO_CALL Variant_Copy(		PIN geoVariant *pSource,
						  PIN POUT geoVariant *pDestination)
{
	geoVarTypeEunm type;
	if ( (NULL !=pSource) && (NULL !=pDestination))
	{
		Variant_Clear(pDestination);

		type=pSource->vType ;
		pDestination->vType = type;
		switch (type)
		{
		case vTypeAString:
			pDestination->vAString.Length = pSource->vAString.Length;
			return Copy_blockData_to_Variant(
				pDestination,pSource->vAString.Data,
				pSource->vAString.Length+sizeof(geoChar));
		case vTypeString:
			if (!(pSource->vString.Length))
			{
				memcpy(pDestination, pSource, PSVARIANT_SIZE);
				return geoRET_SUCC;
			}
			pDestination->vString.Length = pSource->vString.Length;
			return Copy_blockData_to_Variant(
				pDestination,pSource->vString.Data,
				pSource->vString.Length+sizeof(geoChar));
		case vTypeWString:
			pDestination->vWString.Length = pSource->vWString.Length;
			return Copy_blockData_to_Variant(
				pDestination,pSource->vWString.Data,
				pSource->vWString.Length+sizeof(geoWChar));
		case vTypeBlob:
			pDestination->vBlob.Length = pSource->vBlob.Length;
			return Copy_blockData_to_Variant(
				pDestination,pSource->vBlob.Data,
				pSource->vBlob.Length);
		default:
			memcpy(pDestination, pSource, PSVARIANT_SIZE);
		}
		return geoRET_SUCC;
	}
	return geoERR_COMMON_PARAMETER_INVALID;
}

geoBool GEO_CALL Variant_Equal(geoVariant *pFirst, geoVariant *pSecond)
{
	geoVarTypeEunm type;
	if (pFirst&&pSecond)
	{
		type=pFirst->vType;
		if (type == pSecond->vType)
		{
			return 	is_same_value[type](pFirst,pSecond);
		}
		return geoFALSE;

	}
	return geoFALSE;
}

///		获取geoVariant变量的数据转换成double类型的值
geoDouble GEO_CALL geoVariant_GetDouble( const geoVariant* value )
{
	switch (value->vType)
	{
	case vTypeInt8:
		return static_cast<geoDouble> (value->vInt8);
	case vTypeInt16:
		return static_cast<geoDouble> (value->vInt16);
	case vTypeInt32:
		return static_cast<geoDouble> (value->vInt32);
	case vTypeInt64:
		return static_cast<geoDouble> (value->vInt64);
	case vTypeUInt8:
		return static_cast<geoDouble> (value->vUInt8);
	case vTypeUInt16:
		return static_cast<geoDouble> (value->vUInt16);
	case vTypeUInt32:
		return static_cast<geoDouble> (value->vUInt32);
	case vTypeUInt64:
		return static_cast<geoDouble> (value->vUInt64);
	case vTypeFloat:
		return static_cast<geoDouble> (value->vFloat);
	case vTypeDouble:
		return value->vDouble;
	case vTypeBool:
		return  static_cast<geoDouble> (value->vBool);
	default:
		assert(0);
		return 0;
	}
}



geoAPIStatus GEO_CALL VariantTypeCast(geoUInt8 DataType, geoVariant* var_src,geoVariant* var_dst )
{
	if (!(DataType > vTypeEmpty && DataType < vTypeMax))
	{
		return geoERR_COMMON_DATATYPE;
	}
	geoAPIStatus nRet =geoRET_SUCC;
	if (IsNotNull(var_dst))
	{
		RET_ERR(Variant_Clear(var_dst)); 
		RET_ERR(Variant_Copy(var_src,var_dst));
	}
	geoVariant* pvariant= IsNotNull(var_dst)? var_dst:var_src;
	return Variant_changeType[DataType](pvariant);
}
