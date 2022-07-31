#include "plpin.h"

PLPin::PLPin()
{
    hasVariable = false;
    hasInputLink = false;
}

PLPin::PLPin(const PLPin &pin)
{
    name = pin.name;
    value = pin.value;
    hasVariable = false;
    hasInputLink = false;
}

QString PLPin::getStrValue()
{
    QString ret;
    char temp[128];

    var2str(temp, value, value.t);
    ret.sprintf("%s", temp);

    return ret;
}
