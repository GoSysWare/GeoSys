
################################################################################
# NOTE:此处设置为自动处理，设置编译后的目录和文件，禁止修改
#add postfix 'd' to target filename on windows or '_debug' on mac OS
CONFIG(release, debug|release):{
     CONFIG_FLAG = Release
}
CONFIG(debug, debug|release):{
     CONFIG_FLAG = Debug
     mac: TARGET = $$join(TARGET,,,_debug)
     win32: TARGET = $$join(TARGET,,,d)
}
message("PROJECT configure style :$$CONFIG_FLAG")


#设置生成目标到./bin/Debug 或./bin/Release 下
DESTDIR = $$join(PROJECT_BIN,,,/$$CONFIG_FLAG)
#不存在则自动创建文件夹
!exists($$DESTDIR){
    message("dest dir is not existsed:$$DESTDIR create it!")
    system($$USR_MKDIR $$DESTDIR)
}
# 设置和自动创建编译、链接的中间文件夹
TEMP_COMPILE_DIR = $$join(PROJECT_TMP,,,/Compile)
TEMP_COMPILE_DIR = $$join(TEMP_COMPILE_DIR,,,/$$join(TARGET,,,/$$CONFIG_FLAG))

!exists($$TEMP_COMPILE_DIR){
    message("dest dir is not existsed:$$TEMP_COMPILE_DIR")
    system($$USR_MKDIR $$TEMP_COMPILE_DIR)
}
#设置QT生成makefile文件的目录
OUT_PWD = $$TEMP_COMPILE_DIR

message("makefile  dir: $$OUT_PWD")
#设置默认的共享库链接地址
QMAKE_LIBDIR += $$join(PROJECT_LIB,,,/$$CONFIG_FLAG)\
                $$join(PROJECT_BIN,,,/$$CONFIG_FLAG)
#设置默认的头文件包含地址
INCLUDEPATH += $$PROJECT_INC
INCLUDEPATH += $$PROJECT_DIR/src/include
INCLUDEPATH += $$_PRO_FILE_PWD_/include
DEPENDPATH  +=
message("includes  dir: $$INCLUDEPATH")


################################################################################
#共享库自动处理
#如果是windows，将所有的共享库自动连接尾缀为d，这样在LIB中可以无区别编写
#CONFIG(debug, debug|release):windows:{
#     tempval = $$find(LIBS,"-l")
#     for(val,tempval){
#            LIBS -= $$val
#            val = $$join(val,,,d)
#            LIBS += $$val
#        }
#     message("POST LIBS is : $$LIBS")
#}

#指定rcc命令将.qrc文件转换成qrc_*.h文件的存放目录
RCC_DIR +=$$PROJECT_REC

windows:{
    #应用程序的资源文件
    RC_FILE +=
    #.def文件
    DEF_FILE +=
    #应用程序所要连接的资源文件
    RES_FILE +=
    message("Windows Version RC file:$$RC_FILE ")
}




#指定moc命令将含Q_OBJECT的头文件转换成标准.h文件的存放目录
MOC_DIR = $$TEMP_COMPILE_DIR

#指定uic命令将.ui文件转化成ui_*.h文件的存放的目录
UI_DIR = $$TEMP_COMPILE_DIR

#指定目标文件(obj)的存放目录
OBJECTS_DIR = $$TEMP_COMPILE_DIR

#if usr cmd 'make - install',set install dir
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
OTHER_FILES +=
