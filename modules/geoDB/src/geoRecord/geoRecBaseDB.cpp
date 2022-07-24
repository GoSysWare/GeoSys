#ifndef	LIB_RECORDS_EXPORTS
#define	LIB_RECORDS_EXPORTS
#endif
#include "preCompile.h"
#include "geoRecBaseDB.h"

CRecBaseDB_Impl::CRecBaseDB_Impl(DbEnv *dbEnv,DBTYPE dbType):
						dbEnv_(dbEnv),
						tDBType_(dbType),
						nKeyType_(vTypeEmpty),
						nValType_(vTypeEmpty),
						nKeyDbcSize_(0),
						nValDbcSize_(0)								

{
	GEO_NEW_NORETURN(db_, Db(dbEnv_,0));

}
CRecBaseDB_Impl::~CRecBaseDB_Impl()
{

	//dbEnv是外界传递，此处不能删除

	if (IsNotNull(db_))
	{
		delete db_;
	}
}
geoInt32 CRecBaseDB_Impl::Init(geoUInt8 nKeyType ,
							  geoUInt32 nKeySize ,
							  geoUInt8 nValType ,
							  geoUInt32 nValSize)
{
	geoAPIStatus nRet = geoRET_SUCC;

	return nRet;
}
geoInt32 CRecBaseDB_Impl::UnInit()
{
	geoAPIStatus nRet = geoRET_SUCC;
	return nRet;
}
geoInt32 CRecBaseDB_Impl::AddRec(geoVoid *dbKey, geoVoid *dbVal)
{
	//由于默认操作时不做任何DB的操作，默认操作是操作失败的
	//如果想要操作成功，则在Impl的子类重载此操作，返回成功即可
	geoAPIStatus nRet = geoRET_FAIL;
	return nRet;
}
geoInt32 CRecBaseDB_Impl::InsertRec(geoVoid *dbcursor, geoVoid *dbKey, geoVoid *dbVal)
{
	//由于默认操作时不做任何DB的操作，默认操作是操作失败的
	//如果想要操作成功，则在Impl的子类重载此操作，返回成功即可
	geoAPIStatus nRet = geoRET_FAIL;
	return nRet;
}
geoInt32 CRecBaseDB_Impl::DelRec(geoVoid *dbKey)
{

	geoAPIStatus nRet = geoRET_FAIL;
	return nRet;
}
geoInt32 CRecBaseDB_Impl::MfyRec(geoVoid *dbKey, geoVoid *dbVal)
{

	geoAPIStatus nRet = geoRET_FAIL;
	return nRet;
}
geoInt32 CRecBaseDB_Impl::GetRec(geoVoid *dbKey, geoVoid **dbVal)
{

	geoAPIStatus nRet = geoRET_FAIL;
	return nRet;
}
geoInt32 CRecBaseDB_Impl::QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_FAIL;
	return nRet;
}
geoInt32 CRecBaseDB_Impl::QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_FAIL;
	return nRet;
}


void CRecBaseDB_Impl::SetKeyDbcSize(geoUInt32 nSize){nKeyDbcSize_ = nSize;}
void CRecBaseDB_Impl::SetValDbcSize(geoUInt32 nSize){nValDbcSize_ = nSize;}
geoUInt32 CRecBaseDB_Impl::GetKeyDbcSize() const{return nKeyDbcSize_;}
geoUInt32 CRecBaseDB_Impl::GetValDbcSize()const{return nValDbcSize_;}

void CRecBaseDB_Impl::SetKeyDbcType(geoUInt8 nType){nKeyType_ = nType;}
void CRecBaseDB_Impl::SetValDbcType(geoUInt8 nType){nValType_ = nType;}
geoUInt8 CRecBaseDB_Impl::GetKeyDbcType() const{return nKeyType_;}
geoUInt8 CRecBaseDB_Impl::GetValDbcType() const {return nValType_;}

geoUInt32 CRecBaseDB::dbNum_ = 1;

CRecBaseDB::CRecBaseDB(CRecBaseDB_Impl *impl):
			bIsOpen_(geoFALSE),
			impl_(impl),
			mDBFlags_(DB_CREATE),
			nRecCount_(0)


{
	dbEnv_ = impl->dbEnv_;
	db_ = impl->db_;

	geoChar temp[4];
	memset(temp,0, 4);
	itoa(dbNum_, temp, 10);
	strcpy(strDBName_, DEFAULT_BASEDB_DBNAME);
	strcat(strDBName_, temp);
	strcpy(strFileName_, DEFAULT_BASEDB_DBFILNAME);
	strcat(strFileName_, temp);
	dbNum_ ++;
}
 CRecBaseDB::~CRecBaseDB()
{
	if (IsNull(impl_))
	{
		delete impl_;
	}
	
 }
 
 ///	初始化数据库前，留给子类使
 
 geoInt32 CRecBaseDB::PreInitDB()
 {
	 geoAPIStatus nRet = geoRET_SUCC;
	 return nRet;
 }
geoInt32  CRecBaseDB::InitDB(geoStr dbName,
							geoStr fileName)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(PreInitDB());
	memset(strDBName_, 0, sizeof(strDBName_));
	memset(strFileName_, 0, sizeof(strFileName_));
	if (IsNotNull(dbName))
	{
		strcpy(strDBName_, dbName);
	}
	
	strcpy(strFileName_, fileName);

	//当用户初始化了文件名，则计数器要减去1
	dbNum_--;
	RET_ERR(PostInitDB());
	return nRet;
}

