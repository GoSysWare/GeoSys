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
    pliomodel.cpp \
    dlgipaddress.cpp \
    ../../../geoCalcCore/src/geoCalc/kernel/k_command.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_compress.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_evdata.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_functionblock.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_io.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_lib.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_process.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_program.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_project.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_state.c \
    ../../../geoCalcCore/src/geoCalc/kernel/k_util.c \
    ../../../geoCalcCore/src/geoCalc/net/cfgbus.c \
    ../../../geoCalcCore/src/geoCalc/net/evbus.c \
    ../../../geoCalcCore/src/geoCalc/net/stbbus.c \
    ../../../geoCalcCore/src/geoCalc/net/vnet.c \
    ../../../geoCalcCore/src/geoCalc/net/vtcp.c \
    ../../../geoCalcCore/src/geoCalc/net/vudp.c \
    ../../../geoCalcCore/src/geoCalc/rtdb/BinTree.c \
    ../../../geoCalcCore/src/geoCalc/rtdb/helper.c \
    ../../../geoCalcCore/src/geoCalc/rtdb/RBTree.c \
    ../../../geoCalcCore/src/geoCalc/rtdb/rtdb.c \
    ../../../geoCalcCore/src/geoCalc/rtdb/station.c \
    ../../../geoCalcCore/src/geoCalc/lib/Arithmetic/Arithmetic.c \
    ../../../geoCalcCore/src/geoCalc/lib/Bistable/Bistable.c \
    ../../../geoCalcCore/src/geoCalc/lib/Comm/Comm.c \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/Comparison.c \
    ../../../geoCalcCore/src/geoCalc/lib/Control/Control.c \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/Converter.c \
    ../../../geoCalcCore/src/geoCalc/lib/Counter/Counter.c \
    ../../../geoCalcCore/src/geoCalc/lib/Driver/Driver.c \
    ../../../geoCalcCore/src/geoCalc/lib/IO/IO.c \
    ../../../geoCalcCore/src/geoCalc/lib/Logic/Logic.c \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/Maths.c \
    ../../../geoCalcCore/src/geoCalc/lib/Selection/Selection.c \
    ../../../geoCalcCore/src/geoCalc/lib/System/System.c \
    ../../../geoCalcCore/src/geoCalc/lib/Timer/Timer.c \
    ../../../geoCalcCore/src/geoCalc/lib/Trigger/Trigger.c
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
    ../../../geoCalcCore/src/geoCalc/rtdb/BinTree.h \
    ../../../geoCalcCore/src/geoCalc/rtdb/CapiGlobal.h \
    ../../../geoCalcCore/src/geoCalc/rtdb/helper.h \
    ../../../geoCalcCore/src/geoCalc/rtdb/RBTree.h \
    ../../../geoCalcCore/src/geoCalc/rtdb/rtdb.h \
    ../../../geoCalcCore/src/geoCalc/rtdb/station.h
FORMS += 
RESOURCES += resource.qrc \
    images.qrc
OTHER_FILES +=


#set macro define in the project
DEFINES += WIN32_LEAN_AND_MEAN

#this source files and header files  may be add something by yourself
INCLUDEPATH += ../../../geoCalcCore/include

#set other lib dir if you need
QMAKE_LIBDIR +=

