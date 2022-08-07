#include "plpin.h"

PLPin::PLPin()
{
    hasVariable = false;
    hasInputLink = false;
}
PLPin::~PLPin()
{

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
    return QString::fromStdString(var2str(value));
}
