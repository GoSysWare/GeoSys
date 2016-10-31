#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include"geoLogMsg.h"
#include"geoSingleton.h"
#include"geoString.h"
#include"geoErrno.h"
#include"geoTime.h"
#include<iostream>

#if defined (_WIN32) 
#  define LOG_MSG_SYSLOG_BACKEND Log_Msg_NT_Event_Log
#elif 
#  define LOG_MSG_SYSLOG_BACKEND Log_Msg_UNIX_Syslog
#endif

#define UPDATE_COUNT(COUNT, LEN) \
   do { if (static_cast<size_t> (LEN) > COUNT) COUNT = 0; \
     else COUNT -= static_cast<size_t> (LEN); \
   } while (0)

LOG_MSG_SYSLOG_BACKEND log_backend_;
static unsigned long log_backend_flags_;

// Symbolic names for the <ACE_Log_Priority> enumerators.
static geoTChar const * priority_names[] =
{
	GEO_TEXT("LM_SHUTDOWN"),
	GEO_TEXT("LM_TRACE"),
	GEO_TEXT("LM_DEBUG"),
	GEO_TEXT("LM_INFO"),
	GEO_TEXT("LM_NOTICE"),
	GEO_TEXT("LM_WARNING"),
	GEO_TEXT("LM_STARTUP"),
	GEO_TEXT("LM_ERROR"),
	GEO_TEXT("LM_CRITICAL"),
	GEO_TEXT("LM_ALERT"),
	GEO_TEXT("LM_EMERGENCY"),
	GEO_TEXT("LM_UNK(04000)"),
	GEO_TEXT("LM_UNK(010000)"),
	GEO_TEXT("LM_UNK(020000)"),
	GEO_TEXT("LM_UNK(040000)"),
	GEO_TEXT("LM_UNK(0100000)"),
	GEO_TEXT("LM_UNK(0200000)"),
	GEO_TEXT("LM_UNK(0400000)"),
	GEO_TEXT("LM_UNK(01000000)"),
	GEO_TEXT("LM_UNK(02000000)"),
	GEO_TEXT("LM_UNK(04000000)"),
};

static const geoTChar * priority_name(Log_Priority p)
{
	return priority_names[geo_log2(p)];
}
static geoUInt32 priority(GeoLogRecord *recd)
{
	return geo_log2((geoUInt32)recd->type_);
}
static void init_logrecord(GeoLogRecord *recd)
{
	recd->length_ = 0;
	recd->msg_data_ = nullptr;
	recd->msg_data_ = 0;
	recd->pid_ = 0;
	recd->type_ = 0;
	recd->tm_ = 0;

	GEO_NEW_NORETURN(recd->msg_data_, geoTChar[MAXLOGMSGLEN]);
	if (0 != recd->msg_data_)
	{
		recd->msg_data_size_ = MAXLOGMSGLEN;
		recd->msg_data_[0] = '\0';
	}
}
static void unit_logrecord(GeoLogRecord *recd)
{
	if (recd->msg_data_)
	{
		delete[] recd->msg_data_;
		recd->msg_data_ = nullptr;
	}
}
static int msg_data(GeoLogRecord *recd ,const geoTChar *data)
{
	size_t const newlen = geo_strlen(data) + 1;  // Will need room for '\0'
	if (newlen > recd->msg_data_size_)
	{
		geoTChar *new_msg_data = 0;

		GEO_NEW_RETURN(new_msg_data, geoTChar[newlen], -1);
		if (recd->msg_data_ != nullptr)
		{
			delete[] recd->msg_data_;
		}
		recd->msg_data_ = new_msg_data;
		recd->msg_data_size_ = newlen;
	}
	geo_strcpy(recd->msg_data_, data);

	size_t len = sizeof(GeoLogRecord) + (sizeof(geoTChar) * ((geo_strlen(recd->msg_data_) + 1)));

	recd->length_ = static_cast<geoUInt32> (len);
	return 0;
}

static int format_msg(GeoLogRecord *recd,
	geoUInt32 verbose_flag,
	geoTChar *verbose_msg, 
	size_t verbose_msg_size)
{
	/* 012345678901234567890123456     */
	/* yyyy-mm-dd hh:mm:ss.mmm<nul> */
	geoTChar timestamp[24]; 
#if defined (_WIN32)
	const geoTChar *verbose_fmt = GEO_TEXT("%s@%s@%u@%s@%s");
	const geoTChar *verbose_lite_fmt = GEO_TEXT("%s@%s@%s");
#else
	const geoTChar *verbose_fmt = GEO_TEXT("%ls@%ls@%u@%ls@%ls");
	const geoTChar *verbose_lite_fmt = GEO_TEXT("%ls@%ls@%ls");
#endif

	if (GEO_BIT_ENABLED(verbose_flag,
		GeoLog::VERBOSE)
		|| GEO_BIT_ENABLED(verbose_flag,
			GeoLog::VERBOSE_LITE))
	{
		if (0 == geo_timestamp(recd->tm_,
			timestamp,
			sizeof(timestamp) / sizeof(geoTChar)))
			return -1;

		// Historical timestamp in VERBOSE[_LITE] used 3 places for partial sec.
		// 012345678901234567890123456
		// 1989-10-18 14:25:36.123<nul>
		timestamp[23] = '\0';
	}

	if (GEO_BIT_ENABLED(verbose_flag,
		GeoLog::VERBOSE))
	{
		geo_snprintf(verbose_msg, verbose_msg_size,
			verbose_fmt,
			timestamp,
			recd->pid_,
			priority_name(Log_Priority(recd->type_)),
			recd->msg_data_);
	}
	else if (GEO_BIT_ENABLED(verbose_flag, GeoLog::VERBOSE_LITE))
		geo_snprintf(verbose_msg, verbose_msg_size,
			verbose_lite_fmt,
			timestamp,
			priority_name(Log_Priority(recd->type_)),
			recd->msg_data_);
	else
		geo_strcpy(verbose_msg, recd->msg_data_);
	return 0;
}


