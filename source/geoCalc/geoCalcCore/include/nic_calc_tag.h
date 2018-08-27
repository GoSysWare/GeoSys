#ifndef NIC_CALC_TAG_H
#define NIC_CALC_TAG_H

#include "nicDefs.h"
#include "nic_calc_IDmap.h"
#include "nicTagNameMap.h"
//标签名，描述，标签类型，数据类型，ID号，工程计算属性
typedef enum
{
    CALC_Prop_Min =0,
    CALC_Prop_Name =CALC_Prop_Min,
    CALC_Prop_Description,
    CALC_Prop_TagType,
    CALC_Prop_DataType,
    CALC_Prop_Id,
    CALC_Prop_BengCal,
    CALC_Prop_Max,
}nicCALCPropEnum;

typedef struct
{
    //名称属性
    nicChar		Name[TAG_NAME_SIZE];		// 点名
    nicChar     Description[TAG_DESC_SIZE];	// 点名
    nicUInt8  TagType;					// 点类型
    nicUInt8  DataType;					//数据类型
    nicUInt32	Id;						// 结点ID号
    nicUInt8  BengCal;
    nicTagStatusFlag Flag;				// 状态标志
}nicCALCTagCom;

class CALCTag
{
public:
    CALCTag(nicUInt32 size);
    ~CALCTag();

public:
    nicInt32 AddTag_CALCTag(
            nicIN nicPropValueList* pPropValueList,
            nicOUT nicUInt32 externID);

    nicInt32 DelTag_CALCTag(nicUInt32 externID);

    nicInt32 ModifyTag_CALCTag(
            nicIN nicUInt32 externID,
            nicIN nicPropValueList* pPropValueList);


    nicInt32 GetTagNameByExID(nicIN nicUInt32 externID, nicOUT nicStr& pName);
    nicInt32 GetExIDByTagName(nicIN nicStr pName, nicOUT nicUInt32 *externID);
    nicUInt32 GetCount();
    nicBool IsTagExist(nicUInt32 externID);

private:
    nicInt32 SetPropList_CALCTag(
            nicIN nicUInt32 localID,
            nicIN nicPropIdList* pPropIdList,
            nicIN nicPropValueList* pValueList);
    nicInt32 GetPropList_CALCTag(
            nicIN nicUInt32 localID,
            nicIN nicPropIdList* pPropIdList,
            nicOUT nicPropValueList* pValueList);
    nicInt32 GetPropList_CALCTag(nicUInt32 localID,
            nicCALCTagCom* & pTagPropList);

    nicInt32 GetCALCProp(nicUInt32 localID, nicUInt32 PropId,
            nicVariant* pValue);
    nicInt32 SetCALCProp(nicUInt32 localID, nicUInt32 PropId,
            nicVariant* pValue);

    nicBool IsCALCProp(nicUInt32 nPropId);

    void InitCALCPropFunc();
//    nicBool IsTagExistLocalID(nicUInt32 localID);

    typedef nicInt32 (CALCTag::*nicGetPropFunction)(nicUInt32, nicVariant*);


    typedef nicInt32 (CALCTag::*nicSetPropFunction)(nicUInt32, nicVariant*);

    typedef struct
    {
        nicGetPropFunction GetFunction;
        nicSetPropFunction SetFunction;
        nicUInt8 DataType;
    } nicPropProcess;
    nicPropProcess PropProcess_[CALC_Prop_Max];

    nicInt32 GetCALC_TagType(nicUInt32 localID, nicVariant* pValue);
    nicInt32 SetCALC_TagType(nicUInt32 localID, nicVariant* pValue);

    nicInt32 GetCALC_Name(nicUInt32 localID, nicVariant *pValue);
    nicInt32 SetCALC_Name(nicUInt32 localID, nicVariant *pValue);

    nicInt32 GetCALC_Id(nicUInt32 localID, nicVariant* pValue);
    nicInt32 SetCALC_Id(nicUInt32 localID, nicVariant* pValue);

    nicInt32 GetCALC_DataType(nicUInt32 localID, nicVariant* pValue);
    nicInt32 SetCALC_DataType(nicUInt32 localID, nicVariant* pValue);

    nicInt32 GetCALC_Description(nicUInt32 localID, nicVariant* pValue);
    nicInt32 SetCALC_Description(nicUInt32 localID, nicVariant* pValue);

    nicInt32 GetCALC_BengCal(nicUInt32 localID, nicVariant* pValue);
    nicInt32 SetCALC_BengCal(nicUInt32 localID, nicVariant* pValue);

private:
    nicCALCTagCom* pData_;
    CNameMap *name_idMap;
    CdbidMap *dbidMap;
    nicUInt32 curID;
    nicUInt32 max_size;
};



#endif // NIC_CALC_TAG_H
