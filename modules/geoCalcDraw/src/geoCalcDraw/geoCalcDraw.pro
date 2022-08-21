#LIBS += -lwsock32 \
#    -lws2_32

include(../../gprefix.pri)




TARGET = nicCalcDraw
TEMPLATE = app
SOURCES += main.cpp \
    plmainframe.cpp \
    cadpanel.cpp \
    libpanel.cpp \
    progpanel.cpp \
    plmainmodel.cpp \
    plfunctionblock.cpp \
    plpin.cpp \
    plpoint.cpp \
    pllink.cpp \
    plvlink.cpp \
    plevdata.cpp \
    plprogram.cpp \
    plcommand.cpp \
    pltarget.cpp \
    plselobject.cpp \
    dlgaddprog.cpp \
    plproject.cpp \
    evdatapanel.cpp \
    evdatamodel.cpp \
    dlgevdata.cpp \
    dlgpinset.cpp \
    dlgsaveproj.cpp \
    dlgobjname.cpp \
    plionode.cpp \
#    pliomodel.cpp \
    dlgipaddress.cpp \
    /home/shuimujie/Works/GeoSys/bazel-bin/modules/calc/proto/value.pb.cc \
    ../../../calc/kernel/k_command.cpp \
    ../../../calc/kernel/k_compress.cpp \
    ../../../calc/kernel/k_evdata.cpp \
    ../../../calc/kernel/k_functionblock.cpp \
#    ../../../calc/kernel/k_io.cpp \
    ../../../calc/kernel/k_lib.cpp \
    ../../../calc/kernel/k_process.cpp \
    ../../../calc/kernel/k_program.cpp \
    ../../../calc/kernel/k_project.cpp \
#    ../../../calc/kernel/k_state.cpp \
    ../../../calc/kernel/k_util.cpp \
    ../../../calc/net/cfgbus.cpp \
    ../../../calc/net/evbus.cpp \
#    ../../../calc/net/stbbus.cpp \
    ../../../calc/net/vnet.cpp \
    ../../../calc/net/vtcp.cpp \
    ../../../calc/net/vudp.cpp \
    ../../../calc/rtdb/BinTree.cpp \
    ../../../calc/rtdb/helper.cpp \
    ../../../calc/rtdb/RBTree.cpp \
    ../../../calc/rtdb/rtdb.cpp \
    ../../../calc/rtdb/station.cpp \
    ../../../calc/lib/Arithmetic/Arithmetic.cpp \
#    ../../../calc/lib/Bistable/Bistable.cpp \
#    ../../../calc/lib/Comm/Comm.cpp \
#    ../../../calc/lib/Comparison/Comparison.cpp \
#    ../../../calc/lib/Control/Control.cpp \
#    ../../../calc/lib/Converter/Converter.cpp \
    ../../../calc/lib/Counter/Counter.cpp \
#    ../../../calc/lib/Driver/Driver.cpp \
    ../../../calc/lib/Fsm/Fsm.cpp

#    ../../../calc/lib/IO/IO.cpp \
#    ../../../calc/lib/Logic/Logic.cpp \
#    ../../../calc/lib/Maths/Maths.cpp \
#    ../../../calc/lib/Opencv/Opencv.cpp \
#    ../../../calc/lib/Selection/Selection.cpp \
#    ../../../calc/lib/System/System.cpp \
#    ../../../calc/lib/Timer/Timer.cpp \
#    ../../../calc/lib/Trigger/Trigger.cpp
HEADERS += plmainframe.h \
    cadpanel.h \
    libpanel.h \
    progpanel.h \
    plmainmodel.h \
    gdefine.h \
    plfunctionblock.h \
    plpin.h \
    plpoint.h \
    pllink.h \
    plvlink.h \
    plevdata.h \
    plprogram.h \
    plcommand.h \
    pltarget.h \
    plselobject.h \
    dlgaddprog.h \
    plproject.h \
    evdatapanel.h \
    evdatamodel.h \
    dlgevdata.h \
    dlgpinset.h \
    dlgsaveproj.h \
    dlgobjname.h \
    plionode.h \
    pliomodel.h \
    dlgipaddress.h \
    ../../../calc/rtdb/BinTree.h \
    ../../../calc/rtdb/CapiGlobal.h \
    ../../../calc/rtdb/helper.h \
    ../../../calc/rtdb/RBTree.h \
    ../../../calc/rtdb/rtdb.h \
    ../../../calc/rtdb/station.h
