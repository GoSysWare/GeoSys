#include "plevdata.h"

PLEVData::PLEVData()
{

}

PLEVData::PLEVData(const PLEVData &ev)
{
    id = ev.id;
    idLog = ev.idLog;
    name = ev.name;
    comment = ev.comment;
    refIn = ev.refIn;
    refOut = ev.refOut;
    initValue = ev.initValue;
    value = ev.value;
    isSelected = ev.isSelected;
}
PLEVData::~PLEVData()
{

}

QString PLEVData::getStrValue()
{
    return QString::fromStdString(var2str(value));
}
