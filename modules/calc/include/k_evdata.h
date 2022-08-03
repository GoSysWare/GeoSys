#ifndef k_evdata_h
#define k_evdata_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_datatype.h"
#include "value.pb.h"


typedef shared_ptr<value_t> val_t;
typedef shared_ptr<value> vav_t;

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
void var2str(char *str, const val_t &v, int it);
void str2var(char *str, val_t *v, int it);

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
