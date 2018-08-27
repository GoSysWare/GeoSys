
#include "preCompile.h"
#include "geoRecTable.h"
#include "geoRecDBVariant.h"
#include "geoRecDBTables.h"



CRecTable::CRecTable(geoStr strFileName, geoStr strEnvPath, DbEnv* dbEnv)
{

	GEO_NEW_NORETURN(dbTableImpl_, CDBTables_Impl(dbEnv));
	GEO_NEW_NORETURN(dbTable_, CRecBaseDB(dbTableImpl_));
	GEO_NEW_NORETURN(dbEnv_, DbEnv(0));
	strcpy(strFileName_, strFileName);
	strcpy(strCreateName_, DEFAULT_TABLE_CREATENAME);
	strcpy(strDesc_, DEFAULT_TABLE_DESC);

	memset(strEnvPath_, 0,sizeof(strEnvPath_));
	strncpy(strEnvPath_, strEnvPath, strlen(strEnvPath));
	strncpy(strEnvPath_ + strlen(strEnvPath), DIRECTORY_SEPARATOR_STR_A, 1);
	strncpy(strEnvPath_ + strlen(strEnvPath) + 1, strFileName_, strlen(strFileName_)+1);

	//ACE_DIR *base_dir = opendir_emulation(strEnvPath_);
	//ACE_DIR *base_dir = opendir(strEnvPath_);
	//if (!base_dir)
	//{
	//	mkdir(strEnvPath_, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH );
	//}
	dbEnv_->add_data_dir(strEnvPath_);
	dbEnv_->set_cachesize(0, DEFAULT_ENV_CACHESIZE, DEFAULT_ENV_CACHENUM);
	dbEnv_->open(strEnvPath_, DB_CREATE | DB_INIT_MPOOL | DB_PRIVATE, 0);

	nColumnCount_ = 0;
	tbIsInitFinished_ = geoFALSE;
}
CRecTable::~CRecTable()
{
	if (IsNotNull(dbTableImpl_))
	{
		delete dbTableImpl_;
	}
	if (IsNotNull(dbTable_))
	{
		delete dbTable_;
	}
	if (IsNotNull(dbEnv_))
	{
		delete dbEnv_;
	}
}