int log_record_print(GeoLogRecord *recd, geoUInt32 verbose_flag,ostream &s)
{
		geoTChar * verbose_msg = 0;
		GEO_NEW_RETURN(verbose_msg, geoTChar[MAXVERBOSELOGMSGLEN], -1);

		int const result = format_msg(recd, verbose_flag, verbose_msg,MAXVERBOSELOGMSGLEN);

		if (result == 0)
		{
			s << GEO_TEXT_ALWAYS_CHAR(verbose_msg);
			s.flush();
		}

		delete[] verbose_msg;

		return result;
	return 0;
}

static int log_record_print(GeoLogRecord *recd, geoUInt32 verbose_flag,FILE *fp)
{

		geoTChar *verbose_msg = 0;

		GEO_NEW_RETURN(verbose_msg, geoTChar[MAXVERBOSELOGMSGLEN], -1);

		int result = format_msg(recd, verbose_flag, verbose_msg,MAXVERBOSELOGMSGLEN);

		if (result == 0)
		{
			if (fp != 0)
			{
				int const verbose_msg_len =
					static_cast<int> (geo_strlen(verbose_msg));
#if !defined (_WIN32)
				int const fwrite_result = geo_fprintf(fp,GEO_TEXT("%ls"),verbose_msg);
#else
				int const fwrite_result = geo_fprintf(fp,GEO_TEXT("%s"),verbose_msg);
#endif
				// We should have written everything
				if (fwrite_result != verbose_msg_len)
					result = -1;
				else
					::fflush(fp);
			}
		}
		delete[] verbose_msg;

		return result;
}


/// Default is to use stderr.
unsigned long  GeoLog::flags_ = GeoLog::STDERR;
/// Current offset of msg_[].
ptrdiff_t GeoLog::msg_off_ = 0;

/// Default per-thread priority mask
/// By default, no priorities are enabled.
unsigned long  GeoLog::default_priority_mask_ = 0;

SingletonGrabber<GeoLog> GeoLog::grab;


/// Default per-process priority mask
/// By default, all priorities are enabled.
unsigned long  GeoLog::process_priority_mask_ = LM_SHUTDOWN
| LM_TRACE
| LM_DEBUG
| LM_INFO
| LM_NOTICE
| LM_WARNING
| LM_STARTUP
| LM_ERROR
| LM_CRITICAL
| LM_ALERT
| LM_EMERGENCY;
int GeoLog::last_error_adapter(void)
{
	return last_error();
}


 GeoLog *GeoLog::instance(void)
{
	return grab.GetInstance();
}
 void GeoLog::disable_debug_messages(Log_Priority priority)
 {
	 GEO_CLR_BITS(GeoLog::default_priority_mask_, priority);
	 GeoLog *i = GeoLog::instance();
	 i->priority_mask(i->priority_mask() & ~priority);

 }

 void GeoLog::enable_debug_messages(Log_Priority priority)
 {
	 GEO_SET_BITS(GeoLog::default_priority_mask_, priority);
	 GeoLog *i = GeoLog::instance();
	 i->priority_mask(i->priority_mask() | priority);
 }


 GeoLog::GeoLog(void)
	 :errnum_(0),
	 linenum_(0),
	 msg_(0),
	 ostream_(0),
	 priority_mask_(default_priority_mask_),
	 timestamp_(0),
	 ostream_refcount_(0)
 {

	 this->conditional_values_.is_set_ = false;

	 char *timestamp = ::getenv("LOG_TIMESTAMP");
	 if (timestamp != 0)
	 {
		 // If variable is set or is set to date tag so we print date and time.
		 if (::strcmp(timestamp, "TIME") == 0)
		 {
			 this->timestamp_ = 1;
		 }
		 else if (::strcmp(timestamp, "DATE") == 0)
		 {
			 this->timestamp_ = 2;
		 }
	 }
	 GEO_NEW_NORETURN(this->msg_, geoTChar[MAXLOGMSGLEN + 1]);
	 memset(this->msg_, 0, MAXLOGMSGLEN + 1);

 }
 GeoLog::~GeoLog()
 {
	 this->cleanup_ostream();
	 if(this->msg_ != nullptr)
	 delete[] this->msg_;
 }

 int GeoLog::open(geoUInt32 flags , const geoTChar *logger_key)
 {
	 int status = 0;
	 log_backend_.reset();
	 if (GEO_BIT_ENABLED(flags, GeoLog::LOGGER)|| GEO_BIT_ENABLED(flags, GeoLog::SYSLOG))
	 {
		 if (logger_key == 0 && GEO_BIT_ENABLED(flags, GeoLog::LOGGER))
			 status = -1;
		 else
			 status = log_backend_.open(logger_key);

		 if (status == -1)
			 GEO_SET_BITS(GeoLog::flags_, GeoLog::STDERR);
		 else
		 {
			 if (GEO_BIT_ENABLED(flags, GeoLog::LOGGER))
				 GEO_SET_BITS(GeoLog::flags_, GeoLog::LOGGER);

			 if (GEO_BIT_ENABLED(flags, GeoLog::SYSLOG))
				 GEO_SET_BITS(GeoLog::flags_, GeoLog::SYSLOG);
		 }
	 }
	 else if (GEO_BIT_ENABLED(GeoLog::flags_, GeoLog::LOGGER)|| GEO_BIT_ENABLED(GeoLog::flags_, GeoLog::SYSLOG))
	 {
		 GEO_CLR_BITS(GeoLog::flags_, GeoLog::LOGGER);
		 GEO_CLR_BITS(GeoLog::flags_, GeoLog::SYSLOG);
		 GEO_SET_BITS(GeoLog::flags_, GeoLog::STDERR);
	 }

	 if (status != -1&& GEO_BIT_ENABLED(flags,GeoLog::STDERR) == 0)
		 GEO_CLR_BITS(GeoLog::flags_,GeoLog::STDERR);

	 if (GEO_BIT_ENABLED(flags,GeoLog::VERBOSE_LITE))
		 GEO_SET_BITS(GeoLog::flags_, GeoLog::VERBOSE_LITE);

	 else if (GEO_BIT_ENABLED(flags,GeoLog::VERBOSE))
		 GEO_SET_BITS(GeoLog::flags_,GeoLog::VERBOSE);

	 if (GEO_BIT_ENABLED(flags, GeoLog::OSTREAM))
	 {
		 GEO_SET_BITS(GeoLog::flags_,GeoLog::OSTREAM);
		 if (this->msg_ostream() == 0)
			 this->msg_ostream(GEO_DEFAULT_LOG_STREAM);
	 }


	 if (GEO_BIT_ENABLED(flags, GeoLog::SILENT))
		 GEO_SET_BITS(GeoLog::flags_, GeoLog::SILENT);

	 return status;
 }

 void GeoLog::set_flags(unsigned long f)
 {
	 GEO_SET_BITS(GeoLog::flags_, f);
 }


 void GeoLog::clr_flags(unsigned long f)
 {
	 GEO_CLR_BITS(GeoLog::flags_, f);
 }
 unsigned long GeoLog::flags(void)
 {
	 return GeoLog::flags_;
 }
 unsigned long GeoLog::priority_mask(unsigned long n_mask)
 {

	 unsigned long o_mask;
	 o_mask = GeoLog::process_priority_mask_;
	 GeoLog::process_priority_mask_ = n_mask;
	 return o_mask;
 }
 unsigned long GeoLog::priority_mask()
 {
	 return this->priority_mask_;
 }

 int GeoLog::log_priority_enabled(Log_Priority log_priority)
 {
	 return GEO_BIT_ENABLED(this->priority_mask_| GeoLog::process_priority_mask_, log_priority);
 }
 /// Set the value of the errnum (by convention this corresponds to
 /// errno).
 void GeoLog::errnum(int e)
 {
	 this->errnum_ = e;
 }

 /// Get the value of the errnum (by convention this corresponds to
 /// errno).
 int GeoLog::errnum(void) const
 {
	 return this->errnum_;
 }
