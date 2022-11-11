#ifndef PLMAINMODEL_H
#define PLMAINMODEL_H

#include <QDebug>
#include <QList>
#include <QStringList>
#include <QStringListModel>
#include "plcommand.h"
#include "plprogram.h"
#include "plmodule.h"
#include "plevdata.h"
#include "plcommand.h"
#include "plproject.h"
#include "evdatamodel.h"


class PLMainModel
{
public:
    PLMainModel();
    void clear();
    void updateFuncList(int libIndex);
    void updateProgList();
    QStringListModel modelLibrary;
    QStringListModel modelFunction;
    QStringListModel modelModule;
    QStringListModel modelProgram;

    EVDataModel modelEVData;

    PLProject project;

    unsigned int cmdID;
    QList<PLCommand> cmdList;

    int objID;
    QList<PLModule> modList;
    QList<PLEVData> evList;

    bool exeCommand(PLCommand &cmd);
    PLProgram *prgCurrent;

    bool isModified;

    void makeLkNewCmd(PLCommand &cmd, PLLink &lk, bool newId = true);
    void makeLkMoveCmd(PLCommand &cmd, PLLink &lk);
    void makeLkRemoveCmd(PLCommand &cmd, PLLink &lk);
    void makeFbNewCmd(PLCommand &cmd, PLFunctionBlock &fb, bool newId = true, bool newName = true);
    void makeFbMoveCmd(PLCommand &cmd, PLFunctionBlock &fb);
    void makeFbRemoveCmd(PLCommand &cmd, PLFunctionBlock &fb);
    void makeViNewCmd(PLCommand &cmd, PLVLink &vlk, bool newId = true);
    void makeViRemoveCmd(PLCommand &cmd, PLVLink &vlk);
    void makeVoNewCmd(PLCommand &cmd, PLVLink &vlk, bool newId = true);
    void makeVoRemoveCmd(PLCommand &cmd, PLVLink &vlk);
    void makeEvNewCmd(PLCommand &cmd, PLEVData &ev, bool newId = true);
    void makeEvSetCmd(PLCommand &cmd, PLEVData &ev);
    void makeEvRemoveCmd(PLCommand &cmd, PLEVData &ev);
    void makePrgNewCmd(PLCommand &cmd, PLProgram &prg, bool newId = true);
    void makePrgRemoveCmd(PLCommand &cmd, PLProgram &prg);
    void makePrgRenameCmd(PLCommand &cmd, PLProgram &prg);
    void makePinSetCmd(PLCommand &cmd, int idPrg, int idFb, int idPin, QString val);
    void makeLkCopyCmd(PLCommand &cmd, PLLink &lk);
    void makeFbCopyCmd(PLCommand &cmd, PLFunctionBlock &fb);

    static void removeDualCommands(QList<PLCommand> &list, bool all);
    static bool isCmdObjRemoved(PLCommand *cmd);
    static void extractObjsId(int &idObj, QList<PLEVData> &evs);
    static bool extractObjsId(int &idObj, QList<PLFunctionBlock> &fbs, QList<PLLink> &lks);
    static bool extractObjsId(int &idObj, QList<PLProgram> &prgs, QList<PLEVData> &evs, QList<PLCommand> &setpins);

    void extract();

private:
    void initLibrary();
};

#endif // PLMAINMODEL_H
