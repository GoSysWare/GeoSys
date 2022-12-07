#ifndef PLMODULE_H
#define PLMODULE_H

#include <QList>
#include "plprogram.h"

class PLModule
{
public:
    PLModule();
    void clear();
    void renewUuid();
    QString description();
    QString getUuid();
    int id;
    int idLog;
    QString name;
    QString desc;
    QString uuid;
    QList<PLProgram> prgList;
};

#endif // PLPROGRAM_H
