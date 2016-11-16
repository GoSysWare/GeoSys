#ifndef	LIB_RECORDS_EXPORTS
#define	LIB_RECORDS_EXPORTS
#endif
#include "preCompile.h"
#include "geoRecDBTables.h"
#include "geoRecBaseDB.h"
//当存入内容为字符串时，用内存对比会比字符串耗时，因为字符串对比遇'\0'结束，
//但用内存对比灵活性较大，因为可以对比int long float甚至时结构体等型时，很通用
geoInt32 CDBTables_Impl::DbCompareFunc(Db *_db, const Dbt * Key_1, const Dbt * Key_2)
{
	geoInt32 ret = memcmp(Key_1->get_data(), Key_2->get_data(), COLUMN_KEY_SIZE);
	return ret;
}

CDBTables_Impl::CDBTables_Impl(DbEnv *dbEnv,DBTYPE dbType):CRecBaseDB_Impl(dbEnv,dbType)
{
	db_->set_bt_compare(&CDBTables_Impl::DbCompareFunc);
}
CDBTables_Impl::~CDBTables_Impl()
{

}
geoInt32 CDBTables_Impl::Init(geoUInt8 nKeyType, geoUInt32 nKeySize, geoUInt8 nValType, geoUInt32 nValSize)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//key时列名,字符串
	SetKeyDbcType(vTypeString);
	SetKeyDbcSize(nKeySize);
	//val是geoColumnInfo结构体,geoDataType_Blob
	SetValDbcType(vTypeBlob);
	SetValDbcSize(nValSize);
	return nRet;
}
geoInt32 CDBTables_Impl::UnInit()
{
	geoAPIStatus nRet = geoRET_SUCC;
	return nRet;
}
geoInt32 CDBTables_Impl::AddRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	geoChar *_key = geoNULL;
	geoByte *_data = geoNULL;
	NewAndClear((geoVoid **)&_key, nKeyDbcSize_);
	::memcpy(_key, dbKey, strlen((geoChar*)dbKey));
	NewAndClear((geoVoid **)&_data, nValDbcSize_);


	::memcpy(_data, dbVal, sizeof(geoColumnInfo));
	Dbc *cursor_ptr = geoNULL;;
	db_->cursor(NULL, &cursor_ptr, 0);

	Dbt key(_key, nKeyDbcSize_);
	Dbt data(_data,nValDbcSize_);

	geoInt32 ret = cursor_ptr->put(&key, &data, DB_KEYFIRST);


	if (cursor_ptr != NULL)
	{
		cursor_ptr->close();
	}
	FreeAndNull((geoVoid **)&_key);
	FreeAndNull((geoVoid **)&_data);
	if (ret != 0)
	{
		return geoRET_FAIL;
	}

	return nRet;
}
//插入操作暂不实现
geoInt32 CDBTables_Impl::InsertRec(geoVoid *dbcursor, geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	nRet = geoRET_FAIL;
	return nRet;
}
geoInt32 CDBTables_Impl::DelRec(geoVoid *dbKey)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoChar *_key = geoNULL;

	NewAndClear((geoVoid **)&_key, nKeyDbcSize_);
	memcpy(_key, dbKey, strlen((geoChar*)dbKey));

	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	Dbt tempkey(_key, nKeyDbcSize_);
	Dbt data;
	if (cursorp->get(&tempkey, &data, DB_SET) == 0)
	{
		cursorp->del(0);
	}

	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	FreeAndNull((geoVoid **)&_key);
	return nRet;
}
//不修改Key，只修改Val
geoInt32 CDBTables_Impl::MfyRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	GEO_ASSERT(IsNotNull(dbVal));
	geoChar *_key = geoNULL;
	geoByte *_data = geoNULL;
	NewAndClear((geoVoid **)&_key, nKeyDbcSize_);
	memcpy(_key, dbKey, strlen((geoChar*)dbKey));
	NewAndClear((geoVoid **)&_data, nValDbcSize_);


	memcpy(_data, dbVal, nValDbcSize_);

	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey(_key, nKeyDbcSize_);
	Dbt tempdata;
	//Dbt tempdata1;
	//Dbt key(_key, nKeyDbcSize_);
	Dbt data(_data, nValDbcSize_);
	if ((nRet = cursorp->get(&tempkey, &tempdata, DB_SET)) == 0)
	{
		nRet = cursorp->put(&tempkey, &data, DB_CURRENT);
	}
	FreeAndNull((geoVoid **)&_key);
	FreeAndNull((geoVoid **)&_data);
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
geoInt32 CDBTables_Impl::GetRec(geoVoid *dbKey, geoVoid **dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//GEO_ASSERT(IsNotNull(dbKey));
	//GEO_ASSERT(IsNotNull(dbVal));
	//GEO_ASSERT(IsNull(*dbVal));

	geoChar *_key = geoNULL;

	//Key输入缓冲,用缓冲是因为输入的dbKey可能比nKeyDbcSize_小，而此db是内存对比的，所以需要将多出的内存部分清零
	NewAndClear((geoVoid **)&_key, nKeyDbcSize_);
	memcpy(_key, dbKey, strlen((geoChar*)dbKey));

	//Value输出缓冲
	NewAndClear(dbVal, nValDbcSize_);

	//ACE_DEBUG((LM_DEBUG, "CDBTables_Impl::GetRec --nValDbcSize_: %d\n",nValDbcSize_));

	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey(_key, nKeyDbcSize_);
	Dbt tempdata;

	if ((nRet = cursorp->get(&tempkey, &tempdata, DB_SET)) == 0)
	{
		memcpy(*dbVal, tempdata.get_data(), nValDbcSize_);
	}
	FreeAndNull((geoVoid **)&_key);
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
geoInt32 CDBTables_Impl::QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoStringList **keyname = (geoStringList **)ppReconlist;
	//输出缓冲区
	std::vector<string> tempVector;

	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey;;
	Dbt tempdata;

	while ((nRet = cursorp->get(&tempkey, &tempdata, DB_NEXT)) == 0)
	{
		string temp((char*)tempkey.get_data());
		tempVector.push_back(temp);
	}
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	if (tempVector.size() > 0)
	{
		NewStrListEx(keyname,tempVector.size());
		for (geoUInt32 i = 0; i < tempVector.size() ; i++)
		{
			NewAndCopyStr(&(*keyname)->List[i], tempVector[i].c_str());
		}
	}
	else
	{
		NewStrList(keyname);
	}
	return nRet;
}