int GeoLog::linenum(void) const
 {
	 return this->linenum_;
 }

void GeoLog::linenum(int l)
 {
	 this->linenum_ = l;
 }

const char * GeoLog::file(void)
{
	return this->file_;
}


void
GeoLog::file(const char *s)
{
	geo_strsncpy(this->file_, s, sizeof this->file_);
}

const geoTChar * GeoLog::msg(void)
{
	return this->msg_ + GeoLog::msg_off_;
}


void GeoLog::msg(const geoTChar *m)
{
	geo_strsncpy(this->msg_, m,((MAXLOGMSGLEN + 1) / sizeof(geoTChar)));
}

ostream *GeoLog::msg_ostream(void) const
{
	return this->ostream_;
}

void
GeoLog::msg_ostream(ostream *m)
{
	this->ostream_ = m;
}

void
GeoLog::cleanup_ostream()
{
	if (this->ostream_refcount_ >0)
	{
		if (--this->ostream_refcount_ == 0)
		{
			delete this->ostream_;
			this->ostream_ = 0;
		}
		this->ostream_refcount_ = 0;
	}
}

void
GeoLog::msg_ostream(ostream *m, bool delete_ostream)
{
	if (this->ostream_ == m)
	{
		// Same stream, allow user to change the delete_ostream "flag"
		if (delete_ostream && ostream_refcount_ ==0)
		{
			ostream_refcount_ = 1;
		}
		else if (!delete_ostream && this->ostream_refcount_ != 0)
		{

			this->ostream_refcount_ = 0;
		}
		return;
	}

	this->cleanup_ostream();

	if (delete_ostream)
	{
		ostream_refcount_ = 1;
	}
	this->ostream_ = m;
}

