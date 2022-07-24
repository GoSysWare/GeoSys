
/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     georeTableManager.h													*
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

#ifndef GEOSYS_RECORD_TABLE_MANAGER_H__
#define GEOSYS_RECORD_TABLE_MANAGER_H__

#include "geoRecTable.h"
#include "geoRecComm.h"

using namespace std;
#include<list>
#include<map>

typedef std::map<geoTableName, RecTable_ptr>	geoTableMap;
typedef geoTableMap::iterator	geoTableMapIter;


//概念:
//记录:相当与单元格

class CTableManager
{
public:

	
	///	构造函数
	 
	CTableManager();

	
	///	析构函数
	 
	~CTableManager();

	
	///	初始化
	 
	geoInt32 Init(geoStr envPath);

	
	///	反初始化
	 
	geoInt32 UnInit();

	
	///	创建一个表格
	 
	geoInt32 CreateTable(geoStr tableName);

	
	///	打开表格
	 
	geoInt32 OpenTable(geoStr tableName);

	
	///	打开表格后进行添加列操作
	 
	geoInt32 AddColumnItem(geoStr tableName, geoStr columnName, geoUInt8 valueType, geoUInt32 columnSize);

	
	///	打开表格后进行删除列操作
	 
	geoInt32 DelColumnItem(geoStr tableName, geoStr columnName);

	
	///	关闭表格
	 
	geoInt32 CloseTable(geoStr tableName);

	
	///	删除表格
	 
	geoInt32 DeleteTable(geoStr tableName);

	/// <summary>
	///	同步表格
	
	geoInt32 SyncTab(geoStr tableName);

	
	///	关闭所有表格
	 
	geoInt32 CloseAllTab();

	
	///	同步所有已经打开的表格
	 
	geoInt32 SyncAllOpenTab();

	
	///	删除所有表格
	 
	geoInt32 DelAllTab();

	
	///	得到表格的信息
	 
	geoInt32 GetTableInfo(geoStr tableName, geoRecTableInfo *tbInfo);

	
	///	对表格的某个列字段添加记录
	 
	geoInt32 AddRecord(geoStr tableName, geoStr nFieldName, geoVariant *pValue);

	
	///	对表格添加一整行
	 
	geoInt32 AddRow(geoStr tableName, geoStringList *nFieldList, geoVariantList *nValueList); 

	
	///	根据行号删除表中的记录,当删除的的行数大于当前最大行数时,也算成功,因为这种操作也合理
	 
	geoInt32 DelRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno);

	
	///	根据行号删除表中的一整行,当删除的的行数大于当前最大行数时,也算成功,因为这种操作也合理
	 
	geoInt32 DelRow(geoStr tableName, geoUInt32 recno);

	
	///	修改表格的记录
	 
	geoInt32 ModifyRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno, geoVariant *nval);

	
	///	根据行号来修改对应的一整行
	 
	geoInt32 ModifyRow(geoStr tableName, geoUInt32 recno, geoStringList *nFieldList, geoVariantList *nValueList);

	
	///	获取某表中某字段的数据类型
	 
	geoInt32 GetColumnType(geoStr tableName, geoStr fieldName, POUT geoUInt8* fieldType);

	
	///	根据行号获取表的格字段下记录
	 
	geoInt32 GetRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno, POUT geoVariant **pValue);

	
	///	根据行号获取表的一整行
	 
	geoInt32 GetRow(geoStr tableName, geoStringList *fieldList, geoUInt32 recno, POUT geoVariantList **nValueList);

	
	///	获取某表某字段特定值对应的所有记录号
	 
	geoInt32 QueryRecordsAdapterEqual(geoStr tableName, geoStr fieldName, geoVariant *nval, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);

	
	///	获取某表某字段值范围对应的所有记录号//范围查询采用前闭后开区间
	 
	geoInt32 QueryRecordsAdapterScope(geoStr tableName, geoStr fieldName, geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);

	
	///	获取某表某字段为某些值时的所有记录号，字段值之间条件是交集
	 
	geoInt32 QueryRecordsAdapterIntersection(geoStr tableName, geoStringList* columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);

	
	///	获取某表中，等于某些字段值的所有记录号，字段值之间条件是并集
	 
	geoInt32 QueryRecordsAdapterUnion(geoStr tableName, geoStringList *columnNameList, geoVariantList *nValueList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);

	
	///	判断表格是否存在
	 
	geoBool IsTableExist(geoStr tbname);

    
    ///	获取最大记录号
     
    geoInt32 GetMaxRecno(geoStr tableName, geoUInt32* maxRecno);

private:
	
	///	获取表格记录指针
	 
	RecTable_ptr GetRecTableByName(geoStr tbname);
	
	///	删除表格记录
	 
	geoBool DelRecTableByName(geoStr tbname);
	//初始化完成，防止原存的表格名再被添加
	geoBool tbIsInitFinished_;

	//内部数据库环境变量
	DbEnv *dbEnv_;

	//表格链表
	geoTableMap tableList_;

	//表格个数
	geoUInt32  tableCount_;

	//同步周期
	geoUInt32 _savePeriod;

	//内存池大小
	geoUInt64 _mpoolSize;

	//存储表名模板
	CDBTables_Impl *tbMgrImpl_;

	//存储表名库
	CRecBaseDB_ptr tbMgr_;

	//数据库所处的文件名
	geoChar strFileName_[SIZE_LENGTH_256];

	//数据库环境目录
	geoStr envPath_;
};

#endif
