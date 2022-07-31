#include <QFile>
#include <QTextStream>
#include "plmainmodel.h"
#include "k_functionblock.h"
#include "k_lib.h"
#include "k_command.h"
#include "k_project.h"

PLMainModel::PLMainModel()
{
    cmdID = 0;
    objID = 0;
    prgCurrent = NULL;

    initLibrary();
    updateFuncList(0);

    prj_init(0);

    isModified = false;
}

void PLMainModel::initLibrary()
{
    lib_init();
    lib_t *lib = lib_first();

    QStringList list;
    while(lib != NULL){
        list << lib->libname;
        lib = lib_next();
    }
    modelLibrary.setStringList(list);
}

void PLMainModel::updateFuncList(int libIndex)
{
    lib_t *lib = lib_first();
    for(int i=0; i<libIndex; i++){
        lib = lib_next();
    }

    QStringList list;
    void *fb = lib->first();
    while(fb != ((void*) 0)){
        list << ((fb_t*)fb)->h.fcname;
        fb = lib->next();
    }
    modelFunction.setStringList(list);
}

void PLMainModel::clear()
{
    cmdID = 0;
    objID = 0;
    prgCurrent = NULL;
    prgList.clear();
    cmdList.clear();
    modelEVData.beginReset();
    evList.clear();
    modelEVData.endReset();
    prj_reset();
    project.clear();

    prj_reset();
}

void PLMainModel::updateProgList()
{
    QStringList list;

    for(int i=0; i<prgList.size(); i++){
        PLProgram prg = prgList.at(i);
        list << prg.name;
    }

    modelProgram.setStringList(list);
}


bool PLMainModel::exeCommand(PLCommand &cmd)
{
    if(cmdID < cmd.id){
        cmdID = cmd.id;
        //qDebug() << "command id:" << cmdID;
    }

    char cline[1024];
    strncpy(cline, cmd.cmdLine.toStdString().c_str(), sizeof(cline)-1);
    //qDebug() << cmd.cmdLine;
    cmd_dispatch(cline);

    if(!cmd.dispatch()){
        return false;
    }

    if(cmd.fun != "setprj"){
        cmdList.append(cmd);
    }

    return true;
}

void PLMainModel::makeLkNewCmd(PLCommand &cmd, PLLink &lk, bool newId)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "addlk";
    if(newId){
        objID++;
        lk.id = objID;
    }
    cmd.para.sprintf("%d,%d,%d,%d,%d,%d", lk.idPrg, lk.id, lk.idFbSrc, lk.pinSrc, lk.idFbTgt, lk.pinTgt);
    lk.removeDualPoints();
    cmd.res.clear();
    QString sp;
    for(int i=0; i<lk.pts.size(); i++){
        sp.sprintf("%d/%d,", lk.pts.at(i).x, lk.pts.at(i).y);
        cmd.res += sp;
    }
    cmd.makeCmdLine();
}

void PLMainModel::makeLkRemoveCmd(PLCommand &cmd, PLLink &lk)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "rmlk";
    cmd.para.sprintf("%d,%d", lk.idPrg, lk.id);
    cmd.makeCmdLine();
}

void PLMainModel::makeLkMoveCmd(PLCommand &cmd, PLLink &lk)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "mvlk";
    cmd.para.sprintf("%d,%d", lk.idPrg, lk.id);
    lk.removeDualPoints();
    cmd.res = "";
    QString sp;
    for(int i=0; i<lk.pts.size(); i++){
        sp.sprintf("%d/%d,", lk.pts.at(i).x, lk.pts.at(i).y);
        cmd.res += sp;
    }
    cmd.makeCmdLine();
}

