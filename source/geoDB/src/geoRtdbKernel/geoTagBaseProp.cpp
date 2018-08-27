#include "preCompile.h"
#include "geoTagBaseProp.h"
#include "geoTagMap.h"



//判断名称是否为合法的标签名
//标签名为 数字、字母 和 '_'符号，且以数字、字母开头
geoBool CheckTagNameValid(geoChar* ShortName)
{
	//如果不是数字或者字母开头，错误
	if (::isdigit(*ShortName) && ::isalpha(*ShortName))
	{
		return geoFALSE;
	}
	geoChar * temp = ShortName;

	while (*temp != ('\0'))
	{
		if (isascii(*ShortName))
		{
			if (::isalpha(*temp) || ::isdigit(*temp) || (*temp) == '_')
			{
				//do nothing
			}
			else
			{
				return geoFALSE;
			}
		}
		temp++;
	}
	return geoTRUE;
}
//通配符匹配检查，用作标签名过滤、检索、查找
static bool StrWildMatch(char* str1, char* pattern)
{
	if (str1 == NULL) return false;
	if (pattern == NULL) return false;
	int len1 = strlen(str1);
	int len2 = strlen(pattern);
	int mark = 0;//用于分段标记,'*'分隔的字符串
	int p1 = 0, p2 = 0;

	while (p1<len1 && p2<len2)
	{
		if (pattern[p2] == '?')
		{
			p1++;
			p2++;
			continue;
		}
		if (pattern[p2] == '*')
		{
			// 如果当前是*号，则mark前面一部分已经获得匹配，
			// 从当前点开始继续下一个块的匹配
			p2++;
			mark = p2;
			continue;
		}
		if (str1[p1] != pattern[p2])
		{
			if (p1 == 0 && p2 == 0)
			{

				// 如果是首字符，特殊处理，不相同即匹配失败
				return false;
			}
			/*
			* pattern: ...*bdef*...
			*              ^
			*             mark
			*                ^
			*                p2
			*              ^
			*             new p2
			* str1:.....bdcf...
			*             ^
			*             p1
			*            ^
			*          new p1
			* 如上示意图所示，在比到e和c处不想等
			* p2返回到mark处，
			* p1需要返回到下一个位置。
			* 因为*前已经获得匹配，所以mark打标之前的不需要再比较
			*/
			p1 -= p2 - mark - 1;
			p2 = mark;
			continue;
		}
		// 此处处理相等的情况

		p1++;
		p2++;
	}
	if (p2 == len2)
	{
		if (p1 == len1)
		{
			// 两个字符串都结束了，说明模式匹配成功

			return true;
		}
		if (pattern[p2 - 1] == '*')
		{
			// str1还没有结束，但pattern的最后一个字符是*，所以匹配成功
			return true;
		}
	}
	while (p2<len2)
	{
		// pattern多出的字符只要有一个不是*,匹配失败
		if (pattern[p2] != '*')
			return false;
		p2++;
	}
	return true;
}
//释放空间TagPropList
static  void FreeTagPropList(geoTagPropList **ppTagPropList)
{
	if (ppTagPropList == geoNULL || *ppTagPropList == geoNULL)
	{
		return;
	}
	geoTagPropList* pTagPropList = *ppTagPropList;
	FreeAndNull((geoVoid**)&(pTagPropList->APIStatus));
	FreeAndNull((geoVoid**)&(pTagPropList->Value));
	FreeAndNull((geoVoid**)ppTagPropList);
}
//分配空间TagPropList
static geoAPIStatus NewTagPropListEx(geoTagPropList **ppTagPropList,geoUInt16 nCount)
{
	geoAPIStatus nRet = geoRET_SUCC;
	GEO_ASSERT(ppTagPropList != geoNULL);
	GEO_ASSERT(*ppTagPropList == geoNULL);

	RET_ERR(NewAndClear((geoVoid**)ppTagPropList, sizeof(geoTagPropList)));
	geoTagPropList* pTagPropList = *ppTagPropList;
	pTagPropList->PropCount = nCount;
	if (nRet = NewAndClear((geoVoid**)&(pTagPropList->APIStatus), sizeof(geoAPIStatus*)*nCount) != geoRET_SUCC)
	{
		FreeTagPropList(ppTagPropList);
		return nRet;
	}
	if (nRet = NewAndClear((geoVoid**)&(pTagPropList->Value), sizeof(geoVariant*)*nCount) != geoRET_SUCC)
	{
		FreeTagPropList(ppTagPropList);
		return nRet;
	}
	nRet = geoRET_SUCC;

	return nRet;
}
static geoAPIStatus  FillTagBasePropList(
	geoPropValueList *pPropValueList,
	geoTagPropList *pTagPropList,
	geoAPIStatus* pAPIStatusList)
{

	GEO_ASSERT(pPropValueList != geoNULL);
	GEO_ASSERT(pPropValueList->PropCount>0);
	GEO_ASSERT(pPropValueList->PropValueList != geoNULL);

	geoUInt16 nPropId;
	for (geoUInt16 i = 0; i<pPropValueList->PropCount; ++i)
	{
		nPropId = pPropValueList->PropValueList[i].PropId;
		if (GeoBaseTagProp::IsTagBaseProp(nPropId))
		{
			if (*(pTagPropList->Value) != geoNULL && (pTagPropList->PropCount>i))
			{
				return geoERR_TAG_PROP_REDUPLICATE;
			}
			pTagPropList->Value[nPropId] = &(pPropValueList->PropValueList[i].Value);
			pTagPropList->APIStatus[nPropId] = pAPIStatusList + i;
		}
	}
	return geoRET_SUCC;
}




 GeoBaseTagProp::GeoBaseTagProp(GeoTagMap * hashNameMap):GeoTagVector()
{
	GEO_ASSERT(IsNotNull(hashNameMap));
	mHash = hashNameMap;
}

 GeoBaseTagProp::GeoBaseTagProp(GeoTagMap * hashNameMap,
	geoChar * strPathName,
	geoUInt32 nCapacity,
	geoChar * strAuthor,
	geoChar * strOEM):
	 GeoTagVector(strPathName, nCapacity, strAuthor, strOEM)
{
	GEO_ASSERT(IsNotNull(hashNameMap));
	mHash = hashNameMap;

}
 geoAPIStatus  GeoBaseTagProp::InitNameHash()
 {
	 geoAPIStatus nRet;
	 for (geoUInt32 i = 1; i< GetCurrentIndex(); ++i)
	 {
		 if (!IsDeleted(i))
		 {
			 RET_ERR(mHash->bind(mData[i].Name,i));
		 }
	 }
	 return geoRET_SUCC;

 }
 geoAPIStatus GeoBaseTagProp::Init()
 {
	 geoAPIStatus nRet = geoRET_SUCC;
	 InitTagBasePropList();
	 RET_ERR(GeoTagVector::Init());
	 RET_ERR(InitNameHash());
	 return nRet;
 }
 geoAPIStatus GeoBaseTagProp::UnInit()
 {
	 return GeoTagVector::UnInit();
 }

 geoVoid GeoBaseTagProp::InitTagBasePropList()
 {
		m_pTagBasePropProcess[geoProp_Id].DataType = geoVarTypeEnum::vTypeInt32 ;
		m_pTagBasePropProcess[geoProp_Id].GetFunction = &GeoBaseTagProp::GetProp_Id;
		m_pTagBasePropProcess[geoProp_Id].SetFunction = geoNULL;
		m_pTagBasePropProcess[geoProp_Id].FilterFunction = geoNULL;

		m_pTagBasePropProcess[geoProp_TagType].DataType = geoVarTypeEnum::vTypeUInt8;
		m_pTagBasePropProcess[geoProp_TagType].GetFunction = &GeoBaseTagProp::GetProp_TagType;
		m_pTagBasePropProcess[geoProp_TagType].SetFunction = &GeoBaseTagProp::SetProp_TagType;
		m_pTagBasePropProcess[geoProp_TagType].FilterFunction = &GeoBaseTagProp::FilterProp_TagType;;


		m_pTagBasePropProcess[geoProp_Name].DataType = geoVarTypeEnum::vTypeString;
		m_pTagBasePropProcess[geoProp_Name].GetFunction = &GeoBaseTagProp::GetProp_Name;
		m_pTagBasePropProcess[geoProp_Name].SetFunction = &GeoBaseTagProp::SetProp_Name;
		m_pTagBasePropProcess[geoProp_Name].FilterFunction = &GeoBaseTagProp::FilterProp_Name;


		m_pTagBasePropProcess[geoProp_DataType].DataType = geoVarTypeEnum::vTypeUInt8;
		m_pTagBasePropProcess[geoProp_DataType].GetFunction = &GeoBaseTagProp::GetProp_DataType;
		m_pTagBasePropProcess[geoProp_DataType].SetFunction = &GeoBaseTagProp::SetProp_DataType;
		m_pTagBasePropProcess[geoProp_DataType].FilterFunction = &GeoBaseTagProp::FilterProp_DataType;


		m_pTagBasePropProcess[geoProp_Description].DataType = geoVarTypeEnum::vTypeString;
		m_pTagBasePropProcess[geoProp_Description].GetFunction = &GeoBaseTagProp::GetProp_Description;
		m_pTagBasePropProcess[geoProp_Description].SetFunction = &GeoBaseTagProp::SetProp_Description;
		m_pTagBasePropProcess[geoProp_Description].FilterFunction = &GeoBaseTagProp::FilterProp_Description;

		m_pTagBasePropProcess[geoProp_InitValue].DataType = geoVarTypeEnum::vTypeDouble;
		m_pTagBasePropProcess[geoProp_InitValue].GetFunction = &GeoBaseTagProp::GetProp_InitValue;
		m_pTagBasePropProcess[geoProp_InitValue].SetFunction = &GeoBaseTagProp::SetProp_InitValue;
		m_pTagBasePropProcess[geoProp_InitValue].FilterFunction = &GeoBaseTagProp::FilterProp_InitValue;

		m_pTagBasePropProcess[geoProp_Unit].DataType = geoVarTypeEnum::vTypeInt8;
		m_pTagBasePropProcess[geoProp_Unit].GetFunction = &GeoBaseTagProp::GetProp_Unit;
		m_pTagBasePropProcess[geoProp_Unit].SetFunction = &GeoBaseTagProp::SetProp_Unit;
		m_pTagBasePropProcess[geoProp_Unit].FilterFunction = &GeoBaseTagProp::FilterProp_Unit;

		m_pTagBasePropProcess[geoProp_ParentId].DataType = geoVarTypeEnum::vTypeUInt32;
		m_pTagBasePropProcess[geoProp_ParentId].GetFunction = &GeoBaseTagProp::GetProp_ParentId;
		m_pTagBasePropProcess[geoProp_ParentId].SetFunction = geoNULL;
		m_pTagBasePropProcess[geoProp_ParentId].FilterFunction = geoNULL;

		m_pTagBasePropProcess[geoProp_NextId].DataType = geoVarTypeEnum::vTypeUInt32;
		m_pTagBasePropProcess[geoProp_NextId].GetFunction = &GeoBaseTagProp::GetProp_NextId;
		m_pTagBasePropProcess[geoProp_NextId].SetFunction = geoNULL;
		m_pTagBasePropProcess[geoProp_NextId].FilterFunction = geoNULL;

		m_pTagBasePropProcess[geoProp_PrevId].DataType = geoVarTypeEnum::vTypeUInt32;
		m_pTagBasePropProcess[geoProp_PrevId].GetFunction = &GeoBaseTagProp::GetProp_PrevId;
		m_pTagBasePropProcess[geoProp_PrevId].SetFunction = geoNULL;
		m_pTagBasePropProcess[geoProp_PrevId].FilterFunction = geoNULL;

		m_pTagBasePropProcess[geoProp_FirstChildId].DataType = geoVarTypeEnum::vTypeUInt32;
		m_pTagBasePropProcess[geoProp_FirstChildId].GetFunction = &GeoBaseTagProp::GetProp_FirstChildId;
		m_pTagBasePropProcess[geoProp_FirstChildId].SetFunction = geoNULL;
		m_pTagBasePropProcess[geoProp_FirstChildId].FilterFunction = geoNULL;

		m_pTagBasePropProcess[geoProp_CreateTime].DataType = geoVarTypeEnum::vTypeTimeStamp;
		m_pTagBasePropProcess[geoProp_CreateTime].GetFunction = &GeoBaseTagProp::GetProp_CreateTime;
		m_pTagBasePropProcess[geoProp_CreateTime].SetFunction = &GeoBaseTagProp::SetProp_CreateTime;
		m_pTagBasePropProcess[geoProp_CreateTime].FilterFunction = &GeoBaseTagProp::FilterProp_CreateTime;;

		m_pTagBasePropProcess[geoProp_LastModifyTime].DataType = geoVarTypeEnum::vTypeTimeStamp;
		m_pTagBasePropProcess[geoProp_LastModifyTime].GetFunction = &GeoBaseTagProp::GetProp_LastModifyTime;
		m_pTagBasePropProcess[geoProp_LastModifyTime].SetFunction = &GeoBaseTagProp::SetProp_LastModifyTime;
		m_pTagBasePropProcess[geoProp_LastModifyTime].FilterFunction = &GeoBaseTagProp::FilterProp_LastModifyTime;;

 }



