#include "plmainframe.h"
#include "gdefine.h"
#include "dlgsaveproj.h"
#include "dlgipaddress.h"
#include "cfgbus.h"
#include "k_command.h"

#include <QTimer>
#include <QAction>
#include <QtWidgets>
class ActStatTimer : public QTimer
{
public:
    ActStatTimer(QObject *parent = 0)
        : QTimer(parent)
    {
        setInterval(200);
    };
    ~ActStatTimer()
    {
    };

    void timerEvent(QTimerEvent *e){
        //qDebug() << "enter actstattimer";
        gMainFrame->updateActionState();
    };
};


PLMainFrame::PLMainFrame()
{
    setWindowTitle(tr("geoCalc - new project"));

    scrProgCad = new QScrollArea;
    panelProgCad = new CadPanel;
    scrProgCad->setBackgroundRole(QPalette::Light);
    scrProgCad->setWidget(panelProgCad);
    setCentralWidget(scrProgCad);

    createActions();
    createToolBar();
    createDockWindows();

    ActStatTimer *actStatTimer = new ActStatTimer(this);
    actStatTimer->start();

}

PLMainFrame::~PLMainFrame()
{
}

void PLMainFrame::createActions()
{
    actPrjNew = new QAction(QIcon(":/images/new.png"), tr("&New"),this);
    actPrjNew->setShortcut(tr("Ctrl+N"));
    actPrjNew->setStatusTip(tr("Create a new project"));
    connect(actPrjNew, SIGNAL(triggered()), this, SLOT(prjNew()));

    actPrjOpen = new QAction(QIcon(":/images/open.png"), tr("&Open"),this);
    actPrjOpen->setShortcut(tr("Ctrl+O"));
    actPrjOpen->setStatusTip(tr("Open an exiting project"));
    connect(actPrjOpen, SIGNAL(triggered()), this, SLOT(prjOpen()));

    actPrjSave = new QAction(QIcon(":/images/save.png"), tr("&Save"),this);
    actPrjSave->setShortcut(tr("Ctrl+S"));
    actPrjSave->setStatusTip(tr("Save current project"));
    connect(actPrjSave, SIGNAL(triggered()), this, SLOT(prjSave()));

    actPrjSaveAs = new QAction(QIcon(":/images/saveas.png"), tr("Save as"),this);
    actPrjSaveAs->setStatusTip(tr("Save current project as..."));
    connect(actPrjSaveAs, SIGNAL(triggered()), this, SLOT(prjSaveAs()));

    actEditSelectAll = new QAction(QIcon(":/images/all.png"), tr("Select &all"),this);
    actEditSelectAll->setShortcut(tr("Ctrl+A"));
    actEditSelectAll->setStatusTip(tr("Select all"));
    connect(actEditSelectAll, SIGNAL(triggered()), this, SLOT(editSelectAll()));

    actEditCopy = new QAction(QIcon(":/images/copy.png"), tr("&Copy"),this);
    actEditCopy->setShortcut(tr("Ctrl+C"));
    actEditCopy->setStatusTip(tr("Copy"));
    connect(actEditCopy, SIGNAL(triggered()), this, SLOT(editCopy()));

    actEditPaste = new QAction(QIcon(":/images/paste.png"), tr("&Paste"),this);
    actEditPaste->setShortcut(tr("Ctrl+V"));
    actEditPaste->setStatusTip(tr("Paste"));
    connect(actEditPaste, SIGNAL(triggered()), this, SLOT(editPaste()));

    actEditDelete = new QAction(QIcon(":/images/delete.png"), tr("&Delete"),this);
    //actEditDelete->setShortcut(tr(""));
    actEditDelete->setStatusTip(tr("Delete"));
    connect(actEditDelete, SIGNAL(triggered()), this, SLOT(editDelete()));

    actZoomIn = new QAction(QIcon(":/images/zoomin.png"), tr("Zomm in"), this);
    actZoomIn->setStatusTip(tr("Zoom in"));
    connect(actZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));

    actZoomNormal = new QAction(QIcon(":/images/zoomnormal.png"), tr("Zomm normal"), this);
    actZoomNormal->setStatusTip(tr("Zoom normal"));
    connect(actZoomNormal, SIGNAL(triggered()), this, SLOT(zoomNormal()));

    actZoomOut = new QAction(QIcon(":/images/zoomout.png"), tr("Zomm out"), this);
    actZoomOut->setStatusTip(tr("Zoom out"));
    connect(actZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));

    actTgtOnline = new QAction(QIcon(":/images/online.png"), tr("Online"), this);
    actTgtOnline->setStatusTip(tr("Online"));
    connect(actTgtOnline, SIGNAL(triggered()), this, SLOT(tgtOnline()));

    actTgtOffline = new QAction(QIcon(":/images/offline.png"), tr("Offline"), this);
    actTgtOffline->setStatusTip(tr("Offline"));
    connect(actTgtOffline, SIGNAL(triggered()), this, SLOT(tgtOffline()));

    actTgtSync = new QAction(QIcon(":/images/sync.png"), tr("Synchronize"), this);
    actTgtSync->setStatusTip(tr("Synchronize"));
    connect(actTgtSync, SIGNAL(triggered()), this, SLOT(tgtSync()));

    actTgtMonitor = new QAction(QIcon(":/images/monitor.png"), tr("Monitor"), this);
    actTgtMonitor->setStatusTip(tr("Monitor"));
    connect(actTgtMonitor, SIGNAL(triggered()), this, SLOT(tgtMonitor()));

    actTgtDownload = new QAction(QIcon(":/images/download.png"), tr("Download"), this);
    actTgtDownload->setStatusTip(tr("Download"));
    connect(actTgtDownload, SIGNAL(triggered()), this, SLOT(tgtDownload()));

    actTgtUpload = new QAction(QIcon(":/images/upload.png"), tr("Upload"), this);
    actTgtUpload->setStatusTip(tr("Upload"));
    connect(actTgtUpload, SIGNAL(triggered()), this, SLOT(tgtUpload()));

    actShowProj = new QAction(QIcon(":/images/proj.png"), tr("Show project"), this);
    actShowProj->setStatusTip(tr("Show project"));
    connect(actShowProj, SIGNAL(triggered()), this, SLOT(showProj()));

    actShowTarget = new QAction(QIcon(":/images/target.png"), tr("Show target"), this);
    actShowTarget->setStatusTip(tr("Show target"));
    connect(actShowTarget, SIGNAL(triggered()), this, SLOT(showTarget()));

    actShowVariable = new QAction(QIcon(":/images/variable.png"), tr("&Show variable"), this);
    actShowVariable->setStatusTip(tr("Show variable"));
    connect(actShowVariable, SIGNAL(triggered()), this, SLOT(showVariable()));

    actAbout = new QAction(QIcon(":/images/about.png"), tr("&About"), this);
    actAbout->setStatusTip(tr("About"));
    connect(actAbout, SIGNAL(triggered()), this, SLOT(about()));
}