void PLMainModel::makeFbNewCmd(PLCommand &cmd, PLFunctionBlock &fb, bool newId,  bool newName)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "addfb";
    if(newId){
        objID++;
        fb.id = objID;
    }
    cmd.para.sprintf("%d,%d,", fb.idPrg, fb.id);
    cmd.para += fb.libName;
    cmd.para += ",";
    cmd.para += fb.funName;
    if(newName){
        fb.blkName.sprintf("fb%d", fb.id);
    }
    QString r;
    r.sprintf("%d,%d", fb.x, fb.y);
    cmd.res = fb.blkName;
    cmd.res += ",";
    cmd.res += r;
    cmd.makeCmdLine();
}

void PLMainModel::makeFbRemoveCmd(PLCommand &cmd, PLFunctionBlock &fb)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "rmfb";
    cmd.para.sprintf("%d,%d", fb.idPrg, fb.id);
    cmd.makeCmdLine();
}

void PLMainModel::makeFbMoveCmd(PLCommand &cmd, PLFunctionBlock &fb)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "mvfb";
    cmd.para.sprintf("%d,%d", fb.idPrg, fb.id);
    QString sxy;
    sxy.sprintf(",%d,%d", fb.x, fb.y);
    cmd.res = fb.blkName;
    cmd.res += sxy;
    cmd.makeCmdLine();
}

void PLMainModel::makeViNewCmd(PLCommand &cmd, PLVLink &vlk,  bool newId)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "addvi";
    if(newId){
        objID++;
        vlk.id = objID;
    }
    cmd.para.sprintf("%d,%d,%d,%d,%d",vlk.idPrg, vlk.id, vlk.idEv, vlk.idFb, vlk.idPin);
    cmd.makeCmdLine();
}

void PLMainModel::makeViRemoveCmd(PLCommand &cmd, PLVLink &vlk)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "rmvi";
    cmd.para.sprintf("%d,%d", vlk.idPrg, vlk.id);
    cmd.makeCmdLine();
}

void PLMainModel::makeVoNewCmd(PLCommand &cmd, PLVLink &vlk, bool newId)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "addvo";
    if(newId){
        objID++;
        vlk.id = objID;
    }
    cmd.para.sprintf("%d,%d,%d,%d,%d",vlk.idPrg, vlk.id, vlk.idEv, vlk.idFb, vlk.idPin);
    cmd.makeCmdLine();
}

void PLMainModel::makeVoRemoveCmd(PLCommand &cmd, PLVLink &vlk)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "rmvo";
    cmd.para.sprintf("%d,%d", vlk.idPrg, vlk.id);
    cmd.makeCmdLine();
}

void PLMainModel::makeEvNewCmd(PLCommand &cmd, PLEVData &ev, bool newId)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "addev";
    if(newId){
        objID++;
        ev.id = objID;
    }

    char type[128], value[128];
    type2str(type, ev.initValue.t);
    var2str(value, ev.initValue, ev.initValue.t);
    cmd.para.sprintf("%d,%s,%s", ev.id, type, value);
    cmd.res = ev.name;
    cmd.res += ",";
    cmd.res += ev.comment;
    cmd.makeCmdLine();
}

void PLMainModel::makeEvSetCmd(PLCommand &cmd, PLEVData &ev)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "setev";
    char value[128];
    var2str(value, ev.initValue, ev.initValue.t);
    cmd.para.sprintf("%d,%s", ev.id, value);
    cmd.res = ev.name;
    cmd.res += ",";
    cmd.res += ev.comment;
    cmd.makeCmdLine();

    QString v = value;
}

void PLMainModel::makeEvRemoveCmd(PLCommand &cmd, PLEVData &ev)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "rmev";
    cmd.para.sprintf("%d", ev.id);
    cmd.makeCmdLine();
}

void PLMainModel::makePrgNewCmd(PLCommand &cmd, PLProgram &prg, bool newId)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "addprg";
    if(newId){
        objID++;
        prg.id = objID;
    }
    cmd.para.sprintf("%d", prg.id);
    cmd.res = prg.name;
    cmd.makeCmdLine();
}

