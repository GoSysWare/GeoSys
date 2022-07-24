/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.						                         *
*                                                                            *
*  @file     geoRecDBVariant.h													*
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
#ifndef  GEOSYS_RECORD_DBVARIANT_H__
#define GEOSYS_RECORD_DBVARIANT_H__
#include <vector>
#include "db/db_cxx.h"
#include "geoBasicType.h"
#include "geoRecBaseDB.h"

using namespace std;
//此类是用Recon作为key的，只是val要根据模板类型进行选择，如int,double
//T是val的数据类型，注意这个没办法用作字符串类型的val。

//除去字符串类型作为Val的Bdb
template <typename T>
class   CDBVariant_Impl:public CRecBaseDB_Impl
{
public:
	CDBVariant_Impl(DbEnv *dbEnv,DBTYPE dbType =DB_BTREE );
	virtual ~CDBVariant_Impl();
	virtual geoInt32 Init(geoUInt8 nKeyType=0, geoUInt32 nKeySize=0, geoUInt8 nValType=0, geoUInt32 nValSize=0);
	virtual geoInt32 UnInit();
	virtual geoInt32 AddRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 InsertRec(geoVoid *dbcursor, geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 DelRec(geoVoid *dbKey);
	virtual geoInt32 MfyRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 GetRec(geoVoid *dbKey, geoVoid **dbVal);
	virtual geoInt32 QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist);
	virtual geoInt32 QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist);
	static geoInt32 DbKeyCompareFunc(Db *_db, const Dbt * Key_1, const Dbt * Key_2);

};

//专门用来处理geoString的bdb
template <geoUInt32 DBVALSIZE >
class   CDBStirng_Impl:public CRecBaseDB_Impl
{
public:
	CDBStirng_Impl(DbEnv *dbEnv,DBTYPE dbType =DB_BTREE );
	virtual ~CDBStirng_Impl();
	virtual geoInt32 Init(geoUInt8 nKeyType = 0,geoUInt32 nKeySize=0,geoUInt8 nValType =0,geoUInt32 nValSize= 0);
	virtual geoInt32 UnInit();
	virtual geoInt32 AddRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 InsertRec(geoVoid *dbcursor,geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 DelRec(geoVoid *dbKey);
	virtual geoInt32 MfyRec(geoVoid *dbKey, geoVoid *dbVal);
	virtual geoInt32 GetRec(geoVoid *dbKey, geoVoid **dbVal);
	virtual geoInt32 QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist);
	virtual geoInt32 QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist);
	static geoInt32 DbKeyCompareFunc(Db *_db, const Dbt * Key_1, const Dbt * Key_2);
};


template <typename T>
//key1是user的，key_2是db的
geoInt32 CDBVariant_Impl<T>::DbKeyCompareFunc(Db *_db, const Dbt * Key_1, const Dbt * Key_2)
{
	geoUInt32 * _key1 = (geoUInt32 * )Key_1->get_data();
	geoUInt32 * _key2 = (geoUInt32 * )Key_2->get_data();

	return  (*_key1) - (*_key2);
}
template <typename T>
CDBVariant_Impl<T>::CDBVariant_Impl(DbEnv *dbEnv,DBTYPE dbType):CRecBaseDB_Impl(dbEnv,dbType)
{
	db_->set_bt_compare(&CDBVariant_Impl<T>::DbKeyCompareFunc);
}
template <typename T>
CDBVariant_Impl<T>::~CDBVariant_Impl()
{

}
template <typename T>
geoInt32 CDBVariant_Impl<T>::Init(geoUInt8 nKeyType, geoUInt32 nKeySize, geoUInt8 nValType, geoUInt32 nValSize)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//key是recon
	SetKeyDbcType(geoDataType_UInt32);
	SetKeyDbcSize(sizeof(geoUInt32));

	//val是geoDataType_Blob,所有的数值都以内存方式存储
	SetValDbcType(geoDataType_Blob);
	SetValDbcSize(sizeof(T));
	return nRet;
}
template <typename T>
geoInt32 CDBVariant_Impl<T>::UnInit()
{
	geoAPIStatus nRet = geoRET_SUCC;
	return nRet;
}
template <typename T>
geoInt32 CDBVariant_Impl<T>::AddRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	geoUInt32 *_key = (geoUInt32*)dbKey;
	T *_data = (T *)dbVal;
	Dbc *cursor_ptr;
	db_->cursor(NULL, &cursor_ptr, 0);

	Dbt key(_key, nKeyDbcSize_);
	Dbt data(_data, nValDbcSize_);
