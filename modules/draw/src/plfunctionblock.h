#ifndef PLFUNCTIONBLOCK_H
#define PLFUNCTIONBLOCK_H

#include <QList>
#include "plpin.h"

class PLFunctionBlock
{
public:
    PLFunctionBlock();
    PLFunctionBlock(const PLFunctionBlock &fb);
    int idMod;
    int idPrg;
    int id;
    int idLog;
    int flag;
    unsigned long long cycle_time;
    unsigned long long begin_time;
    unsigned long long expend_time;
    QString libName;
    QString funName;
    QString blkName;
    QList<PLPin> input;
    QList<PLPin> output;
    QList<PLPin> property;
    int x;
    int y;
    int w;
    int h;
    bool isSelected;
};

#endif // PLFUNCTIONBLOCK_H
