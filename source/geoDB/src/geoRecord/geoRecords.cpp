#ifndef LIB_RECORDS_EXPORTS
#define LIB_RECORDS_EXPORTS
#endif // !LIB_RECORDS_EXPORTS


#include "geoBasicType.h"
#include "geoRecords.h"
#include "geoRecTableManager.h"

//全局管理类指针
CTableManager *g_TableMgr = geoNULL;

 RECORDS_API geoAPIStatus GEO_CALL REC_Init(geoStr envPath)
{
	if (IsNotNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	g_TableMgr = new CTableManager();
	return g_TableMgr->Init(envPath);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_UnInit()
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	g_TableMgr->UnInit();
	delete g_TableMgr;
	g_TableMgr = geoNULL;
	return geoRET_SUCC;
}

 RECORDS_API geoAPIStatus GEO_CALL REC_CreateTable(geoStr tableName)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->CreateTable(tableName);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_OpenTable(geoStr tableName)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->OpenTable(tableName);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_AddColumnItem(geoStr tableName, geoStr columnName, geoUInt8 valueType, geoUInt32 columnSize)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->AddColumnItem(tableName, columnName, valueType, columnSize);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_DelColumnItem(geoStr tableName, geoStr columnName)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->DelColumnItem(tableName, columnName);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_CloseTable(geoStr tableName)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->CloseTable(tableName);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_DeleteTable(geoStr tableName)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->DeleteTable(tableName);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_SyncTable(geoStr tableName)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->SyncTab(tableName);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_CloseAllTab()
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->CloseAllTab();
}

 RECORDS_API geoAPIStatus GEO_CALL REC_SyncAllOpenTab()
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->SyncAllOpenTab();
}

 RECORDS_API geoAPIStatus GEO_CALL REC_DelAllTab()
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->DelAllTab();
}
 
 RECORDS_API geoAPIStatus GEO_CALL REC_GetTableInfo(geoStr tableName, geoRecTableInfo *tbInfo)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->GetTableInfo(tableName, tbInfo);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_AddRecord(geoStr tableName, geoStr nFieldName, geoVariant *pValue)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->AddRecord(tableName, nFieldName, pValue);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_AddRow(geoStr tableName, geoStringList *nFieldList, geoVariantList *nValueList) 
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->AddRow(tableName, nFieldList, nValueList);
}

 RECORDS_API geoAPIStatus GEO_CALL REC_DelRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->DelRecord(tableName, fieldName, recno);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_DelRow(geoStr tableName, geoUInt32 recno)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->DelRow(tableName, recno);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_ModifyRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno, geoVariant *nval)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->ModifyRecord(tableName, fieldName, recno, nval);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_ModifyRow(geoStr tableName, geoUInt32 recno, geoStringList *nFieldList, geoVariantList *nValueList)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->ModifyRow(tableName, recno, nFieldList, nValueList);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_GetColumnType(geoStr tableName, geoStr fieldName, POUT geoUInt8* fieldType)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->GetColumnType(tableName, fieldName, fieldType);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_GetRecord(geoStr tableName, geoStr fieldName, geoUInt32 recno, POUT geoVariant **pValue)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->GetRecord(tableName, fieldName, recno, pValue);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_GetRow(geoStr tableName, geoStringList *fieldList, geoUInt32 recno, POUT geoVariantList **nValueList)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->GetRow(tableName, fieldList, recno, nValueList);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterEqual(geoStr tableName, geoStr fieldName, geoVariant *nval, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->QueryRecordsAdapterEqual(tableName, fieldName, nval, rangeCount, recnoList);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterScope(geoStr tableName, geoStr fieldName, geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->QueryRecordsAdapterScope(tableName, fieldName, nvBegin, nvEnd, rangeCount, recnoList);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterIntersection(geoStr tableName, geoStringList* columnNameList, geoVariantList *nvList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->QueryRecordsAdapterIntersection(tableName, columnNameList, nvList, rangeCount, recnoList);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_QueryRecordsAdapterUnion(geoStr tableName, geoStringList *columnNameList, geoVariantList *nValueList, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	if (IsNull(g_TableMgr))
	{
		return geoRET_FAIL;
	}
	return g_TableMgr->QueryRecordsAdapterUnion(tableName, columnNameList, nValueList, rangeCount, recnoList);
}
 RECORDS_API geoAPIStatus GEO_CALL REC_IsTableExist(geoStr tableName, POUT geoBool* isTabExist)
{
	if (IsNull(g_TableMgr) || IsNull(isTabExist))
	{
		return geoRET_FAIL;
	}
	*isTabExist = g_TableMgr->IsTableExist(tableName);
	return geoRET_SUCC;
}

 RECORDS_API geoAPIStatus GEO_CALL REC_GetMaxRecno(geoStr tableName, geoUInt32* maxRecno)
{
    if (IsNull(g_TableMgr))
    {
        return geoRET_FAIL;
    }
    return g_TableMgr->GetMaxRecno(tableName, maxRecno);
}