geoAPIStatus GeoBaseTagProp::GetProp_Id(geoUInt32 unTagId, geoVariant *pValue)
{

	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(pValue != geoNULL);
	pValue->varType = m_pTagBasePropProcess[geoProp_Id].DataType;
	pValue->vUInt32 = mData[unTagId].Id;
	GEO_ASSERT(mData[unTagId].Id == unTagId);
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::GetProp_TagType(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(pValue != geoNULL);
	pValue->varType = m_pTagBasePropProcess[geoProp_TagType].DataType;
	pValue->vUInt16 = mData[unTagId].TagType;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::SetProp_TagType(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(pValue != geoNULL);
	GEO_ASSERT(pValue->varType == m_pTagBasePropProcess[geoProp_TagType].DataType);

	if (mData[unTagId].TagType == pValue->vUInt8)
	{
		return geoERR_TAG_PROP_NOT_CHANGED;
	}
	mData[unTagId].TagType = pValue->vUInt8;
	return geoRET_SUCC;
}
geoAPIStatus GeoBaseTagProp::FilterProp_TagType(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));

	if (pValue->varType != geoVarTypeEnum::vTypeUInt8)
	{
		return geoERR_COMMON_DATATYPE;
	}
	if (mData[unTagId].TagType == pValue->vUInt8)
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER; 
}