//	ACE_DEBUG((LM_DEBUG, " CDBVariant_Impl<T>::AddRec --nValDbcSize_: %d\n",nValDbcSize_));
	geoInt32 ret = cursor_ptr->put(&key, &data, DB_KEYFIRST);
	if (cursor_ptr != NULL)
	{
		cursor_ptr->close();
	}
	if (ret != 0)
	{
		return geoRET_FAIL;
	}

	return nRet;
}
template <typename T>
//插入操作暂不实现
geoInt32 CDBVariant_Impl<T>::InsertRec(geoVoid *dbcursor,geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	nRet = geoRET_FAIL;
	return nRet;
}
template <typename T>
geoInt32 CDBVariant_Impl<T>::DelRec(geoVoid *dbKey)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoUInt32 *_key = (geoUInt32*)dbKey;
	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	Dbt tempkey(_key, nKeyDbcSize_);
	Dbt data;
	nRet = cursorp->get(&tempkey, &data, DB_SET);
	if (nRet == 0)
	{
		cursorp->del(geoNULL);
	}

	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
template <typename T>
//不修改Key，只修改Val
geoInt32 CDBVariant_Impl<T>::MfyRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	geoUInt32 *_key = (geoUInt32*)dbKey;
	T *_data = (T *)dbVal;


	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt key(_key, nKeyDbcSize_);
	Dbt tempdata;
	Dbt data(_data,nValDbcSize_);

//	ACE_DEBUG((LM_DEBUG, " CDBVariant_Impl<T>::MfyRec --nValDbcSize_: %d\n",nValDbcSize_));

	if ((nRet = cursorp->get(&key, &tempdata, DB_SET)) == 0)
	{
		nRet = cursorp->put(&key, &data, DB_CURRENT);

	}
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
template <typename T>
geoInt32 CDBVariant_Impl<T>::GetRec(geoVoid *dbKey, geoVoid **dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	geoUInt32 *_key = (geoUInt32*)dbKey;

	//Value输出缓冲
	NewAndClear(dbVal,nValDbcSize_);
//	ACE_DEBUG((LM_DEBUG, " CDBVariant_Impl<T>::GetRec --nValDbcSize_: %d\n",nValDbcSize_));
	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey(_key, nKeyDbcSize_);
	Dbt tempdata;
	RET_ERR(cursorp->get(&tempkey, &tempdata, DB_SET));

	memcpy(*dbVal, tempdata.get_data(), nValDbcSize_);

	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
template <typename T>
geoInt32 CDBVariant_Impl<T>::QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoRecnoList **retlist = (geoRecnoList **)ppReconlist;
	//输出缓冲区
	std::vector<geoUInt32> tempVector;
	T* setval =(T*)dbVal;

	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey;
	Dbt tempdata;

	while ((nRet = cursorp->get(&tempkey,&tempdata,DB_NEXT)) == 0 && (rangeCount--))
	{
		T* tempT = (T*)tempdata.get_data();
		if (*tempT == *setval )
		{
			tempVector.push_back(*((geoUInt32*)tempkey.get_data()));
		}

	}
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	if (tempVector.size() > 0)
	{
		NewReconListEx(retlist, tempVector.size());
		for (geoUInt32 i = 0; i < tempVector.size() ; i++)
		{
			(*retlist)->RecnoList[i] = tempVector[i];
		}
	}
	else
	{
		NewReconList(retlist);
	}

	return nRet;
}
template <typename T>
geoInt32 CDBVariant_Impl<T>::QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoRecnoList **retlist = (geoRecnoList **)ppReconlist;
	//输出缓冲区
	std::vector<geoUInt32> tempVector;

	T *sval =(T*)dbValStart;
	T *eval =(T*)dbValEnd;
	T tswap;
	//如果起止的值顺序相反，则内部调整
	if (*sval > *eval)
	{
		tswap = *sval;
		*sval = *eval;
		*eval = tswap;
	}

	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey;;
	Dbt tempdata;

	while ((nRet = cursorp->get(&tempkey,&tempdata,DB_NEXT)) == 0 && (rangeCount--))
	{
		T * tempT = (T *)tempdata.get_data();
		if ( (* sval <= *tempT) && (*tempT < *eval))
		{
			tempVector.push_back(*((geoUInt32*)tempkey.get_data()));
		}

	}
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	if (tempVector.size() > 0)
	{
		NewReconListEx(retlist,tempVector.size());
		for (geoUInt32 i = 0; i < tempVector.size(); i++)
		{
			(*retlist)->RecnoList[i] = tempVector[i];
		}
	}
	else
	{
		NewReconList(retlist);
	}
	return nRet;
}




