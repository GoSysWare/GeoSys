
#include "preCompile.h"
#include "geoRecTableManager.h"
//#include <unistd.h>
#include <sys/stat.h>


CTableManager::CTableManager()
{
	strcpy(strFileName_, DEFAULT_TABLESMGR_DBFILNAME);
	tableCount_ = 0;
	envPath_ = NULL;
	tbIsInitFinished_ = geoFALSE;
}

CTableManager::~CTableManager()
{
	if (IsNotNull(tbMgrImpl_))
			{
				delete tbMgrImpl_;
			}
			if (IsNotNull(tbMgr_))
			{
				delete tbMgr_;
			}
			if (IsNotNull(dbEnv_))
			{
				delete dbEnv_;
			}
			if (IsNotNull(envPath_))
			{
				free(envPath_);
			}
}
geoInt32 CTableManager::Init(geoStr envPath)
{	
	geoAPIStatus nRet = geoRET_SUCC;
	if (tbIsInitFinished_ == geoTRUE)
	{
		return geoRET_FAIL;
	}
	if (IsNull(envPath) || !strcmp(envPath, ""))
	{
		return geoRET_FAIL;
	}
	NewAndCopyStr(&envPath_, envPath);
	////ACE_DIR *base_dir = opendir_emulation(envPath_);
	//ACE_DIR *base_dir = opendir(envPath_);
	//if(!base_dir)
	//{
	//	mkdir(envPath_, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
	//	ACE_DIR *again_dir = opendir(envPath_);
	//	if(!again_dir)
	//	{
	//		return geoRET_FAIL;
	//	}
		//todo:remmber
//		if(!mkdir(envPath_, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH))
//		  return geoRET_FAIL;
	}

	GEO_NEW_NORETURN(dbEnv_ , DbEnv(0));
	dbEnv_->set_cachesize(0, DEFAULT_ENV_CACHESIZE, DEFAULT_ENV_CACHENUM);
	dbEnv_->open(envPath_, DB_CREATE | DB_INIT_MPOOL | DB_PRIVATE, 0);


	GEO_NEW_RETURN(tbMgrImpl_ , CDBTables_Impl(dbEnv_), geoRET_FAIL);
	GEO_NEW_RETURN(tbMgr_ , CRecBaseDB(tbMgrImpl_), geoRET_FAIL);


	tbMgrImpl_->Init(vTypeString, TABLE_KEY_SIZE, geoDataType_Blob, sizeof(geoRecTableInfo));


	tbMgr_->InitDB(strFileName_, strFileName_);

	tbMgr_->OpenDB();
	tbIsInitFinished_ = geoFALSE;
	tbMgr_->GetKeyNum(&tableCount_);

	geoStringList *keynames = geoNULL;

	tbMgr_->QueryRec_Range(0, 0, 0, (geoVoid **)&keynames);

//	ACE_ASSERT(tableCount_ == keynames->Count);
	for (geoUInt32 i = 0; i <keynames->Count; i++ )
	{
		CreateTable(keynames->List[i]);
	}
	tbIsInitFinished_ = geoTRUE;
	FreeStrList(&keynames);
	return nRet;
}

geoInt32 CTableManager::UnInit()
{	
	geoAPIStatus nRet = geoRET_SUCC;
	if (tbIsInitFinished_ == geoTRUE)
	{
		tbMgr_->SyncDB();
		tbMgr_->CloseDB();

		if (IsNotNull(tbMgrImpl_))
		{
			delete tbMgrImpl_;
		}
		if (IsNotNull(tbMgr_))
		{
			delete tbMgr_;
		}
		if (IsNotNull(dbEnv_))
		{
			delete dbEnv_;
		}
		if (IsNotNull(envPath_))
		{
			free(envPath_);
		}
		tableCount_ = 0;
		tableList_.clear();
		_savePeriod = 0;
		_mpoolSize = 0;
		tbIsInitFinished_ = geoFALSE;
	}
	return nRet;
}

