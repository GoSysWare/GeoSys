#ifndef k_evdata_h
#define k_evdata_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_datatype.h"

#define T_NONE	0
#define T_BOOL	0x10
#define T_INT	0x20
#define T_REAL	0x30
#define T_LREAL	0x40
#define T_TIME  0x50
#define	T_ANY	0x60
#define	T_CVIMG	0x70
#define	T_STRING 0x80

#define T_MASK	0xf0

typedef union{
	Bool b;
	Int i;
	Real f;
	LReal fl;
	Time tm;
	CvImg *mat;
	String *str;

} var_t;

typedef struct{
	Int t;		/* type */
	Int f;		/* flag */
	var_t v;	/* value */
} val_t;

/* Variable Node */
typedef struct EVNode{
	struct EVNode *p_prev;
	struct EVNode *p_next;
	int id;
	char name[EVNAMESIZE];
	val_t v;
} evnode_t;

void type2str(char *ct, int it);
void str2type(char *ct, int *it);
void var2str(char *str, const var_t &v, int it);
void str2var(char *str, var_t *v, int it);

val_t* ev_find(int id);
int ev_add(int id, char *type, char *val, char *name);
int ev_remove(int id);
void ev_reset();
void ev_dump();
evnode_t* ev_gethead();
int ev_img_size();
char *ev_to_img(char *buf);
char *ev_from_img(char *buf);

// #ifdef __cplusplus
// }
// #endif
#endif
