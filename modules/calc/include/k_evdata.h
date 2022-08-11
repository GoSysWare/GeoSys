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
	std::string name;
	vam_t v;
} evnode_t;

std::string type2str( v_type it);
v_type str2type(const std::string& str);
std::string  var2str(const value_tm &v);
value_tm str2var(const std::string & str);
void setvar(vam_t vam,value_tm val);
int setvar(vam_t vam,v_type t, value_tm val);

vam_t * ev_find_v(int id);
int ev_add(int id, const std::string & val, const std::string &name);
int ev_remove(int id);
void ev_reset();
void ev_dump();
evnode_t* ev_gethead();
int ev_img_size();
// char *ev_to_img(char *buf);
// char *ev_from_img(char *buf);

// #ifdef __cplusplus
// }
// #endif
#endif
