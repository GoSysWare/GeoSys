#ifndef rtdb_h
#define rtdb_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "modules/calc/include/k_datatype.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/evbus.h"

#define DESCSIZE 32
#define EUSIZE  8
#define AM_ON	0x01
#define AM_OFF	0x02
#define AM_LO	0x04
#define AM_LOLO	0x08
#define AM_HI	0x10
#define AM_HIHI	0x20
#define FG_ALARM	0xff
#define FG_CONFIG	0x1000
#define FG_VALID	0x8000
typedef struct Tag{
	char name[EVNAMESIZE];
	char desc[DESCSIZE];
	char eu[EUSIZE];
	Int type;
	Int flag;
	Int mask;
	Int group;
	float min;
	float max;
	float lo;
	float lolo;
	float hi;
	float hihi;
	Time uptime;
	val_t val;
} tag_t;

typedef struct TagID{
	int id_station;
	int id_tag;
}tagid_t;


int rtdb_init();
void rtdb_uninit();
void rtdb_loadcfg();
void rtdb_savecfg();

// #ifdef __cplusplus
// }
// #endif
#endif