geoAPIStatus GeoBaseTagProp::GetProp_Name(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(IsNull(pValue->vString.Data));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_Name].DataType;
	pValue->vString.Length = (geoUInt32)geo_strlen(mData[unTagId].Name);
	pValue->vString.Data = reinterpret_cast<geoStr>(malloc((pValue->vString.Length + 1) * sizeof(geoChar)));
	if (IsNull(pValue->vString.Data))
	{
		pValue->vString.Length = 0;
		return geoERR_COMMON_NO_MEMORY;
	}
	geo_strncpy(pValue->vString.Data, mData[unTagId].Name, pValue->vString.Length + 1);
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::SetProp_Name(geoUInt32 unTagId, geoVariant *pValue)
{
	geoAPIStatus nRet = geoRET_SUCC;
	GEO_ASSERT(IsNotNull(mHash));
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(pValue != geoNULL);
	GEO_ASSERT(pValue->varType == m_pTagBasePropProcess[geoProp_Name].DataType);
	if (geo_strcmp(mData[unTagId].Name, pValue->vString.Data) == 0)
	{
		return geoERR_TAG_PROP_NOT_CHANGED;
	}
	if (!mHash->find(pValue->vString.Data))
	{
		return geoERR_TAG_NAME_REDUPLICATE;
	}
	//如果是已经使用的标签设定标签名
	if (mData[unTagId].Id != geoTagId_Unused)
	{
		mHash->unbind(mData[unTagId].Name);
	}

	geo_strncpy(mData[unTagId].Name, pValue->vString.Data, pValue->vString.Length + 1);


	nRet = mHash->bind(mData[unTagId].Name,unTagId);


	return nRet;
}

