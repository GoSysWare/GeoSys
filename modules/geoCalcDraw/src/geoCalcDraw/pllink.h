#ifndef PLLINK_H
#define PLLINK_H

#include <QList>
#include "plpoint.h"
#include "plpin.h"

class PLLink
{
public:
    PLLink();
    PLLink(const PLLink &lk);
    void clear();
    void removeDualPoints();

    int idPrg;
    int id;
    int idLog;
    int idFbSrc;
    int pinSrc;
    int idFbTgt;
    int pinTgt;
    bool isSelected;
    bool markSrc;
    bool markTgt;
    int typeSrc;
    int typeTgt;
    QList<PLPoint> pts;
    PLPin *pin;
};

#endif // PLLINK_H