void PLMainModel::makePrgRemoveCmd(PLCommand &cmd, PLProgram &prg)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "rmprg";
    cmd.para.sprintf("%d", prg.id);
    cmd.makeCmdLine();
}

void PLMainModel::makePrgRenameCmd(PLCommand &cmd, PLProgram &prg)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "setprg";
    cmd.para.sprintf("%d", prg.id);
    cmd.res = prg.name;
    cmd.makeCmdLine();
}

void PLMainModel::makePinSetCmd(PLCommand &cmd, int idPrg, int idFb, int idPin, QString val)
{
    cmdID++;
    cmd.id = cmdID;
    cmd.fun = "setpin";
    cmd.para.sprintf("%d,%d,%d,", idPrg, idFb, idPin);
    cmd.para += val;
    cmd.makeCmdLine();
}

void PLMainModel::makeLkCopyCmd(PLCommand &cmd, PLLink &lk)
{
    cmd.id = -1;
    cmd.fun = "cplk";
    cmd.para.sprintf("%d,%d,%d,%d,%d,%d", lk.idPrg, lk.id, lk.idFbSrc, lk.pinSrc, lk.idFbTgt, lk.pinTgt);
    cmd.res.clear();
    QString sp;
    for(int i=0; i<lk.pts.size(); i++){
        sp.sprintf("%d/%d,", lk.pts.at(i).x, lk.pts.at(i).y);
        cmd.res += sp;
    }
    cmd.makeCmdLine();
}

void PLMainModel::makeFbCopyCmd(PLCommand &cmd, PLFunctionBlock &fb)
{
    cmd.id = -1;
    cmd.fun = "cpfb";
    cmd.para.sprintf("%d,%d,", fb.idPrg, fb.id);
    cmd.para += fb.libName;
    cmd.para += ",";
    cmd.para += fb.funName;
    cmd.res.sprintf("%d,%d", fb.x, fb.y);
    cmd.makeCmdLine();
}

static int paraCompare(QString &p1, QString &p2){
    int l;
    l = p1.size();
    if(l > p2.size()){
        l = p2.size();
    }

    int r = 0;
    QChar c1, c2;
    for(int i=0; i<l-1; i++){
        c1 = p1.at(i);
        c2 = p2.at(i);
        if(c1 != c2){
            return r;
        }
        if(c1 == ',' || c1 == ';'){
            r++;
        }
    }

    return r;
}

static bool isSamePinSet(QString &p1, QString &p2)
{
    if(paraCompare(p1, p2) >= 3){
        //qDebug() << "same:" << p1 << " - " << p2;
        return true;
    }else{
        //qDebug() << "diff:" << p1 << " - " << p2;
        return false;
    }
}

static bool isSameEvSet(QString p1, QString p2)
{
    if(p1 == p2){
    //if(paraCompare(p1, p2) >= 1){
        return true;
    }else{
        return false;
    }
}

static bool isSamePrgSet(QString p1, QString p2)
{
    if(p1 == p2){
    //if(paraCompare(p1, p2) >= 1){
        return true;
    }else{
        return false;
    }
}

