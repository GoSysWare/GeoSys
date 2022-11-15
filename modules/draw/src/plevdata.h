#ifndef PLEVDATA_H
#define PLEVDATA_H

#include <QString>
#include "modules/calc/include/k_evdata.h"

class PLEVData
{
public:
    PLEVData();
    PLEVData(const PLEVData &ev);
    ~PLEVData();

    QString getStrValue();

    int id;
    int idLog;
    QString name;
    QString desc;
    int refIn;
    int refOut;
    int type;
    value_tm initValue;
    value_tm value;
    bool isSelected;
};

#endif // PLEVDATA_H
