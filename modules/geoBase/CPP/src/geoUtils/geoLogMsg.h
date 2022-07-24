/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.                    *
*                                                                            *
*  @file     geoLogMsg.h                                                     *
*  @brief    错误跟踪，输出跟踪，文件日志跟踪处理                             *
*		参考ACE_Log_Msg														*
*    
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : 必须在支持C++11环境下编译通过                            *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/10/7 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef		GEOSYS_UTILS_LOGMSG_H__
#define		GEOSYS_UTILS_LOGMSG_H__

#include "geoBasicType.h"
#include "geoUtils.h"
#include "geoErrno.h"
#include"geoSingleton.h"
#include <atomic>
#include <mutex>
#include <ostream>
using namespace std;


class GeoLog;
struct GeoLogRecord;

//如果不想启动log，注释本定义
#define GEO_HAVE_TRACE 

//全局默认日志跟随整个附加进程中的生命周期
#define GEO_LOG GeoLog::instance()

//只有定义了GEO_HAVE_DEBUG宏，整个系统跟踪信息才写入log
#if !defined  (GEO_HAVE_TRACE)
#if !defined (GEO_TRACE)
# define GEO_TRACE(X) do {} while (0)
#endif
#else
#  define GEO_TRACE(X) \
do {	\
	int __geo_error = GeoLog::last_error_adapter(); \
	GEO_LOG->conditional_set(__FILE__, __LINE__, __geo_error); \
	GEO_LOG->log X; \
} while (0)

#endif //  GEO_HAVE_TRACE

//控制台输出log
#define trace_printf(X,...) \
do {	\
	int __geo_error = GeoLog::last_error_adapter(); \
	GEO_LOG->conditional_set(__FILE__, __LINE__, __geo_error); \
	GEO_LOG->log (LM_DEBUG,X,__VA_ARGS__); \
} while (0)

//文件输出log
#define trace_fout(X,...) \
do {\
	int __geo_error = GeoLog::last_error_adapter(); \
	GEO_LOG->set_flags(GeoLog::OSTREAM);    \
	GEO_LOG->clr_flags(GeoLog::STDERR | GeoLog::LOGGER);    \
	GEO_LOG->conditional_set(__FILE__, __LINE__, __geo_error); \
	GEO_LOG->log(LM_DEBUG,X,__VA_ARGS__); \
} while (0)
//系统日志输出log
#define trace_syslog(X,...)  \
do {\
	int __geo_error = GeoLog::last_error_adapter(); \
	GEO_LOG->set_flags(GeoLog::SYSLOG);    \
	GEO_LOG->clr_flags(GeoLog::STDERR | GeoLog::LOGGER |GeoLog::OSTREAM);    \
	GEO_LOG->conditional_set(__FILE__, __LINE__, __geo_error); \
	GEO_LOG->log(LM_DEBUG,X,__VA_ARGS__); \
} while (0)


#define VERBOSE_LEN 128

#define MAXVERBOSELOGMSGLEN (VERBOSE_LEN+MAXLOGMSGLEN)

/**
* @enum Log_Priority
*
* @brief This data type indicates the relative priorities of the
*    logging messages, from lowest to highest priority.
*
*/
enum Log_Priority
{
	// = Note, this first argument *must* start at 1!
	/// Shutdown the logger (decimal 1).
	LM_SHUTDOWN = 01,
	/// Messages indicating function-calling sequence (decimal 2).
	LM_TRACE = 02,
	/// Messages that contain information normally of use only when
	/// debugging a program (decimal 4).
	LM_DEBUG = 04,
	/// Informational messages (decimal 8).
	LM_INFO = 010,
	/// Conditions that are not error conditions, but that may require
	/// special handling (decimal 16).
	LM_NOTICE = 020,
	/// Warning messages (decimal 32).
	LM_WARNING = 040,
	/// Initialize the logger (decimal 64).
	LM_STARTUP = 0100,
	/// Error messages (decimal 128).
	LM_ERROR = 0200,
	/// Critical conditions, such as hard device errors (decimal 256).
	LM_CRITICAL = 0400,
	/// A condition that should be corrected immediately, such as a
	/// corrupted system database (decimal 512).
	LM_ALERT = 01000,
	/// A panic condition.  This is normally broadcast to all users
	/// (decimal 1024).
	LM_EMERGENCY = 02000,
	/// The maximum logging priority.
	LM_MAX = LM_EMERGENCY,
	/// Do not use!!  This enum value ensures that the underlying
	/// integral type for this enum is at least 32 bits.
	LM_ENSURE_32_BITS = 0x7FFFFFFF
};


