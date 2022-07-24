#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include "geoStringMap.h"
#include "geoString.h"
#include "geoError.h"
GeoStringMap::GeoStringMap(geoVoid)
{
	hash_.rehash(DEFAULT_NAMEHASH_SIZE);
	this->init();
}

GeoStringMap::GeoStringMap(geoUInt32 size)
{

	hash_.rehash(size);
	this->init();
}
GeoStringMap::~GeoStringMap(geoVoid)
{
	delete_all_ext_id();
	//hash_.clear();
}

geoAPIStatus GeoStringMap::bind(geoChar* name, geoUInt32& id)
{
	//分配空间，并复制字符串
	// 将名称转为大写
	geoChar  *pdata;
	pdata = reinterpret_cast<geoChar*>(malloc(geo_strlen(name) + sizeof(geoChar)));
	if (pdata == geoNULL)
	{
		return geoERR_COMMON_NO_MEMORY;
	}
	geo_strcpy(pdata, name);
	geo_strupr(pdata);

	geoAPIStatus nRet = geoRET_SUCC;
	NameHash_Pair p = hash_.insert(NameHash_ValueType(pdata, id));
	if (p.second == false)
	{
		free(pdata);
		return geoRET_FAIL;
	}
	else
	{
		return geoRET_SUCC;
	}
}

geoAPIStatus GeoStringMap::unbind(geoChar* name, geoUInt32 id)
{
	// 将名称转为大写
	geoAPIStatus nRet = geoRET_SUCC;
	geoChar  *pdata;
	pdata = reinterpret_cast<geoChar*>(malloc(geo_strlen(name) + sizeof(geoChar)));
	geo_strcpy(pdata, name);
	geo_strupr(pdata);

	NameHash_Iter iter = hash_.find(pdata);

	if (iter != hash_.end())
	{
		if (id != 0 && id != iter->second)
		{
			free(pdata);
			return geoRET_FAIL; //Id号不匹配
		}
		hash_.erase(iter);
		nRet = geoRET_SUCC;
	}
	else
	{
		nRet = geoRET_FAIL;
	}
	free(pdata);
	return nRet; 
}


geoAPIStatus GeoStringMap::delete_all_ext_id()
{

	for (NameHash_Iter iter = hash_.begin(); iter != hash_.end(); iter++)
	{
		free((*iter).first);
	}
	return geoRET_SUCC;
}


geoAPIStatus GeoStringMap::find(geoChar* name, geoUInt32& id)
{
	// 将名称转为大写
	geoAPIStatus nRet = geoRET_SUCC;
	geoChar  *pdata = geoNULL;
	pdata = reinterpret_cast<geoChar*>(malloc(geo_strlen(name) + sizeof(geoChar)));
	geo_strcpy(pdata, name);
	geo_strupr(pdata);

	NameHash_Iter iter = hash_.find(pdata);

	if (iter != hash_.end())
	{
		id = iter->second;
		nRet = geoRET_SUCC;
	}
	else
	{
		id = -1;
		nRet = geoERR_TAG_NAME_NOT_EXIST;
	}
	free(pdata);
	return nRet;
}

geoAPIStatus GeoStringMap::init()
{
	geoAPIStatus nRet = geoRET_SUCC;
	// todo: 做个文件存储hashmap，启动时自动生成加载
	return nRet;
}
