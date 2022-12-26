#ifndef PLCOMMAND_H
#define PLCOMMAND_H

#include <QString>
#include "plproject.h"
#include "plmodule.h"
#include "plprogram.h"
#include "plfunctionblock.h"
#include "plevdata.h"
#include "plvlink.h"


#include "modules/calc/proto/edit.pb.h"

class PLCommand
{
public:
    PLCommand();
    ~PLCommand();

    PLCommand(Bus::EditInfo  info);
    bool dispatch();
    void reset();

    
    Bus::EditInfo editInfo;
    bool mark;

    static PLEVData *getEv(int id);
    static PLProgram *getProgram(PLModule * mod,int idPrg);
    static PLFunctionBlock *getFunctionBlock(PLProgram *prg, int idFB);
    static PLLink *getLink(PLProgram *prg, int idLk);
    static PLVLink *getVi(PLProgram *prg, int idVi);
    static PLVLink *getVo(PLProgram *prg, int idVo);

    static PLModule *getModule(int idMod);

    void setModule(PLModule *mod);
    static bool removeModule(int modId);
    
    void setProgram(PLProgram *prg);
    static bool removeProgram(int modId,int prgId);

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
