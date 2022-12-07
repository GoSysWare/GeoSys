#include <QStringList>
#include <QUuid>

#include "plmodule.h"


PLModule::PLModule()
{
    clear();
}

void PLModule::clear()
{    
    uuid = QUuid::createUuid().toString();
}

void PLModule::renewUuid()
{
    uuid = QUuid::createUuid().toString();
}

QString PLModule::description()
{
    return desc;
}

QString PLModule::getUuid()
{
    return uuid;
}