/**
* @class GeoLog
*
* @brief 本日志可以支持文件输出，OS系统日志输出，控制台输出
*    
*
*/
class GEO_UITLS_API GeoLog
{
public:
	// Logger Flags.
	enum
	{
		/// Write messages to stderr.
		STDERR = 1,
		/// Write messages to the local client logger daemon.
		LOGGER = 2,
		/// Write messages to the ostream * stored in thread-specific
		/// storage.
		OSTREAM = 4,

		VERBOSE = 8,
		/// Display messages in a less verbose manner (i.e., only print
		/// information that can change between calls).
		VERBOSE_LITE = 16,
		/// Do not print messages at all (just leave in thread-specific
		/// storage for later inspection).
		SILENT = 32,
		/// Write messages to the system's event log.
		SYSLOG = 128
	};
	
	/// Returns a pointer to the Singleton.
	static GeoLog *instance(void);
	/// Pointer to the Singleton.
	static 	SingletonGrabber<GeoLog> grab;
	/// Returns last error.
	static int last_error_adapter(void);

	/// Clears the flag from the default priority mask used to
	/// initialize GeoLog instances.
	static void disable_debug_messages(Log_Priority priority = LM_DEBUG);

	/// Sets GeoLog flag in the default priority mask used to initialize
	/// GeoLog instances.
	static void enable_debug_messages(Log_Priority priority = LM_DEBUG);


	GeoLog(void);

	~GeoLog(void);

	int open(geoUInt32 options_flags =GeoLog::STDERR,const geoTChar *logger_key = 0);

	void set_flags(unsigned long f);

	void clr_flags(unsigned long f);

	unsigned long flags(void);

	//int acquire(void);

	//int release(void);


	void errnum(int);

	int errnum(void) const;

	void linenum(int);

	int linenum(void) const;

	void file(const char *);

	const char *file(void);


	void msg(const geoTChar *);

	const geoTChar *msg(void);


	void msg_ostream(ostream *);

	void msg_ostream(ostream *, bool delete_ostream);

	ostream *msg_ostream(void) const;

	unsigned long priority_mask();

	unsigned long priority_mask(unsigned long);

	int log_priority_enabled(Log_Priority log_priority);

	void set(const char *file,
		int line,
		int errnum = 0,
		ostream *os = 0);

	/// These values are only actually set if the requested priority is
	/// enabled.
	void conditional_set(const char *file,
		int line,
		int errnum);
	/**
	* Format a message to the thread-safe logging mechanism.  Valid
	* options (prefixed by '%', as in printf format strings) include:
	*  - 'A': print an  value (which could be either double)
	*  - 'a': abort the program at this point abruptly.
	*  - 'b': print a ssize_t value
	*  - 'B': print a size_t value
	*  - 'c': print a character
	*  - 'C': print a char* character string (also see s and W)
	*  - 'i', 'd': print a decimal number
	*  - 'e', 'E', 'f', 'F', 'g', 'G': print a double
	*  - 'l': print line number where an error occurred.
	*  - 'M': print the name of the priority of the message.
	*  - 'N': print file name where the error occurred.
	*  - 'n': print the name of the program (or "<unknown>" if not set)
	*  - 'o': print as an octal number
	*  - 'P': print out the current process id
	*  - 'Q': print out the uint64 number
	*  - 'q': print out the int64 number
	*  - '@': print a void* pointer (in hexadecimal)
	*  - 'r': call the function pointed to by the corresponding argument
	*  - 'S': print out the appropriate signal message corresponding
	*         to var-argument, e.g., as done by strsignal()
	*  - 's': prints a TCHAR* character string (also see C and W)
	*  - 'T': print timestamp in hour:minute:sec:usec format (plain option,
	*         i.e. without any flags, prints system supplied timestamp;
	*         with '#' flag added expects ACE_Time_Value* in argument list)
	*  - 'D': print timestamp as Weekday Month day year hour:minute:sec.usec
	*         (plain option, i.e. without any flags, prints system supplied
	*         timestamp; with '#' flag added expects ACE_Time_Value* in
	*         argument list)
	*  - 't': print thread id (1 if single-threaded)
	*  - 'u': print as unsigned int
	*  - 'w': prints a wide character
	*  - 'W': prints a wchar_t* character string (also see C and s)
	*  - 'x': print as a hex number
	*  - 'X': print as a hex number
	*  - 'z': print an WChar character
	*  - 'Z': print an WChar character string
	*  - ':': print a time_t value as an integral number
	*  - '%': print out a single percent sign, '%'
	*  - '?': print out stack trace (see Stack_Trace.h header comments)
	*/
	int log(Log_Priority priority, const geoTChar *format, ...);