geoAPIStatus GeoBaseTagProp::FilterProp_Name(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	if (pValue->varType != geoVarTypeEnum::vTypeAString && pValue->varType != geoVarTypeEnum::vTypeString)
	{
		return geoERR_COMMON_DATATYPE;
	}
	//使用外来字符串长度作为比较运算长度限值
	GEO_ASSERT(pValue->vString.Length <= TAG_NAME_SIZE);
	//通配符匹配
	if (StrWildMatch(mData[unTagId].Name, pValue->vString.Data))
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER;
}
geoAPIStatus GeoBaseTagProp::GetProp_DataType(geoUInt32 unTagId, geoVariant *pValue)
{

	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	pValue->varType = m_pTagBasePropProcess[geoProp_DataType].DataType;
	pValue->vUInt8 = mData[unTagId].DataType;
	return geoRET_SUCC;
}

//此函数暂不暴露给SetProp接口，只是在添加点时被调用
geoAPIStatus GeoBaseTagProp::SetProp_DataType(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeUInt8);

	if (mData[unTagId].Id != geoTagId_Unused)
	{
		return geoERR_TAG_CANNOT_SETPROP;
	}

	mData[unTagId].DataType = pValue->vUInt8;
	return geoRET_SUCC;
}
geoAPIStatus GeoBaseTagProp::FilterProp_DataType(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));

	if (pValue->varType != geoVarTypeEnum::vTypeUInt8)
	{
		return geoERR_COMMON_DATATYPE;
	}
	if (mData[unTagId].DataType == pValue->vUInt8)
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER;
}


