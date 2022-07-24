#include "plfunctionblock.h"

PLFunctionBlock::PLFunctionBlock()
{
    flag = 0;
    isSelected = false;
}

PLFunctionBlock::PLFunctionBlock(const PLFunctionBlock &fb)
{
    idPrg = fb.idPrg;
    id = fb.id;
    libName = fb.libName;
    funName = fb.funName;
    blkName = fb.blkName;
    x = fb.x;
    y = fb.y;
    w = fb.w;
    h = fb.h;

    flag = fb.flag;
    isSelected = fb.isSelected;

    input = fb.input;
    output = fb.output;
    property = fb.property;
}
