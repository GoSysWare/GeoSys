#include "plevdata.h"

PLEVData::PLEVData()
{
   initValue.mutable_v()->set_t(v_type::T_NONE);
   value.mutable_v()->set_t(v_type::T_NONE);

}

PLEVData::PLEVData(const PLEVData &ev)
{
    id = ev.id;
    idLog = ev.idLog;
    name = ev.name;
    desc = ev.desc;
    refIn = ev.refIn;
    refOut = ev.refOut;
    initValue = ev.initValue;
    value = ev.value;
    isSelected = ev.isSelected;
    type  = ev.type;

}
PLEVData::~PLEVData()
{

}

QString PLEVData::getStrValue()
{
    return QString::fromStdString(value.v().ShortDebugString());
}
