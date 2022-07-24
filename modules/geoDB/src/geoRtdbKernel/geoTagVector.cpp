#include "preCompile.h"
#include "geoTagVector.h"



GeoTagVector::GeoTagVector()
{
	//初始化库信息
	memset(&mDataBaseInfo, 0, sizeof(geoDataBaseInfo));
	mDataBaseInfo.Version = GEOSYS_RTDB_VERSION;
	mDataBaseInfo.Capacity = TAG_DEFUALT_CAPACITY;
	mDataBaseInfo.CurrentIndex = 1;
	mDataBaseInfo.ValidCount = 0;
	geo_strcpy(mDataBaseInfo.Author, TAG_INFO_DEFAULT_AUTHOR);
	geo_strcpy(mDataBaseInfo.OEM, TAG_INFO_DEFAULT_OEM);


	mData = geoNULL;
	memset(mStrPathName, 0, sizeof(mStrPathName));
	//取得当前进程运行目录
	geo_getcwd(this->mStrPathName, sizeof(mStrPathName));
	geo_strncat(this->mStrPathName, TAG_DEFAULT_CONFIG_DIR, sizeof(TAG_DEFAULT_CONFIG_DIR));
	geo_strncat(this->mStrPathName, TAG_DATA_FILENAME, sizeof(TAG_DATA_FILENAME));

}
//初始化先给内部赋值，如果有配置文件则初始值被覆盖
GeoTagVector::GeoTagVector(geoChar * strPathName,
						geoUInt32 unCapacity,
						geoChar * strAuthor ,
						geoChar * strOEM )
{

	//初始化库信息
	memset(&mDataBaseInfo, 0, sizeof(geoDataBaseInfo));
	mDataBaseInfo.Version = GEOSYS_RTDB_VERSION;
	//设置的容量小于400 ，都以4w作为初始容量
	//设置的容量大于20W，以20W作为初始容量
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
		//取得当前进程运行目录
		geo_getcwd(this->mStrPathName, sizeof(mStrPathName));
		geo_strncat(this->mStrPathName, TAG_DEFAULT_CONFIG_DIR, sizeof(TAG_DEFAULT_CONFIG_DIR));
	}
	else
	{
		//手动设置配置文件目录
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
	//检查配置文件是否存在

	if (geo_access(mStrPathName,6) ==  0)
	{
		nRet = LoadDataFile(mStrPathName);
	}
	else//不存在
	{
		//分配空间
		mData = (geoTagBase *)malloc(mDataBaseInfo.Capacity * sizeof(geoTagBase));
		if (IsNull(mData))
		{
			return geoERR_COMMON_NO_MEMORY;
		}
		//初始化根标签 ID=0
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
	//此时空间为mCapacity ;mCurrentIndex = 1; mValidCount = 0;
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
	//先读信息部分
	ret = fread(&mDataBaseInfo, sizeof(geoDataBaseInfo), 1, fp);
	//校验信息
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
	//根据配置文件建立数据
	mData = (geoTagBase *)malloc(mDataBaseInfo.Capacity * sizeof(geoTagBase));
	if (IsNull(mData))
	{
		fclose(fp);
		return geoERR_COMMON_NO_MEMORY;
	}
	//读数据部分
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
	//初始化列表相关的值，这个是指针，所以每次都需要重新赋值
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

	//判断是否存在
	if (geo_access(strFileFullName, 0) != 0)
	{
		//wb 只写打开或新建一个二进制文件；只允许写数据。
		fp = fopen(strFileFullName, "wb");
		if (IsNull(fp))
		{
			return geoERR_TAG_DATAFILE_OPEN;
		}
	}
	else
	{
		//“r+” 以可读写方式打开文件，该文件必须存在。
		fp =fopen(strFileFullName, "r+b");
		if (fp == 0)
		{
			return geoERR_TAG_DATAFILE_CREATE;
		}
	}
	//预定大小为最大容量大小
	//geo_ftruncate(fp, mDataBaseInfo.Capacity* sizeof(geoTagBase) + sizeof(geoDataBaseInfo));
	//存数据库信息
	//生成校验码
	mDataBaseInfo.Check = crc32(&mDataBaseInfo, RTK_FIELD_OFFSET(geoDataBaseInfo, Check));
	//写入文件
	ret = fwrite(&mDataBaseInfo, sizeof(geoDataBaseInfo), 1, fp);
	if (ret != 1)
	{
		fclose(fp);
		return geoERR_TAG_DATAFILE_SAVE;
	}

	//一个个的存起来,这个效率无法改变
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
	//存进去后mChangedList要清空
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
	//初始化标签
	InitTag(*tagId);

	//有效标签增加
	mDataBaseInfo.ValidCount++;
	return 0;
}

///删除的标签不复用，index只增不减
geoAPIStatus GeoTagVector::DelTag(geoUInt32  tagId)
{
	if (tagId >= mDataBaseInfo.Capacity)
	{
		// 统一TRACE
		return geoERR_TAG_NOT_EXIST;
	}
	if (tagId == 0)
	{
		// 根结点不能被删除
		// 统一TRACE
		return geoERR_TAG_DELETE_ROOT;
	}
	if (IsDeleted(tagId))
	{
		// 统一TRACE
		return geoERR_TAG_HAVE_DELETED;
	}

	mData[tagId].Flag.Deleted = 1;
	mData[tagId].Flag.Changed = 1;



	//有效标签减少
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

	//Id号底层不赋值，给上层赋值用
	pTag->Id = geoTagId_Unused;
	pTag->ParentId = geoTagId_Unused;
	pTag->NextId = geoTagId_Unused;
	pTag->PrevId = geoTagId_Unused;
	pTag->FirstChildId = geoTagId_Unused;
	pTag->Unit = 0;		//默认单位编号为 0
	pTag->Flag.Changed = 1;
	pTag->Flag.Deleted = 0;
	pTag->CreateTime = geo_get_system_time();

	RtkInitializeListHead(&pTag->DeviceLink);
	RtkInitializeListHead(&pTag->RefreshLink);
	return 0;
}
///清空标签,回滚一个已经存在的标签
geoAPIStatus GeoTagVector::ClearTag(geoUInt32 tagId)
{
	geoTagBase* pTag = mData + tagId;
	memset(pTag, 0, sizeof(geoTagBase));
	//有效标签减少
	mDataBaseInfo.ValidCount--;
	//当前标签回退
	mDataBaseInfo.CurrentIndex -- ;
	return 0;
}