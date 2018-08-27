#ifndef PLPROJECT_H
#define PLPROJECT_H
#include <QString>

class PLProject
{
public:
    PLProject();
    void clear();
    void renewUuid();
    QString description();
    QString getProjCmdLine();

    QString name;
    QString uuid;
    QString fileName;
};

#endif // PLPROJECT_H
