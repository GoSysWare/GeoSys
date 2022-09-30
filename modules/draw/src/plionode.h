#ifndef PLIONODE_H
#define PLIONODE_H

#include <QString>
#include <QList>

class PLIONode
{
public:
    enum Type {Root, Station, Module};
    PLIONode(Type t, int idSta, int idMod);
    ~PLIONode();

    Type type;
    int idStation;
    int idModule;
    PLIONode *parent;
    QList<PLIONode*> children;
};

#endif // PLIONODE_H
