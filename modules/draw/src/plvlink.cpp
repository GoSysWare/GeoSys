#include "plvlink.h"

PLVLink::PLVLink()
{
    pin = NULL;
    ev = NULL;
    fb = NULL;
    isSelected = false;
}

PLVLink::PLVLink(const PLVLink &vlk)
{
    idPrg = vlk.idPrg;
    id = vlk.id;
    idLog = vlk.idLog;
    idFb = vlk.idFb;
    idPin = vlk.idPin;
    idEv = vlk.idEv;
    isInput = vlk.isInput;
    isSelected = vlk.isSelected;
    mark = vlk.mark;
    pin = vlk.pin;
    ev = vlk.ev;
    fb = vlk.fb;
}