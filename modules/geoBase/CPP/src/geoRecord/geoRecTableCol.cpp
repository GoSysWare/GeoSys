

#include "preCompile.h"
#include "geoRecTableCol.h"

CRecTableCol::CRecTableCol(DbEnv *dbenv)
{
	dbenv_ = dbenv;
}
CRecTableCol::~CRecTableCol()
{
	if (IsNotNull(recColDb_))
	{
		delete recColDb_;
	}
}
geoInt32 CRecTableCol::TC_OpenColumn()
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (recColDb_->bIsOpen_ == geoTRUE)
	{
		return nRet;
	}
	geoStr* pdir = (geoStr*)malloc(sizeof(geoStr)*2);
	dbenv_->get_home((const char**)pdir);
	pdir[1] = NULL;
	int result = 0;
	result = recColDb_->GetDb()->set_partition_dirs((const char**)pdir);
	result = recColDb_->GetDb()->set_partition(10, NULL, db_partition_fun); //根据回调函数分区
	recColDb_->OpenDB();
	free(pdir);
	return nRet;
}
geoInt32 CRecTableCol::TC_CloseColumn()
{
	geoAPIStatus nRet = geoRET_SUCC;
	recColDb_->CloseDB();
	return nRet;
}
geoInt32 CRecTableCol::TC_AddColumnItem(geoStr columnName, geoUInt8 valueType, geoUInt32 columnSize)
{
	geoAPIStatus nRet = geoRET_SUCC;
	//判断添加列的数据类型
	if ( valueType <= vTypeEmpty || valueType >= vTypeMax)
	{
		return geoRET_FAIL;
	}
	switch (valueType)
	{
	case vTypeBool:
		{
			CDBVariant_Impl<geoBool> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoBool); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoBool>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeInt8:
		{
			CDBVariant_Impl<geoInt8> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoInt8); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoInt8>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeUInt8:
		{
			CDBVariant_Impl<geoUInt8> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoUInt8); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoUInt8>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeInt16:
		{
			CDBVariant_Impl<geoInt16> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoInt16); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoInt16>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeUInt16:
		{
			CDBVariant_Impl<geoUInt16> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoUInt16); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoUInt16>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeInt32:
		{
			CDBVariant_Impl<geoInt32> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoInt32); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoInt32>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeUInt32:
		{
			CDBVariant_Impl<geoUInt32> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoUInt32); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoUInt32>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeInt64:
		{
			CDBVariant_Impl<geoInt64> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoInt64); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoInt64>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeUInt64:
		{
			CDBVariant_Impl<geoUInt64> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoUInt64); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoUInt64>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl),geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeFloat:
		{
			CDBVariant_Impl<geoFloat> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoFloat); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoFloat>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeDouble:
		{
			CDBVariant_Impl<geoDouble> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoDouble); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoDouble>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL); 
			vImpl->Init();
			break;
		}
	case vTypeTimeStamp:
		{
			CDBVariant_Impl<geoTime> *vImpl =  geoNULL; 
			info_.RecordSize = sizeof(geoTime); 
			GEO_NEW_RETURN(vImpl, CDBVariant_Impl<geoTime>(dbenv_), geoRET_FAIL); 
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(vImpl), geoRET_FAIL);
			vImpl->Init();
			break;
		}
	case vTypeAString :
	case vTypeWString :
	case vTypeString :
	case vTypeBlob :
		if ( 0 <= columnSize && columnSize <= 32)
		{
			info_.RecordSize = 32;
			CDBStirng_Impl<32> *strImpl =  geoNULL;
			GEO_NEW_RETURN(strImpl, CDBStirng_Impl<32>(dbenv_), geoRET_FAIL);
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(strImpl), geoRET_FAIL);
			strImpl->Init();

		}
		else if( 32 < columnSize && columnSize <= 64)
		{
			info_.RecordSize = 64;
			CDBStirng_Impl<64> *strImpl =  geoNULL;
			GEO_NEW_RETURN(strImpl, CDBStirng_Impl<64>(dbenv_), geoRET_FAIL);
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(strImpl), geoRET_FAIL);
			strImpl->Init();
		}
		else if( 64 < columnSize && columnSize <= 128)
		{
			info_.RecordSize = 128;
			CDBStirng_Impl<128> *strImpl =  geoNULL;
			GEO_NEW_RETURN(strImpl, CDBStirng_Impl<128>(dbenv_), geoRET_FAIL);
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(strImpl), geoRET_FAIL);
			strImpl->Init();
		}else if( 128 < columnSize && columnSize <= 256)
		{
			info_.RecordSize = 256;
			CDBStirng_Impl<256> *strImpl =  geoNULL;
			GEO_NEW_RETURN(strImpl, CDBStirng_Impl<256>(dbenv_), geoRET_FAIL);
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(strImpl), geoRET_FAIL);
			strImpl->Init();
		}else if( 256 < columnSize && columnSize <= 512)
		{
			info_.RecordSize = 512;
			CDBStirng_Impl<512> *strImpl =  geoNULL;
			GEO_NEW_RETURN(strImpl, CDBStirng_Impl<512>(dbenv_), geoRET_FAIL);
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(strImpl), geoRET_FAIL);
			strImpl->Init();
		}else if( 512 < columnSize && columnSize <= 1024)
		{
			info_.RecordSize = 1024;
			CDBStirng_Impl<1024> *strImpl =  geoNULL;
			GEO_NEW_RETURN(strImpl, CDBStirng_Impl<1024>(dbenv_), geoRET_FAIL);
			GEO_NEW_RETURN(recColDb_, CRecBaseDB(strImpl), geoRET_FAIL);
			strImpl->Init();
		}
		else
				{
					info_.RecordSize = 2048;
					CDBStirng_Impl<2048> *strImpl =  geoNULL;
					GEO_NEW_RETURN(strImpl, CDBStirng_Impl<2048>(dbenv_), geoRET_FAIL);
					GEO_NEW_RETURN(recColDb_, CRecBaseDB(strImpl), geoRET_FAIL);
					strImpl->Init();
				}
		break;
	default:
		return geoRET_FAIL;
	}

	geoChar tempColName[128];
	memset(tempColName, 0, sizeof(tempColName));
	strncpy(tempColName, columnName, strlen(columnName));
	strncpy(tempColName + strlen(columnName), DEFAULT_BASEDB_SUFFIX, sizeof(DEFAULT_BASEDB_SUFFIX));
	RET_ERR(recColDb_->InitDB(geoNULL, tempColName));

	TC_OpenColumn();

	recColDb_->GetMaxRecno(&info_.CurSize);
	strcpy(info_.Name.Data,columnName);
	info_.Datatype = valueType;
	info_.MaxSize = info_.CurSize * info_.RecordSize / 1000;
	return nRet;
}
geoInt32 CRecTableCol::TC_DelColumnItem()
{
	geoAPIStatus nRet = geoRET_SUCC;
	//清空里面所有的内容
	RET_ERR(TC_DelAllColumnItem());
	//同步到文件
	recColDb_->SyncDB();
	recColDb_->CloseDB();

	return nRet;
}
geoInt32 CRecTableCol::TC_AddRecord(geoVariant *pVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	//无论添加成功还是失败，都算添加过了，计数器+1,TC_GetRecrod做处理保证
	//取值失败时返回一个空类型的值
	if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE)
	{
		info_.CurSize++;
		return geoRET_FAIL;
	}
	geoUInt32 recon = info_.CurSize +1;
    if(info_.Datatype != pVal->varType)
    {
        return geoRET_FAIL;
    }
	if (pVal->varType == vTypeString ||
		pVal->varType == vTypeAString ||
		pVal->varType == vTypeWString ||
		pVal->varType == vTypeBlob)
	{
		info_.CurSize++;
		RET_ERR(recColDb_->AddRec(&recon, (geoVoid*)pVal->vString.Data));
	}
	else
	{
		info_.CurSize++;
		RET_ERR(recColDb_->AddRec(&recon, (geoVoid*)&pVal->vBool));
	}
	//计数器+1
	return nRet;
}
geoInt32 CRecTableCol::TC_MfyRecord(geoUInt32 recno, geoVariant *pVal)
{
    geoAPIStatus nRet = geoRET_SUCC;
    if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE)
    {
        return geoRET_FAIL;
    }
    if (recno > info_.CurSize)
    {
        return geoRET_FAIL;
    }
	if (pVal->varType == vTypeString ||
		pVal->varType == vTypeAString ||
		pVal->varType == vTypeWString ||
		pVal->varType == vTypeBlob)
    {
        RET_ERR(recColDb_->MfyRec(&recno, (geoVoid*)pVal->vString.Data));	
    }
    else
    {
        RET_ERR(recColDb_->MfyRec(&recno, (geoVoid*)&pVal->vBool));
    }

    return nRet;
}
geoInt32 CRecTableCol::TC_DelRecord(geoUInt32 recno)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE)
	{
		return geoRET_FAIL;
	}
	if (recno > info_.CurSize)
	{
		return nRet;
	}
	RET_ERR(recColDb_->DelRec(&recno));
	//每一列下面的记录号只增不减，保持对齐
	//info_.CurSize--;
	return nRet;
}