	//int log(Log_Priority priority, const geoWChar *format, ...);

	int log(const geoTChar *format,Log_Priority priority,va_list argp);

	int  log(GeoLogRecord &log_record, int suppress_stderr);

	private:
		ostream *ostream_;
		int errnum_;

		int linenum_;

		/// File where the error occurred.
		char file_[PATH_MAX + 1];

		geoTChar* msg_; // Add one for NUL-terminator.

		unsigned long  priority_mask_;

		/// Always timestamp?
		int timestamp_;

		static unsigned long  process_priority_mask_;

		static unsigned long  flags_;

		static ptrdiff_t msg_off_;

		static unsigned long  default_priority_mask_;

		static void close(void);
		void cleanup_ostream();
		std::atomic<unsigned long> ostream_refcount_;
	struct
	{
		bool is_set_;
		const char *file_;
		int line_;
		int errnum_;
	} conditional_values_;

	// = Disallow these operations.
	GeoLog &operator= (const GeoLog &) = delete;
	GeoLog(const GeoLog &) = delete;
};


#include<pshpack8.h>
struct GeoLogRecord
{
	geoInt32 length_;
	/// Type of logging record.
	geoUInt32 type_;
	/// Time that the logging record was generated.
	geoTimeStamp  tm_;
	/// Id of process that generated the logging record.
	geoInt32 pid_;
	/// Allocated size of msg_data_ 
	size_t msg_data_size_;
	/// Logging record data
	geoTChar *msg_data_;   // Heap-allocated text message area
};
#include<poppack.h>


class  Log_Msg_Backend
{
public:
	virtual ~Log_Msg_Backend(void) {};

	virtual int open(const geoTChar *logger_key) = 0;

	virtual int reset(void) = 0;

	virtual int close(void) = 0;

	virtual int log(GeoLogRecord &log_record) = 0;
};
#if defined (_WIN32)
class  Log_Msg_NT_Event_Log: public Log_Msg_Backend
{
public:

	Log_Msg_NT_Event_Log(void);

	virtual ~Log_Msg_NT_Event_Log(void);

	virtual int open(const geoTChar *logger_key);

	virtual int reset(void);

	virtual int close(void);

	virtual int log(GeoLogRecord &log_record);

private:
	HANDLE evlog_handle_;
};
#else//linux
class  Log_Msg_UNIX_Syslog : public Log_Msg_Backend
{
public:

	Log_Msg_UNIX_Syslog(void);

	virtual ~Log_Msg_UNIX_Syslog(void);

	virtual int open(const geoTChar *logger_key);

	/// Reset the backend.
	virtual int reset(void);

	/// Close the backend completely.
	virtual int close(void);

	/// This is called when we want to log a message.
	virtual int log(GeoLogRecord &log_record);

private:
	int convert_log_priority(geoUInt32 lm_priority);

	int convert_log_mask(int lm_mask);
};

#endif

#endif