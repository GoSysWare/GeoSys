#ifndef PLSELOBJECT_H
#define PLSELOBJECT_H

#include "pllink.h"
#include "plfunctionblock.h"
#include "plvlink.h"

const int PT_NONE=0;
const int PT_INPUT=1;
const int PT_OUTPUT=2;
const int PT_FB=3;
const int PT_LKH=4;
const int PT_LKV=5;
const int PT_VI=6;
const int PT_VO=7;

class PLSelObject
{
public:
    PLSelObject();
    void reset();

    int type;
    int value;
    PLFunctionBlock *fb;
    PLLink *lk;
    PLVLink *vlk;
};

#endif // PLSELOBJECT_H
