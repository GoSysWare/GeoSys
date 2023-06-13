#include <stddef.h>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "modules/calc/include/k_functionblock.h"

#include "modules/calc/ioss/ioss.h"

#include "CURL_SEND"

static void *fb_table[]={
	&fb_CURL_SEND,

	};

static size_t cursor;


void http_int()
{
  curl_global_init(CURL_GLOBAL_ALL);
}




void *http_first()
{
	cursor = 0;
	return fb_table[0];
}

void *http_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