FORMS += 
RESOURCES += resource.qrc \
    images.qrc
OTHER_FILES +=


#set macro define in the project
DEFINES += WIN32_LEAN_AND_MEAN

#this source files and header files  may be add something by yourself
INCLUDEPATH += ../../../calc/include \
                ../../../../ \
                /home/shuimujie/Works/GeoSys/bazel-bin \
                /home/shuimujie/Works/GeoSys/bazel-GeoSys/external/com_google_protobuf/src \
                /usr/include/opencv4 \


#set other lib dir if you need
QMAKE_LIBDIR +=

LIBS += -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc \
        -lopencv_imgcodecs \
        -L/home/shuimujie/Works/GeoSys/bazel-bin/external/com_google_protobuf/ \
        -lprotobuf \
        -lprotobuf_lite

include(../../gpostfix.pri)

DISTFILES += \
    images_win7/about.png \
    images_win7/all.png \
    images_win7/copy.png \
    images_win7/cursorcp.png \
    images_win7/cursorev.png \
    images_win7/cursorfb.png \
    images_win7/cursorlk.png \
    images_win7/cursorna.png \
    images_win7/delete.png \
    images_win7/download.png \
    images_win7/monitor.png \
    images_win7/new.png \
    images_win7/offline.png \
    images_win7/online.png \
    images_win7/open.png \
    images_win7/paste.png \
    images_win7/proj.png \
    images_win7/save.png \
    images_win7/saveas.png \
    images_win7/sync.png \
    images_win7/target.png \
    images_win7/upload.png \
    images_win7/variable.png \
    images_win7/zoomin.png \
    images_win7/zoomnormal.png \
    images_win7/zoomout.png \
    images/minus.png \
    ../../../calc/lib/Bistable/RS \
    ../../../calc/lib/Bistable/SR \
    ../../../calc/lib/Comm/RG_BOOL \
    ../../../calc/lib/Comm/RG_INT \
    ../../../calc/lib/Comm/RG_REAL \
    ../../../calc/lib/Comm/WG_BOOL \
    ../../../calc/lib/Comm/WG_INT \
    ../../../calc/lib/Comm/WG_REAL \
    ../../../calc/lib/Comparison/EQ_INT \
    ../../../calc/lib/Comparison/EQ_LREAL \
    ../../../calc/lib/Comparison/EQ_REAL \
    ../../../calc/lib/Comparison/GE_INT \
    ../../../calc/lib/Comparison/GE_LREAL \
    ../../../calc/lib/Comparison/GE_REAL \
    ../../../calc/lib/Comparison/GT_INT \
    ../../../calc/lib/Comparison/GT_LREAL \
    ../../../calc/lib/Comparison/GT_REAL \
    ../../../calc/lib/Comparison/LE_INT \
    ../../../calc/lib/Comparison/LE_LREAL \
    ../../../calc/lib/Comparison/LE_REAL \
    ../../../calc/lib/Comparison/LT_INT \
    ../../../calc/lib/Comparison/LT_LREAL \
    ../../../calc/lib/Comparison/LT_REAL \
    ../../../calc/lib/Comparison/NE_INT \
    ../../../calc/lib/Comparison/NE_LREAL \
    ../../../calc/lib/Comparison/NE_REAL \
    ../../../calc/lib/Control/BALANCE \
    ../../../calc/lib/Control/DDS \
    ../../../calc/lib/Control/DIFF \
    ../../../calc/lib/Control/ES_MA \
    ../../../calc/lib/Control/FILTER \
    ../../../calc/lib/Control/FIRST \
    ../../../calc/lib/Control/HL_ALM \
    ../../../calc/lib/Control/HL_LMT \
    ../../../calc/lib/Control/INTEG \
    ../../../calc/lib/Control/LEADLAG \
    ../../../calc/lib/Control/LIMV \
    ../../../calc/lib/Control/PID \
    ../../../calc/lib/Control/RAT_ALM \
    ../../../calc/lib/Control/RAT_LMT \
    ../../../calc/lib/Control/RMP \
    ../../../calc/lib/Control/SFT_BOOL \
    ../../../calc/lib/Control/SFT_REAL \
    ../../../calc/lib/Control/SS_MA \
    ../../../calc/lib/Control/TOTALIZER \
    ../../../calc/lib/Converter/B2DT \
    ../../../calc/lib/Converter/B2I \
    ../../../calc/lib/Converter/B2LR \
    ../../../calc/lib/Converter/B2R \
    ../../../calc/lib/Converter/DT2B \
    ../../../calc/lib/Converter/DT2I \
    ../../../calc/lib/Converter/DT2LR \
    ../../../calc/lib/Converter/DT2R \
    ../../../calc/lib/Converter/I2B \
    ../../../calc/lib/Converter/I2DT \
    ../../../calc/lib/Converter/I2LR \
    ../../../calc/lib/Converter/I2R \
    ../../../calc/lib/Converter/LR2B \
    ../../../calc/lib/Converter/LR2DT \
    ../../../calc/lib/Converter/LR2I \
    ../../../calc/lib/Converter/LR2R \
    ../../../calc/lib/Converter/R2B \
    ../../../calc/lib/Converter/R2DT \
    ../../../calc/lib/Converter/R2I \
    ../../../calc/lib/Converter/R2LR \
    ../../../calc/lib/Converter/SCALING \
    ../../../calc/lib/Counter/CTUD_INT \
    ../../../calc/lib/Driver/D_AS_VAL \
    ../../../calc/lib/Driver/D_DS_VAL \
    ../../../calc/lib/Driver/D_DT_VAL \
    ../../../calc/lib/Driver/MTR_LGE \
    ../../../calc/lib/Driver/MTR_LTE \
    ../../../calc/lib/Driver/S_E_VAL \
    ../../../calc/lib/IO/DM1x1 \
    ../../../calc/lib/IO/DM2x1 \
    ../../../calc/lib/IO/DM3x1 \
    ../../../calc/lib/IO/DM4x1 \
    ../../../calc/lib/Logic/AND \
    ../../../calc/lib/Logic/AND4 \
    ../../../calc/lib/Logic/NOT \
    ../../../calc/lib/Logic/OR \
    ../../../calc/lib/Logic/OR4 \
    ../../../calc/lib/Logic/XOR \
    ../../../calc/lib/Maths/ABS \
    ../../../calc/lib/Maths/ACOS \
    ../../../calc/lib/Maths/ASIN \
    ../../../calc/lib/Maths/ATAN \
    ../../../calc/lib/Maths/AVE4W \
    ../../../calc/lib/Maths/COS \
    ../../../calc/lib/Maths/EXP \
    ../../../calc/lib/Maths/FUN12 \
    ../../../calc/lib/Maths/LN \
    ../../../calc/lib/Maths/LOG \
    ../../../calc/lib/Maths/MOD \
    ../../../calc/lib/Maths/POLYNOM \
    ../../../calc/lib/Maths/SIN \
    ../../../calc/lib/Maths/SQRT \
    ../../../calc/lib/Maths/TAN \
    ../../../calc/lib/Selection/SIX_SEL_N \
    ../../../calc/lib/Selection/THRSEL \
    ../../../calc/lib/Selection/TWOSEL \
    ../../../calc/lib/System/SysState \
    ../../../calc/lib/Timer/DELAY \
    ../../../calc/lib/Timer/SPO \
    ../../../calc/lib/Timer/TOFF \
    ../../../calc/lib/Timer/TON \
    ../../../calc/lib/Timer/TP \
    ../../../calc/lib/Trigger/D_TRIG \
    ../../../calc/lib/Trigger/U_TRIG
