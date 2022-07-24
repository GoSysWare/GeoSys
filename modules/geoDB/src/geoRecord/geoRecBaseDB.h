/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRecBaseDB.h													*
*  @brief																	*
*																			 *
*
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : 必须在支持C++11环境下编译通过                            *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/10/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_RECORD_MACRO_H__
#define GEOSYS_RECORD_MACRO_H__

#include "geoBasicType.h"
#include "db/db_cxx.h"

#include "geoRecComm.h"



class   CRecBaseDB_Impl
{
public:
	CRecBaseDB_Impl(DbEnv *dbEnv, DBTYPE dbType =DB_BTREE );
	virtual ~CRecBaseDB_Impl();
	virtual geoInt32 Init(geoUInt8 nKeyType = 0,
		geoUInt32 nKeySize = 0 ,
		geoUInt8 nValType = 0,
		geoUInt32 nValSize= 0);
	virtual geoInt32 UnInit();
	virtual geoInt32 AddRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 InsertRec(geoVoid *dbcursor, geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 DelRec(geoVoid *dbKey);
	virtual geoInt32 MfyRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 GetRec(geoVoid *dbKey, geoVoid **dbVal);
	virtual geoInt32 QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist);
	virtual geoInt32 QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist);
	void SetKeyDbcSize(geoUInt32 nSize);
	void SetValDbcSize(geoUInt32 nSize);
	geoUInt32 GetKeyDbcSize() const;
	geoUInt32 GetValDbcSize()const;

	void SetKeyDbcType(geoUInt8 nType);
	void SetValDbcType(geoUInt8 nType);
	geoUInt8 GetKeyDbcType() const;
	geoUInt8 GetValDbcType() const;

	Db* db_;   

	DbEnv *dbEnv_;

	DBTYPE tDBType_;  
protected:

	geoUInt8 nKeyType_;

	geoUInt8 nValType_;

	geoUInt32 nKeyDbcSize_;

	geoUInt32 nValDbcSize_;


};

class   CRecBaseDB
{
public:

	CRecBaseDB(CRecBaseDB_Impl *impl);

	virtual ~CRecBaseDB();

	virtual geoInt32  InitDB(
		geoStr dbName,
		geoStr fileName);


	virtual geoInt32 PreInitDB();

	virtual geoInt32 PostInitDB();

	geoInt32 OpenDB();


	geoInt32 CloseDB(); 

	geoInt32 AddRec(geoVoid *dbKey, geoVoid *dbVal);
	geoInt32 InsertRec(geoVoid *dbcursor, geoVoid *dbKey, geoVoid *dbVal);
	geoInt32 DelRec(geoVoid *dbKey);
	geoInt32 MfyRec(geoVoid *dbKey, geoVoid *dbVal);
	geoInt32 GetRec(geoVoid *dbKey, geoVoid **dbVal);
	geoInt32 QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist);

	geoInt32 QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist);

	geoInt32 ClearAllRec();

	virtual geoInt32 PreSyncDB();

	geoInt32 SyncDB();

	virtual geoInt32 PostSyncDB();

	geoInt32 GetKeyNum(geoUInt32 *keyCount) ;


	geoBool GetOpenState() const;

	geoInt32 GetMaxRecno(geoUInt32 *keyMax);


	geoInt32 GetDBName(geoStr* dbname) const;

	Db* GetDb() const ;

	DbEnv* GetDbEnv() const ;

	static geoUInt32 dbNum_;

	geoBool bIsOpen_;   
private:


	CRecBaseDB_Impl *impl_;

	Db* db_;   

	DbEnv *dbEnv_;

	REC_STATUS_MARK mDBFlags_;   


	geoChar strFileName_[PATH_MAX];


	geoChar strFileDir_[PATH_MAX];


	geoChar strDBName_[32];     


	geoUInt32 nRecCount_;

};
typedef CRecBaseDB* CRecBaseDB_ptr;

#endif

