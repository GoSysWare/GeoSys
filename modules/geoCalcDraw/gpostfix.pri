
################################################################################
# NOTE:�˴�����Ϊ�Զ��������ñ�����Ŀ¼���ļ�����ֹ�޸�
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


#��������Ŀ�굽./bin/Debug ��./bin/Release ��
DESTDIR = $$join(PROJECT_BIN,,,/$$CONFIG_FLAG)
#���������Զ������ļ���
!exists($$DESTDIR){
    message("dest dir is not existsed:$$DESTDIR create it!")
    system($$USR_MKDIR $$DESTDIR)
}
# ���ú��Զ��������롢���ӵ��м��ļ���
TEMP_COMPILE_DIR = $$join(PROJECT_TMP,,,/Compile)
TEMP_COMPILE_DIR = $$join(TEMP_COMPILE_DIR,,,/$$join(TARGET,,,/$$CONFIG_FLAG))

!exists($$TEMP_COMPILE_DIR){
    message("dest dir is not existsed:$$TEMP_COMPILE_DIR")
    system($$USR_MKDIR $$TEMP_COMPILE_DIR)
}
#����QT����makefile�ļ���Ŀ¼
OUT_PWD = $$TEMP_COMPILE_DIR

message("makefile  dir: $$OUT_PWD")
#����Ĭ�ϵĹ�������ӵ�ַ
QMAKE_LIBDIR += $$join(PROJECT_LIB,,,/$$CONFIG_FLAG)\
                $$join(PROJECT_BIN,,,/$$CONFIG_FLAG)
#����Ĭ�ϵ�ͷ�ļ�������ַ
INCLUDEPATH += $$PROJECT_INC
INCLUDEPATH += $$PROJECT_DIR/src/include
INCLUDEPATH += $$_PRO_FILE_PWD_/include
DEPENDPATH  +=
message("includes  dir: $$INCLUDEPATH")


################################################################################
#������Զ�����
#�����windows�������еĹ�����Զ�����β׺Ϊd��������LIB�п����������д
#CONFIG(debug, debug|release):windows:{
#     tempval = $$find(LIBS,"-l")
#     for(val,tempval){
#            LIBS -= $$val
#            val = $$join(val,,,d)
#            LIBS += $$val
#        }
#     message("POST LIBS is : $$LIBS")
#}

#ָ��rcc���.qrc�ļ�ת����qrc_*.h�ļ��Ĵ��Ŀ¼
RCC_DIR +=$$PROJECT_REC

windows:{
    #Ӧ�ó������Դ�ļ�
    RC_FILE +=
    #.def�ļ�
    DEF_FILE +=
    #Ӧ�ó�����Ҫ���ӵ���Դ�ļ�
    RES_FILE +=
    message("Windows Version RC file:$$RC_FILE ")
}




#ָ��moc�����Q_OBJECT��ͷ�ļ�ת���ɱ�׼.h�ļ��Ĵ��Ŀ¼
MOC_DIR = $$TEMP_COMPILE_DIR

#ָ��uic���.ui�ļ�ת����ui_*.h�ļ��Ĵ�ŵ�Ŀ¼
UI_DIR = $$TEMP_COMPILE_DIR

#ָ��Ŀ���ļ�(obj)�Ĵ��Ŀ¼
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
