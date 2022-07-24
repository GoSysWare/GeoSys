#ifndef NIC_CALC_UTIL_H
#define NIC_CALC_UTIL_H
#include "nicDefs.h"
#include "k_evdata.h"

nicInt32 nicVariantToVal_t(nicVariant* nicVar, val_t* calcVar)
{
    if(nicVar==nicNULL || calcVar==nicNULL)
    {
        return nicRET_Fail;
    }

    if (nicVar->DataType >nicDataType_Max || nicVar->DataType < nicDataType_Empty)
    {
        return nicRET_Fail;
    }

    switch(nicVar->DataType)
    {
    case nicDataType_Empty:
        return nicRET_Fail;
    case nicDataType_Bool:
        calcVar->t = T_BOOL;
        calcVar->v.b = nicVar->Bool;
        break;
    case nicDataType_Int8:
    case nicDataType_Int16:
    case nicDataType_Int32:
        calcVar->t = T_INT;
        calcVar->v.i = nicVar->Int32;
        break;
    case nicDataType_Float:
        calcVar->t = T_REAL;
        calcVar->v.f = nicVar->Float;
        break;
    case nicDataType_Double:
        calcVar->t = T_LREAL;
        calcVar->v.fl = nicVar->Double;
        break;
    default:
        return nicRET_Fail;
    }
    return nicRET_OK;

//    if(nicVar->DataType == nicDataType_Bool)
//    {
//        calcVar->t = T_BOOL;
//        calcVar->v.b = nicVar->Bool;
//        return nicRET_OK;
//    }else if(nicVar->DataType == nicDataType_Int8 ||
//             nicVar->DataType == nicDataType_Int16 ||
//             nicVar->DataType == nicDataType_Int32)
//    {
//        calcVar->t = T_INT;
//        calcVar->v.i = nicVar->Int32;
//        return nicRET_OK;
//    }else if(nicVar->DataType == nicDataType_Float)
//    {
//        calcVar->t = T_REAL;
//        calcVar->v.f = nicVar->Float;
//        return nicRET_OK;
//    }else if(nicVar->DataType == nicDataType_Double)
//    {
//        calcVar->t = T_REAL;
//        calcVar->v.fl = nicVar->Double;
//        return nicRET_OK;
//    }else
//    {
//        return nicRET_Fail;
//    }
//    return nicRET_Fail;
}

nicInt32 Val_tTonicVariant(val_t* calcVar, nicVariant* nicVar)
{
    if(nicVar==nicNULL || calcVar==nicNULL)
    {
        return nicRET_Fail;
    }

    switch(calcVar->t){
    case T_NONE:
        return nicRET_Fail;
    case T_BOOL:
        nicVar->DataType = nicDataType_Bool;
        nicVar->Bool = calcVar->v.b;
        break;
    case T_INT:
        nicVar->DataType = nicDataType_Int32;//小心此处改变了目标数据类型
        nicVar->Int32 = calcVar->v.i;
        break;
    case T_REAL:
        nicVar->DataType = nicDataType_Float;
        nicVar->Float = calcVar->v.f;
        break;
    case T_LREAL:
        nicVar->DataType = nicDataType_Double;
        nicVar->Double = calcVar->v.fl;
        break;
    default:
        return nicRET_Fail;
    }
    return nicRET_OK;
}


#endif // NIC_CALC_UTIL_H