geoInt32 CTableManager::CreateTable(geoStr tableName)
{
	geoAPIStatus nRet = geoRET_SUCC;

	if (tableCount_ >= TABLE_MAX_SIZE)
	{
		return geoRET_FAIL;	
	}

	if (IsTableExist(tableName)== geoTRUE)
	{
		return geoRET_FAIL;
	}

	RecTable_ptr recTable = geoNULL;
	

	GEO_NEW_RETURN(recTable, CRecTable(tableName, envPath_, dbEnv_), geoRET_FAIL);

	RET_ERR(recTable->TB_CreateTable(tableName));


	geoTableName tbn;
	strcpy(tbn.Data, tableName);

	tableList_.insert(geoTableMap::value_type(tbn, recTable));

	if (tbIsInitFinished_ == geoTRUE)
	{
		RET_ERR(tbMgr_->AddRec(tableName, &recTable->tbInfo_));
		tableCount_++;
	}
	tbMgr_->SyncDB();	
	return nRet;
}

geoInt32 CTableManager::OpenTable(geoStr tableName)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (tbIsInitFinished_ == geoFALSE)
	{
		return geoRET_FAIL;
	}
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_OpenTable());
	return nRet;
}

geoInt32 CTableManager::AddColumnItem(geoStr tableName, geoStr columnName, geoUInt8 valueType, geoUInt32 columnSize)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_AddColumnItem(columnName, valueType, columnSize));
	return nRet;
}

geoInt32 CTableManager::DelColumnItem(geoStr tableName, geoStr columnName)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_DelColumnItem(columnName));
	return nRet;
}

geoInt32 CTableManager::CloseTable(geoStr tableName)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_CloseTable());
	return nRet;
}

/// <summary>
///	同步表格

geoInt32 CTableManager::SyncTab(geoStr tableName)
{
	geoAPIStatus nRet = geoRET_SUCC;
		RecTable_ptr tb = GetRecTableByName(tableName);
		if (IsNull(tb))
		{
			return geoRET_FAIL;
		}
		RET_ERR(tb->TB_SyncTable());
		return nRet;
}

geoInt32 CTableManager::DeleteTable(geoStr tableName)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb= GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_DelTable());
	DelRecTableByName(tableName);
	tableCount_--;
	tbMgr_->SyncDB();
	return nRet;
}

geoInt32 CTableManager::CloseAllTab()
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoTableMapIter it = tableList_.begin();

	while (it != tableList_.end())
	{
		it->second->TB_CloseTable();
		it++;
	}
	return nRet;
}

geoInt32 CTableManager::SyncAllOpenTab()
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoTableMapIter it = tableList_.begin();

	while (it != tableList_.end())
	{
		it->second->TB_SyncTable();
		it++;
	}
	return nRet;
}


geoInt32 CTableManager::DelAllTab()
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoTableMapIter it = tableList_.begin();

	while (it != tableList_.end())
	{
		it->second->TB_DelTable();
		it++;
	}
	return nRet;
}

geoInt32 CTableManager::GetTableInfo(geoStr tableName, geoRecTableInfo *tbInfo)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	*tbInfo = tb->tbInfo_;
	return nRet;
}

geoInt32 CTableManager::AddRecord(geoStr tableName, geoStr nFieldName, geoVariant *pValue)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_AddRecord(nFieldName, pValue));
	return nRet;
}

geoInt32 CTableManager::AddRow(geoStr tableName, geoStringList *nFieldList, geoVariantList *nValueList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_AddRow(nFieldList, nValueList))
	return nRet;
}

geoInt32 CTableManager::DelRecord(  geoStr tableName,  geoStr columnName, geoUInt32 recno)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if(IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_DelRecord(columnName, recno));
	return nRet;
}

geoInt32 CTableManager::DelRow(geoStr tableName, geoUInt32 recno)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_DelRow(geoNULL, recno));
	return nRet;
}

geoInt32 CTableManager::ModifyRecord(geoStr tableName, geoStr columnName, geoUInt32 recno, geoVariant *nval)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_MfyRecord(columnName, recno, nval));
	return nRet;
}

