
################################################################################
# ���ļ�ΪQT ͨ�ù������� Ŀ¼ģ�壬������linux��windows��
# ��ģ����Է��������QT�������̣�ע����UTF-8����
# ʹ�÷���������QT���̣���pro�ļ�ͷ����prefix.pri����pro�ļ�ĩβ����postfix.pri
# �����ڶ����������е������Ŀ��������������Ŀ��ÿ������Ŀ�����ô�ģ��
# ��ģ���ص㣺1 �����Լ������Ĵ������������Դ�򲻿�Դ�����ÿ�
#           2 ��vs2015��eclipse��QT ������һ�µ�Ŀ¼�ṹ
#           3 �м�����ļ���Դ����룬����汾����svnֻ����Դ��
#           4 �Զ���������м����,
#
#
#
# ���� George-Kuo  guooujie@163.com
# �汾      ʱ��             �޸�����
# ��һ��    2013-08-03       ����������Ŀ¼
# �ڶ���    2016-07-21       ����qt5�޸�һ������
#
#
#Ŀ¼�ṹ����
#--+WorkSpace                       ***************************     �����ռ䣬����Ŀ����Ŀ¼
#
#   ---+ Project 1                  ***************************     ����Ŀ
#
# 	--+ bin                     ***************************     �����̵����յ��Ժ�����Ŀ��·������Debug��Release
#		---Debug
#		---Release
#	--+ inlcude                 ***************************     ��������ͷ�ļ�Ŀ¼������Դ��ĵ��������ͷ�ļ������ڴ˰������ɷֱ������ļ��У�
#		--+ model 1
#		--+ model 2
#		--+ others
#		--- .....
#	--+ 3rd                     ***************************     ��Դ��ĵ�������Ŀ¼��������������Ժͱ��빤�߲�ȷ�������������Դ�����
#	--+ docs                    ***************************     �������ɵ�ע���ļ�Ŀ¼
#	--+ lib                     ***************************     ����Դ��ĵ�������Ŀ¼����Debug��Release
#		---Debug
#		---Release
#	--+ other                   ***************************     �����ļ�Ŀ¼
#	--+ res                     ***************************     ��Դ�ļ�Ŀ¼��ͼƬ��ͼ�ꡢ��������Ƶ�ȣ���ԴĿ¼һ���ڸ���ģ�����Խ���
#		--icon
#		--graph
#	--+ sample                  ***************************     �������Ŀ¼
#	--+ setup                   ***************************     ��װ��ص�Դ����߽ű�Ŀ¼
#
#	--+ src                     ***************************     Դ��Ŀ¼����ģ����
#
#		---model 1(.pro)    ***************************     pro�ļ��ڴˣ�������
#		---model 2
#		---model 3
#		--- ......
#	--+ temp                    ***************************     �м��ļ�Ŀ¼�����ֱ�����̺����ӹ���
#		---Compile
#		---Link
#	--+ test                    ***************************     ���Դ���Ŀ¼�������ģ�鴦��
#	--+ tools                   ***************************     ��Ŀ��������Ŀ¼
################################################################################


################################################################################
#����ȫ�ֵ�Ŀ¼����
#���Ŀ¼�����ڵ�ǰ·��(PWD)
################################################################################
PROJECT_DIR = $$dirname(_PRO_FILE_PWD_)
PROJECT_DIR = $$dirname(PROJECT_DIR)                 # ��Ŀ��Ŀ¼��pwd��������Ŀ¼�� ./Project =../../pro
PROJECT_INC = $$join(PROJECT_DIR,,,/include)
PROJECT_3RD = $$join(PROJECT_DIR,,,/3rd)
PROJECT_BIN = $$join(PROJECT_DIR,,,/bin )
PROJECT_LIB = $$join(PROJECT_DIR,,,/lib )
PROJECT_TMP = $$join(PROJECT_DIR,,,/temp )
PROJECT_REC = $$join(PROJECT_DIR,,,/res )
PROJECT_SRC = $$join(PROJECT_DIR,,,/src )
PROJECT_SAM = $$join(PROJECT_DIR,,,/sample )
PROJECT_TLS = $$join(PROJECT_DIR,,,/tools )
PROJECT_STP = $$join(PROJECT_DIR,,,/setup )


message("source dir :$$PROJECT_SRC")
message("pro file dir :$$_PRO_FILE_PWD_")
message("QT lib version :$$QT_VERSION")

#���ð汾
windows:VERSION = 2.2.3.4 # major.minor.patch.build
else:VERSION = 2.2.3    # major.minor.patch
#���ò�Ʒ����
QMAKE_TARGET_PRODUCT = test product
#���ù�˾
QMAKE_TARGET_COMPANY = microsoft
#�����ļ�����
QMAKE_TARGET_DESCRIPTION =  template
#���ð�Ȩ
QMAKE_TARGET_COPYRIGHT = George-Kuo Copyright

message("Product Version is:$$VERSION ")
#usr define variables
UNUSED =

################################################################################
#����һЩ�ļ��м��ļ�����shell����
#����Ŀ¼���ļ��Զ�����
################################################################################
windows:{
    USR_FILE_CP  = copy /y
    USR_DIR_CP   = xcopy  /s /q /y /i          #����windows���ļ��п�������
    USR_DEL_FILE = del
    USR_DEL_DIR  = rmdir
    USR_MOVE     = move
    USR_MKDIR    = mkdir                       #����windows���ļ�����������

}
unix:{
    USR_FILE_CP  = cp -f
    USR_DIR_CP   = cp  -rf          #����linux���ļ��п�������
    USR_DEL_FILE = rm -f
    USR_DEL_DIR  = rm -rf
    USR_MOVE     = mv -f
    USR_MKDIR    = mkdir -p         #����linux���ļ�����������

}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

