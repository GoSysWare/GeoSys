#include "preCompile.h"
#include "geoTagVector.h"



GeoTagVector::GeoTagVector()
{
	//��ʼ������Ϣ
	memset(&mDataBaseInfo, 0, sizeof(geoDataBaseInfo));
	mDataBaseInfo.Version = GEOSYS_RTDB_VERSION;
	mDataBaseInfo.Capacity = TAG_DEFUALT_CAPACITY;
	mDataBaseInfo.CurrentIndex = 1;
	mDataBaseInfo.ValidCount = 0;
	geo_strcpy(mDataBaseInfo.Author, TAG_INFO_DEFAULT_AUTHOR);
	geo_strcpy(mDataBaseInfo.OEM, TAG_INFO_DEFAULT_OEM);


	mData = geoNULL;
	memset(mStrPathName, 0, sizeof(mStrPathName));
	//ȡ�õ�ǰ��������Ŀ¼
	geo_getcwd(this->mStrPathName, sizeof(mStrPathName));
	geo_strncat(this->mStrPathName, TAG_DEFAULT_CONFIG_DIR, sizeof(TAG_DEFAULT_CONFIG_DIR));
	geo_strncat(this->mStrPathName, TAG_DATA_FILENAME, sizeof(TAG_DATA_FILENAME));

}
//��ʼ���ȸ��ڲ���ֵ������������ļ����ʼֵ������
GeoTagVector::GeoTagVector(geoChar * strPathName,
						geoUInt32 unCapacity,
						geoChar * strAuthor ,
						geoChar * strOEM )
{

	//��ʼ������Ϣ
	memset(&mDataBaseInfo, 0, sizeof(geoDataBaseInfo));
	mDataBaseInfo.Version = GEOSYS_RTDB_VERSION;
	//���õ�����С��400 ������4w��Ϊ��ʼ����
	//���õ���������20W����20W��Ϊ��ʼ����
	mDataBaseInfo.Capacity = unCapacity < (TAG_DEFUALT_CAPACITY / 100) ?
								TAG_DEFUALT_CAPACITY:
									unCapacity  > TAG_MAX_CAPACITY ?
													TAG_MAX_CAPACITY: unCapacity;
	mDataBaseInfo.CurrentIndex = 1;
	mDataBaseInfo.ValidCount = 0;
	geo_strcpy(mDataBaseInfo.Author, strAuthor);
	geo_strcpy(mDataBaseInfo.OEM, strOEM);


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
	geo_strncat(this->mStrPathName, TAG_DATA_FILENAME, sizeof(TAG_DATA_FILENAME));
}

GeoTagVector::~GeoTagVector()
{
}
geoAPIStatus GeoTagVector::Init()
{
	geoAPIStatus nRet = geoRET_FAIL;
	//��������ļ��Ƿ����

	if (geo_access(mStrPathName,6) ==  0)
	{
		nRet = LoadDataFile(mStrPathName);
	}
	else//������
	{
		//����ռ�
		mData = (geoTagBase *)malloc(mDataBaseInfo.Capacity * sizeof(geoTagBase));
		if (IsNull(mData))
		{
			return geoERR_COMMON_NO_MEMORY;
		}
		//��ʼ������ǩ ID=0
		geoTagBase* pTag = mData;
		memset((geoVoid*)(pTag), 0, sizeof(geoTagBase));
		pTag->ParentId = geoTagId_Unused;
		pTag->NextId = geoTagId_Unused;
		pTag->PrevId = geoTagId_Unused;
		pTag->FirstChildId = geoTagId_Unused;
		pTag->Id = geoTagId_Root;
		pTag->Flag.IsNode = 1;
		SetChangedFlag(0);
		mChangedList.push_back(0);

		nRet = geoRET_SUCC;
	}
	//��ʱ�ռ�ΪmCapacity ;mCurrentIndex = 1; mValidCount = 0;
	return nRet;

}




geoAPIStatus GeoTagVector::UnInit()
{
	
	SaveDataFile(mStrPathName);

	if (IsNotNull(mData))
	{
		free(mData);
		mData = geoNULL;
	}
	return 0;
}