void
GeoLog::set(const char *file,
	int line,
	int errnum,
	ostream *os)
{
	this->file(file);
	this->linenum(line);
	this->errnum(errnum);
	this->msg_ostream(os);
}



 void GeoLog::conditional_set(const char *file,
	 int line,
	 int errnum)
 {
	 this->conditional_values_.is_set_ = true;
	 this->conditional_values_.file_ = file;
	 this->conditional_values_.line_ = line;
	 this->conditional_values_.errnum_ = errnum;
 }

 int GeoLog::log(Log_Priority priority, const geoTChar *format, ...)
 {
	 // Start of variable args section.
	 va_list argp;

	 va_start(argp, format);

	 int const result = this->log(format,
		 priority,
		 argp);
	 va_end(argp);

	 return result;

	 return 0;
 }
 int  GeoLog::log(GeoLogRecord &log_record, int suppress_stderr)
 {
	 int result = 0;

	 u_long flags = this->flags();
	 if (GEO_BIT_DISABLED(flags, GeoLog::SILENT))
	 {
		 if (GEO_BIT_ENABLED(flags, GeoLog::STDERR) && !suppress_stderr) // This is taken care of by our caller.
			 log_record_print(&log_record, flags, stderr);

		 if (GEO_BIT_ENABLED(flags, GeoLog::LOGGER) ||
			 GEO_BIT_ENABLED(flags, GeoLog::SYSLOG))
		 {
			 result = log_backend_.log(log_record);
		 }
		 if (GEO_BIT_ENABLED(flags, GeoLog::OSTREAM) && this->msg_ostream() != 0)
			
			 log_record_print(&log_record,flags,*this->msg_ostream());
	 }

	 return result;
 }
 int GeoLog::log(const geoTChar *format_str,Log_Priority log_priority, va_list argp)
 {
	 typedef void(*PTF)(...);

	 bool const conditional_values = this->conditional_values_.is_set_;

	 this->conditional_values_.is_set_ = false;

	 if (this->log_priority_enabled(log_priority) == 0)
		 return 0;
	 if (conditional_values)
		 this->set(this->conditional_values_.file_,
			 this->conditional_values_.line_,
			 this->conditional_values_.errnum_,
			 this->msg_ostream());
	 GeoLogRecord record;

	 init_logrecord(&record);

	 record.pid_ = geo_getpid();
	 record.type_ = log_priority;
	 record.tm_ = geo_get_system_time();

	 geoTChar *bp = const_cast<geoTChar *> (this->msg());
	 size_t bspace = MAXLOGMSGLEN;  // Leave room for Nul term.
	 if (this->msg_off_ <= MAXLOGMSGLEN+1)
		 bspace -= static_cast<size_t> (this->msg_off_);

	 geoTChar test[2];
	 bool can_check = geo_snprintf(test, 1, GEO_TEXT("x")) != -1;

	 bool abort_prog = false;
	 int exit_value = 0;

	 geoUInt32 flags = this->flags();

	 if (GEO_BIT_ENABLED(flags, GeoLog::VERBOSE))
	 {
		 geoTChar * program_name_ = GEOSYS_DEFAULT_NAME;
		 for (const geoTChar *s = program_name_; bspace > 1 && (*bp = *s) != '\0'; ++s, --bspace)
		 {
			 bp++;
		 }
		*bp++ = '|';
		--bspace; 
	 }
	 if (timestamp_ > 0)
	 {
		 geoTChar day_and_time[24];
		 const geoTChar *s = 0;
		 if (timestamp_ == 1)
		 {
			 s = geo_timestamp(geoTime_Zero,day_and_time,sizeof(day_and_time) / sizeof(geoTChar),true);
		 }
		 else
		 {
			 // Print time and date
			 geo_timestamp(geoTime_Zero,day_and_time,sizeof(day_and_time) / sizeof(geoTChar));
			 s = day_and_time;
		 }
		 for (; bspace > 1 && (*bp = *s) != '\0'; ++s, --bspace)
		 {
			 ++bp;
		 }
		*bp++ = '|';
		--bspace;
	 }

	 while (*format_str != '\0' && bspace > 0)
	 {

		 if (*format_str != '%')
		 {
			 *bp++ = *format_str++;
			 --bspace;
		 }
		 else if (format_str[1] == '%') // An "escaped" '%' (just print one '%').
		 {
			 *bp++ = *format_str++;    // Store first %
			 ++format_str;             // but skip second %
			 --bspace;
		 }
		 else
		 {

			 const geoTChar *abort_str = GEO_TEXT("Aborting...");
			 const geoTChar *start_format = format_str;
			 size_t fspace = 128;
			 geoTChar format[128]; // Converted format string
			 ::memset(format, '\0', 128); // Set this string to known values.
			 geoTChar *fp = 0;         // Current format pointer
			 int       wp = 0;      // Width/precision extracted from args
			 bool      done = false;
			 bool      skip_nul_locate = false;
			 int       this_len = 0;    // How many chars s[n]printf wrote

			 fp = format;
			 *fp++ = *format_str++;   // Copy in the %
			 --fspace;

			 int tmp_indent = 0;
	
			 while (!done)
			 {
				 done = true; // Unless a conversion spec changes it

				 switch (*format_str)
				 {
				 case '-':
				 case '+':
				 case '0':
				 case ' ':
				 case '#':
				 case '1':
				 case '2':
				 case '3':
				 case '4':
				 case '5':
				 case '6':
				 case '7':
				 case '8':
				 case '9':
				 case '.':
				 case 'h':
					 *fp++ = *format_str;
					 --fspace;
					 done = false;
					 break;
				 case 'L':
					 *fp++ = 'l';
					 done = false;
					 break;

				 case '*':
					 wp = va_arg(argp, int);
					 if (can_check)
						 this_len = geo_snprintf(fp, fspace, GEO_TEXT("%d"), wp);
					 else
						 this_len = geo_sprintf(fp, GEO_TEXT("%d"), wp);
					 UPDATE_COUNT(fspace, this_len);
					 fp += geo_strlen(fp);
					 done = false;
					 break;

				 case 'A':
				 {
					 geo_strcpy(fp, GEO_TEXT("f"));
					 --fspace;
					 double const value = va_arg(argp, double);
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, value);
					 else
						 this_len = geo_sprintf(bp, format, value);
					 UPDATE_COUNT(bspace, this_len);
				 }
				 break;

				 case 'a': // Abort program after handling all of format string.
					 abort_prog = true;
					 exit_value = va_arg(argp, int);
					 geo_strsncpy(bp, abort_str, bspace);
					 if (bspace > geo_strlen(abort_str))
						 bspace -= geo_strlen(abort_str);
					 else
						 bspace = 0;
					 break;

				 case 'l':             // Source file line number
					 geo_strcpy(fp, GEO_TEXT("d"));
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, this->linenum());
					 else
						 this_len = geo_sprintf(bp, format, this->linenum());
					 break;

				 case 'N':             // Source file name
#if !defined (_WIN32)
					 geo_strcpy(fp, GEO_TEXT("ls"));
#else
					 geo_strcpy(fp, GEO_TEXT("s"));
#endif
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, this->file() ? GEO_TEXT_CHAR_TO_TCHAR(this->file()) : GEO_TEXT("<unknown file>"));
					 else
						 this_len = geo_sprintf(bp, format, this->file() ? GEO_TEXT_CHAR_TO_TCHAR(this->file()) : GEO_TEXT("<unknown file>"));
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 case 'n':             // Program name
#if !defined (_WIN32)
					 geo_strcpy(fp, GEO_TEXT("ls"));
#else 
					 geo_strcpy(fp, GEO_TEXT("s"));
#endif
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, GEOSYS_DEFAULT_NAME);
					 else
						 this_len = geo_sprintf(bp, format, GEOSYS_DEFAULT_NAME);
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 case 'P':             // Process ID

					 geo_strcpy(fp, GEO_TEXT("d"));
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, static_cast<int> (geo_getpid()));
					 else
						 this_len = geo_sprintf(bp, format, static_cast<int> (geo_getpid()));
					 UPDATE_COUNT(bspace, this_len);
					 break;


				 case 'M': // Print the name of the priority of the message.
					 if (format[1] == GEO_TEXT('.') && format[2] == GEO_TEXT('1'))
					 {
						 fp = format;
						 fp++;

# if defined (_UNICODE)
#     if defined (_WIN32) // Windows uses 'c' for a wide character
						 geo_strcpy(fp, GEO_TEXT("c"));
#     else 
						 geo_strcpy(fp, GEO_TEXT("lc"));
#     endif
# else 
						 // Non-unicode builds simply use a standard character format specifier
						 geo_strcpy(fp, GEO_TEXT("c"));
# endif 

						 if (can_check)
						 {
							 this_len = geo_snprintf
							 (bp, bspace, format, (int)
								 (log_priority <= LM_WARNING) ?
								 (log_priority <= LM_DEBUG) ?
								 (log_priority <= LM_TRACE) ?
								 (log_priority == LM_SHUTDOWN) ?
								 GEO_TEXT('S') : GEO_TEXT('T') : GEO_TEXT('D') :
								 (log_priority <= LM_NOTICE) ?
								 (log_priority == LM_INFO) ?
								 GEO_TEXT('I') : GEO_TEXT('N') : GEO_TEXT('W') :
								 (log_priority <= LM_CRITICAL) ?
								 (log_priority <= LM_ERROR) ?
								 (log_priority == LM_STARTUP) ?
								 GEO_TEXT('U') : GEO_TEXT('E') : GEO_TEXT('C') :
								 (log_priority <= LM_EMERGENCY) ?
								 (log_priority == LM_ALERT) ?
								 GEO_TEXT('A') : GEO_TEXT('!') : GEO_TEXT('?'));
						 }
						 else
						 {
							 this_len = geo_sprintf
							 (bp, format, (int)
								 (log_priority <= LM_WARNING) ?
								 (log_priority <= LM_DEBUG) ?
								 (log_priority <= LM_TRACE) ?
								 (log_priority == LM_SHUTDOWN) ?
								 GEO_TEXT('S') : GEO_TEXT('T') : GEO_TEXT('D') :
								 (log_priority <= LM_NOTICE) ?
								 (log_priority == LM_INFO) ?
								 GEO_TEXT('I') : GEO_TEXT('N') : GEO_TEXT('W') :
								 (log_priority <= LM_CRITICAL) ?
								 (log_priority <= LM_ERROR) ?
								 (log_priority == LM_STARTUP) ?
								 GEO_TEXT('U') : GEO_TEXT('E') : GEO_TEXT('C') :
								 (log_priority <= LM_EMERGENCY) ?
								 (log_priority == LM_ALERT) ?
								 GEO_TEXT('A') : GEO_TEXT('!') : GEO_TEXT('?'));
						 }

						 UPDATE_COUNT(bspace, this_len);
					 }
					 else
					 {
#if !defined (_WIN32) && defined (_UNICODE)
						 geo_strcpy(fp, GEO_TEXT("ls"));
#else
						 geo_strcpy(fp, GEO_TEXT("s"));
#endif
						 if (can_check)
							 this_len = geo_snprintf(bp, bspace, format, priority_name(log_priority));
						 else
							 this_len = geo_sprintf(bp, format, priority_name(log_priority));
						 UPDATE_COUNT(bspace, this_len);
					 }
					 break;






				 case 'r': // Run (invoke) this subroutine.
				 {
					 ptrdiff_t const osave = GeoLog::msg_off_;

					 if (GEO_BIT_ENABLED(flags, GeoLog::SILENT) && bspace > 1)
					 {
						 *bp++ = '{';
						 --bspace;
					 }
					 GeoLog::msg_off_ = bp - this->msg_;

					 (*va_arg(argp, PTF))();

					 if (GEO_BIT_ENABLED(flags, GeoLog::SILENT) && bspace > (1 + geo_strlen(bp)))
					 {
						 bspace -= (geo_strlen(bp) + 1);
						 bp += geo_strlen(bp);
						 *bp++ = '}';
					 }
					 *bp = '\0';
					 skip_nul_locate = true;
					 GeoLog::msg_off_ = osave;
					 break;
				 }


				 case 'D': // Format the timestamp in format:
						   // yyyy-mm-dd hour:minute:sec.msec
				 {
					 geoTChar day_and_time[24];
					 // Did we find the flag indicating a time value argument
					 if (format[1] == GEO_TEXT('#'))
					 {
						 geoTimeStamp* time_value = va_arg(argp, geoTimeStamp*);
						 geo_timestamp(*time_value,
							 day_and_time,
							 sizeof(day_and_time) / sizeof(geoTChar));
					 }
					 else
					 {
						 geo_timestamp(geoTime_Zero, day_and_time, sizeof(day_and_time) / sizeof(geoTChar));
					 }
#if !defined (_WIN32) && defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("ls"));
#else
					 geo_strcpy(fp, GEO_TEXT("s"));
#endif
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, day_and_time);
					 else
						 this_len = geo_sprintf(bp, format, day_and_time);
					 UPDATE_COUNT(bspace, this_len);
					 break;
				 }

				 case 'T': // Format the timestamp in
						   // hour:minute:sec.usec format.
				 {
					 geoTChar day_and_time[24];
#if !defined (_WIN32) && defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("ls"));
#else
					 geo_strcpy(fp, GEO_TEXT("s"));
#endif
					 // Did we find the flag indicating a time value argument
					 if (format[1] == GEO_TEXT('#'))
					 {
						 geoTimeStamp* time_value = va_arg(argp, geoTimeStamp*);
						 if (can_check)
							 this_len = geo_snprintf(bp, bspace, format,
								 geo_timestamp(*time_value, day_and_time, sizeof day_and_time / sizeof(geoTChar)));
						 else
							 this_len = geo_sprintf
							 (bp, format, geo_timestamp(*time_value, day_and_time, sizeof day_and_time / sizeof(geoTChar)));
					 }
					 else
					 {
						 if (can_check)
							 this_len = geo_snprintf(bp, bspace, format, geo_timestamp(geoTime_Zero, day_and_time, sizeof day_and_time / sizeof(geoTChar)));
						 else
							 this_len = geo_sprintf(bp, format, geo_timestamp(geoTime_Zero, day_and_time, sizeof day_and_time / sizeof(geoTChar)));
					 }
					 UPDATE_COUNT(bspace, this_len);
					 break;
				 }

				 case 't': // Format thread id.
