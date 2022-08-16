#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"
#include <opencv2/opencv.hpp>
#include "modules/calc/proto/image.pb.h"
#include "IMG_READ"
#include "IMG_WRITE"


static void *fb_table[]={
	&fb_OPENCV_READ,
	&fb_OPENCV_WRITE,
	};

static size_t cursor;

void *opencv_first()
{
	cursor = 0;
	return fb_table[0];
}

void *opencv_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