template <geoUInt32 DBVALSIZE >
//key1是user的，key_2是db的
geoInt32 CDBStirng_Impl<DBVALSIZE>::DbKeyCompareFunc(Db *_db, const Dbt * Key_1, const Dbt * Key_2)
{
	geoUInt32 * _key1 = (geoUInt32 * )Key_1->get_data();
	geoUInt32 * _key2 = (geoUInt32 * )Key_2->get_data();

	return  (*_key1) - (*_key2);
}
template <geoUInt32 DBVALSIZE >
CDBStirng_Impl< DBVALSIZE>::CDBStirng_Impl(DbEnv *dbEnv,DBTYPE dbType):CRecBaseDB_Impl(dbEnv, dbType)
{
	db_->set_bt_compare(&CDBStirng_Impl<DBVALSIZE>::DbKeyCompareFunc);
}
template <geoUInt32 DBVALSIZE >
CDBStirng_Impl< DBVALSIZE>::~CDBStirng_Impl()
{

}
template <geoUInt32 DBVALSIZE >
geoInt32 CDBStirng_Impl< DBVALSIZE>::Init(geoUInt8 nKeyType, geoUInt32 nKeySize, geoUInt8 nValType, geoUInt32 nValSize)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//key是recon
	SetKeyDbcType(vTypeUInt32);
	SetKeyDbcSize(sizeof(geoUInt32));

	//val是geoDataType_Blob,所有的数值都以内存方式存储
	SetValDbcType(vTypeString);
	SetValDbcSize(DBVALSIZE);
	return nRet;
}
template <geoUInt32 DBVALSIZE >
geoInt32 CDBStirng_Impl< DBVALSIZE>::UnInit()
{
	geoAPIStatus nRet = geoRET_SUCC;
	return nRet;
}
template <geoUInt32 DBVALSIZE >
geoInt32 CDBStirng_Impl< DBVALSIZE>::AddRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	geoUInt32 *_key = (geoUInt32*)dbKey;
	geoChar * strTemp = (geoChar *)dbVal;
	geoChar *_data = geoNULL;

	NewAndClear((geoVoid **)&_data, nValDbcSize_);

//	ACE_DEBUG((LM_DEBUG, " CDBStirng_Impl< DBVALSIZE>::AddRec --nValDbcSize_: %d\n",nValDbcSize_));

	geoUInt32 len = min(strlen(strTemp), nValDbcSize_);
	memcpy(_data,strTemp,len);

	Dbc *cursor_ptr;
	db_->cursor(NULL, &cursor_ptr, 0);

	Dbt key(_key, nKeyDbcSize_);
	Dbt data(_data, nValDbcSize_);
	geoInt32 ret = cursor_ptr->put(&key, &data, DB_KEYFIRST);
	if (cursor_ptr != NULL)
	{
		cursor_ptr->close();
	}
	FreeAndNull((geoVoid **)&_data);
	if (ret != 0)
	{
		return geoRET_FAIL;
	}

	return nRet;
}
template <geoUInt32 DBVALSIZE >
//插入操作暂不实现
geoInt32 CDBStirng_Impl< DBVALSIZE>::InsertRec(geoVoid *dbcursor, geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;
	nRet = geoRET_FAIL;
	return nRet;
}
template <geoUInt32 DBVALSIZE >
geoInt32 CDBStirng_Impl< DBVALSIZE>::DelRec(geoVoid *dbKey)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoUInt32 *_key = (geoUInt32*)dbKey;
	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	Dbt tempkey(_key, nKeyDbcSize_);
	Dbt data;
	nRet = cursorp->get(&tempkey, &data, DB_SET);
	if (nRet == 0)
	{
		cursorp->del(geoNULL);
	}

	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
