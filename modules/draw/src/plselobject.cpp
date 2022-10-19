#include "plselobject.h"

PLSelObject::PLSelObject()
{
    reset();
}

void PLSelObject::reset()
{
    type = PT_NONE;
    value = 0;
    fb = NULL;
    lk = NULL;
}
