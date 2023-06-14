#ifndef PLPIN_H
#define PLPIN_H

#include <QString>
#include "modules/calc/include/k_evdata.h"

class PLPin
{
public:
    PLPin();
    ~PLPin();

    PLPin(const PLPin &pin);
    QString getStrValue();
    QString getStrPureValue();
    QString name;
    value_tm value;
    v_type   type;
    bool hasVariable;
    bool hasInputLink;
};

#endif // PLPIN_H
