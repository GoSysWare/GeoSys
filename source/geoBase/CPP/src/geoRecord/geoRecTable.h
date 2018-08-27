
/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     georeTable.h													*
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
#ifndef  GEOSYS_RECORD_TABLE_H__
#define GEOSYS_RECORD_TABLE_H__


#include "geoBasicType.h"
#include "geoRecComm.h"

#include "geoRecBaseDB.h"
#include "geoRecDBTables.h"
#include "geoRecTableCol.h"

using namespace std;
#include<list>
#include<map>

class CRecTableCol;
typedef std::map<geoColumnName, CRecTableCol_ptr>	geoColumnMap;
typedef geoColumnMap::iterator 	geoColumnIter;

//单独的表格类
class  CRecTable 
{
public:
	CRecTable(geoStr strFileName, geoStr strEnvPath, DbEnv* dbEnv);
	CRecTable(geoStr strFileName, geoStr strEnvPath, geoStr tbUserNmae, geoStr tbDesc);
	~CRecTable();
	//表格操作
	geoInt32 TB_CreateTable(geoStr tableName);
	geoInt32 TB_OpenTable();
	geoInt32 TB_CloseTable();
	geoInt32 TB_DelTable();
	geoInt32 TB_SyncTable();
    geoInt32 TB_GetMaxRecno(geoUInt32* maxRecno);

	//列操作
	geoInt32 TB_AddColumnItem(geoStr columnName, geoUInt8 valueType, geoUInt32 columnSize);
	geoInt32 TB_DelColumnItem(geoStr columnName);
	geoInt32 TB_DelAllColumnItem();
	geoInt32 TB_GetColumnType(geoStr columnName, geoUInt8* dataType);

	//记录操作
	geoInt32 TB_AddRecord(geoStr columnName, geoVariant *pVal);
	geoInt32 TB_DelRecord(geoStr columnName, geoUInt32 recno);
	geoInt32 TB_MfyRecord(geoStr columnName, geoUInt32 recno, geoVariant *pVal);
	geoInt32 TB_GetRecord(geoStr columnName, geoUInt32 recno, geoVariant **pVal);

	geoInt32 TB_AddRow( geoStringList *columnName, geoVariantList *nValueList);
	geoInt32 TB_DelRow( geoStringList *columnName, geoUInt32 recno);
	geoInt32 TB_MfyRow( geoStringList *columnName, geoUInt32 recno , geoVariantList *nValueList);
	geoInt32 TB_GetRow( geoStringList *columnName, geoUInt32 recno , geoVariantList **nValueList);

	geoInt32 TB_QueryAdapterEqual(geoStr columnName, geoVariant *nval, geoUInt32 rangeCount, geoRecnoList **recnoList);
	geoInt32 TB_QueryAdapterScope(geoStr columnName, geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);
	geoInt32 TB_QueryRecordsAdapterIntersection(geoStringList *columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);
	geoInt32 TB_QueryRecordsAdapterUnion(geoStringList *columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);

	CRecBaseDB * GetTableDB()const 
	{
		return dbTable_;
	}
	geoRecTableInfo tbInfo_;

	geoBool IsTableOpen()
	{
		return dbTable_->bIsOpen_;
	}
	geoBool IsTableExist(geoStr strColumnName);
protected:

	CRecTableCol_ptr GetRecColByName(geoStr columnName);
	geoBool DelRecColByName(geoStr columnName);
private:
	DbEnv *dbEnv_;
	//初始化完成，防止原存的列名再被添加
	geoBool tbIsInitFinished_;

	geoColumnMap columnList_;

	geoChar strEnvPath_[PATH_MAX];
	geoChar strFileName_[PATH_MAX];
	geoChar strTableName_[TABLE_NAME_SIZE];
	geoChar strCreateName_[TABLE_CREATENAME_SIZE];
	geoChar strDesc_     [TABLE_DESC_SIZE];
	geoUInt32 nColumnCount_;
	geoTime tCreateTime_;
	geoTime tLastSaveTime_;
	//一个表格的列名组成的db
	//此db是以colname为key，colInfo为val的db
	CDBTables_Impl *dbTableImpl_;
	CRecBaseDB * dbTable_;
};
typedef CRecTable* RecTable_ptr;
#endif
