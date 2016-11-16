/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                      *
*                                                                            *
*  @file     geoError.h                                                     *
*  @brief    GeoSys 平台错误码处理                             *
*
*	错误码分配如下
*	画面组态工具-40000 ~ -39500	HMI运行主界面	-39500~ -39000
*	流程图显示	-39000~ -38500	报警显示模块	-38500~ -38000
*	I&C故障显示	-38000~ -37500	日志模块	-37500~ -37000
*	规程模块	-37000~ -36500	挂牌模块	-36500~ -36000
*	趋势模块	-36000~ -35500	当前值模块	-35500~ -35000
*	趋势模块	-35000~ -34500	打印模块	-34500~ -34000
*	权限模块	-34000~ -33500	工况模块	-33500~ -33000
*	状态列表模块	-33000~ -32500	在线记事本	-32500~ -32000
*	POP模块	-32000~ -31500	在线帮组	-31500~ -31000
*	操作员报告	-31000~ -30500	系统操作模块	-30500~ -30000
*	核电专有功能模块	-30000~ -29500	HMI预留	-29500~ -20000
*	实时库内核	-20000~ -19500	历史库内核	-19500~ -19000
*	历史存储	-19000~ -18500	权限服务	-18500~ -18000
*	报警服务	-18000~ -17500	事件记录	-17500~ -17000
*	计算内核	-17000~ -16500	网络组件	-16500~ -16000
*	挂牌服务	-16000~ -15500	IOSS	-15500~ -15000
*	数据库预留	-10000~ -5000
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         :									                         *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/10/14 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_UTILS_ERROR_H__
#define  GEOSYS_UTILS_ERROR_H__


typedef enum
{
	geoERR_COMMON_MIN = -5000,					// 程序常见的错误起始码
	geoERR_COMMON_NO_MEMORY,
	geoERR_COMMON_DATATYPE,
	geoERR_COMMON_DATACHANGE_FAIL,
	geoERR_COMMON_PARAMETER_INVALID,
	geoERR_COMMON_FILE_NOT_EXIST,
	geoERR_COMMON_MAX = -4000,					// 程序常见的错误最大码
} geoErrorCode_COMMON;



typedef enum
{
	geoERR_DB_MIN = -10000,						// 数据库通用起始错误码
	geoERR_DB_VERSION_DIFFRENT,					// 数据库版本不一致

	geoERR_DB_MAX = -5000,						// 数据库通用最大错误码
} geoErrorCode_DB;


