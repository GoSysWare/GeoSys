#ifndef PLVLINK_H
#define PLVLINK_H

#include "plpin.h"
#include "plevdata.h"
#include "plfunctionblock.h"

class PLVLink
{
public:
    PLVLink();
    PLVLink(const PLVLink &vlk);

    int idPrg;
    int id;
    int idLog;
    int idFb;
    int idPin;
    int idEv;
    bool isInput;
    bool isSelected;
    bool mark;
    PLPin *pin;
    PLEVData *ev;
    PLFunctionBlock *fb;
};

#endif // PLVLINK_H