geoInt32 CRecTable::TB_CreateTable(geoStr strTableName)
{
	geoAPIStatus nRet = geoRET_SUCC;

	RET_ERR(dbTableImpl_->Init(vTypeString, COLUMN_KEY_SIZE, vTypeBlob, sizeof(geoColumnInfo)));

	geoChar fileName_[SIZE_LENGTH_256];
	strcpy(fileName_, DEFAULT_TABLESMGR_DBFILNAME);
	strcpy(strTableName_, strTableName);

	RET_ERR(dbTable_->InitDB(strTableName_, fileName_));

	//打开表格所在的文件与库
	RET_ERR(TB_OpenTable());

	tbIsInitFinished_ = geoFALSE;

	dbTable_->GetKeyNum(&nColumnCount_);

	geoStringList *colnames = geoNULL;
	//取得文件中已经有的表名
	dbTable_->QueryRec_Range(0, 0, 0, (geoVoid **)&colnames);

	//ACE_ASSERT(nColumnCount_ == colnames->Count);


	for (geoUInt32 i = 0; i <colnames->Count; i++ )
	{
		geoColumnInfo *info = geoNULL;
		dbTable_->GetRec(colnames->List[i], (geoVoid**)&info);
		TB_AddColumnItem(colnames->List[i], info->Datatype, info->RecordSize);
		FreeAndNull((geoVoid**)&info);
	}

	tbIsInitFinished_ = geoTRUE;
	FreeStrList(&colnames);

	return nRet;

}
geoInt32 CRecTable::TB_OpenTable()
{
	geoAPIStatus nRet = geoRET_SUCC;

	RET_ERR(dbTable_->OpenDB());
	geoColumnIter it = columnList_.begin();
	//将db已有的column的db都打开
	while (it != columnList_.end())
	{
		it->second->TC_OpenColumn();
		it++;
	}
	return nRet;
}
geoInt32 CRecTable::TB_CloseTable()
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoColumnIter it = columnList_.begin();
	//此处不能循环调用TB_DelColumnItem方法来删除所有列，因为TB_DelColumnItem对columnList_进行了修改
	while (it != columnList_.end())
	{
		it->second->TC_CloseColumn();
		it++;
	}
	RET_ERR(dbTable_->CloseDB());

	return nRet;
}
geoInt32 CRecTable::TB_DelTable()
{
	geoAPIStatus nRet = geoRET_SUCC;
	//先删除所有的列db，此时columnList_已经为空
	RET_ERR(TB_DelAllColumnItem());
	//删除自身的表格信息db
	dbTable_->ClearAllRec();
	//关闭表格
	dbTable_->CloseDB();
	return nRet;
}
geoInt32 CRecTable::TB_AddColumnItem(geoStr columnName, geoUInt8 valueType, geoUInt32 columnSize)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//判断表有没有打开
	if (IsTableOpen() == geoFALSE)
	{
		return geoRET_FAIL;
	}
	//判断表格是否存在内存Map中
	if (IsTableExist(columnName) == geoTRUE)
	{
		return geoRET_FAIL;
	}
	//得到当前可以利用的类指针
	CRecTableCol_ptr recCol= geoNULL;

	//创建列名类，同一个表格的列db库放在以表格名为文件名的文件中
	GEO_NEW_RETURN(recCol, CRecTableCol(dbEnv_), geoRET_FAIL);
	RET_ERR(recCol->TC_AddColumnItem(columnName, valueType, columnSize));


	geoColumnName _colname;
	strcpy(_colname.Data, columnName);

	columnList_.insert(geoColumnMap::value_type(_colname, recCol));

	if (tbIsInitFinished_ == geoTRUE)
	{
		dbTable_->AddRec(columnName, &recCol->info_);
		nColumnCount_++;
	}
	dbTable_->SyncDB();
	return nRet;
}
geoInt32 CRecTable::TB_DelColumnItem(geoStr columnName)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc = GetRecColByName(columnName);
	if(IsNull(tc))
	{
		return geoRET_FAIL;
	}
	//清空列内容，释放列内部的db
	RET_ERR(tc->TC_DelColumnItem());
	//删除db中的列名为key，列信息为val的db
	dbTable_->DelRec(columnName);
	//清除类指针
	DelRecColByName(columnName);

	nColumnCount_--;
	dbTable_->SyncDB();
	return nRet;
}
geoInt32 CRecTable::TB_DelAllColumnItem()
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoColumnIter it = columnList_.begin();
	//此处不能循环调用TB_DelColumnItem来删除所有列，因为TB_DelColumnItem对columnList_进行了修改
	while (it != columnList_.end())
	{
		it->second->TC_DelColumnItem();
		//释放类指针，但不是在map中删除，map依然有指针值
		delete it->second;
		it++;
	}
	//清空Map
	columnList_.clear();

	return nRet;
}
geoInt32 CRecTable::TB_GetColumnType(geoStr columnName, geoUInt8* dataType)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc= GetRecColByName(columnName);
	if (IsNull(tc))
	{
		return geoRET_FAIL;
	}
	*dataType = tc->info_.Datatype;
	return nRet;

}
geoInt32 CRecTable::TB_AddRecord(geoStr columnName, geoVariant *pVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc= GetRecColByName(columnName);
	if(IsNull(tc))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tc->TC_AddRecord(pVal));
	return nRet;

}
geoInt32 CRecTable::TB_DelRecord(geoStr columnName, geoUInt32 recno)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc= GetRecColByName(columnName);
	if(IsNull(tc))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tc->TC_DelRecord(recno));
	return nRet;
}
geoInt32  CRecTable::TB_MfyRecord(geoStr columnName, geoUInt32 recno, geoVariant *pVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc = GetRecColByName(columnName);
	if(IsNull(tc))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tc->TC_MfyRecord(recno, pVal));
	return nRet;
}
geoInt32 CRecTable::TB_GetRecord(geoStr columnName, geoUInt32 recno, geoVariant **pVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc= GetRecColByName(columnName);
	if(IsNull(tc))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tc->TC_GetRecord(recno, pVal));
	return nRet;

}
geoInt32 CRecTable::TB_AddRow( geoStringList *columnName, geoVariantList *nValueList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//指针为null默认是整行添加
	if (IsNull(columnName) && nValueList->ValueCount == nColumnCount_)
	{
		geoColumnMap::iterator it = columnList_.begin();
		geoUInt32 i = 0;
		while(it != columnList_.end())
		{
			it->second->TC_AddRecord(&nValueList->ValueList[i]);
			it++;
			i++;
		}		
		return nRet;
	}
	if (columnName->Count != nValueList->ValueCount)
	{
		return geoFALSE;
	}
	for (geoUInt32 i = 0; i< columnName->Count; i++)
	{
		//如果添加一行时，有一个失败了肿么办呢？只能让没添加成功的列计数器照样+1
		//当正好get这个没添加成功的记录时，不返回错误，而是返回一个没有任何内容的geoVariant就解决啦
		TB_AddRecord(columnName->List[i], nValueList->ValueList + i);
	}
	return nRet;
}
geoInt32 CRecTable::TB_DelRow(geoStringList *columnName, geoUInt32 recno)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//指针为null默认是整行删除
	if (IsNull(columnName))
	{
		geoColumnMap::iterator it = columnList_.begin();
		while(it != columnList_.end())
		{
			it->second->TC_DelRecord(recno);
			it++;
		}		
		return nRet;
	}

	for (geoUInt32 i = 0; i< columnName->Count;i++)
	{
		TB_DelRecord(columnName->List[i], recno);
	}
	return nRet;
}
geoInt32 CRecTable::TB_MfyRow( geoStringList *columnName,  geoUInt32 recno ,geoVariantList *nValueList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//指针为null默认是整行修改
	if (IsNull(columnName) && nValueList->ValueCount == nColumnCount_)
	{
		geoColumnMap::iterator it = columnList_.begin();
		geoUInt32 i = 0;
		while(it != columnList_.end())
		{
			it->second->TC_MfyRecord(recno, &nValueList->ValueList[i]);
			it++;
			i++;
		}		
		return nRet;
	}
	if (columnName->Count != nValueList->ValueCount)
	{
		return geoFALSE;
	}
	for (geoUInt32 i = 0; i< columnName->Count; i++)
	{
		TB_MfyRecord(columnName->List[i], recno, nValueList->ValueList +i);
	}
	return nRet;
}
geoInt32 CRecTable::TB_GetRow(geoStringList *columnName, geoUInt32 recno, geoVariantList **nValueList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//当名字指针为空时，默认得到表格内一整行

	if (IsNull(columnName))
	{
		NewValueListEx(nValueList, nColumnCount_);
		
		geoColumnMap::iterator it = columnList_.begin();
		geoUInt32 i = 0;
		while (it != columnList_.end())
		{
			geoVariant * temp = geoNULL;
			it->second->TC_GetRecord(recno, &temp);
			Variant_Copy(temp, (*nValueList)->ValueList + i);
			FreeAndNull((geoVoid **)&temp);
			it++;
			i++;
		}
	}
	else
	{
		NewValueListEx(nValueList, columnName->Count);
		
		for (geoUInt32 i = 0; i < columnName->Count; i++)
		{
			geoVariant * temp = geoNULL;
			TB_GetRecord(columnName->List[i], recno, &temp);
			Variant_Copy(temp, (*nValueList)->ValueList + i);
			FreeAndNull((geoVoid **)&temp);
		}
	}

	return nRet;
}
geoInt32 CRecTable::TB_QueryAdapterEqual(geoStr columnName, geoVariant *nval, geoUInt32 rangeCount, geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc = GetRecColByName(columnName);
	if(IsNull(tc))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tc->TC_QueryAdapterEqual(nval, rangeCount, recnoList));
	return nRet;
}
geoInt32 CRecTable::TB_QueryAdapterScope(geoStr columnName, geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	CRecTableCol_ptr tc = GetRecColByName(columnName);
	if(IsNull(tc))
	{
		return geoRET_FAIL;
	}
	RET_ERR(tc->TC_QueryAdapterScope(nvBegin, nvEnd, rangeCount, recnoList));
	return nRet;
}
geoInt32 CRecTable::TB_QueryRecordsAdapterIntersection(geoStringList *columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (columnNameList->Count != nvList->ValueCount)
	{
		return geoRET_FAIL;
	}
	//当只有一个时，快速返回
	if (columnNameList->Count == 1)
	{
		RET_ERR(TB_QueryAdapterEqual(columnNameList->List[0], &nvList->ValueList[0], rangeCount, recnoList));
	}
	else
	{
		map<geoUInt32, geoUInt32>  tmplist;
		geoUInt32 nCount = 0;
		for(geoUInt32 i = 0; i < columnNameList->Count; i++)
		{
			geoRecnoList *rlist = geoNULL;
			RET_ERR(TB_QueryAdapterEqual(columnNameList->List[i], &nvList->ValueList[i], rangeCount, &rlist));
			for (geoUInt32 k = 0 ; k < rlist->RecnoCount; k++)
			{
				tmplist[rlist->RecnoList[k]]++;
			}
			FreeAndNull((geoVoid**)&rlist);
		}
		//取得交集的个数
		map<geoUInt32,geoUInt32> ::iterator it = tmplist.begin();
		while (it != tmplist.end())
		{
			if (it->second == columnNameList->Count)
			{
				nCount++;
			}
			it++;
		}
		if (nCount == 0)
		{
			return geoFALSE;
		}
		//分配返回缓冲，赋值
		NewReconListEx(recnoList, nCount);
		it = tmplist.begin();
		geoUInt32 num =0;
		while(it != tmplist.end())
		{
			if (it->second == columnNameList->Count)
			{
				(*recnoList)->RecnoList[num++] = it->first;
			}
			it++;
		}
		ACE_ASSERT(num == nCount);
	}
	return nRet;
}
geoInt32 CRecTable::TB_QueryRecordsAdapterUnion(geoStringList *columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (columnNameList->Count != nvList->ValueCount)
	{
		return geoRET_FAIL;
	}
	//当只有一个时，快速返回
	if (columnNameList->Count == 1)
	{
		RET_ERR(TB_QueryAdapterEqual(columnNameList->List[0], &nvList->ValueList[0], rangeCount, recnoList));
	}
	else
	{
		//多个数组求交集的算法，此算法不能用于太大数组的返回
		map<geoUInt32, geoUInt32>  tmplist;
		for(geoUInt32 i = 0; i < columnNameList->Count; i++)
		{
			geoRecnoList *rlist = geoNULL;
			RET_ERR(TB_QueryAdapterEqual(columnNameList->List[i], &nvList->ValueList[i], rangeCount, &rlist));
			for (geoUInt32 k = 0 ; k < rlist->RecnoCount; k++)
			{
				tmplist[rlist->RecnoList[k]]++;
			}
			FreeAndNull((geoVoid**)&rlist);
		}
		//取得交集的个数
		map<geoUInt32, geoUInt32> ::iterator it = tmplist.begin();

		if (tmplist.size() == 0)
		{
			return geoFALSE;
		}
		//分配返回缓冲，赋值
		NewReconListEx(recnoList, tmplist.size());
		it = tmplist.begin();
		geoUInt32 num =0;
		while(it != tmplist.end())
		{
			(*recnoList)->RecnoList[num++] = it->first;
			it++;
		}
		ACE_ASSERT(num == tmplist.size());
	}
	return nRet;
}

