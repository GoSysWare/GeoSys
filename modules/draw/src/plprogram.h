#ifndef PLPROGRAM_H
#define PLPROGRAM_H

#include <QList>
#include "plfunctionblock.h"
#include "pllink.h"
#include "plvlink.h"

class PLProgram
{
public:
    PLProgram();
    int idMod;
    int id;
    int idLog;
    QString name;
    QString desc;
    int type;
    QList<PLFunctionBlock> fbs;
    QList<PLLink> lks;
    QList<PLVLink> vis;
    QList<PLVLink> vos;
};

#endif // PLPROGRAM_H
