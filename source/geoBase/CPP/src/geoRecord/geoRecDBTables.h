/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRecDBTables.h													*
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
#ifndef  GEOSYS_RECORD_DBTABLES_H__
#define GEOSYS_RECORD_DBTABLES_H__

#include "geoBasicType.h"
#include "geoRecBaseDB.h"

//以字符串为key，结构体为val的bdb
class   CDBTables_Impl:public CRecBaseDB_Impl
{
public:
	CDBTables_Impl(DbEnv *dbEnv,DBTYPE dbType =DB_BTREE );
	~CDBTables_Impl();
	virtual geoInt32 Init(geoUInt8 nKeyType = 0, geoUInt32 nKeySize=0, geoUInt8 nValType=0, geoUInt32 nValSize=0);
	virtual geoInt32 UnInit();
	virtual geoInt32 AddRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 InsertRec(geoVoid *dbcursor,geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 DelRec(geoVoid *dbKey);
	virtual geoInt32 MfyRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 GetRec(geoVoid *dbKey, geoVoid **dbVal);
	//注意：这个范围查找，在此bdb中返回所有的key,与recon做为key的模板不同，dbValStart，dbValEnd参数无效
	virtual geoInt32 QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist);
	static geoInt32 DbCompareFunc(Db *_db, const Dbt * Key_1, const Dbt* Key_2);
};


#endif