CRecTableCol_ptr CRecTable::GetRecColByName(geoStr columnName)
{
	//判断表名是否存在
	geoColumnIter it;
	geoColumnName tcn;
	strcpy(tcn.Data, columnName);
	it = columnList_.find(tcn);
	if (it == columnList_.end())
	{
		return geoNULL;
	}
	return it->second;
}
geoBool CRecTable::DelRecColByName(geoStr columnName)
{
	//判断表名是否存在
	geoColumnIter it;
	geoColumnName tcn;
	strcpy(tcn.Data, columnName);
	it = columnList_.find(tcn);
	if (it == columnList_.end())
	{
		return geoFALSE;
	}
	//清空CRecTableCol_ptr指针
	delete it->second;
	//在Map中删除
	columnList_.erase(it);

	return geoTRUE;
}
geoBool CRecTable::IsTableExist(geoStr columnName)
{
	//判断表名是否存在
	geoColumnIter it;
	geoColumnName tcn;
	strcpy(tcn.Data, columnName);
	it = columnList_.find(tcn);
	if (it == columnList_.end())
	{
		return geoFALSE;
	}
	return geoTRUE;
}
geoInt32 CRecTable::TB_SyncTable()
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoColumnIter it = columnList_.begin();
	while(it!= columnList_.end())
	{
		it->second->TC_SyncCol();
		it++;
	}
	return nRet;
}

geoInt32 CRecTable::TB_GetMaxRecno(geoUInt32* maxRecno)
{
    geoAPIStatus nRet = geoRET_SUCC;
    CRecTableCol_ptr tc = geoNULL;

    geoColumnIter it;
    if(columnList_.size()==0)
    {
        return geoRET_FAIL;
    }
    it = columnList_.begin();
    tc = it->second;
    if(IsNull(tc))
    {
        return geoRET_FAIL;
    }
    *maxRecno = tc->TC_GetMaxRecno();
    return nRet;
}
