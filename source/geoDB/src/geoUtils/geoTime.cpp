#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include"geoTime.h"

const geoTimeStamp  geoTime_Zero = 0;



//以毫秒为计量单位
//此计时以系统启动时间为基准，
//此时间可以得到系统启动后CPU的tick计数，表示系统启动了多少毫秒
//主要用在程序内部定时，调节系统时间对程序无影响的地方
GEO_UITLS_API geoTime   GEO_CALL geo_get_steady_time()
{
	return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();

}
//以毫秒为计量单位
//此时间可以得到当前系统时间
//主要用在时间戳上
GEO_UITLS_API geoTimeStamp  GEO_CALL geo_get_system_time()
{
	return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

}

//毫秒的geoTime转换为CPU的tick时间
//为标准函数和系统函数所用
GEO_UITLS_API steady_clock::time_point   GEO_CALL geo_geotime_to_steadytime(geoTime absTime)
{

	return steady_clock::time_point(steady_clock::duration(milliseconds(absTime)));
}

// Returns the given timestamp in the form
// "hour:minute:second:microsecond."  The month, day, and year are
// also stored in the beginning of the date_and_time array
// using ISO-8601 format.
// 012345678901234567890123456
// 2010-12-02 12:56:00.123456<nul>

GEO_UITLS_API geoTChar * GEO_CALL geo_timestamp(const geoTimeStamp& time_value,
	geoTChar date_and_time[],
	size_t date_and_timelen,
	bool return_pointer_to_first_digit)
{
	if (date_and_timelen < 24)
	{
		errno = EINVAL;
		return 0;
	}

	geoTimeStamp cur_time =
		(time_value == geoTime_Zero) ?
		geo_get_system_time() : time_value;
	time_t secs = cur_time / 1000;
	struct tm tms;
	geo_localtime_r(&secs, &tms);
	geo_snprintf(date_and_time,
		date_and_timelen,
		GEO_TEXT("%4.4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d.%03ld"),
		tms.tm_year + 1900,
		tms.tm_mon + 1,
		tms.tm_mday,
		tms.tm_hour,
		tms.tm_min,
		tms.tm_sec,
		static_cast<long> (cur_time % 1000));
	date_and_time[date_and_timelen - 1] = '\0';
	return &date_and_time[10 + (return_pointer_to_first_digit != 0)];
}
#if defined (_WIN32)
GEO_UITLS_API time_t GEO_CALL FileTimeToUnixTime(FILETIME & ft)
{
	ULARGE_INTEGER ull;

	ull.LowPart = ft.dwLowDateTime;
	ull.HighPart = ft.dwHighDateTime;

	return ull.QuadPart / 10000000ULL - 11644473600ULL;
}
#endif