geoInt32 CRecTableCol::TC_GetRecord(geoUInt32 recno, geoVariant **pVal)
{
	geoAPIStatus nRet = geoRET_SUCC;

	if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE||recno > info_.CurSize )
	{
		Variant_New(vTypeEmpty, pVal);
		return geoRET_SUCC;
	}
	NEW_Variant(pVal);
	(*pVal)->varType = info_.Datatype;
	if (info_.Datatype == vTypeString ||
		info_.Datatype == vTypeAString ||
		info_.Datatype == vTypeWString ||
		info_.Datatype == vTypeBlob)
	{
		RET_ERR(recColDb_->GetRec(&recno, (geoVoid**)&(*pVal)->vString.Data));
		(*pVal)->vString.Length = strlen((*pVal)->vString.Data);
	}
	else
	{
		geoChar * buff = geoNULL;
		recColDb_->GetRec(&recno, (geoVoid**)&buff);
		memcpy(&(*pVal)->vBool, buff, info_.RecordSize);
		FreeAndNull((geoVoid**)&buff);
	}
	return nRet;
}
geoInt32 CRecTableCol::TC_QueryAdapterEqual(geoVariant *nval, geoUInt32 rangeCount, geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;	
	if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE)
	{
		return geoRET_FAIL;
	}
	if (nval->varType == vTypeAString||
		nval->varType == vTypeString ||
		nval->varType == vTypeWString ||
		nval->varType == vTypeBlob)
	{
		//todo:remmber
		recColDb_->QueryRec_Equal(nval->vString.Data, rangeCount, (geoVoid**)recnoList);
	}
	else
	{
		recColDb_->QueryRec_Equal(&nval->vBool, rangeCount, (geoVoid**)recnoList);
	}
	return nRet;
}
geoInt32 CRecTableCol::TC_QueryAdapterScope(geoVariant *nvBegin, geoVariant *nvEnd, geoUInt32 rangeCount, POUT geoRecnoList **recnoList)
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE)
	{
		return geoRET_FAIL;
	}
	if (nvBegin->varType != info_.Datatype || nvEnd->varType != info_.Datatype)
	{
		return geoRET_FAIL;
	}
	if (info_.Datatype == vTypeAString ||
		info_.Datatype == vTypeString ||
		info_.Datatype == vTypeWString ||
		info_.Datatype == vTypeBlob)
	{
		RET_ERR(recColDb_->QueryRec_Range(nvBegin->vString.Data, nvEnd->vString.Data, rangeCount, (geoVoid**)recnoList));
	}
	else
	{
		RET_ERR(recColDb_->QueryRec_Range(&nvBegin->vBool, &nvEnd->vBool, rangeCount, (geoVoid**)recnoList));
	}
	return nRet;
}
geoInt32 CRecTableCol::TC_DelAllColumnItem()
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE)
	{
		return geoRET_FAIL;
	}
	RET_ERR(recColDb_->ClearAllRec());
	return nRet;
}
geoInt32 CRecTableCol::TC_SyncCol()
{
	geoAPIStatus nRet = geoRET_SUCC;
	if (IsNull(recColDb_) || recColDb_->bIsOpen_ == geoFALSE)
	{
		return geoRET_FAIL;
	}
	RET_ERR(recColDb_->SyncDB());
	return nRet;
}

geoUInt32 CRecTableCol::TC_GetMaxRecno()
{
    return info_.CurSize;
}
