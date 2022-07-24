
/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     georeTablecol.h													*
*  @brief														*
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
#ifndef  GEOSYS_RECORD_TABLECOL_H__
#define GEOSYS_RECORD_TABLECOL_H__

#include "geoBasicType.h"
#include "geoRecComm.h"

#include "geoRecBaseDB.h"
#include "geoRecDBTables.h"

using namespace std;
#include<list>
#include<map>




//表头类,管理列的dbd
class CRecTableCol
{
public:
	~CRecTableCol();
	CRecTableCol(DbEnv *dbenv);

	geoInt32 TC_OpenColumn();
	geoInt32 TC_CloseColumn();
	geoInt32 TC_SyncCol();
    geoUInt32 TC_GetMaxRecno();

	geoInt32 TC_AddColumnItem(geoStr columnName, geoUInt8 valueType,geoUInt32 columnSize);
	geoInt32 TC_DelColumnItem();
	geoInt32 TC_DelAllColumnItem();

	geoInt32 TC_AddRecord(geoVariant *pVal);
	geoInt32 TC_MfyRecord(geoUInt32 recno,geoVariant *pVal);
	geoInt32 TC_DelRecord(geoUInt32 recno);
	geoInt32 TC_GetRecord(geoUInt32 recno,geoVariant **pVal);
	geoInt32 TC_QueryAdapterEqual(geoVariant *nval, geoUInt32 rangeCount, geoRecnoList **recnoList);
	geoInt32 TC_QueryAdapterScope(geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);
	geoColumnInfo info_;

private:

	CRecBaseDB_ptr GetRecTableByName(geoStr tbname);
	geoChar strColName_[COLUMN_NAME_SIZE];
	DbEnv *dbenv_;
	//此db是以recno为key，Variant为val的db
	CRecBaseDB * recColDb_;
};
typedef CRecTableCol* CRecTableCol_ptr;

#endif