geoAPIStatus GeoBaseTagProp::GetProp_Description(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	//保证必须初始化过pValue
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_Description].DataType;
	pValue->vString.Length = (geoUInt32)geo_strlen(mData[unTagId].Description);
	if (pValue->vString.Length == 0)
	{
		return geoRET_SUCC;
	}
	pValue->vString.Data = reinterpret_cast<geoStr>(malloc((pValue->vString.Length + 1) * sizeof(geoChar)));
	if (pValue->vString.Data == geoNULL)
	{
		pValue->vString.Length = 0;
		return geoERR_COMMON_NO_MEMORY;
	}
	geo_strcpy(pValue->vString.Data, mData[unTagId].Description);
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::SetProp_Description(geoUInt32 unTagId, geoVariant *pValue)
{
	geoAPIStatus nRet = geoRET_SUCC;

	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == m_pTagBasePropProcess[geoProp_Description].DataType);
	GEO_ASSERT(pValue->vString.Length < TAG_DESC_SIZE);
	if (geo_strcmp(mData[unTagId].Description, pValue->vString.Data) == 0)
	{
		return geoERR_TAG_PROP_NOT_CHANGED;
	}
	geo_strncpy(mData[unTagId].Description, pValue->vString.Data, pValue->vString.Length + 1);
	return nRet;
}
geoAPIStatus GeoBaseTagProp::FilterProp_Description(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	if (pValue->varType != geoVarTypeEnum::vTypeAString && pValue->varType != geoVarTypeEnum::vTypeString)
	{
		return geoERR_COMMON_DATATYPE;
	}
	//使用外来字符串长度作为比较运算长度限值
	GEO_ASSERT(pValue->vString.Length <= TAG_DESC_SIZE);
	//通配符匹配
	if (StrWildMatch(mData[unTagId].Description, pValue->vString.Data))
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER;
}
geoAPIStatus GeoBaseTagProp::GetProp_Unit(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	pValue->varType = m_pTagBasePropProcess[geoProp_Unit].DataType;
	pValue->vUInt8 = mData[unTagId].Unit;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::SetProp_Unit(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeUInt8);
	mData[unTagId].Unit = pValue->vUInt8;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::FilterProp_Unit(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));

	if (pValue->varType != geoVarTypeEnum::vTypeUInt8)
	{
		return geoERR_COMMON_DATATYPE;
	}
	if (mData[unTagId].Unit == pValue->vUInt8)
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER;
}

geoAPIStatus GeoBaseTagProp::GetProp_InitValue(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	pValue->varType = m_pTagBasePropProcess[geoProp_InitValue].DataType;
	pValue->vDouble = mData[unTagId].InitValue;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::SetProp_InitValue(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(IsNotNull(pValue));
	mData[unTagId].InitValue = geoVariant_GetDouble(pValue);
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::FilterProp_InitValue(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));

	if (pValue->varType != geoVarTypeEnum::vTypeDouble)
	{
		return geoERR_COMMON_DATATYPE;
	}
	//浮点数比较相等时，必须采用此种方法，不然由于精度问题，浮点数很难真正相等
	if (fabs(mData[unTagId].InitValue - pValue->vUInt8) < GEO_EPSINON)
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER;
}
geoAPIStatus GeoBaseTagProp::GetProp_ParentId(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_ParentId].DataType;
	pValue->vUInt32 = mData[unTagId].ParentId;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::GetProp_NextId(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_NextId].DataType;
	pValue->vUInt32 = mData[unTagId].NextId;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::GetProp_PrevId(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_PrevId].DataType;
	pValue->vUInt32 = mData[unTagId].PrevId;
	return geoRET_SUCC;

}