#if !defined (_UNICODE) //ASCII
#if defined(_WIN32)
				 {
					 geo_strcpy(fp, GEO_TEXT("u"));
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, static_cast<unsigned> (::GetCurrentThreadId()));
					 else
						 this_len = geo_sprintf(bp, format, static_cast <unsigned> (::GetCurrentThreadId()));
				 }
#else
				 {
					 pid_t t_id = pthread_self();
					 geo_snprintf(bp, bspace, "%lu", (unsigned long)t_id);
				 }
#endif

#else	// UNICODE
#if defined(_WIN32)
					 {
						 char tid_buf[32] = {};
						 geo_snprintf(tid_buf,sizeof tid_buf,"%u",static_cast <unsigned> (::GetCurrentThreadId()));
						 this_len = geo_strlen(tid_buf);
						 geo_strncpy(bp, GEO_TEXT_CHAR_TO_TCHAR(tid_buf), bspace);
					 }
#else
					 {
						 char tid_buf[32] = {};
						 geo_snprintf(tid_buf, sizeof tid_buf, "%u", static_cast <unsigned> (pthread_self()));
						 this_len = geo_strlen(tid_buf);
						 geo_strncpy(bp, GEO_TEXT_CHAR_TO_TCHAR(tid_buf), bspace);
					 }