geoAPIStatus GeoTagVector::LoadDataFile(geoChar * strFileFullName)
{
	GEO_ASSERT(IsNotNull(strFileFullName));
	GEO_ASSERT(IsNull(mData));
	geoAPIStatus nRet = geoRET_FAIL;
	FILE *fp = geoNULL;
	geoUInt32 * temp = geoNULL;
	size_t ret = 0;
	geoUInt32 checkCRC;
	fp = ::fopen(strFileFullName, "rb");
	if (IsNull(fp))
	{
		return geoERR_TAG_DATAFILE_OPEN;
	}
	//�ȶ���Ϣ����
	ret = fread(&mDataBaseInfo, sizeof(geoDataBaseInfo), 1, fp);
	//У����Ϣ
	//checkCRC = crc32(buff, sizeof(geoUInt32) * 4 + TAG_AUTHOR_SIZE + TAG_OEM_SIZE);
	checkCRC = crc32(&mDataBaseInfo, RTK_FIELD_OFFSET(geoDataBaseInfo, Check));
	if (mDataBaseInfo.Check != checkCRC)
	{
		fclose(fp);
		return geoERR_COMMON_CHECK_FAILED;
	}
	if (mDataBaseInfo.Version != GEOSYS_RTDB_VERSION)
	{
		fclose(fp);
		return geoERR_TAG_DATAFILE_VERSION;
	}
	//���������ļ���������
	mData = (geoTagBase *)malloc(mDataBaseInfo.Capacity * sizeof(geoTagBase));
	if (IsNull(mData))
	{
		fclose(fp);
		return geoERR_COMMON_NO_MEMORY;
	}
	//�����ݲ���
	fpos_t pos = sizeof(geoDataBaseInfo);
	fsetpos(fp, &pos);
	ret = fread(mData, sizeof(geoTagBase), mDataBaseInfo.CurrentIndex, fp);
	if (ret !=  mDataBaseInfo.CurrentIndex)
	{
		free(mData);
		mData = geoNULL;
		fclose(fp);
		return geoERR_COMMON_FILE_FAILED;
	}
	fclose(fp);
	//��ʼ���б���ص�ֵ�������ָ�룬����ÿ�ζ���Ҫ���¸�ֵ
	for (geoUInt32 i = 0; i < mDataBaseInfo.CurrentIndex; i++)
	{
		RtkInitializeListHead(&mData[i].DeviceLink);
		RtkInitializeListHead(&mData[i].RefreshLink);
	}

	nRet = geoRET_SUCC;
	return nRet;
}


geoAPIStatus GeoTagVector::SaveDataFile(geoChar * strFileFullName)
{
	GEO_ASSERT(IsNotNull(strFileFullName));
	GEO_ASSERT(IsNotNull(mData));
	geoAPIStatus nRet = geoRET_FAIL;
	FILE *fp = geoNULL;
	geoUInt32 nTagId = geoTagId_Root;
	size_t ret = 0;

	//�ж��Ƿ����
	if (geo_access(strFileFullName, 0) != 0)
	{
		//wb ֻд�򿪻��½�һ���������ļ���ֻ����д���ݡ�
		fp = fopen(strFileFullName, "wb");
		if (IsNull(fp))
		{
			return geoERR_TAG_DATAFILE_OPEN;
		}
	}
	else
	{
		//��r+�� �Կɶ�д��ʽ���ļ������ļ�������ڡ�
		fp =fopen(strFileFullName, "r+b");
		if (fp == 0)
		{
			return geoERR_TAG_DATAFILE_CREATE;
		}
	}
	//Ԥ����СΪ���������С
	//geo_ftruncate(fp, mDataBaseInfo.Capacity* sizeof(geoTagBase) + sizeof(geoDataBaseInfo));
	//�����ݿ���Ϣ
	//����У����
	mDataBaseInfo.Check = crc32(&mDataBaseInfo, RTK_FIELD_OFFSET(geoDataBaseInfo, Check));
	//д���ļ�
	ret = fwrite(&mDataBaseInfo, sizeof(geoDataBaseInfo), 1, fp);
	if (ret != 1)
	{
		fclose(fp);
		return geoERR_TAG_DATAFILE_SAVE;
	}

	//һ�����Ĵ�����,���Ч���޷��ı�
	fpos_t pos = 0;
	for each (auto tagId in mChangedList)
	{
		pos = tagId * sizeof(geoTagBase) + sizeof(geoDataBaseInfo);
		fsetpos(fp, &pos);
		ret = fwrite(mData + tagId, sizeof(geoTagBase),1, fp);
		if (ret != 1)
		{
			fclose(fp);
			return geoERR_TAG_DATAFILE_SAVE;
		}
	}
	//���ȥ��mChangedListҪ���
	mChangedList.clear();
	fclose(fp);
	nRet = geoRET_SUCC;
	return nRet;
}

