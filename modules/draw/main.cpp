#include <QApplication>
#include "src/plmainframe.h"
#include "src/plmainmodel.h"
#include "src/pltarget.h"

PLMainFrame *gMainFrame;
PLMainModel *gMainModel;
PLTarget *gTarget;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PLMainModel modMain;
    gMainModel = &modMain;

    PLTarget target;
    gTarget = &target;

    PLMainFrame frmMain;
    frmMain.show();
    gMainFrame = &frmMain;

    return app.exec();
}
