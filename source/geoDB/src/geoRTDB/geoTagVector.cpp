#include "preCompile.h"
#include "geoTagVector.h"
#include "geoListEntry.h"


GeoTagVector::GeoTagVector()
{
	this->mCapacity = TAG_DEFUALT_CAPACITY;
	this->mCurrentIndex = 1;
	this->mValidCount = 0;
	mData = geoNULL;
	memset(mStrPathName, 0, sizeof(mStrPathName));
	memset(mAuthor, 0, sizeof(mAuthor));
	memset(mOEM, 0, sizeof(mOEM));
	//取得当前进程运行目录
	geo_getcwd(this->mStrPathName, sizeof(mStrPathName));
	geo_strncat(this->mStrPathName, TAG_DEFAULT_CONFIG_DIR, sizeof(TAG_DEFAULT_CONFIG_DIR));



}

GeoTagVector::GeoTagVector(geoUInt32 unCapacity,
						geoChar * strPathName,
						geoChar * strAuthor ,
						geoChar * strOEM )
{

	this->mCapacity = unCapacity;
	this->mCurrentIndex = 1;
	this->mValidCount = 0;
	mData = geoNULL;
	memset(mStrPathName, 0, sizeof(mStrPathName));
	if (IsNull(strPathName))
	{
		//取得当前进程运行目录
		geo_getcwd(this->mStrPathName, sizeof(mStrPathName));
		geo_strncat(this->mStrPathName, TAG_DEFAULT_CONFIG_DIR, sizeof(TAG_DEFAULT_CONFIG_DIR));
	}
	else
	{
		//手动设置配置文件目录
		geo_strcpy(this->mStrPathName, strPathName);
	}
	geo_strcpy(this->mAuthor, strAuthor);
	geo_strcpy(this->mOEM, strOEM);

}

GeoTagVector::~GeoTagVector()
{
}
geoAPIStatus GeoTagVector::Init()
{
	//分配数据内存
	mData = (geoTagBase *)malloc(mCapacity * sizeof(geoTagBase));
	return 0;

}
geoAPIStatus GeoTagVector::UnInit()
{
	return 0;
}


geoAPIStatus  GeoTagVector::LoadInfoFile(geoChar * strFileFullName)
{
	return 0;
}

geoAPIStatus GeoTagVector::LoadDataFile(geoChar * strFileFullName)
{
	GEO_ASSERT(IsNotNull(strFileFullName));
	GEO_ASSERT(IsNotNull(mData));
	geoAPIStatus nRet = geoRET_FAIL;
	geoChar buff[256] = {0};
	FILE *fp = geoNULL;
	size_t ret = 0;
	fp = ::fopen(strFileFullName, "r");
	if (fp == geoNULL)
	{
		return geoERR_COMMON_FILE_NOT_EXIST;
	}
	char
	//先读信息部分
		//版本 4
		//容量 4
		//有效个数 4
		//当前索引 4
		//作者  32
		//单位  64
		//校验   4
	ret = fread(buff,sizeof(geoUInt32) * 4 + TAG_AUTHOR_SIZE + TAG_OEM_SIZE + ４，)；

		



	return nRet;
}

geoAPIStatus GeoTagVector::SaveInfoFile(geoChar * strFileFullName)
{
	return 0;
}

geoAPIStatus GeoTagVector::SaveDataFile(geoChar * strFileFullName)
{
	return 0;
}

geoAPIStatus GeoTagVector::AddTag(geoUInt32 * tagId)
{
	return 0;
}

geoAPIStatus GeoTagVector::DelTag(geoUInt32 * tagId)
{
	return 0;
}

geoAPIStatus GeoTagVector::InitTag(geoUInt32 tagId)
{
	return 0;
}
