#ifndef PLMAINFRAME_H
#define PLMAINFRAME_H

#include <QtGui>
#include <QScrollArea>
#include <QMainWindow>
#include <QDebug>
#include <QTreeView>
#include <QToolBar>
#include "cadpanel.h"
#include "libpanel.h"
#include "progpanel.h"
#include "evdatapanel.h"
#include "modulepanel.h"
class PLMainFrame : public QMainWindow {
    Q_OBJECT
public:
    PLMainFrame();
    ~PLMainFrame();
    void updateCadView();
    void updateActionState();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void prjNew();
    void prjOpen();
    void prjSave();
    void prjSaveAs(bool holdUuid = false);
    void editSelectAll();
    void editCopy();
    void editPaste();
    void editDelete();
    void zoomIn();
    void zoomNormal();
    void zoomOut();
    void tgtOnline();
    void tgtOffline();
    void tgtSync();
    void tgtMonitor();
    void tgtDownload();
    void tgtUpload();
    void showProj();
    void showTarget();
    void showVariable();
    void about();

private:
    void createActions();
    void createToolBar();
    void createDockWindows();
    void openProject(QString fileName);

    QAction *actPrjNew;
    QAction *actPrjOpen;
    QAction *actPrjSave;
    QAction *actPrjSaveAs;
    QAction *actEditSelectAll;
    QAction *actEditCopy;
    QAction *actEditPaste;
    QAction *actEditDelete;
    QAction *actZoomIn;
    QAction *actZoomNormal;
    QAction *actZoomOut;
    QAction *actTgtOnline;
    QAction *actTgtOffline;
    QAction *actTgtSync;
    QAction *actTgtMonitor;
    QAction *actTgtDownload;
    QAction *actTgtUpload;
    QAction *actShowProj;
    QAction *actShowTarget;
    QAction *actShowVariable;
    QAction *actAbout;

    QToolBar *toolBar_menu;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTarget;
    QMenu *menuView;
    QToolBar *toolBar;
    QDockWidget *dockProj;
    QDockWidget *dockEVData;
    QDockWidget *dockTarget;
    QTabWidget *tabProj;
    QScrollArea *scrProgCad;
    CadPanel *panelProgCad;
    ModulePanel *panelMods;
    ProgPanel *panelProgs;
    LibPanel *panelLib;
    EVDataPanel *panelEVData;
    //TargetPanel *panelTarget;
    QTreeView *panelTarget;
};

#endif // PLMAINFRAME_H
