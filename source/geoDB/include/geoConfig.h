

#ifndef  GEOSYS_OS_CONFIG_H__
#define  GEOSYS_OS_CONFIG_H__




#include "geoVersion.h"
#include "geoVersionNameSpace.h"

#define rtkm_node_key_length   16


////如果编译器不支持C++11编译自动失败
//#if __cplusplus < 20131103L  
//#error "should use C++ 11 implementation"  
//#endif  


#ifdef _WIN32
#pragma warning(disable:4996) //全部关掉
#endif // _WIN32


#endif