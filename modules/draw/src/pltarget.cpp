#include "pltarget.h"
#include "gdefine.h"


//定时器中刷新各个引脚和变量的值，并更新画面
void PLTarget::timerEvent(QTimerEvent *e)
{
    //  if(0 == cfgbus_send(FUNCPRJINFO, 0, NULL)){
    //      prjinfo_t *pinfo = cfgbus_prjinfo();
    //      idCmdTarget = pinfo->id_cmd;
    //      uuidTarget = pinfo->uuid;
    //      //qDebug() << uuidTarget << idCmdTarget;
    //  }else{
    //      online(false, NULL);
    //  }

    // if(bMonitor){        
    //     if(0 == cfgbus_send(FUNCIMG, 0, NULL)){
    //         int i, j, k, n;
    //         // load fbs value
    //         PLProgram *prg;
    //         PLFunctionBlock *fb;
    //         fb_t *p_fb;
    //         for(i=0; i<gMainModel->prgList.size(); i++){
    //             prg = &gMainModel->prgList[i];
    //             for(j=0; j<prg->fbs.size(); j++){
    //                 fb = &prg->fbs[j];
    //                 p_fb = prj_fbfind(fb->idPrg, fb->id);
    //                 // input
    //                 for(k=0; k<fb->input.size(); k++){
    //                     fb->input[k].value = *(p_fb->ins[k].v);
    //                 }
    //                 // output
    //                 for(k=0; k<fb->output.size(); k++){
    //                     fb->output[k].value = *(p_fb->outs[k].v);
    //                     qDebug() << "fb" << fb->id << "pin" << k << "val" << fb->output[k].value.v().i();
    //                 }
    //                 // property
    //                 for(k=0; k<fb->property.size(); k++){
    //                     fb->property[k].value = *(p_fb->props[k].v);
    //                 }
    //             }
    //         }
    //         // load evs value
    //         PLEVData *ev;
    //         value_tm *p_ev;
    //         for(int i=0; i<gMainModel->evList.size(); i++){
    //             ev = &gMainModel->evList[i];
    //             p_ev = ev_find_v(ev->id)->get();
    //             ev->value = *p_ev;
    //         }
    //         gMainFrame->updateCadView();
    //     }else{
    //         online(false, NULL);
    //     }
    // }

    //static int i = 0;
    //qDebug() << "timer:" << i++ << uuidTarget;
}

PLTarget::PLTarget(QObject *parent)
    : QTimer(parent)
{

    bOnline = false;
    bMonitor = false;

    setInterval(200);
}

PLTarget::~PLTarget()
{

}

bool PLTarget::online(bool mode, char *ip)
{
    // if(mode == bOnline){
    //     return false;
    // }

    // if(mode){
    //     if(0 == cfgbus_connect(ip)){
    //         bOnline = true;
    //         start();
    //     }
    // }else{
    //     stop();
    //     cfgbus_disconnect();
    //     bOnline = false;
    //     bMonitor = false;
    //     idCmdTarget = 0;
    //     uuidTarget.clear();
    //     gMainFrame->updateCadView();
    // }

    // return bOnline;

    return false;

}

bool PLTarget::sync()
{
    // if(!bOnline){
    //     return false;
    // }
    // if(bMonitor){
    //     return false;
    // }
    // if(!isMatch()){
    //     return false;
    // }
    // if(isSync()){
    //     return false;
    // }

    // QByteArray bigCmd;
    // for(int i=0; i<gMainModel->cmdList.size(); i++){
    //     if(gMainModel->cmdList.at(i).id > idCmdTarget){
    //         bigCmd += QByteArray::number(gMainModel->cmdList.at(i).cmdLine.toLatin1().length());
    //         bigCmd += gMainModel->cmdList.at(i).cmdLine.toLatin1();
    //     }
    // }
    // if(bigCmd.length() >= sizeof(cmdsbuf)){
    //     return false;
    // }
    // strncpy(cmdsbuf, bigCmd.data(), sizeof(cmdsbuf)-1);
    // cmdsbuf[sizeof(cmdsbuf)-1] = 0;

    // stop();

    // if(0 != cfgbus_send(FUNCSTOP, 0, NULL)){
    //     online(false, NULL);
    //     return false;
    // }

    // if(0 == cfgbus_send(FUNCCMD, strlen(cmdsbuf)+1, cmdsbuf)){
    //     cfgbus_send(FUNCRUN, 0, NULL);
    //     start();
    //     return true;
    // }else{
    //     online(false, NULL);
    //     return false;
    // }
    return false;

}