typedef enum
{
	geoERR_RTDB_MIN = -20000,						// 实时库起始错误码
	geoERR_RTDB_COMMON = geoERR_RTDB_MIN,			// 实时库全局通用错误码，不想具体定义的错误都可以用此错误码
	///
	geoERR_TAG_MIN = -19900,						//标签相关的错误码
	geoERR_TAG_COMMON = geoERR_TAG_MIN,				//标签全局通用错误码，不想具体定义的错误都可以用此错误码
	geoERR_TAG_DATAFILE_CREATE,						//标签数据配置文件创建失败
	geoERR_TAG_DATAFILE_OPEN,						//标签数据配置文件打开失败
	geoERR_TAG_DATAFILE_SAVE,						//标签数据配置文件保存写入失败
	geoERR_TAG_DATAFILE_NOTEXIST,
	geoERR_TAG_INFOFILE_CLOSE,
	geoERR_TAG_COUNT_OVERFLOW,
	geoERR_TAG_NOT_EXIST,
	geoERR_TAG_NAME_REDUPLICATE,
	geoERR_TAG_NAME_NOT_EXIST,
	geoERR_DEVICE_ID_REDUPLICATE,
	geoERR_TAG_NAMEHASH_FAILTURE,
	geoERR_SYSTEM_PROP_GET,
	geoERR_SYSTEM_PROP_SET,
	geoERR_DEVICE_ADD,
	geoERR_DEIVCE_PROP_GET,
	geoERR_DEIVCE_PROP_SET,
	geoERR_TAG_LACK_PROP,
	geoERR_TAG_WRONG_NAME,
	geoERR_SYSTEM_NOT_EXIST,
	geoERR_SYSTEM_ROOT_DELETE,
	geoERR_TAG_PROP_FILTER,
	geoERR_TAG_PROP_CANNOT_CHANGE,
	geoERR_TAG_PROP_NOT_CHANGED,
	geoERR_TAG_DATATYPE,
	geoERR_TAG_DATATYPE_HAS_SET,
	geoERR_TAG_UNITNO_OVERFLOW,
	geoERR_TAG_COMPRESS_OVERRUN,
	geoERR_TAG_CREATETIME_HAS_SET,
	geoERR_TAG_PROP_GET,
	geoERR_TAG_PROP_SET,
	geoERR_TAG_PROP_REDUPLICATE,
	geoERR_FAIL_IN_BATCH,
	geoERR_TAG_RETRIEVAL_TYPE,
	geoERR_TAG_RETRIEVAL,
	geoERR_TAG_CONFIGFILE_SAVE,
	geoERR_TAG_HAS_DELETED,
	geoERR_DB_ANAPROP_NOT_CHANGED,
	geoERR_TAGEXTEND_PROP_NOT_EXIST,
	geoERR_DB_ANAPROP_CANNOT_CHANGE,
	geoERR_DB_DIGPROP_CANNOT_CHANGE,
	geoERR_DB_RESTRAINPROP_NOT_CHANGED,
	geoERR_COMMON_STARTDB_FAIL,
	geoERR_TAG_FLAG,
	geoERR_TAG_CANNOT_COPY,
	geoERR_RTDB_PROXY_MIN = -19900,					//实时库接口代码相关的错误码

	geoERR_RTDB_MAX = -19500,						//实时库最大错误码
}geoErrorCode_RTDB;

typedef enum
{
	geoERR_HISD_MIN = -19500,						// 历史库起始错误码
	geoERR_HISD_COMMON = geoERR_HISD_MIN,			// 历史库全局通用错误码，不想具体定义的错误都可以用此错误码
													//
													geoERR_HISD_MAX = -19000,						//历史库最大错误码

}geoErrorCode_HISD;

