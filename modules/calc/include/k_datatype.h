/* 为了简化数据的类型转换和传递，不支持无符号整数 */
#ifndef k_datatype_h
#define k_datatype_h
#ifdef __cplusplus
extern "C" {
#endif

#define PMC_OK 0
#define PMC_FAIL 1

#define PL_TRUE 1
#define PL_FALSE 0

typedef int Bool;
typedef int Int;
typedef float Real;
typedef double LReal;
typedef double Time;

typedef unsigned short Word;

#ifdef __cplusplus
}
#endif
#endif