LIBS +=


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
    ../../../geoCalcCore/src/geoCalc/lib/Bistable/RS \
    ../../../geoCalcCore/src/geoCalc/lib/Bistable/SR \
    ../../../geoCalcCore/src/geoCalc/lib/Comm/RG_BOOL \
    ../../../geoCalcCore/src/geoCalc/lib/Comm/RG_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comm/RG_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comm/WG_BOOL \
    ../../../geoCalcCore/src/geoCalc/lib/Comm/WG_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comm/WG_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/EQ_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/EQ_LREAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/EQ_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/GE_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/GE_LREAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/GE_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/GT_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/GT_LREAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/GT_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/LE_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/LE_LREAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/LE_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/LT_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/LT_LREAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/LT_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/NE_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/NE_LREAL \
    ../../../geoCalcCore/src/geoCalc/lib/Comparison/NE_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Control/BALANCE \
    ../../../geoCalcCore/src/geoCalc/lib/Control/DDS \
    ../../../geoCalcCore/src/geoCalc/lib/Control/DIFF \
    ../../../geoCalcCore/src/geoCalc/lib/Control/ES_MA \
    ../../../geoCalcCore/src/geoCalc/lib/Control/FILTER \
    ../../../geoCalcCore/src/geoCalc/lib/Control/FIRST \
    ../../../geoCalcCore/src/geoCalc/lib/Control/HL_ALM \
    ../../../geoCalcCore/src/geoCalc/lib/Control/HL_LMT \
    ../../../geoCalcCore/src/geoCalc/lib/Control/INTEG \
    ../../../geoCalcCore/src/geoCalc/lib/Control/LEADLAG \
    ../../../geoCalcCore/src/geoCalc/lib/Control/LIMV \
    ../../../geoCalcCore/src/geoCalc/lib/Control/PID \
    ../../../geoCalcCore/src/geoCalc/lib/Control/RAT_ALM \
    ../../../geoCalcCore/src/geoCalc/lib/Control/RAT_LMT \
    ../../../geoCalcCore/src/geoCalc/lib/Control/RMP \
    ../../../geoCalcCore/src/geoCalc/lib/Control/SFT_BOOL \
    ../../../geoCalcCore/src/geoCalc/lib/Control/SFT_REAL \
    ../../../geoCalcCore/src/geoCalc/lib/Control/SS_MA \
    ../../../geoCalcCore/src/geoCalc/lib/Control/TOTALIZER \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/B2DT \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/B2I \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/B2LR \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/B2R \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/DT2B \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/DT2I \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/DT2LR \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/DT2R \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/I2B \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/I2DT \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/I2LR \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/I2R \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/LR2B \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/LR2DT \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/LR2I \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/LR2R \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/R2B \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/R2DT \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/R2I \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/R2LR \
    ../../../geoCalcCore/src/geoCalc/lib/Converter/SCALING \
    ../../../geoCalcCore/src/geoCalc/lib/Counter/CTUD_INT \
    ../../../geoCalcCore/src/geoCalc/lib/Driver/D_AS_VAL \
    ../../../geoCalcCore/src/geoCalc/lib/Driver/D_DS_VAL \
    ../../../geoCalcCore/src/geoCalc/lib/Driver/D_DT_VAL \
    ../../../geoCalcCore/src/geoCalc/lib/Driver/MTR_LGE \
    ../../../geoCalcCore/src/geoCalc/lib/Driver/MTR_LTE \
    ../../../geoCalcCore/src/geoCalc/lib/Driver/S_E_VAL \
    ../../../geoCalcCore/src/geoCalc/lib/IO/DM1x1 \
    ../../../geoCalcCore/src/geoCalc/lib/IO/DM2x1 \
    ../../../geoCalcCore/src/geoCalc/lib/IO/DM3x1 \
    ../../../geoCalcCore/src/geoCalc/lib/IO/DM4x1 \
    ../../../geoCalcCore/src/geoCalc/lib/Logic/AND \
    ../../../geoCalcCore/src/geoCalc/lib/Logic/AND4 \
    ../../../geoCalcCore/src/geoCalc/lib/Logic/NOT \
    ../../../geoCalcCore/src/geoCalc/lib/Logic/OR \
    ../../../geoCalcCore/src/geoCalc/lib/Logic/OR4 \
    ../../../geoCalcCore/src/geoCalc/lib/Logic/XOR \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/ABS \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/ACOS \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/ASIN \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/ATAN \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/AVE4W \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/COS \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/EXP \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/FUN12 \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/LN \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/LOG \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/MOD \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/POLYNOM \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/SIN \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/SQRT \
    ../../../geoCalcCore/src/geoCalc/lib/Maths/TAN \
    ../../../geoCalcCore/src/geoCalc/lib/Selection/SIX_SEL_N \
    ../../../geoCalcCore/src/geoCalc/lib/Selection/THRSEL \
    ../../../geoCalcCore/src/geoCalc/lib/Selection/TWOSEL \
    ../../../geoCalcCore/src/geoCalc/lib/System/SysState \
    ../../../geoCalcCore/src/geoCalc/lib/Timer/DELAY \
    ../../../geoCalcCore/src/geoCalc/lib/Timer/SPO \
    ../../../geoCalcCore/src/geoCalc/lib/Timer/TOFF \
    ../../../geoCalcCore/src/geoCalc/lib/Timer/TON \
    ../../../geoCalcCore/src/geoCalc/lib/Timer/TP \
    ../../../geoCalcCore/src/geoCalc/lib/Trigger/D_TRIG \
    ../../../geoCalcCore/src/geoCalc/lib/Trigger/U_TRIG