geoAPIStatus GeoBaseTagProp::GetProp_FirstChildId(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_FirstChildId].DataType;
	pValue->vUInt32 = mData[unTagId].FirstChildId;
	return geoRET_SUCC;
}
geoAPIStatus GeoBaseTagProp::GetProp_CreateTime(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_CreateTime].DataType;
	pValue->vTimeStamp = mData[unTagId].CreateTime;
	return geoRET_SUCC;
}
geoAPIStatus GeoBaseTagProp::SetProp_CreateTime(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(pValue != geoNULL);
	if (mData[unTagId].CreateTime == pValue->vTimeStamp)
	{
		return geoERR_TAG_PROP_NOT_CHANGED;
	}
	mData[unTagId].CreateTime = pValue->vTimeStamp;
	return geoRET_SUCC;
}
geoAPIStatus GeoBaseTagProp::FilterProp_CreateTime(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));

	if (pValue->varType != geoVarTypeEnum::vTypeTimeStamp)
	{
		return geoERR_COMMON_DATATYPE;
	}
	if (mData[unTagId].CreateTime == pValue->vTimeStamp)
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER;
}
geoAPIStatus GeoBaseTagProp::GetProp_LastModifyTime(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	pValue->varType = m_pTagBasePropProcess[geoProp_LastModifyTime].DataType;
	pValue->vTimeStamp = mData[unTagId].LastModifyTime;
	return geoRET_SUCC;
}
geoAPIStatus GeoBaseTagProp::SetProp_LastModifyTime(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(pValue != geoNULL);
	if (mData[unTagId].LastModifyTime == pValue->vTimeStamp)
	{
		return geoERR_TAG_PROP_NOT_CHANGED;
	}
	mData[unTagId].LastModifyTime = pValue->vTimeStamp;
	return geoRET_SUCC;
}
geoAPIStatus GeoBaseTagProp::FilterProp_LastModifyTime(geoUInt32 unTagId, geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pValue));

	if (pValue->varType != geoVarTypeEnum::vTypeTimeStamp)
	{
		return geoERR_COMMON_DATATYPE;
	}
	if (mData[unTagId].CreateTime == pValue->vTimeStamp)
	{
		return geoRET_SUCC;
	}
	return geoERR_TAG_PROP_FILTER;
}
geoAPIStatus GeoBaseTagProp::GetExtend(geoUInt32 unTagId, geoUInt8* pnTagType, geoUInt32* pnExtendId)
{
	GEO_ASSERT(IsExist(unTagId));
	*pnTagType = mData[unTagId].TagType;
	*pnExtendId = mData[unTagId].ExtendId;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::GetExtendId(geoUInt32 unTagId, geoUInt32* pnExtendId)
{
	GEO_ASSERT(IsExist(unTagId));
	*pnExtendId = mData[unTagId].ExtendId;
	return geoRET_SUCC;
}

geoAPIStatus GeoBaseTagProp::SetExtendId(geoUInt32 unTagId, geoUInt32 unExtendID)
{
	GEO_ASSERT(IsExist(unTagId));
	mData[unTagId].ExtendId = unExtendID;
	return geoRET_SUCC;
}

 inline geoBool GeoBaseTagProp::IsTagBaseProp(geoUInt16 nPropId)
{
	return (nPropId<geoProp_TagBase_Max);
}

geoAPIStatus GeoBaseTagProp::SetProperty(
	geoUInt32 unTagId,
	geoUInt16 nPropId,
	geoVariant *pValue)
{
	if (unTagId == 0)
	{
		return geoERR_TAG_CANNOT_SETPROP;
	}

	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsTagBaseProp(nPropId));
	GEO_ASSERT(IsNotNull(pValue));
	if (IsNull(m_pTagBasePropProcess[nPropId].SetFunction))
	{
		return geoERR_TAG_CANNOT_SETPROP;
	}
	// 假定客户端已将类型转换为标准类型
	GEO_ASSERT(pValue->varType == m_pTagBasePropProcess[nPropId].DataType);
	geoAPIStatus nRet = (this->*m_pTagBasePropProcess[nPropId].SetFunction)(unTagId, pValue);
	if ((geoSucc(nRet)))
	{
		geoVariant modifyTime;
		modifyTime.varType = geoVarTypeEnum::vTypeTimeStamp;
		modifyTime.vTimeStamp = geo_get_system_time();
		SetProp_LastModifyTime(unTagId, &modifyTime);
		SetChangedFlag(unTagId);
	}
	return nRet;
}

geoAPIStatus GeoBaseTagProp::GetProperty(
	geoUInt32 unTagId,
	geoUInt16 nPropId,
	geoVariant *pValue)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsTagBaseProp(nPropId));
	GEO_ASSERT(IsNotNull(pValue));
	if (IsNull(m_pTagBasePropProcess[nPropId].GetFunction))
	{
		return geoERR_TAG_CANNOT_GETPROP;
	}
	GEO_ASSERT(pValue->varType == geoVarTypeEnum::vTypeEmpty);
	return (this->*m_pTagBasePropProcess[nPropId].GetFunction)(unTagId, pValue);
}



