#ifndef k_functionblock_h
#define k_functionblock_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_datatype.h"
#include "k_evdata.h"

// typedef void (*fbrun)(void *);


#define PININPUT 1
#define PINOUTPUT 2
#define PINPROPERTY 3
#define FBFLAGIO	0x00000001
#define FBFLAGEXPORT	0x00000002

using fb_function = std::function<void(void*)>;

//FB的头定义
typedef struct FBHead{
	std::string fcname;
	unsigned int ni;		/* in count */
	unsigned int no;		/* out count */
	unsigned int np;		/* property count */
    Int flag;			/* export fb */
	fb_function run;
	// fbrun run;
} fbhead_t;

typedef struct Pin{
	std::string pinname;
	v_type t;	/* type */
	vam_t v;	/* value */
} pin_t;

typedef struct FB{
	fbhead_t h;
	std::vector<pin_t> d;
} fb_t;

fb_t *fb_new(fb_t *p_source);
void fb_delete(fb_t *p_fb);
pin_t *fb_getpin(fb_t *p_fb, int pintype, unsigned int n);
int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, value_tm v);
std::string fb_pins_to_string(fb_t *p_fb);
std::string fb_vars_to_string(fb_t *p_fb);
void fb_dump(fb_t *p_fb);

// #ifdef __cplusplus
// }
// #endif
#endif
