#ifndef PLPROGRAM_H
#define PLPROGRAM_H

#include <QList>
#include "plfunctionblock.h"
#include "pllink.h"

class PLProgram
{
public:
    PLProgram();

    int id;
    int idLog;
    QString name;
    QList<PLFunctionBlock> fbs;
    QList<PLLink> lks;
};

#endif // PLPROGRAM_H