bool PLMainModel::isCmdObjRemoved(PLCommand *cmd)
{
    int idPrg, idFb, idLk, idVi, idVo, idEv;
    PLProgram *prg;

    if(cmd->fun == "addprg"){
        idPrg = cmd->para.split(",")[0].toInt();
        if(NULL == PLCommand::getProgram(idPrg)){
            return true;
        }
    }else if(cmd->fun == "rmprg"){
        idPrg = cmd->para.toInt();
        if(NULL == PLCommand::getProgram(idPrg)){
            return true;
        }
    }else if(cmd->fun == "addev" || cmd->fun == "setev"){
        idEv = cmd->para.split(",")[0].toInt();
        if(NULL == PLCommand::getEv(idEv)){
            return true;
        }
    }else if(cmd->fun == "rmev"){
        idEv = cmd->para.toInt();
        if(NULL == PLCommand::getEv(idEv)){
            return true;
        }
    }else if(cmd->fun == "addfb" || cmd->fun == "rmfb" || cmd->fun == "mvfb" || cmd->fun == "setpin"){
        idPrg = cmd->para.split(",")[0].toInt();
        prg = PLCommand::getProgram(idPrg);
        if(NULL == prg){
            return true;
        }
        idFb = cmd->para.split(",")[1].toInt();
        if(NULL == PLCommand::getFunctionBlock(prg, idFb)){
            return true;
        }
    }else if(cmd->fun == "addlk" || cmd->fun == "rmlk" || cmd->fun == "mvlk"){
        idPrg = cmd->para.split(",")[0].toInt();
        prg = PLCommand::getProgram(idPrg);
        if(NULL == prg){
            return true;
        }
        idLk = cmd->para.split(",")[1].toInt();
        if(NULL == PLCommand::getLink(prg,  idLk)){
            return true;
        }
    }else if(cmd->fun == "addvi" || cmd->fun == "rmvi"){
        idPrg = cmd->para.split(",")[0].toInt();
        prg = PLCommand::getProgram(idPrg);
        if(NULL == prg){
            return true;
        }
        idVi = cmd->para.split(",")[1].toInt();
        if(NULL == PLCommand::getVi(prg, idVi)){
            return true;
        }
    }else if(cmd->fun == "addvo" || cmd->fun == "rmvo"){
        idPrg = cmd->para.split(",")[0].toInt();
        prg = PLCommand::getProgram(idPrg);
        if(NULL == prg){
            return true;
        }
        idVo = cmd->para.split(",")[1].toInt();
        if(NULL == PLCommand::getVo(prg, idVo)){
            return true;
        }
    }else if(cmd->fun == "setpin"){
        idPrg = cmd->para.split(",")[0].toInt();
        prg = PLCommand::getProgram(idPrg);
        if(NULL == prg){
            return true;
        }
    }

    return false;
}

void PLMainModel::removeDualCommands(QList<PLCommand> &list, bool all)
{
    QList<PLCommand*> moveFb;
    QList<PLCommand*> moveLk;
    QList<PLCommand*> setPin;
    QList<PLCommand*> setEv;
    QList<PLCommand*> setPrg;

    int i, j;
    PLCommand *cmd;
    for(i=list.size()-1; i>=0; i--){
        cmd = &list[i];
        cmd->mark = false;
        if(all){
            if(isCmdObjRemoved(cmd)){
                cmd->mark=true;
            }
        }
        if(cmd->fun == "mvfb"){
            for(j=0; j<moveFb.size(); j++){
                if(cmd->para == moveFb.at(j)->para){
                    cmd->mark = true;
                    break;
                }
            }
            if(!cmd->mark){
                moveFb.append(cmd);
            }
        }else if(cmd->fun == "mvlk"){
            for(j=0; j<moveLk.size(); j++){
                if(cmd->para == moveLk.at(j)->para){
                    cmd->mark = true;
                    break;
                }
            }
            if(!cmd->mark){
                moveLk.append(cmd);
            }

        }else if(cmd->fun == "setpin"){
            for(j=0; j<setPin.size(); j++){
                if(isSamePinSet(cmd->para, setPin[j]->para)){
                    cmd->mark = true;
                    break;
                }
            }
            if(!cmd->mark){
                setPin.append(cmd);
            }
        }else if(cmd->fun == "setev"){
            for(j=0; j<setEv.size(); j++){
                if(isSameEvSet(cmd->para, setEv[j]->para)){
                    cmd->mark = true;
                    break;
                }
            }
            if(!cmd->mark){
                setEv.append(cmd);
            }
        }else if(cmd->fun == "setprg"){
            for(j=0; j<setPrg.size(); j++){
                if(isSamePrgSet(cmd->para, setPrg[j]->para)){
                    cmd->mark = true;
                    break;
                }
            }
            if(!cmd->mark){
                setPrg.append(cmd);
            }
        }
    }

    for(i=list.size()-1; i>=0; i--){
        if(list.at(i).mark){
            qDebug()<<"remove:"<<list.at(i).cmdLine;
            list.removeAt(i);
        }
    }
}