///	初始化数据库后，留给子类使用

 geoInt32 CRecBaseDB::PostInitDB()
{
	geoAPIStatus nRet = geoRET_SUCC;
	return nRet;
}

geoInt32 CRecBaseDB::OpenDB()
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(db_))
	{
		return geoRET_FAIL;
	}
	if (bIsOpen_ == geoTRUE)
	{
		return geoRET_SUCC;
	}
	if (0 == strcmp(strDBName_, ""))
	{
		nRet = impl_->db_->open(NULL, strFileName_, NULL, impl_->tDBType_, (u_int32_t)mDBFlags_, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
	}
	else
	{
		nRet = impl_->db_->open(NULL, strFileName_, strDBName_, impl_->tDBType_, (u_int32_t)mDBFlags_, S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
	}
	if (geoErr(nRet))
	{
		bIsOpen_ = geoFALSE;
	}
	else
	{
		bIsOpen_ = geoTRUE;
	}
	return nRet;
}

geoInt32 CRecBaseDB::CloseDB()
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(impl_) || IsNull(impl_->db_))
	{
		return geoRET_FAIL;
	}
	if (bIsOpen_ == geoTRUE)
	{
		RET_ERR(impl_->db_->close(0));
		bIsOpen_ = geoFALSE;
	}
	return nRet;
}
geoInt32 CRecBaseDB::AddRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(impl_->AddRec(dbKey, dbVal));
	nRecCount_++;
	return nRet;
}
geoInt32 CRecBaseDB::InsertRec(geoVoid *dbcursor, geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(impl_->InsertRec(dbcursor, dbKey, dbVal));
	nRecCount_++;
	return nRet;
}
geoInt32 CRecBaseDB::DelRec(geoVoid *dbKey)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(impl_->DelRec(dbKey));
	//nRecCount_--;
	return nRet;
}
geoInt32 CRecBaseDB::MfyRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(impl_->MfyRec(dbKey, dbVal));
	return nRet;
}
geoInt32 CRecBaseDB::GetRec(geoVoid *dbKey, geoVoid **dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(impl_->GetRec(dbKey, dbVal));
	return nRet;
}
geoInt32 CRecBaseDB::QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(impl_->QueryRec_Equal(dbVal, rangeCount, ppReconlist));
	return nRet;
}
geoInt32 CRecBaseDB::QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(impl_->QueryRec_Range(dbValStart, dbValEnd, rangeCount, ppReconlist));
	return nRet;
}
//清空所有的内容
geoInt32 CRecBaseDB::ClearAllRec()
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(impl_) || IsNull(impl_->db_))
	{
		return geoRET_FAIL;
	}
	geoUInt32 count =0;
	RET_ERR(impl_->db_->truncate(0, &count,0));
	return nRet;
}
geoInt32 CRecBaseDB::PreSyncDB()
{
	geoAPIStatus nRet = geoRET_SUCC;
	return nRet;
}

geoInt32 CRecBaseDB::SyncDB()
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(impl_) || IsNull(impl_->db_))
	{
		return geoRET_FAIL;
	}
	RET_ERR(PreSyncDB());
	impl_->db_->sync(0);
	RET_ERR(PostSyncDB());
	return nRet;
}
geoInt32 CRecBaseDB::PostSyncDB()
{
	geoAPIStatus nRet = geoRET_SUCC;
	return nRet;
}
geoInt32 CRecBaseDB::GetMaxRecno(geoUInt32 *keyMax)
{
    geoAPIStatus nRet = geoRET_SUCC;
    //RET_ERR(NewAndCopyStr(dbname, strDBName_));

    Dbc *cursorp = geoNULL;
    Dbt key;
    Dbt data;
    *keyMax = 0;
    geoInt32 retDb;
    if (bIsOpen_ == geoFALSE ||IsNull(db_) )
    {
        return geoRET_FAIL;
    }

    impl_->db_->cursor(NULL, &cursorp, 0);


    while ((retDb = cursorp->get(&key, &data, DB_NEXT)) == 0) 
    {
        geoUInt32 temp = *((geoUInt32*)key.get_data());
        if (temp>*keyMax)
        {
            *keyMax = temp;
        }
    }

    if (cursorp != NULL)
    {
        cursorp->close();
    }

    return nRet;
}

//此处的应该有Db类中的直接返回的接口，不应该需要自己去找
geoInt32 CRecBaseDB::GetKeyNum(geoUInt32 *keyCount)
{
	geoAPIStatus nRet = geoRET_SUCC;
	Dbc *cursorp = geoNULL;
	Dbt key;
	Dbt data;
	*keyCount = 0;
	geoInt32 retDb;
	if (bIsOpen_ == geoFALSE ||IsNull(db_) )
	{
		return geoRET_FAIL;
	}

	impl_->db_->cursor(NULL, &cursorp, 0);


	while ((retDb = cursorp->get(&key, &data, DB_NEXT)) == 0) 
	{
		(*keyCount)++;
	}

	if (cursorp != NULL)
	{
		cursorp->close();
	}
	return nRet;
}

geoInt32 CRecBaseDB::GetDBName(geoStr* dbname) const
{
	geoAPIStatus nRet = geoRET_SUCC;
	RET_ERR(NewAndCopyStr(dbname, strDBName_));
	return nRet;
}

geoBool CRecBaseDB::GetOpenState() const
{
	return bIsOpen_;
}


///	获取内部DB句柄

Db* CRecBaseDB::GetDb() const 
{
	return impl_->db_;
}
DbEnv* CRecBaseDB::GetDbEnv() const 
{
	return impl_->dbEnv_;
}
