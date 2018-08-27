#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS


#include <stdio.h>

#ifdef _WIN32
#include "Rpc.h"
#pragma comment(lib, "Rpcrt4.lib")
#elif defined(__LINUX__)
#include <uuid/uuid.h>
#endif


#include "geoGuid.h"

geoVoid GeoGUID::create()
{
#ifdef _WIN32
	//这里隐含的语法是当一个C++的类可以逐位拷贝，就是没有继承、重载等情况，它类似于一个struct
	//这里即this指针与this->data相同
	UuidCreate((UUID*)this);
#elif defined(__LINUX__)
	uuid_generate(data);
#else
	assert(0);
#endif
}


geoInt32 GeoGUID::to_string(geoChar * buffer)const
{
	geoUInt32 * l=(geoUInt32*)data;
	geoInt32 i;
	i=sprintf(buffer,"%08x-",*l);
	l++;
	geoUInt16 * s=(geoUInt16*)l;
	i+=sprintf(buffer+i,"%04x-",*s);
	s++;
	i+=sprintf(buffer+i,"%04x-",*s);
	s++;
	geoUInt8 *c=(geoUInt8*)s;
	i+=sprintf(buffer+i,"%02x",*c);
	c++;
	for(geoInt32 j=1;j<8;j++,c++){
		i+=sprintf(buffer+i,"%02x",*c);
	}
	return i;
}