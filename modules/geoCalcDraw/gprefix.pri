
################################################################################
# 本文件为QT 通用工程设置 目录模板，适用于linux和windows下
# 此模板可以方便的利用QT建立工程，注意用UTF-8保存
# 使用方法，建立QT工程，在pro文件头包含prefix.pri，在pro文件末尾包含postfix.pri
# 适用于独立调试运行的软件项目，如果是软件大项目，每个子项目可以用此模板
# 本模板特点：1 区分自己开发的代码与第三方开源或不开源的引用库
#           2 在vs2015、eclipse、QT 下做到一致的目录结构
#           3 中间编译文件与源码分离，方便版本管理svn只处理源码
#           4 自动处理编译中间过程,
#
#
#
# 作者 George-Kuo  guooujie@163.com
# 版本      时间             修改内容
# 第一版    2013-08-03       建立基本的目录
# 第二版    2016-07-21       根据qt5修改一下配置
#
#
#目录结构如下
#--+WorkSpace                       ***************************     工作空间，大项目的总目录
#
#   ---+ Project 1                  ***************************     子项目
#
# 	--+ bin                     ***************************     本工程的最终调试和运行目标路径，分Debug和Release
#		---Debug
#		---Release
#	--+ inlcude                 ***************************     公共包含头文件目录，不带源码的第三方库的头文件建议在此包含，可分别设子文件夹，
#		--+ model 1
#		--+ model 2
#		--+ others
#		--- .....
#	--+ 3rd                     ***************************     带源码的第三方库目录，第三方库的语言和编译工具不确定，第三方库的源码编译
#	--+ docs                    ***************************     代码生成的注释文件目录
#	--+ lib                     ***************************     不带源码的第三方库目录，分Debug和Release
#		---Debug
#		---Release
#	--+ other                   ***************************     其他文件目录
#	--+ res                     ***************************     资源文件目录：图片、图标、声音、视频等，资源目录一般在各个模块下自建立
#		--icon
#		--graph
#	--+ sample                  ***************************     样例相关目录
#	--+ setup                   ***************************     安装相关的源码或者脚本目录
#
#	--+ src                     ***************************     源码目录，分模块存放
#
#		---model 1(.pro)    ***************************     pro文件在此！！！！
#		---model 2
#		---model 3
#		--- ......
#	--+ temp                    ***************************     中间文件目录，区分编译过程和链接过程
#		---Compile
#		---Link
#	--+ test                    ***************************     测试代码目录，建议分模块处理
#	--+ tools                   ***************************     项目开发工具目录
################################################################################


################################################################################
#设置全局的目录变量
#这个目录依赖于当前路径(PWD)
################################################################################
PROJECT_DIR = $$dirname(_PRO_FILE_PWD_)
PROJECT_DIR = $$dirname(PROJECT_DIR)                 # 项目根目录是pwd的上两级目录： ./Project =../../pro
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

#设置版本
windows:VERSION = 2.2.3.4 # major.minor.patch.build
else:VERSION = 2.2.3    # major.minor.patch
#设置产品名称
QMAKE_TARGET_PRODUCT = test product
#设置公司
QMAKE_TARGET_COMPANY = microsoft
#设置文件描述
QMAKE_TARGET_DESCRIPTION =  template
#设置版权
QMAKE_TARGET_COPYRIGHT = George-Kuo Copyright

message("Product Version is:$$VERSION ")
#usr define variables
UNUSED =

################################################################################
#设置一些文件夹及文件操作shell命令
#用作目录和文件自动操作
################################################################################
windows:{
    USR_FILE_CP  = copy /y
    USR_DIR_CP   = xcopy  /s /q /y /i          #设置windows下文件夹拷贝命令
    USR_DEL_FILE = del
    USR_DEL_DIR  = rmdir
    USR_MOVE     = move
    USR_MKDIR    = mkdir                       #设置windows下文件夹生成命令

}
unix:{
    USR_FILE_CP  = cp -f
    USR_DIR_CP   = cp  -rf          #设置linux下文件夹拷贝命令
    USR_DEL_FILE = rm -f
    USR_DEL_DIR  = rm -rf
    USR_MOVE     = mv -f
    USR_MKDIR    = mkdir -p         #设置linux下文件夹生成命令

}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