void PLMainFrame::createToolBar()
{
    toolBar_menu = addToolBar(tr("MenuBar"));
    toolBar = addToolBar(tr("ToolBar"));
    //toolBar->addAction(actPrjNew);
    toolBar->addAction(actPrjOpen);
    toolBar->addAction(actPrjSave);
    //toolBar->addAction(actPrjSaveAs);
    toolBar->addSeparator();
    //toolBar->addAction(actEditSelectAll);
    toolBar->addAction(actEditCopy);
    toolBar->addAction(actEditPaste);
    toolBar->addAction(actEditDelete);
    toolBar->addSeparator();
    toolBar->addAction(actZoomIn);
    //toolBar->addAction(actZoomNormal);
    toolBar->addAction(actZoomOut);
    toolBar->addSeparator();
    toolBar->addAction(actTgtOnline);
    toolBar->addAction(actTgtOffline);
    toolBar->addAction(actTgtSync);
    toolBar->addAction(actTgtMonitor);
    //toolBar->addAction(actTgtDownload);
    //toolBar->addAction(actTgtUpload);
    //toolBar->addSeparator();
    //toolBar->addAction(actShowProj);
    //toolBar->addAction(actShowVariable);
    //toolBar->addAction(actShowTarget);
    toolBar->addSeparator();
    toolBar->addAction(actAbout);
    toolBar->addSeparator();

    menuBar = new QMenuBar();
    menuBar->setNativeMenuBar(true);
    menuFile = new QMenu(tr("File"));
    menuEdit = new QMenu(tr("Edit"));
    menuTarget = new QMenu(tr("Target"));
    menuView = new QMenu(tr("View"));    
    //toolBar->addWidget(menuBar);
    toolBar_menu->addWidget(menuBar);
    menuBar->addMenu(menuFile);
    menuBar->addMenu(menuEdit);
    menuBar->addMenu(menuTarget);
    menuBar->addMenu(menuView);
    menuFile->addAction(actPrjNew);
    menuFile->addAction(actPrjOpen);
    menuFile->addAction(actPrjSave);
    menuFile->addAction(actPrjSaveAs);
    menuEdit->addAction(actEditSelectAll);
    menuEdit->addAction(actEditCopy);
    menuEdit->addAction(actEditPaste);
    menuEdit->addAction(actEditDelete);
    menuTarget->addAction(actTgtOnline);
    menuTarget->addAction(actTgtOffline);
    menuTarget->addAction(actTgtSync);
    menuTarget->addAction(actTgtMonitor);
    menuTarget->addAction(actTgtDownload);
    menuTarget->addAction(actTgtUpload);
    menuView->addAction(actShowProj);
    menuView->addAction(actShowVariable);
    menuView->addAction(actShowTarget);
}

