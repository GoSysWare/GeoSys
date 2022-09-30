#ifndef PLCOMMAND_H
#define PLCOMMAND_H

#include <QString>
#include "plprogram.h"
#include "plfunctionblock.h"

class PLCommand
{
public:
    PLCommand();
    PLCommand(QString line);
    bool dispatch();
    void makeCmdLine();

    QString cmdLine;
    int id;
    QString fun;
    QString para;
    QString res;
    bool mark;

    static PLEVData *getEv(int id);
    static PLProgram *getProgram(int id);
    static PLFunctionBlock *getFunctionBlock(PLProgram *prg, int id);
    static PLLink *getLink(PLProgram *prg, int id);
    static PLVLink *getVi(PLProgram *prg, int id);
    static PLVLink *getVo(PLProgram *prg, int id);

    void setProgram(PLProgram *prg);
    static bool removeProgram(int id);

    void setFunctionBlock(PLFunctionBlock *fb);
    static bool removeFunctionBlock(PLProgram *prg, int id);

    void setLink(PLLink *lk, bool onlyRes);
    static bool removeLink(PLProgram *prg, int id);
    static bool addLink(PLProgram *prg, PLLink *lk);

    void setEVData(PLEVData *ev);
    static bool removeEVData(int id);

    void setVLink(PLVLink *vlk);
    static bool addVLinkInput(PLProgram *prg, PLVLink *vlk);
    static bool removeVLinkInput(PLProgram *prg, int id);
    static bool addVLinkOutput(PLProgram *prg, PLVLink *vlk);
    static bool removeVLinkOutput(PLProgram *prg, int id);
};

#endif // PLCOMMAND_H
