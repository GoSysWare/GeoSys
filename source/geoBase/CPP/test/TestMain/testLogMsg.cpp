

#include"geoLogMsg.hh"
#include<ostream>
#include<fstream>
#pragma comment (lib,"geoUtils.lib")


//#define debug(level, fmt, ...) printf(fmt, ##args)
//
//int run_main(int argc, char** argv)
//{
//
//	//GEO_LOG->open( GeoLog::SYSLOG, "SysLog");
//
//	//ostream *output = new std::ofstream("logfile.txt");
//	//GEO_LOG->msg_ostream(output, 1);
//	//GEO_LOG->set_flags(GeoLog::OSTREAM);
//	//GEO_LOG->clr_flags(GeoLog::STDERR | GeoLog::LOGGER);
//	//GEO_TRACE((LM_DEBUG, GEO_TEXT("%N %l %T %t text\n")));
//	//GEO_TRACE((LM_DEBUG, GEO_TEXT("%N %t text\n")));
//	//trace_fout(GEO_TEXT("%N %l %T %t text\n"));
//	//trace_fout(GEO_TEXT("%N %t text\n"));
//	//trace_fout(GEO_TEXT("%N %t gadafdsad\n"));
//	int a = 5, b = 6;
//	trace_printf(GEO_TEXT("gadafdsad %d,%d\n"),a,b);
//	GEO_TRACE((LM_DEBUG, GEO_TEXT("%N %l text %d ,%d\n"),a,b));
//	return 0;
//
//}
//
//int main(int argc, char** argv)
//{
//	run_main(argc, argv);
//
//	return 0;
//}
#include <stdio.h>

#include <windows.h>

void main()

{

	LARGE_INTEGER nFreq;

	LARGE_INTEGER nBeginTime;

	LARGE_INTEGER nEndTime;

	double time;



	QueryPerformanceFrequency(&nFreq);

	QueryPerformanceCounter(&nBeginTime);



	Sleep(1000);



	QueryPerformanceCounter(&nEndTime);

	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;

	ULONGLONG l = GetTickCount64();

	printf("%f\n", time);

	Sleep(1000);

	system("Pause");

}