void PLMainModel::extractObjsId(int &idObj, QList<PLEVData> &evs)
{
    for(int i=0; i<evs.size(); i++){
        evs[i].id = idObj;
        idObj++;
    }
}

bool PLMainModel::extractObjsId(int &idObj, QList<PLFunctionBlock> &fbs, QList<PLLink> &lks)
{
    int i, j;
    for(i=0; i<fbs.size(); i++){
        fbs[i].idLog = idObj;
        idObj++;
    }
    int step;
    PLLink *lk;
    PLFunctionBlock *fb;
    for(i=0; i<lks.size(); i++){
        lk = &lks[i];
        lk->id = idObj;
        idObj++;
        step = 0;
        for(j=0; j<fbs.size(); j++){
            fb = &fbs[j];
            if(lk->idFbSrc == fb->id){
                lk->idFbSrc = fb->idLog;
                step++;
                if(step == 2){
                    break;
                }
            }
            if(lk->idFbTgt == fb->id){
                lk->idFbTgt = fb->idLog;
                step++;
                if(step == 2){
                    break;
                }
            }
        }
        if(step < 2){
            return false;
        }
    }
    for(int i=0; i<fbs.size(); i++){
        fbs[i].id = fbs[i].idLog;
    }

    return true;
}

bool PLMainModel::extractObjsId(int &idObj, QList<PLProgram> &prgs, QList<PLEVData> &evs, QList<PLCommand> &setpins)
{
    PLProgram *prg;
    PLFunctionBlock *fb;
    PLLink *lk;
    PLVLink *vlk;
    int i, j, k, step;

    for(i=0; i<evs.size(); i++){
        evs[i].idLog = idObj;
        idObj++;
    }

    for(i=0; i<prgs.size(); i++){
        prg = &prgs[i];
        prg->idLog = idObj;
        idObj++;
    }

    for(i=0; i<prgs.size(); i++){
        prg = &prgs[i];

        for(j=0; j<prg->fbs.size(); j++){
            fb = &prg->fbs[j];
            fb->idLog = idObj;
            idObj++;
            fb->idPrg = prg->idLog;
        }

        for(j=0; j<prg->lks.size(); j++){
            lk = &prg->lks[j];
            lk->id = idObj;
            idObj++;
            lk->idPrg = prg->idLog;
            step = 0;
            for(k=0; k<prg->fbs.size(); k++){
                fb = &prg->fbs[k];
                if(lk->idFbSrc == fb->id){
                    lk->idFbSrc = fb->idLog;
                    step++;
                    break;
                }
            }
            if(step < 1){
                return false;
            }
            step = 0;
            for(k=0; k<prg->fbs.size(); k++){
                fb = &prg->fbs[k];
                if(lk->idFbTgt == fb->id){
                    lk->idFbTgt = fb->idLog;
                    step++;
                    break;
                }
            }
            if(step < 1){
                return false;
            }
        }

        for(j=0; j<prg->vis.size(); j++){
            vlk = &prg->vis[j];
            vlk->id = idObj;
            idObj++;
            step = 0;
            vlk->idPrg = prg->idLog;
            for(k=0; k<prg->fbs.size(); k++){
                fb = &prg->fbs[k];
                if(vlk->idFb == fb->id){
                    vlk->idFb = fb->idLog;
                    step++;
                    break;
                }
            }
            if(step < 1){
                return false;
            }
            step = 0;
            for(k=0; k<evs.size(); k++){
                if(vlk->idEv == evs[k].id){
                    vlk->idEv = evs[k].idLog;
                    step++;
                    break;
                }
            }
            if(step < 1){
                return false;
            }
        }

        for(j=0; j<prg->vos.size(); j++){
            vlk = &prg->vos[j];
            vlk->id = idObj;
            idObj++;
            step = 0;
            vlk->idPrg = prg->idLog;
            for(k=0; k<prg->fbs.size(); k++){
                fb = &prg->fbs[k];
                if(vlk->idFb == fb->id){
                    vlk->idFb = fb->idLog;
                    step++;
                    break;
                }
            }
            if(step < 1){
                return false;
            }
            step = 0;
            for(k=0; k<evs.size(); k++){
                if(vlk->idEv == evs[k].id){
                    vlk->idEv = evs[k].idLog;
                    step++;
                    break;
                }
            }
            if(step < 1){
                return false;
            }
        }
    }

    PLCommand *cmd;
    int idPrg, idFb, pin;
    QStringList list;
    QString value;
    for(i=setpins.size()-1; i>=0; i--){
        cmd = &setpins[i];
        list = cmd->para.split(",");
        idPrg = list.at(0).toInt();
        idFb = list.at(1).toInt();
        pin = list.at(2).toInt();
        value = list.at(3);
        step = 0;
        for(j=0; j<prgs.size(); j++){
            prg = &prgs[j];
            if(idPrg == prg->id){
                idPrg = prg->idLog;
                step++;
                for(k=0; k<prg->fbs.size(); k++){
                    fb = &prg->fbs[k];
                    if(idFb == fb->id){
                        idFb = fb->idLog;
                        step++;
                        break;
                    }
                }
                break;
            }
        }
        if(step < 2){
            //prg or fb may be deleted!
            setpins.removeAt(i);
        }else{
            cmd->para.sprintf("%d,%d,%d,", idPrg, idFb, pin);
            cmd->para += value;
            cmd->makeCmdLine();
        }
    }


    for(i=0; i<evs.size(); i++){
        evs[i].id = evs[i].idLog;
    }

    for(i=0; i<prgs.size(); i++){
        prg = &prgs[i];
        prg->id = prg->idLog;
        for(j=0; j<prg->fbs.size(); j++){
            fb = &prg->fbs[j];
            fb->id = fb->idLog;
        }
    }

    return true;
}