geoInt32 CTableManager::ModifyRow(geoStr tableName, geoUInt32 recno, geoStringList *nFieldList, geoVariantList *nValueList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_MfyRow(nFieldList, recno, nValueList));
	return nRet;
}

geoInt32 CTableManager::GetColumnType(geoStr tableName, geoStr columnName, POUT geoUInt8* fieldType)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_GetColumnType(columnName, fieldType));

	return nRet;
}

geoInt32 CTableManager::GetRecord(geoStr tableName, geoStr columnName,geoUInt32 recno, POUT geoVariant **pValue)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_GetRecord(columnName, recno, pValue));
	return nRet;
}

geoInt32 CTableManager::GetRow(geoStr tableName, geoStringList *fieldList, geoUInt32 recno, POUT geoVariantList **nv)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RecTable_ptr tb= GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_GetRow(fieldList, recno, nv));
	return nRet;
}

geoInt32 CTableManager::QueryRecordsAdapterEqual(geoStr tableName, geoStr columnName, geoVariant *nval, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (rangeCount == 0 || rangeCount > QUERY_MAX_COUNT)
	{
		return geoRET_FAIL;
	}
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_QueryAdapterEqual(columnName, nval, rangeCount, recnoList));
	return nRet;
}

geoInt32 CTableManager::QueryRecordsAdapterScope(geoStr tableName, geoStr columnName, geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (rangeCount == 0 || rangeCount > QUERY_MAX_COUNT)
	{
		return geoRET_FAIL;
	}
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_QueryAdapterScope(columnName, nvBegin, nvEnd, rangeCount, recnoList));
	return nRet;
}

geoInt32 CTableManager::QueryRecordsAdapterIntersection(geoStr tableName, geoStringList *columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (rangeCount == 0 || rangeCount > QUERY_MAX_COUNT)
	{
		return geoRET_FAIL;
	}
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_QueryRecordsAdapterIntersection(columnNameList, nvList, rangeCount, recnoList));
	return nRet;
}

geoInt32 CTableManager::QueryRecordsAdapterUnion(geoStr tableName, geoStringList *columnNameList, geoVariantList *nValueList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (rangeCount == 0 || rangeCount > QUERY_MAX_COUNT)
	{
		return geoRET_FAIL;
	}
	RecTable_ptr tb = GetRecTableByName(tableName);
	if (IsNull(tb))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tb->TB_QueryRecordsAdapterUnion(columnNameList, nValueList, rangeCount, recnoList));
	return nRet;
}

RecTable_ptr CTableManager::GetRecTableByName(geoStr tbname)
{
	geoTableMapIter it;
	geoTableName tbn;
	strcpy(tbn.Data,tbname);
	it = tableList_.find(tbn);
	if (it == tableList_.end())
	{
		return geoNULL;
	}
	return it->second;
}

geoBool CTableManager::	DelRecTableByName(geoStr tbname)
{
	geoTableMapIter it;
	geoTableName tbn;
	strcpy(tbn.Data,tbname);
	it = tableList_.find(tbn);
	if (it == tableList_.end())
	{
		return geoFALSE;
	}
	it->second->TB_DelTable();
	delete it->second;
	tableList_.erase(it);
	return geoTRUE;	
}

geoBool CTableManager::IsTableExist(geoStr tbname)
{
	//锟叫断憋拷锟斤拷锟角凤拷锟斤拷锟?
	geoTableMapIter it;
	geoTableName tbn;
	strcpy(tbn.Data,tbname);
	it = tableList_.find(tbn);
	if (it == tableList_.end())
	{
		return geoFALSE;
	}
	return geoTRUE;
}

geoInt32 CTableManager::GetMaxRecno(geoStr tableName, geoUInt32* maxRecno)
{
    geoAPIStatus nRet = geoRET_SUCC;
    RecTable_ptr tb = GetRecTableByName(tableName);

    if (IsNull(tb))
    {
        return geoRET_FAIL;
    }
    RET_ERR(tb->TB_GetMaxRecno(maxRecno));
    //tb->tbInfo_;
    return nRet;

}
