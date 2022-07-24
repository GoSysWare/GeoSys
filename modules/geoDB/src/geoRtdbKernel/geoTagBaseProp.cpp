#include "preCompile.h"
#include "geoTagBaseProp.h"
#include "geoTagMap.h"



//�ж������Ƿ�Ϊ�Ϸ��ı�ǩ��
//��ǩ��Ϊ ���֡���ĸ �� '_'���ţ��������֡���ĸ��ͷ
geoBool CheckTagNameValid(geoChar* ShortName)
{
	//����������ֻ�����ĸ��ͷ������
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
//ͨ���ƥ���飬������ǩ�����ˡ�����������
static bool StrWildMatch(char* str1, char* pattern)
{
	if (str1 == NULL) return false;
	if (pattern == NULL) return false;
	int len1 = strlen(str1);
	int len2 = strlen(pattern);
	int mark = 0;//���ڷֶα��,'*'�ָ����ַ���
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
			// �����ǰ��*�ţ���markǰ��һ�����Ѿ����ƥ�䣬
			// �ӵ�ǰ�㿪ʼ������һ�����ƥ��
			p2++;
			mark = p2;
			continue;
		}
		if (str1[p1] != pattern[p2])
		{
			if (p1 == 0 && p2 == 0)
			{

				// ��������ַ������⴦������ͬ��ƥ��ʧ��
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
			* ����ʾ��ͼ��ʾ���ڱȵ�e��c�������
			* p2���ص�mark����
			* p1��Ҫ���ص���һ��λ�á�
			* ��Ϊ*ǰ�Ѿ����ƥ�䣬����mark���֮ǰ�Ĳ���Ҫ�ٱȽ�
			*/
			p1 -= p2 - mark - 1;
			p2 = mark;
			continue;
		}
		// �˴�������ȵ����

		p1++;
		p2++;
	}
	if (p2 == len2)
	{
		if (p1 == len1)
		{
			// �����ַ����������ˣ�˵��ģʽƥ��ɹ�

			return true;
		}
		if (pattern[p2 - 1] == '*')
		{
			// str1��û�н�������pattern�����һ���ַ���*������ƥ��ɹ�
			return true;
		}
	}
	while (p2<len2)
	{
		// pattern������ַ�ֻҪ��һ������*,ƥ��ʧ��
		if (pattern[p2] != '*')
			return false;
		p2++;
	}
	return true;
}
//�ͷſռ�TagPropList
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
//����ռ�TagPropList
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
	//������Ѿ�ʹ�õı�ǩ�趨��ǩ��
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
	//ʹ�������ַ���������Ϊ�Ƚ����㳤����ֵ
	GEO_ASSERT(pValue->vString.Length <= TAG_NAME_SIZE);
	//ͨ���ƥ��
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

//�˺����ݲ���¶��SetProp�ӿڣ�ֻ������ӵ�ʱ������
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
	//��֤�����ʼ����pValue
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
	//ʹ�������ַ���������Ϊ�Ƚ����㳤����ֵ
	GEO_ASSERT(pValue->vString.Length <= TAG_DESC_SIZE);
	//ͨ���ƥ��
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
	//�������Ƚ����ʱ��������ô��ַ�������Ȼ���ھ������⣬�����������������
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
	// �ٶ��ͻ����ѽ�����ת��Ϊ��׼����
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



///	���ӵ������
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
	//�������Խṹ��ռ�
	if (geoFail(NewTagPropListEx(&pTagPropList, geoProp_TagBase_Max)))
	{
		return geoRET_FAIL;
	}
	//��ֵ���Խṹ��ռ�
	if (geoFail(FillTagBasePropList(pPropValueList, pTagPropList, pAPIStatusList)))
	{
		FreeTagPropList(&pTagPropList);
		return geoRET_FAIL;
	}
	//��ǩ���� ��ǩ���͡��������ͱ�����
	if (pTagPropList->Value[geoProp_Name] == geoNULL ||
		pTagPropList->Value[geoProp_TagType] == geoNULL ||
		pTagPropList->Value[geoProp_DataType] == geoNULL)
	{
		FreeTagPropList(&pTagPropList);
		return geoERR_TAG_ADD;
	}
	//�������ͱ�����Ч
	if (pTagPropList->Value[geoProp_DataType]->varType == geoVarTypeEnum::vTypeEmpty)
	{
		FreeTagPropList(&pTagPropList);
		return geoERR_TAG_WRONG_NAME;
	}
	//����Ƿ�Ϊ��Ч�ĵ��ַ�������
	if (CheckTagNameValid(pTagPropList->Value[geoProp_Name]->vString.Data) == geoFALSE)
	{
		FreeTagPropList(&pTagPropList);
		return geoERR_TAG_WRONG_NAME;
	}
	//�����ǩ���Ѿ����ڣ�Ҳ���ɹ�
	if (!mHash->find(pTagPropList->Value[geoProp_Name]->vString.Data))
	{
		return geoERR_TAG_NAME_REDUPLICATE;
	}



	///������Ч�Լ��
	///todo
	///.....

	//��ӱ�ǩ�ţ���Զ������ĩβ��ӣ�������pop
	nRet = GeoTagVector::AddTag(pnNewTagId);
	if (nRet)
	{
		FreeTagPropList(&pTagPropList);
		return nRet;
	}

	nRet = SetTagBasePropList(*pnNewTagId, pTagPropList);
	//��������õ����г�����һЩ������������ֻ�����ԡ�����ֵ�ޱ仯�ȴ���,
	//����������Ҫ�����
	if (nRet == geoERR_TAG_FAIL_IN_BATCH)
	{
		//Ҫ���AddTag�ı�ǩId����յı�ǩ�������һ��Id
		ClearTag(*pnNewTagId);
		*pnNewTagId = geoTagId_Unused;
		FreeTagPropList(&pTagPropList);
		return nRet;
	}
	geoVariant pValue;
	pValue.varType = geoVarTypeEnum::vTypeTimeStamp;
	pValue.vTimeStamp = geo_get_system_time();
	SetProp_CreateTime(*pnNewTagId, &pValue);
	//�Ƶ���Ҫ���������
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

///	�õ���ǩ��һ������
/// pValueList pPropIdList ����Ҫ����ר�ŵ��ڴ���亯������ռ�
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
///	�õ������б�
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

///	���������б�
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
		//�Ƶ���Ҫ���������
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



///	���ñ�ǩ��һ������
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

//ȡ���������� 
inline geoUInt8 GeoBaseTagProp::GetDataType(geoUInt32 unTagId)
{
	return mData[unTagId].DataType;
}

inline geoUInt32 GeoBaseTagProp::GetTagType(geoUInt32 unTagId)
{
	return mData[unTagId].TagType;
}