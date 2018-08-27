/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRecords.h													*
*  @brief		Records模块接口														*
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
#ifndef  GEOSYS_RECORD_H__
#define GEOSYS_RECORD_H__


#include "geoBasicType.h"


typedef struct __tag_RecnoList
{
	geoUInt32 RecnoCount;
	geoUInt32 *	RecnoList;
} geoRecnoList;

#ifdef _WIN32
#ifdef	LIB_RECORDS_EXPORTS
#define RECORDS_API	  __declspec(dllexport)
#else
#define RECORDS_API	  __declspec(dllimport)
#endif
#else
#define RECORDS_API
#endif

#ifdef __cplusplus
extern "C"
{
#endif


///	初始化
 
 RECORDS_API geoAPIStatus GEO_CALL REC_Init(geoStr envPath);


///	反初始化
 
 RECORDS_API geoAPIStatus GEO_CALL REC_UnInit();


///	创建一个表格
 
 RECORDS_API geoAPIStatus GEO_CALL REC_CreateTable(geoStr tableName);


///	打开表格
 
 RECORDS_API geoAPIStatus GEO_CALL REC_OpenTable(geoStr tableName);


///	打开表格后进行添加列操作
 
 RECORDS_API geoAPIStatus GEO_CALL REC_AddColumnItem(geoStr tableName, geoStr columnName, geoUInt8 valueType, geoUInt32 columnSize);


///	打开表格后进行删除列操作
 
 RECORDS_API geoAPIStatus GEO_CALL REC_DelColumnItem(geoStr tableName, geoStr columnName);


///	关闭表格
 
 RECORDS_API geoAPIStatus GEO_CALL REC_CloseTable(geoStr tableName);


///	删除表格
 
 RECORDS_API geoAPIStatus GEO_CALL REC_DeleteTable(geoStr tableName);


///	同步表格

 RECORDS_API geoAPIStatus GEO_CALL REC_SyncTable(geoStr tableName);

/// <summary>
///	关闭所有表格
 
 RECORDS_API geoAPIStatus GEO_CALL REC_CloseAllTab();


///	同步所有已经打开的表格
 
 RECORDS_API geoAPIStatus GEO_CALL REC_SyncAllOpenTab();


///	删除所有表格
 
 RECORDS_API geoAPIStatus GEO_CALL REC_DelAllTab();


///	对表格的某个列字段添加记录
 
 RECORDS_API geoAPIStatus GEO_CALL REC_AddRecord(geoStr tableName, geoStr nFieldName, geoVariant *pValue);


///	对表格添加一整行
 
 RECORDS_API geoAPIStatus GEO_CALL REC_AddRow(geoStr tableName, geoStringList *nFieldList, geoVariantList *nValueList); 


///	根据行号删除表中的记录,当删除的的行数大于当前最大行数时,也算成功,因为这种操作也合理
 
 RECORDS_API geoAPIStatus GEO_CALL REC_DelRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno);


///	根据行号删除表中的一整行,当删除的的行数大于当前最大行数时,也算成功,因为这种操作也合理
 
 RECORDS_API geoAPIStatus GEO_CALL REC_DelRow(geoStr tableName, geoUInt32 recno);


///	修改表格的记录
 
 RECORDS_API geoAPIStatus GEO_CALL REC_ModifyRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno, geoVariant *nval);


///	根据行号来修改对应的一整行
 
 RECORDS_API geoAPIStatus GEO_CALL REC_ModifyRow(geoStr tableName, geoUInt32 recno, geoStringList *nFieldList, geoVariantList *nValueList);


///	获取某表中某字段的数据类型
 
 RECORDS_API geoAPIStatus GEO_CALL REC_GetColumnType(geoStr tableName, geoStr fieldName, POUT geoUInt8* fieldType);


///	根据行号获取表的格字段下记录
 
 RECORDS_API geoAPIStatus GEO_CALL REC_GetRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno, POUT geoVariant **pValue);


///	根据行号获取表的一整行
 
 RECORDS_API geoAPIStatus GEO_CALL REC_GetRow(geoStr tableName, geoStringList *fieldList, geoUInt32 recno, POUT geoVariantList **nValueList);


///	获取某表某字段特定值对应的所有记录号
 
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterEqual(geoStr tableName, geoStr fieldName, geoVariant *nval, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);


///	获取某表某字段值范围对应的所有记录号//范围查询采用前闭后开区间
 
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterScope(geoStr tableName, geoStr fieldName, geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);


///	获取某表某字段为某些值时的所有记录号，字段值之间条件是交集
 
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterIntersection(geoStr tableName, geoStringList* columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);


///	获取某表中，等于某些字段值的所有记录号，字段值之间条件是并集
 
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterUnion(geoStr tableName, geoStringList *columnNameList, geoVariantList *nValueList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList);


///	判断表格是否存在
 
 RECORDS_API geoAPIStatus GEO_CALL REC_IsTableExist(geoStr tableName, POUT geoBool* isTabExist);


 RECORDS_API geoAPIStatus GEO_CALL REC_GetMaxRecno(geoStr tableName, POUT geoUInt32* maxRecno);

#ifdef __cplusplus
};
#endif

#endif
