#ifndef PLMODULE_H
#define PLMODULE_H

#include <QList>
#include "plprogram.h"

class PLModule
{
public:
    PLModule();

    int id;
    int idLog;
    QString name;
    QList<PLProgram> prgs;
};

#endif // PLPROGRAM_H
