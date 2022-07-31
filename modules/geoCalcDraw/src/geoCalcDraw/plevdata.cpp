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

QString PLEVData::getStrValue()
{
    QString ret;
    char temp[128];

    var2str(temp, value, value.t);
    ret.sprintf("%s", temp);

    return ret;
}