#endif
#endif 
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 case 's':                       // String
				 {
#if !defined (_WIN32) && defined (_UNICODE)
					 wchar_t *str = va_arg(argp, wchar_t *);
					 geo_strcpy(fp, GEO_TEXT("ls"));
#else 
					 geoTChar *str = va_arg(argp, geoTChar *);
					 geo_strcpy(fp, GEO_TEXT("s"));
#endif 
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, str ? str : GEO_TEXT("(null)"));
					 else
						 this_len = geo_sprintf(bp, format, str ? str : GEO_TEXT("(null)"));
					 UPDATE_COUNT(bspace, this_len);
				 }
				 break;

				 case 'C':         // Narrow-char string
				 {
					 char *cstr = va_arg(argp, char *);
#if !defined (_WIN32) && defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("S"));
#else 
					 geo_strcpy(fp, GEO_TEXT("s"));
#endif 
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, cstr ? cstr : "(null)");
					 else
						 this_len = geo_sprintf(bp, format, cstr ? cstr : "(null)");
					 UPDATE_COUNT(bspace, this_len);
				 }
				 break;

				 case 'W':
				 {
#if defined (_UNICODE)
					 wchar_t *wchar_str = va_arg(argp, wchar_t *);
# if defined (_WIN32)
#   if defined (_UNICODE)
					 geo_strcpy(fp, ACE_TEXT("s"));
#   else 
					 geo_strcpy(fp, ACE_TEXT("S"));
#   endif 
# else
					 geo_strcpy(fp, ACE_TEXT("ls"));
# endif 
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, wchar_str ? wchar_str : GEO_TEXT_WIDE("(null)"));
					 else
						 this_len = ACE_OS::sprintf(bp, format, wchar_str ? wchar_str : GEO_TEXT_WIDE("(null)"));
#endif
					 UPDATE_COUNT(bspace, this_len);
				 }
				 break;

				 case 'w':              // Wide character
#if defined (_WIN32)
# if defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("c"));
# else 
					 geo_strcpy(fp, GEO_TEXT("C"));
# endif
					 if (can_check)
						 this_len =geo_snprintf(bp, bspace, format, va_arg(argp, int));
					 else
						 this_len = geo_sprintf(bp, format, va_arg(argp, int));
#elif defined (_UNICODE)

					 geo_strcpy(fp, GEO_TEXT("lc"));
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, va_arg(argp, wint_t));
					 else
						 this_len = geo_sprintf(bp, format, va_arg(argp, wint_t));
#else
					 geo_strcpy(fp, GEO_TEXT("u"));
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, va_arg(argp, int));
					 else
						 this_len = geo_sprintf(bp, format, va_arg(argp, int));
#endif
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 case 'z':              // WChar character
				 {
					 wchar_t wtchar =static_cast<wchar_t> (va_arg(argp, int));
#if defined (_WIN32)
# if defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("c"));
# else 
					 geo_strcpy(fp, GEO_TEXT("C"));
# endif 
#elif defined (_UNICODE)

					 geo_strcpy(fp, GEO_TEXT("lc"));
#else 
					 geo_strcpy(fp, GEO_TEXT("u"));
#endif 
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, wtchar);
					 else
						 this_len = geo_sprintf(bp, format, wtchar);
					 UPDATE_COUNT(bspace, this_len);
					 break;
				 }

				 case 'Z':              // ACE_OS::WChar character string
				 {
					 geoWChar *wchar_str = va_arg(argp, geoWChar*);
					 if (wchar_str == 0)
						 break;

					 wchar_t *wchar_t_str = 0;
					 if (sizeof(geoWChar) != sizeof(wchar_t))
					 {
						 size_t len = geo_strlen(wchar_str) + 1;
						 GEO_NEW_NORETURN(wchar_t_str, wchar_t[len]);
						 if (wchar_t_str == 0)
							 break;

						 for (size_t i = 0; i < len; ++i)
						 {
							 wchar_t_str[i] = wchar_str[i];
						 }
					 }
					 if (wchar_t_str == 0)
					 {
						 wchar_t_str = reinterpret_cast<wchar_t*> (wchar_str);
					 }
#if defined (_WIN32)
# if defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("s"));
# else 
					 geo_strcpy(fp, GEO_TEXT("S"));
# endif 
#elif defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("ls"));
#endif
					 if (can_check)
						 this_len = geo_snprintf
						 (bp, bspace, format, wchar_t_str);
					 else
						 this_len = geo_sprintf(bp, format, wchar_t_str);
					 if (sizeof(geoWChar) != sizeof(wchar_t))
					 {
						 delete[] wchar_t_str;
					 }
					 UPDATE_COUNT(bspace, this_len);
					 break;
				 }

				 case 'c':
#if defined (_WIN32) && defined (_UNICODE)
					 geo_strcpy(fp, GEO_TEXT("C"));
#else
					 geo_strcpy(fp, GEO_TEXT("c"));