geoAPIStatus GeoTagVector::AddTag(geoUInt32 * tagId)
{
	GEO_ASSERT(tagId != geoNULL);
	if (mDataBaseInfo.CurrentIndex < mDataBaseInfo.Capacity)
	{
		*tagId = mDataBaseInfo.CurrentIndex;
		mDataBaseInfo.CurrentIndex++;
	}
	else
	{
		*tagId = geoTagId_Unused;
		return geoERR_TAG_COUNT_OVERFLOW;
	}
	//��ʼ����ǩ
	InitTag(*tagId);

	//��Ч��ǩ����
	mDataBaseInfo.ValidCount++;
	return 0;
}

///ɾ���ı�ǩ�����ã�indexֻ������
geoAPIStatus GeoTagVector::DelTag(geoUInt32  tagId)
{
	if (tagId >= mDataBaseInfo.Capacity)
	{
		// ͳһTRACE
		return geoERR_TAG_NOT_EXIST;
	}
	if (tagId == 0)
	{
		// ����㲻�ܱ�ɾ��
		// ͳһTRACE
		return geoERR_TAG_DELETE_ROOT;
	}
	if (IsDeleted(tagId))
	{
		// ͳһTRACE
		return geoERR_TAG_HAVE_DELETED;
	}

	mData[tagId].Flag.Deleted = 1;
	mData[tagId].Flag.Changed = 1;



	//��Ч��ǩ����
	mDataBaseInfo.ValidCount--;
	return 0;
}

geoAPIStatus GeoTagVector::PushToChangedList(geoUInt32 tagId)
{
	geoAPIStatus nRet = geoRET_SUCC;
	mChangedList.push_back(tagId);
	return nRet;
}

geoAPIStatus GeoTagVector::SyncTagToFile()
{
	return SaveDataFile(mStrPathName);
}

geoAPIStatus GeoTagVector::InitTag(geoUInt32 tagId)
{
	GEO_ASSERT((tagId >= 0 && tagId< mDataBaseInfo.CurrentIndex));
	geoTagBase* pTag = mData + tagId;
	memset(pTag, 0, sizeof(geoTagBase));
	pTag->TagType = geoTagTypeEnum::TagType_Invalid;
	pTag->DataType = (geoUInt8)geoVarTypeEnum::vTypeEmpty;

	//Id�ŵײ㲻��ֵ�����ϲ㸳ֵ��
	pTag->Id = geoTagId_Unused;
	pTag->ParentId = geoTagId_Unused;
	pTag->NextId = geoTagId_Unused;
	pTag->PrevId = geoTagId_Unused;
	pTag->FirstChildId = geoTagId_Unused;
	pTag->Unit = 0;		//Ĭ�ϵ�λ���Ϊ 0
	pTag->Flag.Changed = 1;
	pTag->Flag.Deleted = 0;
	pTag->CreateTime = geo_get_system_time();

	RtkInitializeListHead(&pTag->DeviceLink);
	RtkInitializeListHead(&pTag->RefreshLink);
	return 0;
}
///��ձ�ǩ,�ع�һ���Ѿ����ڵı�ǩ
geoAPIStatus GeoTagVector::ClearTag(geoUInt32 tagId)
{
	geoTagBase* pTag = mData + tagId;
	memset(pTag, 0, sizeof(geoTagBase));
	//��Ч��ǩ����
	mDataBaseInfo.ValidCount--;
	//��ǰ��ǩ����
	mDataBaseInfo.CurrentIndex -- ;
	return 0;
}