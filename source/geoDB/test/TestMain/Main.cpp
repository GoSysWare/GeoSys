///////////////////////////////////////////////////////////////////////////////////
///// Copyright (C), GeoSysWare 2016-2020,
///// \file  WindowsNT
///// \brief Windows Nice Try.
///// \author George Kuo 
///// \version 1.0.0
///// \date    2016-2017
///// \warning This class may explode in your face.
//
///// \Function List
//
///// \History: 
/////                 
/////     George Kuo   2016/6/1     1.0.0.1606     create file
///////////////////////////////////////////////////////////////////////////////////
//
//
//
#include"stdlib.h"
#include"stdio.h"
#include<string.h>
//#include"geoTime.hh"
//
//
//


extern int run_main(int argc, char** argv)
{
	char *src = "gfdafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafdsafsdafdsa";
	char *se = new char[9200*1000];
	char dest[10] = { 0 };
	long long  ops =0;
	for (int i = 0; i < 30000; i++)
	{
		memcpy(se + ops, src, 100);
		ops += 100;
	}


	


	return 0;
}

int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}
//