#endif 
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, va_arg(argp, int));
					 else
						 this_len = geo_sprintf(bp, format, va_arg(argp, int));
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 case 'd': case 'i': case 'o':
				 case 'u': case 'x': case 'X':
					 fp[0] = *format_str;
					 fp[1] = '\0';
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, va_arg(argp, int));
					 else
						 this_len = geo_sprintf(bp, format, va_arg(argp, int));
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 case 'F': case 'f': case 'e': case 'E':
				 case 'g': case 'G':
					 fp[0] = *format_str;
					 fp[1] = '\0';
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, va_arg(argp, double));
					 else
						 this_len = geo_sprintf(bp, format, va_arg(argp, double));
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 case 'Q':
				 {
					 const geoTChar *fmt = GEO_TEXT("%I64u");
					 geo_strcpy(fp, &fmt[1]);    // Skip leading %
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace,format,va_arg(argp, geoUInt64));
					 else
						 this_len = geo_sprintf(bp,format,va_arg(argp, geoUInt64));
				 }
				 UPDATE_COUNT(bspace, this_len);
				 break;

				 case 'q':
				 {
					 const geoTChar *fmt = GEO_TEXT("%I64d");
					 geo_strcpy(fp, &fmt[1]);    // Skip leading %
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace,format,va_arg(argp, geoInt64));
					 else
						 this_len = geo_sprintf(bp,format,va_arg(argp, geoInt64));
				 }
				 UPDATE_COUNT(bspace, this_len);
				 break;


				 case ':':
				 {
					 // Assume a 32 bit time_t and change if needed.
					 const geoTChar *fmt = GEO_TEXT("%d");
					 if (sizeof(time_t) == 8)
						 fmt = GEO_TEXT("%I64d");

					 geo_strcpy(fp, &fmt[1]);    // Skip leading %
				 }
				 if (can_check)
					 this_len = geo_snprintf(bp, bspace,
						 format,
						 va_arg(argp, time_t));
				 else
					 this_len = geo_sprintf(bp,format,va_arg(argp, time_t));
				 UPDATE_COUNT(bspace, this_len);
				 break;

				 case '@':
					 geo_strcpy(fp, GEO_TEXT("p"));
					 if (can_check)
						 this_len = geo_snprintf(bp, bspace, format, va_arg(argp, void*));
					 else
						 this_len = geo_sprintf(bp, format, va_arg(argp, void*));
					 UPDATE_COUNT(bspace, this_len);
					 break;

				 default:
					 while (start_format != format_str && bspace > 0)
					 {
						 *bp++ = *start_format++;
						 --bspace;
					 }
					 if (bspace > 0)
					 {
						 *bp++ = *format_str;
						 --bspace;
					 }
					 break;
				 }

				 // Bump to the next char in the caller's format_str
				 ++format_str;
			 }

			 if (!skip_nul_locate)
				 while (*bp != '\0') // Locate end of bp.
					 ++bp;
		 }
	 }

	 *bp = '\0'; // Terminate bp, but don't auto-increment this!

	 int result = 0;

	 // Check that memory was not corrupted, if it corrupted we can't log anything
	 // anymore because all our members could be corrupted.
	 if (bp >= (this->msg_ + MAXLOGMSGLEN + 1))
	 {
		 abort_prog = true;
		 geo_fprintf(stderr, "The following logged message is too long!\n");
	 }
	 else
	 {
		 // Copy the message from thread-specific storage into the transfer
		 // buffer (this can be optimized away by changing other code...).
		 msg_data(&record,this->msg());
		 result = this->log(record,abort_prog);
	 }

	 if (abort_prog)
	 {
			GEO_UNUSED_ARG(exit_value);
			log_record_print(&record, 0, stderr);
			unit_logrecord(&record);
#if defined (_WIN32)
				::abort();
#else
				exit(1);
#endif 
	 }
	 unit_logrecord(&record);
	 return result;


 }

