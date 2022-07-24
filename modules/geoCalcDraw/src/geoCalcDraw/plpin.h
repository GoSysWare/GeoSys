#ifndef PLPIN_H
#define PLPIN_H

#include <QString>
#include "k_evdata.h"

class PLPin
{
public:
    PLPin();
    PLPin(const PLPin &pin);
    QString getStrValue();

    QString name;
    val_t value;
    bool hasVariable;
    bool hasInputLink;
};

#endif // PLPIN_H
