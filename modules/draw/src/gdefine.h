#ifndef GDEFINE_H
#define GDEFINE_H

#include "plmainframe.h"
#include "plmainmodel.h"
#include "pltarget.h"
#include "cyber/cyber.h"

extern PLMainFrame *gMainFrame;
extern PLMainModel *gMainModel;
extern PLTarget *gTarget;
extern std::shared_ptr<apollo::cyber::Node> gNode;
#endif // GDEFINE_H