typedef enum
{
	geoERR_RECD_MIN = -19000,						// 历史存储起始错误码
	geoERR_RECD_COMMON = geoERR_RECD_MIN,			// 历史存储全局通用错误码，不想具体定义的错误都可以用此错误码
													///
													geoERR_RECD_MAX = -18500,						//历史存储最大错误码

}geoErrorCode_Record;
typedef enum
{
	geoERR_USERS_MIN = -18500,						// 用户权限起始错误码
	geoERR_USERS_COMMON = geoERR_USERS_MIN,			// 用户权限全局通用错误码，不想具体定义的错误都可以用此错误码
													///
													geoERR_USERS_MAX = -18000,						//用户权限最大错误码

}geoErrorCode_UERS;
typedef enum
{
	geoERR_ALARM_MIN = -18000,						// 报警起始错误码
	geoERR_ALARM_COMMON = geoERR_ALARM_MIN,			// 报警全局通用错误码，不想具体定义的错误都可以用此错误码
													///
	geoERR_ALARM_MAX = -17500,						//报警最大错误码

}geoErrorCode_Alarm;
typedef enum
{
	geoERR_LOG_MIN = -17500,						// 事件起始错误码
	geoERR_LOG_COMMON = geoERR_LOG_MIN,				// 事件全局通用错误码，不想具体定义的错误都可以用此错误码
													///
	geoERR_LOG_MAX = -17000,						//事件最大错误码

}geoErrorCode_LOG;
typedef enum
{
	geoERR_CALC_MIN = -17000,						// 计算起始错误码
	geoERR_CALC_COMMON = geoERR_CALC_MIN,			// 计算全局通用错误码，不想具体定义的错误都可以用此错误码
													///
	geoERR_CALC_MAX = -16500,						//计算最大错误码

}geoErrorCode_CALC;
typedef enum
{
	geoERR_NET_MIN = -16500,						// 网络组件起始错误码
	geoERR_NET_COMMON = geoERR_NET_MIN,				// 网络组件全局通用错误码，不想具体定义的错误都可以用此错误码
													///
	geoERR_VBUS_COMMON = -16400,						// VBUS全局通用错误码，不想具体定义的错误都可以用此错误码

																										///
	geoERR_TCP_CLIENT_NEED_RESET = -16322,
	geoERR_TCP_NEW_SEND_THREAD = -16321,
	geoERR_TCP_RECVN_FAILED = -16320,
	geoERR_TCP_SENDN_ERR = -16319,
	geoERR_TCP_CONNECT_FAILED = -16318,
	geoERR_TCP_SYS_STATUS_ERR = -16317,
	geoERR_TCP_MAPUNBIND = -16316,
	geoERR_TCP_MQ_SHUTDOWN = -16315,
	geoERR_TCP_GETQ_TIMEOUT = -16314,
	geoERR_TCP_CALLBACK_FUNCTION_SEND = -16313,
	geoERR_TCP_REGISTER_CALLBACK_FAIL = -16312,
	geoERR_TCP_NO_MQ = -16311,
	geoERR_TCP_CONNECTING = -16310,
	geoERR_TCP_API_CONNECT_NOT_FOUND = -16309,
	geoERR_TCP_CONNECT_NOT_FOUND = -16308,
	geoERR_TCP_MAX_CONNECTION = -16307,
	geoERR_TCP_NOHANDLE_FIND = -16306,
	geoERR_TCP_CONNECT_HASHMAP_ERROR = -16305,		//连接的HASH_MAP绑定、解绑或查找错误
	geoERR_TCP_CONNECTMGR_STOPED = -16304,				//
	geoERR_TCP_PARA_FILE_FAIL = -16303,				//RPC服务端客户ID配置文件错误
	geoERR_TCP_START_ERROR = -16302,
	geoERR_TCP_STATUS_BUSY = -16301,					//接口服务忙
	geoERR_TCP_COMMON = -16300,						// TCP全局通用错误码，不想具体定义的错误都可以用此错误码


	geoERR_NET_MAX = -16000,						//网络组件最大错误码

}geoErrorCode_NET;
typedef enum
{
	geoERR_HANG_MIN = -16000,						// 挂牌起始错误码
	geoERR_HANG_COMMON = geoERR_HANG_MIN,			// 挂牌全局通用错误码，不想具体定义的错误都可以用此错误码
													///
													geoERR_HANG_MAX = -15500,						//挂牌最大错误码

}geoErrorCode_HANG;
typedef enum
{
	geoERR_IOSS_MIN = -15500,						// IOSS起始错误码
	geoERR_IOSS_COMMON = geoERR_IOSS_MIN,			// IOSS全局通用错误码，不想具体定义的错误都可以用此错误码
	///
	geoERR_IOSS_OBJECT_NOT_FOUND,
	geoERR_IOSS_DEVICE_NOT_STARTED,
	geoERR_IOSS_DRIVER_NOT_LOADED,

	geoERR_IOSS_DPU_COMMON = -15400,				//DPU驱动错误码
	geoERR_IOSS_SETTYPE_NOT_SUPPORTED,
	geoERR_IOSS_CURSOR_NOT_FOUND,
	geoERR_IOSS_SENDBUF_NOT_FOUND,
	geoERR_IOSS_DEVICE_NOT_CONNECTED,
	geoERR_IOSS_NO_VALID_HANDLE,
	geoERR_IOSS_SOCKET_SEND_FAIL,
	geoERR_IOSS_SEND_LENGTH_NOT_MATCH,

	geoERR_IOSS_MAX = -15000,						//IOSS最大错误码

}geoErrorCode_IOSS;

