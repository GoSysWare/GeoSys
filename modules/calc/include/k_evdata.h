#ifndef k_evdata_h
#define k_evdata_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_datatype.h"
#include "modules/calc/proto/value.pb.h"


typedef std::shared_ptr<value_t> var_t;
typedef std::shared_ptr<value_tm> vam_t;

/* Variable Node */
typedef struct EVNode{
	struct EVNode *p_prev;
	struct EVNode *p_next;
	int id;
	char name[EVNAMESIZE];
	vam_t v;
} evnode_t;


void type2str( std::string& str, int it);
void str2type(const std::string& str, int *it);
void var2str( std::string & str, const var_t &v);
void str2var(const std::string & str,const var_t & v);

vam_t* ev_find(int id);
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