void PLMainModel::extract()
{
    removeDualCommands(cmdList, true);

    int i, j;
    QList<PLCommand> setpins;
    for(i=0; i<cmdList.size(); i++){
        if(cmdList.at(i).fun == "setpin"){
            setpins.append(cmdList.at(i));
        }
    }
    //int idBase = 1;
    objID = 1;
    extractObjsId(objID, prgList, evList, setpins);

    project.renewUuid();

    cmdList.clear();

    cmdID = 0;
    PLCommand cmd;
    for(i=0; i<evList.size(); i++){
        makeEvNewCmd(cmd, evList[i], false);
        cmdList.append(cmd);
    }
    for(i=0; i<prgList.size(); i++){
        makePrgNewCmd(cmd, prgList[i], false);
        cmdList.append(cmd);
    }
    PLProgram *prg;
    for(i=0; i<prgList.size(); i++){
        prg = &prgList[i];
        for(j=0; j<prg->fbs.size(); j++){
            makeFbNewCmd(cmd, prg->fbs[j], false, false);
            cmdList.append(cmd);
        }
        for(j=0; j<prg->lks.size(); j++){
            makeLkNewCmd(cmd, prg->lks[j], false);
            cmdList.append(cmd);
        }
        for(j=0; j<prg->vis.size(); j++){
            makeViNewCmd(cmd, prg->vis[j], false);
            cmdList.append(cmd);
        }
        for(j=0; j<prg->vos.size(); j++){
            makeVoNewCmd(cmd, prg->vos[j], false);
            cmdList.append(cmd);
        }
    }    

    for(i=0; i<setpins.size(); i++){
        cmd = setpins.at(i);
        cmdID++;
        cmd.id = cmdID;
        cmdList.append(cmd);
    }
}
