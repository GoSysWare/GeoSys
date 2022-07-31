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
#define	T_CVMAT	0x70
#define	T_STRING 0x80

#define T_MASK	0xf0

union u_var_t{
	Bool b;
	Int i;
	Real f;
	LReal fl;
	Time tm;
	CvMat mat;
	String str;
	u_var_t(){};
	u_var_t(int i_):i(i_){};
	u_var_t(const u_var_t&){};
	~u_var_t(){};
};
typedef u_var_t var_t;
typedef struct st_val_t{
public:
	Int t;		/* type */
	Int f;		/* flag */
	var_t v;	/* value */
	st_val_t(){};
	st_val_t(Int t_):t(t_),f(0),v(0){};
	st_val_t(Int t_,Int f_):t(t_),f(f_),v(0){};
	st_val_t(Int t_,Int f_,var_t v_):t(t_),f(f_),v(v_){}
	st_val_t(const st_val_t & other){
		switch (t)
		{
			case T_BOOL:
			case T_INT:
			case T_REAL:
			case T_LREAL:
			case T_TIME:
				break;
			case T_STRING:
				new (&v.str)String();
				v.str = other.v.str;
				break;
			case T_CVMAT:
				new (&v.mat) CvMat();
				v.mat = other.v.mat;
				break;
			default:
				break;
		}	
	}
	st_val_t & operator = (const st_val_t & other)
	{
		switch (t)
		{
			case T_BOOL:
			case T_INT:
			case T_REAL:
			case T_LREAL:
			case T_TIME:
				break;
			case T_STRING:
				new (&v.str)String(other.v.str);
				break;
			case T_CVMAT:
				new (&v.mat) CvMat(other.v.mat);
				break;
			default:
				break;
		}	
		return *this;
	}
	~st_val_t()
	{
		switch (t)
		{
		case T_BOOL:
		case T_INT:
		case T_REAL:
		case T_LREAL:
		case T_TIME:
			break;
		case T_STRING:
			v.str.~String();
			break;
		case T_CVMAT:
			v.mat.~CvMat();
			break;
		default:
			break;
		}
	}

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
