#ifndef k_io_h
#define k_io_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_datatype.h"

typedef struct IOCell{
	char id[IOIDSIZE];
	char data[IODATASIZE];
}iocell_t;

#define IOFLAGUSED	0x00000001
typedef struct SHead{
	int rf;
	int wf;
	unsigned int rc;
	unsigned int rcs;
	unsigned int wc;
	unsigned int wcs;
}shead_t;

typedef struct IOStation{
	shead_t h;
	iocell_t in[IOCELLCOUNT];
	iocell_t out[IOCELLCOUNT];
}iostation_t;

iostation_t *io_getstation(int s);
iocell_t *io_getcellin(int s, int c);
iocell_t *io_getcellout(int s, int c);
void cell2str(iocell_t *cell, char *str);
void str2cell(iocell_t *cell, char *str);
void io_init();
void io_input();
void io_output();
void word_invert(Word *w);
char *io_to_img(char *buf);
char *io_from_img(char *buf);

// #ifdef __cplusplus
// }
// #endif
#endif