///	增加单个测点
geoAPIStatus GeoBaseTagProp::AddTag(
	geoPropValueList *pPropValueList,
	geoUInt32 *pnNewTagId,
	geoAPIStatus* pAPIStatusList)
{

	GEO_ASSERT(mData != geoNULL);
	*pnNewTagId = geoTagId_Unused;
	geoUInt32 tempTagId = geoTagId_Unused;
	geoAPIStatus nRet = geoRET_SUCC;
	geoTagPropList * pTagPropList = 0;
	//分配属性结构体空间
	if (geoFail(NewTagPropListEx(&pTagPropList, geoProp_TagBase_Max)))
	{
		return geoRET_FAIL;
	}
	//赋值属性结构体空间
	if (geoFail(FillTagBasePropList(pPropValueList, pTagPropList, pAPIStatusList)))
	{
		FreeTagPropList(&pTagPropList);
		return geoRET_FAIL;
	}
	//标签名、 标签类型、数据类型必须有
	if (pTagPropList->Value[geoProp_Name] == geoNULL ||
		pTagPropList->Value[geoProp_TagType] == geoNULL ||
		pTagPropList->Value[geoProp_DataType] == geoNULL)
	{
		FreeTagPropList(&pTagPropList);
		return geoERR_TAG_ADD;
	}
	//数据类型必须有效
	if (pTagPropList->Value[geoProp_DataType]->varType == geoVarTypeEnum::vTypeEmpty)
	{
		FreeTagPropList(&pTagPropList);
		return geoERR_TAG_WRONG_NAME;
	}
	//检查是否为有效的的字符串名字
	if (CheckTagNameValid(pTagPropList->Value[geoProp_Name]->vString.Data) == geoFALSE)
	{
		FreeTagPropList(&pTagPropList);
		return geoERR_TAG_WRONG_NAME;
	}
	//如果标签名已经存在，也不成功
	if (!mHash->find(pTagPropList->Value[geoProp_Name]->vString.Data))
	{
		return geoERR_TAG_NAME_REDUPLICATE;
	}



	///其他有效性检查
	///todo
	///.....

	//添加标签号，永远都是在末尾添加，类似于pop
	nRet = GeoTagVector::AddTag(pnNewTagId);
	if (nRet)
	{
		FreeTagPropList(&pTagPropList);
		return nRet;
	}

	nRet = SetTagBasePropList(*pnNewTagId, pTagPropList);
	//如果在设置单项中出现了一些错误，如设置了只读属性、设置值无变化等错误,
	//但其他错误要算错误
	if (nRet == geoERR_TAG_FAIL_IN_BATCH)
	{
		//要清空AddTag的标签Id，清空的标签都是最后一个Id
		ClearTag(*pnNewTagId);
		*pnNewTagId = geoTagId_Unused;
		FreeTagPropList(&pTagPropList);
		return nRet;
	}
	geoVariant pValue;
	pValue.varType = geoVarTypeEnum::vTypeTimeStamp;
	pValue.vTimeStamp = geo_get_system_time();
	SetProp_CreateTime(*pnNewTagId, &pValue);
	//推到需要保存队列中
	PushToChangedList(*pnNewTagId);
	FreeTagPropList(&pTagPropList);
	return nRet;
}

geoAPIStatus GeoBaseTagProp::DelTag(geoUInt32 nDelTagId)
{

	geoAPIStatus nRet = geoRET_SUCC;

	if (!IsExist(nDelTagId))
	{
		return geoERR_TAG_NOT_EXIST;
	}
	RET_ERR(mHash->unbind(mData[nDelTagId].Name));
	GeoTagVector::DelTag(nDelTagId);
	PushToChangedList(nDelTagId);
	return geoRET_SUCC;
}