typedef enum
{
	geoERR_SOUND_MIN = -15000,						// 声音起始错误码
	geoERR_SOUND_COMMON = geoERR_SOUND_MIN,			// 声音全局通用错误码，不想具体定义的错误都可以用此错误码
													///
	geoERR_SOUND_MAX = -14500,						//声音最大错误码

}geoErrorCode_SOUND;
//
//typedef enum
//{
//	geoERR_DB_MIN = -20000 ,						// 实时库库错误码起始地址
//
//	geoERR_COMMON_BASE = -20000 ,				// 实时库通用错误
//
//	geoERR_DB_CANNOT_START_BASE,                 //实时库基本属性模块无法启动
//	geoERR_DB_CANNOT_START_DIGITAL,            //实时库开关量模块无法启动
//	geoERR_DB_CANNOT_START_ANALOG,				//实时库模拟量模块无法启动
//	geoERR_DB_CANNOT_START_REAL,					//实时库实时值部分无法启动
//	geoERR_DB_CANNOT_START_NOTIFY,				//实时库通知模块无法启动
//
//	geoERR_DB_CANNOT_STOP,                            //实时库无法正常停止
//	geoERR_DB_CANNOT_STOP_BASE,					//实时库基本属性模块停止出错
//	geoERR_DB_CANNOT_STOP_DIGITAL,              //实时库开关量模块停止出错
//	geoERR_DB_CANNOT_STOP_ANALOG,              //实时库模拟量模块停止出错
//	geoERR_DB_CANNOT_STOP_REAL,                  //实时库实时值部分停止出错
//	geoERR_DB_CANNOT_STOP_NOTIFY,			   //实时库通知模块停止出错
//
//
//	geoERR_TAG_COUNT_OVERFLOW,					//实时库标签数目超出许可
//	geoERR_TAG_INFOFILE_NOTEXIST,				//实时库系统信息文档不存在
//	geoERR_TAG_DATAFILE_NOTEXIST,				//实时库标签点配置信息文档不存在
//
//
//
//	geoERR_TCP_CALLBACK_FUNCTION_SEND ,				// 功能未实现
//	geoERR_COMMON_PARAMETER_INVALID ,					// 参数错误
//	geoERR_FAIL_IN_BATCH ,						// 操作集中有部分操作出错，部分成功
//	geoERR_COMMON_NO_MEMORY ,							// 无足够内存空间
//	geoERR_COMMON_NO_AUHTORITY,							// 无操作权限
//	geoERR_COMMON_STRING_TOO_LONG,						// 字符串太长
//	geoERR_COMMON_DATACHANGE_FAIL,                       // 数据转换出错
//	geoERR_TCP_NO_MQ,									// 同步操作没有发现相关消息队列
//
//	geoERR_INTERFACE_BASE = -19900 ,						// 接口动态库相关错误
//
//	geoERR_TCP_REGISTER_CALLBACK_FAIL,				// 回调函数注册失败
//
//	geoERR_NET_BASE = -19800 ,					// 通讯相关错误
//
//	geoERR_TCP_GETQ_TIMEOUT,						// 操作消息队列超时
//	geoERR_TCP_MQ_SHUTDOWN,						// 消息队列关闭
//	geoERR_TCP_MAPUNBIND,						// 连接信息解除绑定失败
//	geoERR_TCP_SYS_STATUS_ERR,						// 网络连接状态查找失败,没有对应的状态信息保存
//	geoERR_TCP_CONNECT_FAILED,					// 连接失败
//	geoERR_NET_SEndID_N_ERR,						// 发送失败
//	geoERR_TCP_RECVN_FAILED,                     // 接受失败
//	geoERR_NET_NEWTHREAD_SEndID_,					// 线程失败
//	geoERR_NET_NO_CONNECTED,						// 没有连接
//	geoERR_NET_NOHANDLE_FIND,					// 没有保存的handle信息
//	geoERR_TCP_MAX_CONNECTION,					// 最大连接数
//	geoERR_TCP_CLIENT_NEED_RESET,						// 服务器端已经重启，客户端需要重启
//	geoERR_TCP_CONNECTING,					//网络正在连接中
//
//	geoERR_SCHUDULER_BASE = -19700 ,				// 服务器相关错误
//
//	geoERR_SCHUDULER_STATUS_ERROR,				// 服务器处在错误状态
//	geoERR_SCHUDULER_STATUS_STOP,				// 服务器处在停止状态
//	geoERR_SCHUDULER_STATUS_BUSY,				// 服务器处在正忙状态
//	geoERR_TCP_PARA_FILE_FAIL,				// 调度模块读取配置文件失败
//	geoERR_TCP_CONNECT_HASHMAP_ERROR, 		// 读取hash表失败
//	geoERR_SCHEDULER_StartID__ERROR,				// 调度模块启动失败
//	geoERR_TCP_CONNECT_NOT_FOUND,  		// 调度模块中未发现连接信息
//	geoERR_TCP_API_CONNECT_NOT_FOUND,		// 调度模块中未发现应用连接
//	geoERR_TCP_CONNECT_NOT_FOUND,		// 调度模块中未发现网络连接
//	geoERR_TCP_CONNECTMGR_STOPED,					// 连接管理器已经停止
//
//	geoERR_TAGTYPEMANAGER_BASE = -19600 ,		// 测点类型相关错误
//
//	geoERR_TAGTYPEMANAGER_CANNOT_StartID_,			// 测点类型管理模块不能启动
//	geoERR_TAGTYPEMANAGER_MANAGER_FILE_NOT_FOUND,	// 测点类型管理文件不存在
//	geoERR_TAGTYPEMAMAGER_MAMAGER_FILE_FAIL,		// 测点类型管理文件错误
//	geoERR_TAGTYPEMANAGER_TOTAL_PROP_FILE_NOT_FOUND,	// 测点类型完整属性文件不存在
//	geoERR_TAGTYPEMANAGER_TOTAL_PROP_FILE_FAIL,		// 测点类型完整属性文件错误
//
//	geoERR_TAGTYPE_BASE = -19500 ,				// 测点类型相关错误
//
//	geoERR_TAGTYPE_CANNOT_SRART,					// 测点类型动态库不能启动
//	geoERR_TAGTYPE_HAVE_StartID_ED,					// 测点类型动态库已经启动
//	geoERR_TAGTYPE_INFO_FILE_FAIL,				// 测点类型信息文件错误
//	geoERR_TAGTYPE_PROP_FILE_FAIL,				// 测点类型属性文件错误
//
//	geoERR_TAG_BASE = -19400 ,					// 测点相关错误
//
//	geoERR_TAG_HAS_PARENT,						//
//	geoERR_TAG_WRONG_NAME,						//名字里的字符不合法
//	geoERR_TAG_ADD,								// 
//	geoERR_TAG_NAME,								// 
//	geoERR_TAGTREE_DEL,							// 
//	geoERR_TAG_GET_ID,							// 
//	geoERR_TAG_NAMEHASH_UNBIND,					// 
//	geoERR_TAG_GETLONGNAME,						// 
//	geoERR_TAG_NAMEHASH,							// 
//	geoERR_TAG_NAME_TOOLONG,						// 
//	geoERR_TAG_GETSHORTNAME,						// 
//	geoERR_TAGTREE_TRAVERSE,						// 
//	geoERR_TAG_ISANCESTOR,						// 
//	geoERR_TAG_INFOFILE,							// 不能打开测点信息文件
//	geoERR_TAG_DATAFILE,							// 不能打开测点数据文件
//	geoERR_TAG_DELETE_ROOT,						// 
//	geoERR_TAG_HAVE_DELETED,						// 测点已经被删除
//	geoERR_TAG_HAVE_CHILD,							//测点有子节点，不能被删除
//	geoERR_TAG_PROP_REDUPLICATE,					// 属性重复
//	geoERR_TAG_NAME_REDUPLICATE,					// 测点名称重复
//	geoERR_TAG_NAME_NOT_EXIST,					// 测点名不存在
//	geoERR_TAG_NAMEHASH_FAILURE,					// 名称HASH表出错
//	geoERR_TAG_NOT_NODE,							// 指定的点不是结点类型
//	geoERR_TAG_CANNOT_MOVE,						// 测点不能移动
//	geoERR_TAG_CANNOT_COPY,						// 测点不能复制
//	geoERR_TAG_NOT_EXIST,						// 测点不存在
//	geoERR_TAG_PROP_NOT_EXIST,					// 属性不存在
//	geoERR_TAG_PROP_NOT_CHANGED,					// 测点值未攺变
//	geoERR_TAG_PROP_FILTER,						// 测点值被过滤
//	geoERR_TAG_CANNOT_GETPROP,					// 不能读属性
//	geoERR_TAG_CANNOT_SETPROP,					// 不能写属性		
//	geoERR_TAG_LACK_PROP,						// 增加测点时缺少必要属性
//
//	geoERR_DATATYPE,								// 数据类型错误
//	geoERR_DATATYPE_NOT_MATCH,
//	geoERR_TAG_NOT_SAVE_HIS,
//
//	geoERR_TAGNOTIFY_BASE = -19300,
//
//	geoERR_TAGNOTIFY_SUBCRIBE_FAILED,			// 注册失败
//	geoERR_TAGNOTIFY_CANNOT_StartID_,				// 测点订阅发布模块不能启动
//	geoERR_TAGNOTIFY_SUBSCRIBE_MAP_ERROR,		// 测点订阅发布模块的订阅表错误
//	geoERR_TAGNOTIFY_PBULISH_MAP_ERROR,			// 测点订阅发布模块的发布者表错误
//	geoERR_TAGNOTIFY_TAG_NOT_SUBSCRIBED,			// 测点未被订阅
//	geoERR_TAGNOTIFY_CONNECT_NOT_FOUND,			// 连接不存在
//
//	geoERR_REAL_BASE = -19200 ,					// 实时相关错误
//
//	geoERR_REAL_CANNOT_READ,						// 不能读实时值
//	geoERR_REAL_CANNOT_WRITE,					// 不能写实时值
//	geoERR_REAL_DATA_FILE_FAIL,					// 实时数据保存文件错误
//
//	geoERR_REALNOTIFY_BASE = -19100 ,			// 实时相关错误
//
//	geoERR_REALNOTIFY_CANNOT_StartID_,				// 实时订阅发布模块不能启动
//	geoERR_REALNOTIFY_SUBSCRIBE_MAP_ERROR,		// 实时订阅发布模块的订阅表错误
//	geoERR_REALNOTIFY_PUBLISH_MAP_ERROR,			// 实时订阅发布模块的发布者表错误
//	geoERR_REALNOTIFY_TAG_NOTSUBSCRIBED,			// 实时未被订阅
//	geoERR_REALNOTIFY_CONNECT_NOT_FOUND,			// 连接不存在
//
//	geoERR_AUTHORITY_BASE = -19000,				// 权限相关错误
//
//	geoERR_AUTHORITY_SECURITY_AREA_NOT_MATCH,	// 安全区不匹配
//	geoERR_AUTHORITY_WRITE_READONLY_PROPERTY,	// 写只读属性
//	geoERR_TAG_BEYOND_MAX,						// 总点数超过授权
//	geoERR_LICENSE_UPDATA_ERROR,					// 更新License信息失败，停止运行（刚性保护）
//	geoERR_LICENSE_TYPE_NO,						// 没有任何许可证，Server停止运行。（刚性保护）
//	geoERR_LICENSE_DEMO_RUN_TIMEOUT,				// 演示版和开发试用版运行超时，Server停止运行。（刚性保护）
//	geoERR_LICENSE_NOT_PSPACE5,					// 没有获取pSpace 5.x版本的License，Server停止运行。（刚性保护）
//	geoERR_LICENSE_NOT_SIMPLIFIED_CHINESE,		// 没有获取简体中文版本的License，Server停止运行。（刚性保护）
//	geoERR_LICENSE_SITRAP_StartID_,					// SITrap启动。（刚性保护）
//	geoERR_LICENSE_CONNECT_BEYOND_USERAPP_MAX,	//用户自编写的应用程序客户端连接数超过限制值，不能再建立连接。（弹性保护）
//	geoERR_LICENSE_CONNECT_BEYOND_VIEW_MAX,		//View客户端数连接数超过限制值，不能再建立连接。（弹性保护）
//	geoERR_LICENSE_CONNECT_BEYOND_NETVIEW_MAX,	//NetView客户端数连接数超过限制值，不能再建立连接。（弹性保护）
//	geoERR_LICENSE_CONNECT_BEYOND_IO_MAX,		//NetView客户端数连接数超过限制值，不能再建立连接。（弹性保护）
//	geoERR_AUTHORITY_StartID__LICENSE_FAIL,			//启动License失败（刚性保护）
//	geoERR_LICENSE_EVALUATION_TIMEOUT,			//评估版运行超时（刚性保护）
//	geoERR_LICENSE_NO_EX_LICENSE,				//扩展组件没有License授权（弹性保护）
//
//	geoERR_HIS_BASE = -18900 ,					// 历史和历史文件相关错误
//
//	geoERR_HIS_NO_DISK_SPACE,					// 无足够磁盘空间
//	geoERR_HIS_CACHE_OPENED,					    // 缓冲区已经打开
//	geoERR_HIS_CACHE_CLOSED,						// 缓冲区没有打开
//	// 历史管理文件模块错误号
//	geoERR_HIS_NOT_INI_PATH,						// 没有初始化路径
//	geoERR_HIS_MANAGER_FILE_OPENED,				// 历史管理文件已经打开
//	geoERR_HIS_MANAGER_FILE_CLOSED,				// 历史管理文件没有打开
//	geoERR_HIS_DATA_FILE_IN_LIST,				// 文件已在历史数据文件列表，不能被注册
//	geoERR_HIS_MANAGER_FILE_VERSION,				// 管理文件文件版本无效
//	geoERR_HIS_MANAGER_FILE_LABEL,				// 管理文件文件标识无效
//	geoERR_HIS_MANAGER_FILE_INVALID,				// 管理文件文件格式错误
//	geoERR_HIS_UNREGIST_CURRENT_FILE,			// 不能注消当前文件
//	geoERR_HIS_BACKUP_CURRENT_FILE,				// 不能备份当前文件
//	geoERR_HIS_DATA_FILE_NO_DATA,				// 数据文件无数据，不能备份
//	geoERR_HIS_DATA_FILE_TIME_BEYOND,			// 恢复数据文件时，文件时间比当前时间还大，出错
//	geoERR_HIS_DATA_FILE_TIME_OVERLAP,			// 恢复数据文件时，文件时间与现有文件列表重叠
//	geoERR_HIS_DATA_FILE_COUNT_LESS,				// 在替换模式下，历史数据文件的数量过少
//	geoERR_HIS_CAN_NOT_REGIST,					// 不能注册
//	// 历史数据文件模块错误号
//	geoERR_HIS_DATA_FILE_VERSION,				// 管理文件文件版本无效
//	geoERR_HIS_DATA_FILE_LABEL,					// 管理文件文件标识无效
//	geoERR_HIS_CRC,					 		    // 校验错误
//	geoERR_HIS_PAGE_FULL,				 		// 页中数据满了
//	geoERR_HIS_DATA_PAGE_BEYOND_MIN,				// 查找时，时间比数据页内最小时间还小
//	geoERR_HIS_EndID__OF_INDEX_PAGE,					
//	geoERR_HIS_FILE_NOT_IN_LIST,					// 文件ID号在历史管理文件的数据文件列表中找不到
//	geoERR_HIS_SOME_DATA_NOT_SAVED,				// 还有一部分数据因为没有空间，不能插入
//	geoERR_HIS_NEED_PACK_DATA,					// 还余一部分空间，需要压缩历史数据
//	// 游标模块错误号
//	geoERR_HIS_FIND_ERROR,						// 查询出现异常情况
//	geoERR_HIS_BEYOND_MIN,					 	// 比第一个数据的时间还小
//	geoERR_HIS_BEYOND_MAX, 			 			// 比最后一个数据的时间还大
//	geoERR_HIS_NO_EQUAL,							// 不精确匹配
//	geoERR_HIS_PAGE_EMPTY,						// 页空
//	geoERR_HIS_DATA_FILE_NOT_EXIST,				// 所查询的数据位于已移出系统的文件中
//	geoERR_HIS_NO_DATA_FILE,						// 没有历史数据文件
//	geoERR_HIS_BEYOND_COMPRESS,					// 时间比压缩结构中数据时间还要大
//	geoERR_HIS_EQUAL_COMPRESS,					// 数据与压缩结构中数据时间相同
//	geoERR_HIS_PAGE_NOT_OPEN,					// 页未打开
//	geoERR_HIS_NO_DATA,							// 测点在文件中无对应的数据
//	geoERR_HIS_NO_DATA_IN_INDEX_PAGE,			// 索引页无数据
//	geoERR_HIS_NO_DATA_IN_DATA_PAGE,				// 数据页无数据
//	// 读模块错误号
//	geoERR_HIS_NEED_ADJUST_EndID_,					// 需要调整最后一个数据
//	geoERR_HIS_NEED_FOUND_COMPRESS,				// 需要在压缩结构中查询数据	
//	geoERR_HIS_BEYOND_MAX_READ_COUNT,			// 读取数据的个数超出最大读个数	
//	//删除函数错误号
//	geoERR_HIS_DELTIME_LESSTHAN_MIN,   			//删除函数的指定时间段比该测点最小时间还小
//	geoERR_HIS_DELTIME_MORETHAN_MAX,   			//删除函数的指定时间段比该测点最大时间还大
//	geoERR_HIS_BEYOND_NUMBER,					// 统计间隔数不应超过100      
//
//	geoERR_EVENT_BASE = -18800 ,					// 事件相关错误
//
//	geoERR_EVENTNOTIFY_BASE = -18700 ,			// 事件发布相关错误
//
//	geoERR_EVENTNOTIFY_CANNOT_StartID_,				// 事件订阅发布模块不能启动
//	geoERR_EVENTNOTIFY_SUBSCRIBE_MAP_ERROR,		// 事件订阅发布模块的订阅表错误
//	geoERR_EVENTNOTIFY_PUBLISH_MAP_ERROR,		// 事件订阅发布模块的发布者表错误
//	geoERR_EVENTNOTIFY_CONNECT_NOT_FOUND,		// 连接不存在
//
//	geoERR_USER_BASE = -18600 ,					// 用户和用户组相关错误
//
//	geoERR_USER_GROUPNAME_CONFLICT,              //用户组名冲突
//	geoERR_USER_USERNAME_CONFLICT,               //用户名冲突
//	geoERR_USER_USER_IN_GROUP,                   //向用户组添加组中存在的用户
//	geoERR_USER_USER_NOT_IN_GROUP,               //从用户组删除不存在的用户
//	geoERR_USER_REIGISTE_USERNAME_FAIL,          //向系统注册用户名出错
//	geoERR_USER_REIGISTE_GROUPNAME_FAIL,         //向系统注册用户组名出错
//	geoERR_USER_USERGROUP_NOT_EXIST,             //操作不存在的用户组
//	geoERR_USER_USER_NOT_EXIST,                  //操作不存在的用户
//	geoERR_USER_USERNAME_OR_PASSWORD_NOTMATCH,   //用户名和密码不匹配
//	geoERR_USER_READ_PSUSERCONF_FAIL,            //用户和用户组配置文件读出错
//	geoERR_USER_WRITE_PSUSERCONF_FAIL,           //用户和用户组配置文件写错误
//	geoERR_USER_USERGROUP_ONLYREAD,              //用户组只读
//	geoERR_USER_USER_ONLYREAD,                   //用户只读
//	geoERR_USER_LOST_VITAL_DATA ,               //缺失必须字段
//	geoERR_USER_NAME_LENGTH_WRONG,              //用户名或用户组名长度错误；
//	geoERR_USER_NAME_ILLEGAL,                   //用户名或用户组名非法
//	geoERR_USER_CONF_DESTROY,                   //用户配置文件被破坏
//	geoERR_USER_CONF_BACKUP_FAIL,               //用户配置文件备份失败
//
//	geoERR_IOSS_BASE = -18500 ,					// IOSS相关错误号
//	geoERR_IOSS_OBJECT_NOT_FOUND,
//	geoERR_IOSS_DEVICE_NOT_STARTED,
//	geoERR_IOSS_DRIVER_NOT_LOADED,
//
//	geoERR_MAX = -10000 , 						// 接口返回最大错误号
//} geoErrorCodeEnum;


#endif