#if defined (_WIN32)

 Log_Msg_NT_Event_Log::Log_Msg_NT_Event_Log(void)
	 : evlog_handle_(0)
 {
 }

 Log_Msg_NT_Event_Log::~Log_Msg_NT_Event_Log(void)
 {
	 this->close();
 }

 int Log_Msg_NT_Event_Log::open(const geoTChar *logger_key)
 {
	 geoTChar msg_file[_MAX_PATH];

	 if (!GEO_GetModuleFileName(win32_resource_module_,msg_file,_MAX_PATH))
		 return -1;

	 DWORD msg_file_length = static_cast<DWORD> ((geo_strlen(msg_file) + 1) * sizeof(geoTChar));

	 const geoTChar *event_source_name = logger_key ? logger_key : GEOSYS_DEFAULT_NAME;

	 // Information is stored in the registry at a location based on the
	 // program name.
	 geoTChar reg_key[_MAX_PATH];
	 geo_strcpy(reg_key,GEO_TEXT("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\"));
	 size_t reg_key_length = geo_strlen(reg_key);
	 geo_strncat(reg_key,event_source_name,_MAX_PATH - reg_key_length);
	 HKEY hkey;
	 GEO_RegCreateKey(HKEY_LOCAL_MACHINE,reg_key,&hkey);

	 DWORD flags = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;

	 GEO_RegSetValueEx(hkey, GEO_TEXT("TypesSupported"),0,REG_DWORD,(LPBYTE)&flags,sizeof(DWORD));

	 GEO_RegSetValueEx(hkey, GEO_TEXT("EventMessageFile"),0,REG_SZ,(LPBYTE)msg_file,msg_file_length);

	 RegCloseKey(hkey);

	 this->evlog_handle_ = GEO_RegisterEventSource(0,event_source_name);
	 return this->evlog_handle_ ? 0 : -1;
 }

 int Log_Msg_NT_Event_Log::reset(void)
 {
	 return this->close();
 }

 int Log_Msg_NT_Event_Log::close(void)
 {
	 if (this->evlog_handle_ == 0|| DeregisterEventSource(this->evlog_handle_))
	 {
		 this->evlog_handle_ = 0;
		 return 0;
	 }
	 else
		 return -1;
 }

 int Log_Msg_NT_Event_Log::log(GeoLogRecord &log_record)
 {
	 const geoTChar *src_msg_data = log_record.msg_data_;
	 geoTChar msg_data[(MAXLOGMSGLEN * 2) + 1];

	 size_t maxlen = MAXLOGMSGLEN;
	 if (MAXLOGMSGLEN > log_record.msg_data_size_)
		 maxlen = log_record.msg_data_size_;

	 size_t end = 0;
	 for (size_t i = 0, j = 0;
		 i < maxlen;
		 ++i)
	 {
		 if (src_msg_data[i] == '\n')
		 {
			 msg_data[j++] = '\r';
			 msg_data[j++] = '\n';
		 }
		 else
			 msg_data[j++] = src_msg_data[i];

		 end = j;
	 }
	 msg_data[end] = '\0';

	 WORD event_type;
	 switch (log_record.type_)
	 {
	 case LM_STARTUP:
	 case LM_SHUTDOWN:
	 case LM_TRACE:
	 case LM_DEBUG:
	 case LM_INFO:
		 event_type = EVENTLOG_INFORMATION_TYPE;
		 break;
	 case LM_NOTICE:
	 case LM_WARNING:
		 event_type = EVENTLOG_WARNING_TYPE;
		 break;
	 case LM_ERROR:
	 case LM_CRITICAL:
	 case LM_ALERT:
	 case LM_EMERGENCY:
	 default:
		 event_type = EVENTLOG_ERROR_TYPE;
		 break;
	 }

	 const geoTChar* msgs[1];
	 msgs[0] = msg_data;

	 if (GEO_ReportEvent(this->evlog_handle_,event_type, 0, 0, 0, 1, 0, msgs, 0) == 0)
		 return -1;
	 else
		 return 0;
 }

#else

 Log_Msg_UNIX_Syslog::Log_Msg_UNIX_Syslog(void)
 {
 }

 Log_Msg_UNIX_Syslog::~Log_Msg_UNIX_Syslog(void)
 {
	 (void) this->close();
 }

 int Log_Msg_UNIX_Syslog::open(const geoTChar * logger_key)
 {
	 if (logger_key == 0)
		 logger_key =  GEOSYS_DEFAULT_NAME;

# if defined (_UNICODE)
	 openlog(GEO_ALWAYS_CHAR(logger_key), LOG_CONS | LOG_PID, LOG_USER);
# else
	 openlog(const_cast<char *> (logger_key),LOG_CONS | LOG_PID,LOG_USER);
# endif 
	 (void)setlogmask(LOG_UPTO(LOG_DEBUG));
	 return 0;
 }

 int Log_Msg_UNIX_Syslog::reset(void)
 {
	 return this->close();
 }

 int Log_Msg_UNIX_Syslog::close(void)
 {
	 closelog();
	 return 0;
 }

 int
	 Log_Msg_UNIX_Syslog::log(GeoLogRecord &log_record)
 {
	 int syslog_priority = this->convert_log_priority(log_record.type_);
	 u_long flags = GEO_LOG->flags();



	 geoTChar message[MAXVERBOSELOGMSGLEN];
	 geo_strcpy(message, log_record.msg_data());
	 geoTChar *strtokp = 0;

	 for (geoTChar *line = geo_strtok_r(message,GEO_TEXT("\n"),&strtokp);
		 line != 0;
		 line = geo_strtok_r(0,GEO_TEXT("\n"),&strtokp))
	 {

		 if (GEO_BIT_ENABLED(flags, GeoLog::VERBOSE)|| GEO_BIT_ENABLED(flags, GeoLog::VERBOSE_LITE))
		 {
			 geoTChar date_and_time[24];
			 if (0 == geo_timestamp(geoTime_Zero,date_and_time, sizeof(date_and_time), 1))
				 geo_strcpy(date_and_time, GEO_TEXT("<time error>"));
			 const geoTChar *prio_name = priority_name(Log_Priority(log_record.type_));
			 syslog(syslog_priority,"%s: %s: %s",
				 GEO_TEXT_ALWAYS_CHAR(date_and_time),
				 GEO_TEXT_ALWAYS_CHAR(prio_name),
				 GEO_TEXT_ALWAYS_CHAR(line));
		 }
		 else // No formatting required.
			 syslog(syslog_priority, "%s", GEO_TEXT_ALWAYS_CHAR(line));
	 }

	 return 0;
 }

 int Log_Msg_UNIX_Syslog::convert_log_priority(geoUInt32 lm_priority)
 {
	 int syslog_priority;
	 switch (lm_priority)
	 {
	 case LM_TRACE:
	 case LM_DEBUG:
		 syslog_priority = LOG_DEBUG;
		 break;
	 case LM_STARTUP:
	 case LM_SHUTDOWN:
	 case LM_INFO:
		 syslog_priority = LOG_INFO;
		 break;
	 case LM_NOTICE:
		 syslog_priority = LOG_NOTICE;
		 break;
	 case LM_WARNING:
		 syslog_priority = LOG_WARNING;
		 break;
	 case LM_CRITICAL:
		 syslog_priority = LOG_CRIT;
		 break;
	 case LM_ALERT:
		 syslog_priority = LOG_ALERT;
		 break;
	 case LM_EMERGENCY:
		 syslog_priority = LOG_EMERG;
		 break;
	 case LM_ERROR:
	 default:
		 syslog_priority = LOG_ERR;
		 break;
	 }

	 return syslog_priority;
 }

 int Log_Msg_UNIX_Syslog::convert_log_mask(int lm_mask)
 {
	 int syslog_mask = 0;

	 if (GEO_BIT_ENABLED(lm_mask, LM_TRACE)
		 || GEO_BIT_ENABLED(lm_mask, LM_DEBUG))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_DEBUG));

	 if (GEO_BIT_ENABLED(lm_mask, LM_STARTUP)
		 || GEO_BIT_ENABLED(lm_mask, LM_SHUTDOWN)
		 || GEO_BIT_ENABLED(lm_mask, LM_INFO))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_INFO));

	 if (GEO_BIT_ENABLED(lm_mask, LM_NOTICE))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_NOTICE));

	 if (GEO_BIT_ENABLED(lm_mask, LM_ERROR))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_ERR));

	 if (GEO_BIT_ENABLED(lm_mask, LM_WARNING))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_WARNING));

	 if (GEO_BIT_ENABLED(lm_mask, LM_CRITICAL))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_CRIT));

	 if (GEO_BIT_ENABLED(lm_mask, LM_ALERT))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_ALERT));

	 if (GEO_BIT_ENABLED(lm_mask, LM_EMERGENCY))
		 GEO_SET_BITS(syslog_mask, LOG_MASK(LOG_EMERG));

	 return syslog_mask;
 }

#endif