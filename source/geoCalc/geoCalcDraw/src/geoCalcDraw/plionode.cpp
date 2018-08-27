#include "plionode.h"

PLIONode::PLIONode(Type t, int idSta, int idMod)
{
    type = t;
    idStation = idSta;
    idModule = idMod;
    parent = 0;
}

PLIONode::~PLIONode()
{
    qDeleteAll(children);
}
