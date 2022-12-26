#include <QApplication>
#include "src/plmainframe.h"
#include "src/plmainmodel.h"
#include "src/pltarget.h"
#include "cyber/cyber.h"

PLMainFrame *gMainFrame;
PLMainModel *gMainModel;
PLTarget *gTarget;
std::shared_ptr<apollo::cyber::Node> gNode;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

     apollo::cyber::Init(argv[0]);
    gNode = std::move(apollo::cyber::CreateNode("robot_draw"));

    PLMainModel modMain;
    gMainModel = &modMain;

    PLTarget target;
    gTarget = &target;

    PLMainFrame frmMain;
    frmMain.show();
    gMainFrame = &frmMain;

    return app.exec();
}