///	得到标签的一批属性
/// pValueList pPropIdList 都需要经过专门的内存分配函数分配空间
geoAPIStatus GeoBaseTagProp::GetPropList(
	geoUInt32 unTagId,
	geoPropIdList *pPropIdList,
	geoPropValueList* pValueList)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pPropIdList));
	GEO_ASSERT(pPropIdList->PropCount>0);
	GEO_ASSERT(pPropIdList->PropIdList != geoNULL);
	GEO_ASSERT(IsNotNull(pValueList));


	geoAPIStatus nRet = geoRET_SUCC;


	for (geoUInt16 i = 0; i<pPropIdList->PropCount; ++i)
	{
		pValueList->PropValueList[i].PropId = pPropIdList->PropIdList[i];
		nRet = (this->*(m_pTagBasePropProcess[pValueList->PropValueList[i].PropId].GetFunction))(unTagId, &pValueList->PropValueList[i].Value);
		if (nRet)
		{
			return nRet;
		}
	}
	return geoRET_SUCC;
}
///	得到属性列表
geoAPIStatus GeoBaseTagProp::GetTagBasePropList(geoUInt32 unTagId, geoTagPropList * pTagPropList)
{

	geoAPIStatus nRet = geoRET_SUCC;

	GEO_ASSERT(IsExist(unTagId));
	for (geoUInt16 i = 0; i<geoProp_TagBase_Max; ++i)
	{
		if (m_pTagBasePropProcess[i].GetFunction == geoNULL ||
			pTagPropList->Value[i] == geoNULL ||
			*(pTagPropList->APIStatus[i]) != geoRET_SUCC)
		{
			continue;
		}
		GEO_ASSERT(pTagPropList->PropCount >i);
		*(pTagPropList->APIStatus[i]) = (this->*(m_pTagBasePropProcess[i].GetFunction))(unTagId, pTagPropList->Value[i]);
		if (geoFail(*(pTagPropList->APIStatus[i])))
		{
			nRet = geoERR_TAG_FAIL_IN_BATCH;
		}
	}

	return nRet;
}

///	设置属性列表
geoAPIStatus GeoBaseTagProp::SetTagBasePropList(geoUInt32 unTagId, geoTagPropList * pTagPropList)
{

	geoBool bChanged = geoFALSE;
	geoAPIStatus nRet = geoRET_SUCC;
	geoBool bCannotSet = geoFALSE;

	GEO_ASSERT(IsExist(unTagId));
	for (geoUInt16 i = 0; i<geoProp_TagBase_Max; ++i)
	{
		if (pTagPropList->Value[i] == geoNULL ||
			*(pTagPropList->APIStatus[i]) != geoRET_SUCC)
		{
			continue;
		}
		if (m_pTagBasePropProcess[i].SetFunction == geoNULL)
		{
			bCannotSet = geoTRUE;
			continue;
		}
		GEO_ASSERT(pTagPropList->APIStatus[i] != geoNULL);
		*(pTagPropList->APIStatus[i]) = (this->*m_pTagBasePropProcess[i].SetFunction)(unTagId, pTagPropList->Value[i]);
		if (geoSucc(*(pTagPropList->APIStatus[i])))
		{
			bChanged = geoTRUE;
		}
		else if (*(pTagPropList->APIStatus[i]) != geoERR_TAG_PROP_NOT_CHANGED)
		{
			nRet = geoERR_TAG_FAIL_IN_BATCH;
		}
	}

	if (bChanged)
	{
		geoVariant pValue;
		pValue.varType = geoVarTypeEnum::vTypeTimeStamp;
		pValue.vTimeStamp = geo_get_system_time();
		SetProp_LastModifyTime(unTagId, &pValue);
		//推到需要保存队列中
		PushToChangedList(unTagId);
	}
	if (bCannotSet == geoTRUE)
	{
		return geoERR_TAG_CANNOT_SETPROP;
	}
	return nRet;
}
geoAPIStatus GeoBaseTagProp::GetPropList(
	geoUInt32 unTagId,
	geoTagPropList * pTagPropList)
{
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(IsNotNull(pTagPropList) );

	return GetTagBasePropList(unTagId, pTagPropList);
}



///	设置标签的一批属性
geoAPIStatus GeoBaseTagProp::SetPropList(
	geoUInt32 unTagId,
	geoTagPropList * pTagPropList)
{
	if (unTagId == 0)
	{
		return geoERR_TAG_CANNOT_SETPROP;
	}
	GEO_ASSERT(IsExist(unTagId));
	GEO_ASSERT(pTagPropList != geoNULL);
	GEO_ASSERT(pTagPropList->PropCount>0);


	//	RET_ERR(FillTagBasePropListEx(pPropIdList,pValueList,pAPIStatusList));
	return SetTagBasePropList(unTagId, pTagPropList);

}

//取得数据类型 
inline geoUInt8 GeoBaseTagProp::GetDataType(geoUInt32 unTagId)
{
	return mData[unTagId].DataType;
}

inline geoUInt32 GeoBaseTagProp::GetTagType(geoUInt32 unTagId)
{
	return mData[unTagId].TagType;
}