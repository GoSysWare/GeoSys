#include "preCompile.h"
#include "geoTagMap.h"



GeoTagMap::GeoTagMap():GeoStringMap()
{

}
GeoTagMap::GeoTagMap(geoUInt32 size):GeoStringMap(size)
{

}


///根据名字取得ID
geoUInt32 GeoTagMap::GetId(geoChar * pTagName)
{
	GEO_ASSERT(pTagName != geoNULL);
	GEO_ASSERT(geo_strlen(pTagName) <= TAG_NAME_SIZE);
	geoUInt32 unTagId;
	find(pTagName, unTagId);
	return unTagId;
}
///根据名字取得ID
geoAPIStatus GeoTagMap::GetId(geoChar * pTagName, geoUInt32 &unTagId)
{
	geoUInt32 tagId;
	geoAPIStatus nRet = geoRET_SUCC;
	nRet = find(pTagName, tagId);
	//如果没找到
	if (tagId == -1)
	{
		unTagId = geoTagId_Unused;
	}
	return nRet;
}
///根据名字取得ID
///pTagNameList和pTagIdList 需要提前分配空间
///如果有一个标签名没找到，函数返回值是geoERR_TAG_FAIL_IN_BATCH，参数pTagIdList返回Id=geoTagId_Unused
geoAPIStatus GeoTagMap::GetIdList(geoStringList *pTagNameList, geoTagIdList * pTagIdList)
{
	GEO_ASSERT(pTagNameList != geoNULL);
	GEO_ASSERT(pTagNameList->List != geoNULL);
	GEO_ASSERT(pTagIdList != geoNULL);
	GEO_ASSERT(pTagIdList->TagIdList != geoNULL);
	GEO_ASSERT(pTagIdList->TagCount == pTagNameList->Count);
	geoAPIStatus nRet = geoRET_SUCC;
	for (geoUInt32 i = 0; i < pTagNameList->Count; i++)
	{
		nRet = find(pTagNameList->List[i], pTagIdList->TagIdList[i]);
		//如果没找到
		if (pTagIdList->TagIdList[i] == -1)
		{
			nRet = geoERR_TAG_FAIL_IN_BATCH;
			pTagIdList->TagIdList[i] = geoTagId_Unused;
		}
	}
	return nRet;
}