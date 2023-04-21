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
    QString getUuid();

    QString name;
    QString uuid;
    unsigned int cmdId;
    QString desc;
    QString fileName;
};

#endif // PLPROJECT_H
