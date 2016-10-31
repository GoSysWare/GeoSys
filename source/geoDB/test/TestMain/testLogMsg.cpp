

#include"geoLogMsg.hh"
#include<ostream>
#include<fstream>
#pragma comment (lib,"geoUtils.lib")
int run_main(int argc, char** argv)
{

	//GEO_LOG->open( GeoLog::SYSLOG, "SysLog");

	//ostream *output = new std::ofstream("logfile.txt");
	//GEO_LOG->msg_ostream(output, 1);
	//GEO_LOG->set_flags(GeoLog::OSTREAM);
	//GEO_LOG->clr_flags(GeoLog::STDERR | GeoLog::LOGGER);
	//GEO_TRACE((LM_DEBUG, GEO_TEXT("%N %l %T %t text\n")));
	//GEO_TRACE((LM_DEBUG, GEO_TEXT("%N %t text\n")));
	trace_fout(GEO_TEXT("%N %l %T %t text\n"));
	trace_fout(GEO_TEXT("%N %t text\n"));
	trace_fout(GEO_TEXT("%N %t gadafdsad\n"));
	return 0;

}

int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}