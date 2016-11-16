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
	//ȡ�õ�ǰ��������Ŀ¼
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
		//ȡ�õ�ǰ��������Ŀ¼
		geo_getcwd(this->mStrPathName, sizeof(mStrPathName));
		geo_strncat(this->mStrPathName, TAG_DEFAULT_CONFIG_DIR, sizeof(TAG_DEFAULT_CONFIG_DIR));
	}
	else
	{
		//�ֶ����������ļ�Ŀ¼
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
	//���������ڴ�
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
	//�ȶ���Ϣ����
		//�汾 4
		//���� 4
		//��Ч���� 4
		//��ǰ���� 4
		//����  32
		//��λ  64
		//У��   4
	ret = fread(buff,sizeof(geoUInt32) * 4 + TAG_AUTHOR_SIZE + TAG_OEM_SIZE + ����)��

		



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