void PLMainFrame::createDockWindows()
{
    tabProj = new QTabWidget;
    tabProj->setTabPosition(QTabWidget::North);

    panelProgs = new ProgPanel;
    panelLib = new LibPanel;
    tabProj->insertTab(1, panelProgs, tr("Program"));
    tabProj->insertTab(2, panelLib, tr("Library"));

    dockProj = new QDockWidget(gMainModel->project.description(), this);
    dockProj->setWidget(tabProj);
    addDockWidget(Qt::LeftDockWidgetArea, dockProj);

    panelEVData = new EVDataPanel;
    dockEVData = new QDockWidget(tr("Variable table"), this);
    dockEVData->setWidget(panelEVData);
    addDockWidget(Qt::BottomDockWidgetArea, dockEVData);

//     panelTarget = new QTreeView;
//     QFont ft("Monospaced", 9);
//     panelTarget->setFont(ft);
//     panelTarget->setModel(&gTarget->modelIO);
//     dockTarget = new QDockWidget(tr("IO Stations"), this);
//     dockTarget->setWidget(panelTarget);
//     addDockWidget(Qt::BottomDockWidgetArea, dockTarget);
}

void PLMainFrame::prjNew()
{
    if(gTarget->isMonitor()){
        return;
    }

    if(gMainModel->isModified){
        int ret;
        ret = QMessageBox::question(this, tr("Question"), tr("Project have been changed, save it now?"),
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(QMessageBox::Yes == ret){
            prjSave();
        }else if(QMessageBox::Cancel == ret){
            return;
        }
    }

    gMainModel->clear();
    gMainModel->updateProgList();

    dockProj->setWindowTitle(gMainModel->project.description());
    updateCadView();

    gMainModel->isModified = false;
    setWindowTitle(tr("geoCalc - new project"));
}

void PLMainFrame::openProject(QString fileName)
{
    gMainModel->clear();

    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QDataStream in(&file);

    gMainModel->modelEVData.beginReset();

    while(!in.atEnd()){
        QByteArray line;
        in >>line;
        PLCommand cmd(QString::fromLatin1(line));
        if(!gMainModel->exeCommand(cmd)){
            QMessageBox::critical(this, tr("Error"), cmd.cmdLine);
            gMainModel->modelEVData.endReset();
            return;
        }
    }

    file.close();

    gMainModel->modelEVData.endReset();
    gMainModel->updateProgList();
    gMainModel->project.fileName = fileName;

    dockProj->setWindowTitle(gMainModel->project.description());
    updateCadView();

    gMainModel->isModified = false;
    QString title = "geoCalc - ";
    title += fileName;
    setWindowTitle(title);

    int i, j;
    PLProgram *prg;
    for(i=0; i<gMainModel->prgList.size(); i++){
        prg = &gMainModel->prgList[i];
        for(j=0; j<prg->fbs.size(); j++){
            prg->fbs[j].isSelected = false;
        }
        for(j=0; j<prg->lks.size(); j++){
            prg->lks[j].isSelected = false;
        }
    }
}

void PLMainFrame::prjOpen()
{
    if(gTarget->isMonitor()){
        return;
    }

    if(gMainModel->isModified){
        int ret;
        ret = QMessageBox::question(this, tr("Question"), tr("Project have been changed, save it now?"),
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(QMessageBox::Yes == ret){
            prjSave();
        }else if(QMessageBox::Cancel == ret){
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project..."), tr("/pmchome/config/logic"), tr("Type  (*.cl)"));
    if(fileName.isEmpty()){
        return;
    }

    openProject(fileName);
}

void PLMainFrame::prjSave()
{
    if(gMainModel->project.fileName.isEmpty()){
        prjSaveAs(true);
    }

    gMainModel->removeDualCommands(gMainModel->cmdList, false);

    QFile file(gMainModel->project.fileName);
    file.open(QFile::WriteOnly| QFile::Truncate);
    QDataStream out(&file);

    out << gMainModel->project.getProjCmdLine().toLatin1();
    for(int i=0; i<gMainModel->cmdList.size(); i++){
        out << gMainModel->cmdList.at(i).cmdLine.toLatin1();
    }
    file.close();

    gMainModel->isModified = false;
}

void PLMainFrame::prjSaveAs(bool holdUuid)
{
    int i;

    DlgSaveProj dlgSaveProj;
    if(dlgSaveProj.exec() != QDialog::Accepted){
        return;
    }

    if(holdUuid){
        dlgSaveProj.bCompatible = true;
    }
    if(dlgSaveProj.bCompatible){
        gMainModel->removeDualCommands(gMainModel->cmdList, false);
    }else{
        gMainModel->extract();
        prj_reset();
        char cline[1024];
        strncpy(cline, gMainModel->project.getProjCmdLine().toLatin1().data(), sizeof(cline)-1);
        cmd_dispatch(cline);
        for(i=0; i<gMainModel->cmdList.size(); i++){
            strncpy(cline, gMainModel->cmdList.at(i).cmdLine.toLatin1().data(), sizeof(cline)-1);
            cmd_dispatch(cline);
        }
    }

    QFile file(dlgSaveProj.fileName);
    file.open(QFile::WriteOnly| QFile::Truncate);
    QTextStream out(&file);
    out << gMainModel->project.getProjCmdLine().toLatin1();
    for(int i=0; i<gMainModel->cmdList.size(); i++){
        out << gMainModel->cmdList.at(i).cmdLine.toLatin1();
    }
    file.close();

    gMainModel->isModified = false;
    QString title = "geoCalc - ";
    title += dlgSaveProj.fileName;
    setWindowTitle(title);
    gMainModel->project.fileName = dlgSaveProj.fileName;
    dockProj->setWindowTitle(gMainModel->project.description());

    if(!dlgSaveProj.bCompatible){
        updateCadView();
    }
}

void PLMainFrame::editSelectAll()
{
    if(gMainModel->prgCurrent == NULL){
        return;
    }

    int i;
    for(i=0; i<gMainModel->prgCurrent->vis.size(); i++){
        gMainModel->prgCurrent->vis[i].isSelected = true;
    }
    for(i=0; i<gMainModel->prgCurrent->vos.size(); i++){
        gMainModel->prgCurrent->vos[i].isSelected = true;
    }
    for(i=0; i<gMainModel->prgCurrent->lks.size(); i++){
        gMainModel->prgCurrent->lks[i].isSelected = true;
    }
    for(i=0; i<gMainModel->prgCurrent->fbs.size(); i++){
        gMainModel->prgCurrent->fbs[i].isSelected = true;
    }

    updateCadView();
}

void PLMainFrame::editCopy()
{
    if(gTarget->isMonitor()){
        return;
    }

    QByteArray cpCmds;
    panelProgCad->getCopyCommands(cpCmds);
    //qDebug()<<cpCmds;
    //if(cpCmds.isEmpty()){
    //    return;
    //}

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("PL-copyobjs", QByteArray());
    mimeData->setData("cmd-copyobjs",cpCmds);

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setMimeData(mimeData);
}

void PLMainFrame::editPaste()
{
    if(gTarget->isMonitor()){
        return;
    }

    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *mimeData = clipboard->mimeData();
    if(!mimeData->hasFormat("PL-copyobjs")){
        return;
    }
    if(!mimeData->hasFormat("cmd-copyobjs")){
        return;
    }
    QByteArray cpCmds = clipboard->mimeData()->data("cmd-copyobjs");
    panelProgCad->exeCopyCommands(cpCmds);
}

void PLMainFrame::editDelete()
{
    if(QMessageBox::Yes != QMessageBox::question(this, "Question", tr("Confirm to delete"), QMessageBox::Yes | QMessageBox::No)){
        return;
    }

    gMainModel->modelEVData.beginReset();
    panelProgCad->removeAllSelected();
    gMainModel->modelEVData.endReset();
}

void PLMainFrame::zoomIn()
{
    panelProgCad->zoom(1);
    panelProgCad->update();
}

void PLMainFrame::zoomNormal()
{
    panelProgCad->zoom(0);
    panelProgCad->update();
}

void PLMainFrame::zoomOut()
{
    panelProgCad->zoom(-1);
    panelProgCad->update();
}

void PLMainFrame::tgtOnline()
{
    if(gTarget->isOnline()){
        return;
    }

    static QString ip = "127.0.0.1";

    DlgIPAddress dlgIPAddress(this);
    dlgIPAddress.setIP(ip);
    if(QDialog::Accepted != dlgIPAddress.exec()){
        return;
    }

    ip = dlgIPAddress.getIP();
    char ipc[32];
    strcpy(ipc, ip.toStdString().c_str());
    if(!gTarget->online(true, ipc)){
        QMessageBox::critical(this, tr("Error"), tr("Connect fail"));
    }
}

void PLMainFrame::tgtOffline()
{
    gTarget->online(false, NULL);
}

void PLMainFrame::tgtSync()
{
    if(!gTarget->sync()){
        QMessageBox::critical(this, tr("Error"), tr("Synchronize fail"));
    }
}

void PLMainFrame::tgtMonitor()
{
    gTarget->monitor(!gTarget->isMonitor());
    panelProgCad->update();
}

void PLMainFrame::tgtDownload()
{
    if(QMessageBox::Yes != QMessageBox::question(this, "Question", tr("Confirm download"), QMessageBox::Yes | QMessageBox::No)){
        return;
    }

    if(!gTarget->download()){
        QMessageBox::critical(this, tr("Error"), tr("Download fail"));
    }

    dockProj->setWindowTitle(gMainModel->project.description());
}

void PLMainFrame::tgtUpload()
{
    if(!gTarget->isOnline()){
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Project..."), tr("/pmchome/config/logic"), tr("Type  (*.cl)"));
    if(fileName.isEmpty()){
        return;
    }

    QString cmds;
    if(!gTarget->upload(cmds)){
        QMessageBox::critical(this, tr("Error"), tr("Upload fail"));
    }

    QFile file(fileName);
    file.open(QFile::WriteOnly| QFile::Truncate);
    QDataStream out(&file);

    out << cmds.toLatin1();
    file.close();
}

void PLMainFrame::showProj()
{
    dockProj->show();
}

void PLMainFrame::showTarget()
{
//    dockTarget->show();
}

void PLMainFrame::showVariable()
{
    dockEVData->show();
}

void PLMainFrame::about()
{
    QMessageBox::about(this, tr("GeoCalc"),
             tr("<b>By George Kuo  </b>" "GeoSysWare 1.0.0.1"));
}

void PLMainFrame::updateCadView()
{
    panelProgCad->update();
}

void PLMainFrame::updateActionState()
{
    if(gTarget->isOnline()){
        actTgtOnline->setEnabled(false);
        actTgtOffline->setEnabled(true);
        actTgtUpload->setEnabled(true);
        if(gTarget->isSync()){
            actTgtMonitor->setEnabled(true);
        }else{
            actTgtMonitor->setEnabled(false);
        }
        if(gTarget->isMonitor()){
            actTgtMonitor->setChecked(false);
            actTgtDownload->setEnabled(false);
            actTgtSync->setEnabled(false);
        }else{
            actTgtMonitor->setChecked(true);
            actTgtDownload->setEnabled(true);
            if(gTarget->isMatch()){
                if(gTarget->isSync()){
                    actTgtSync->setEnabled(false);
                }else{
                    actTgtSync->setEnabled(true);
                }
            }else{
                actTgtSync->setEnabled(false);
            }
        }
    }else{
        actTgtOnline->setEnabled(true);
        actTgtOffline->setEnabled(false);
        actTgtMonitor->setEnabled(false);
        actTgtSync->setEnabled(false);
        actTgtDownload->setEnabled(false);
        actTgtUpload->setEnabled(false);
    }

    if(gTarget->isMonitor()){
        actPrjNew->setEnabled(false);
        actPrjOpen->setEnabled(false);
    }else{
        actPrjNew->setEnabled(true);
        actPrjOpen->setEnabled(true);
    }

    if(gMainModel->isModified){
        actPrjSave->setEnabled(true);
    }else{
        actPrjSave->setEnabled(false);
    }

    if(dockProj->isVisible()){
        actShowProj->setEnabled(false);
    }else{
        actShowProj->setEnabled(true);
    }
    if(dockEVData->isVisible()){
        actShowVariable->setEnabled(false);
    }else{
        actShowVariable->setEnabled(true);
    }
//    if(dockTarget->isVisible()){
//        actShowTarget->setEnabled(false);
//    }else{
//        actShowTarget->setEnabled(true);
//    }

    if(gTarget->isMonitor()){
        actEditSelectAll->setEnabled(false);
        actEditDelete->setEnabled(false);
        actEditCopy->setEnabled(false);
        actEditPaste->setEnabled(false);
    }else{
        actEditSelectAll->setEnabled(true);
        if(panelProgCad->hasSelectedFb()){
            actEditCopy->setEnabled(true);
        }else{
            actEditCopy->setEnabled(false);
        }
        if(panelProgCad->hasSelectedObj()){
            actEditDelete->setEnabled(true);
        }else{
            actEditDelete->setEnabled(false);
        }
        QClipboard *clipboard = QApplication::clipboard();
        const QMimeData *mimeData = clipboard->mimeData();
        if(mimeData->hasFormat("PL-copyobjs")){
            actEditPaste->setEnabled(true);
        }else{
            actEditPaste->setEnabled(false);
        }
    }

    panelProgs->updateState();
    panelEVData->updateState();
}

void PLMainFrame::closeEvent(QCloseEvent *event)
{
    if(gMainModel->isModified){
        int ret;
        ret = QMessageBox::question(this, tr("Question"), tr("Project have been changed, save it now?"),
                              QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(QMessageBox::Yes == ret){
            prjSave();
        }else if(QMessageBox::Cancel == ret){
            event->ignore();
        }
    }

}
