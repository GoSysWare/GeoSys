#include <QStringList>
#include "plprogram.h"

PLProgram::PLProgram()
{
}
PLProgram::PLProgram(const PLProgram& other)
{
     idMod = other.idMod;
     id = other.id;
     idLog= other.idLog;
     nameMod= other.nameMod;
     name= other.name;
     desc= other.desc;
     type= other.type;
     interval= other.interval;
     fbs= other.fbs;
     lks= other.lks;
     vis= other.vis;
     vos= other.vos;
}

PLProgram::~PLProgram()
{
}
