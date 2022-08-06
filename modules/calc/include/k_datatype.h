
#ifndef k_datatype_h
#define k_datatype_h

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PMC_OK 0
#define PMC_FAIL 1

#define PL_TRUE 1
#define PL_FALSE 0

typedef bool Bool;
typedef int8_t Short;
typedef uint8_t UShort;
typedef int16_t Word;
typedef uint16_t UWord;
typedef int32_t Int;
typedef uint32_t UInt;
typedef int64_t Long;
typedef uint64_t ULong;
typedef float Real;
typedef double LReal;
typedef uint64_t Time;

#pragma pack(push, 1)

typedef struct {
  int len;
  char *data;
} String;
typedef struct {
  int len;
  char *data;
} Blob;

#pragma pack(pop)

#ifdef __cplusplus
}
#endif
#endif