void PLTarget::monitor(bool mode)
{
    if(mode){
        if(!bOnline){
            return;
        }
        if(!isSync()){
            return;
        }
        bMonitor = true;
    }else{
        bMonitor = false;
    }
}

bool PLTarget::download()
{
    // if(!bOnline){
    //     return false;
    // }
    // if(bMonitor){
    //     return false;
    // }
    // if(isSync()){
    //     return false;
    // }

    // gMainModel->project.renewUuid();
    // char cline[1024];
    // strncpy(cline, gMainModel->project.getProjCmdLine().toLatin1().data(), sizeof(cline)-1);
    // cmd_dispatch(cline);


    // QByteArray bigCmd;
    // QBuffer buff_io(&bigCmd);
    // buff_io.open(QFile::WriteOnly| QFile::Truncate);
    // QDataStream out(&buff_io);
    // out.setByteOrder(QDataStream::LittleEndian);
    // out << gMainModel->project.getProjCmdLine().toLatin1();
    // for(int i=0; i<gMainModel->cmdList.size(); i++){
    //     out << gMainModel->cmdList.at(i).cmdLine.toLatin1();
    // }
    // buff_io.close();

    // if(bigCmd.length() >= sizeof(cmdsbuf)){
    //     return false;
    // }
    // memcpy(cmdsbuf, bigCmd.data(), std::min((int)sizeof(cmdsbuf),bigCmd.length()));
    // cmdsbuf[sizeof(cmdsbuf)-1] = 0;
    // stop();

    // if(0 != cfgbus_send(FUNCSTOP, 0, NULL)){
    //     //qDebug() << "Err: FUNCSTOP";
    //     online(false, NULL);
    //     return false;
    // }
    // if(0 != cfgbus_send(FUNCRESET, 0, NULL)){
    //     //qDebug() << "Err: FUNCRESET";
    //     online(false, NULL);
    //     return false;
    // }

    // if(0 == cfgbus_send(FUNCCMD, std::min((int)sizeof(cmdsbuf),bigCmd.length()), cmdsbuf)){
    //     cfgbus_send(FUNCRUN, 0, NULL);
    //     start();
    //     return true;
    // }else{
    //     //qDebug() << "Err: FUNCSTART";
    //     online(false, NULL);
    //     return false;
    // }
    return false;

}

bool PLTarget::upload(QString &cmds)
{
    // if(0 != cfgbus_send(FUNCUCMD,0,NULL)){
    //     online(false, NULL);
    //     return false;
    // }

    // cmds = cfgbus_cmdsbuf();
    // return true;
    return false;

}

bool PLTarget::isOnline()
{
    return bOnline;
}

bool PLTarget::isMonitor()
{
    return bMonitor;
}

bool PLTarget::isMatch()
{
    // if(uuidTarget == gMainModel->project.uuid){
    //     if(idCmdTarget <= gMainModel->cmdID){
    //         return true;
    //     }else{
    //         return false;
    //     }
    // }else{
    //     return false;
    // }

        return false;

}

bool PLTarget::isSync()
{
    // if(isMatch()){
    //     if(idCmdTarget == gMainModel->cmdID){
    //         return true;
    //     }
    // }
    return false;
}
