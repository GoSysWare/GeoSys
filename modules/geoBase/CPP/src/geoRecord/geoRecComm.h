/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRecComm.h													*
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
#ifndef  GEOSYS_RECORD_COMM_H__
#define GEOSYS_RECORD_COMM_H__

#include"geoBasicType.h"
#include "db/db_cxx.h"

#define  DEFAULT_TABLE_CREATENAME	"geosysadmin"
#define  DEFAULT_TABLE_DESC		"table description is  nothing"
#define  DEFAULT_BASEDB_DBNAME		"recdb"
#define  DEFAULT_BASEDB_DBFILNAME		"recdb_"
#define  DEFAULT_TABLESMGR_DBFILNAME		"RecordsMgr.itb"
#define  DEFAULT_BASEDB_SUFFIX		".db"

#define DEFAULT_ENV_CACHENUM 1
#define DEFAULT_ENV_CACHESIZE 104857600
#define TABLE_NAME_SIZE 32
#define COLUMN_NAME_SIZE 32
#define TABLE_CREATENAME_SIZE 16
#define TABLE_DESC_SIZE 64
#define TABLE_KEY_SIZE 32
#define COLUMN_KEY_SIZE 32

//可建立的最大表格数
#define TABLE_MAX_SIZE 32
//表格最大行数
#define ROW_MAX_SIZE 1024 *1024 *2
//表格最大列数
#define COL_MAX_SIZE 32
//可查询的最大记录数
#define  QUERY_MAX_COUNT 30000



typedef geoInt32 REC_STATUS_MARK;


typedef struct  __st_TABLEINFO
{
	geoChar tbName[TABLE_NAME_SIZE];				//表名
	geoChar tbCreateUserName[TABLE_CREATENAME_SIZE];	//创建者姓名
	geoTime tbCreateTime;						//创建时间
	geoTime tbLastSaveTime;						//上次保存时间
	geoChar tbDesc[TABLE_DESC_SIZE];				//表格描述
	geoUInt8 tbType;							//表格类型
	geoUInt32 tbRowCurSize;					    //表格当前有的行数
	geoUInt32 tbColumnCurSize;					//当前最大列数
	geoUInt32 tbRowMaxsize;					    //行数最大容量数
	geoUInt32 tbColMaxsize;					    //列数最大容量数
	geoUInt64 tbMaxSize;						//当前的容量，即占有字节数(KB为单位)
}geoRecTableInfo;




//表名
typedef struct __st_TABLE_KEY{
	geoChar Data[TABLE_KEY_SIZE];
} geoTableName, *geoTableName_Ptr;


//列名
typedef struct __st_COLUMN_KEY{
	geoChar Data[COLUMN_KEY_SIZE];
} geoColumnName, *geoColumnName_Ptr;

//列信息
typedef struct __st_COLUMN_INFO{
	geoColumnName Name;
	geoUInt32	CurSize;
	geoUInt8	Datatype;
	geoUInt64   MaxSize;
	geoUInt32	RecordSize;
} geoColumnInfo, *geoColumnInfo_Ptr;

template<typename T>
int rtk_compare_key(const T & k1, const T & k2)
{
	return strncasecmp((const char *)&k1, (const char *)&k2, sizeof(T));
	//return memcmp((const char *)&k1, (const char *)&k2, sizeof(T));
}

//重载Map模板类中的比较函数
//在Map中可以进行根据关键字进行查找
inline bool operator < (const geoTableName &t1, const geoTableName &t2)
{
	return rtk_compare_key(t1, t2)<0? true : false;
}
inline bool operator == (const geoTableName &t1, const geoTableName &t2)
{
	return rtk_compare_key(t1, t2)==0? true : false;
}

inline bool operator < (const geoColumnName &t1, const geoColumnName &t2)
{
	return rtk_compare_key(t1, t2)<0? true : false;
}
inline bool operator == (const geoColumnName &t1, const geoColumnName &t2)
{
	return rtk_compare_key(t1, t2)==0? true : false;
}
inline geoUInt32 db_partition_fun(Db *db, Dbt *key)
{
	int keyval = 0;
	keyval = *((int*)key->get_data());
	if (keyval < 2000000)
	{
		return 0;
	}
	else if (keyval < 4000000)
	{
		return 1;
	}
	else if (keyval < 6000000)
	{
		return 2;
	}
	else if (keyval < 8000000)
	{
		return 3;
	}
	else if (keyval < 10000000)
	{
		return 4;
	}
	else if (keyval < 12000000)
	{
		return 5;
	}
	else if (keyval < 14000000)
	{
		return 6;
	}
	else if (keyval < 16000000)
	{
		return 7;
	}
	else if (keyval < 18000000)
	{
		return 8;
	}
	else if (keyval < 20000000)
	{
		return 9;
	}
	return 9;
}


#endif