template <geoUInt32 DBVALSIZE >
//不修改Key，只修改Val
geoInt32 CDBStirng_Impl< DBVALSIZE>::MfyRec(geoVoid *dbKey, geoVoid *dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	geoUInt32 *_key = (geoUInt32*)dbKey;
	geoChar* strTemp = (geoChar *)dbVal;
	geoChar *_data = geoNULL;

	NewAndClear((geoVoid **)&_data, nValDbcSize_);
	strcpy(_data,strTemp);

//	ACE_DEBUG((LM_DEBUG, " CDBStirng_Impl< DBVALSIZE>::MfyRec --nValDbcSize_: %d\n",nValDbcSize_));
	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt key(_key, nKeyDbcSize_);
	Dbt tempdata;
	Dbt data(_data, nValDbcSize_);
	if ((nRet = cursorp->get(&key, &tempdata, DB_SET)) == 0)
	{
		nRet = cursorp->put(&key, &data, DB_CURRENT);

	}
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
template <geoUInt32 DBVALSIZE >
geoInt32 CDBStirng_Impl< DBVALSIZE>::GetRec(geoVoid *dbKey, geoVoid **dbVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	geoUInt32 *_key = (geoUInt32*)dbKey;
	geoChar ** _data = (geoChar **) dbVal;

	//Value输出缓冲
	NewAndClear((geoVoid **)_data,nValDbcSize_);
//	ACE_DEBUG((LM_DEBUG, " CDBStirng_Impl< DBVALSIZE>::GetRec --nValDbcSize_: %d\n",nValDbcSize_));
	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey(_key, nKeyDbcSize_);
	Dbt tempdata;
	RET_ERR(cursorp->get(&tempkey, &tempdata, DB_SET));
	memcpy(*_data, tempdata.get_data(), nValDbcSize_);
	(*_data)[nValDbcSize_-1] ='\0';
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	return nRet;
}
template <geoUInt32 DBVALSIZE >
geoInt32 CDBStirng_Impl< DBVALSIZE>::QueryRec_Equal(geoVoid *dbVal, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoChar* setval = (geoChar*)dbVal;
	geoRecnoList **retlist = (geoRecnoList **)ppReconlist;

	//输出缓冲区
	std::vector<geoUInt32> tempVector;


	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey;;
	Dbt tempdata;

	while ((nRet = cursorp->get(&tempkey,&tempdata,DB_NEXT)) == 0 && (rangeCount--))
	{
		geoChar* tempT = (geoChar* )tempdata.get_data();
		if ( memcmp(tempT, setval, strlen(setval)) == 0)
		{
			tempVector.push_back(*((geoUInt32*)tempkey.get_data()));
		}

	}
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	if (tempVector.size() >0 )
	{
		NewReconListEx(retlist,tempVector.size());
		for (geoUInt32 i = 0; i < tempVector.size() ; i++)
		{
			(*retlist)->RecnoList[i] = tempVector[i];
		}
	}
	else
	{
		NewReconList(retlist);
	}
	return nRet;
}
template <geoUInt32 DBVALSIZE >
geoInt32 CDBStirng_Impl< DBVALSIZE>::QueryRec_Range(geoVoid *dbValStart, geoVoid *dbValEnd, geoUInt32 rangeCount, geoVoid **ppReconlist)
{
	geoAPIStatus nRet = geoRET_SUCC;
	geoRecnoList **retlist = (geoRecnoList **)ppReconlist;
	//输出缓冲区
	std::vector<geoUInt32> tempVector;

	geoChar* sval =(geoChar*)dbValStart;
	geoChar* eval =(geoChar*)dbValEnd;
	geoChar* tswap;
	//如果起止的值顺序相反，则内部调整
	if (strcmp(sval,eval) > 0)
	{
		tswap = sval;
		sval = eval;
		eval = tswap;
	}

	Dbc *cursorp = geoNULL;
	db_->cursor(geoNULL, &cursorp, 0);
	if (IsNull(cursorp))
	{
		return geoRET_FAIL;
	}
	Dbt tempkey;;
	Dbt tempdata;

	while ((nRet = cursorp->get(&tempkey, &tempdata, DB_NEXT)) == 0 && (rangeCount--))
	{
		geoChar* tempT = (geoChar*)tempdata.get_data();
		if(memcmp(tempT,sval,strlen(sval)) >= 0  && memcmp(tempT, eval, strlen(eval)) < 0)
		{
			tempVector.push_back(*((geoUInt32*)tempkey.get_data()));
		}

	}
	if (IsNotNull(cursorp ))
	{
		cursorp->close();
	}
	if (tempVector.size() > 0)
	{
		NewReconListEx(retlist,tempVector.size());
		for (geoUInt32 i = 0; i < tempVector.size() ; i++)
		{
			(*retlist)->RecnoList[i] = tempVector[i];
		}
	}
	else
	{
		NewReconList(retlist);
	}
	return nRet;
}


#endif
