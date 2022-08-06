#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_datatype.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_compress.h"

static evnode_t vn_head={&vn_head, &vn_head, 0, ""};
static evnode_t *p_vn_select=&vn_head;


void type2str( std::string& str, int it)
{
	const google::protobuf::EnumDescriptor * desc = v_type_descriptor();
	str = desc->FindValueByNumber(it)->name();
}

void str2type(const std::string& str, v_type *it)
{
	v_type_Parse(str,it);
}

void var2str( std::string & str, const vam_t &v)
{
	str = v->SerializeAsString();
}
	

void str2var(const std::string & str,const vam_t & v)
{
	v->ParseFromString(str);
}


static evnode_t *v_new()
{
	return new evnode_t;;
}

static void v_delete(evnode_t *p_vn)
{
	delete p_vn ;
}

static void v_addbefore(evnode_t *p, evnode_t *p_ref)
{
	p->p_prev = p_ref->p_prev;
	p->p_next = p_ref;
	p_ref->p_prev->p_next = p;
	p_ref->p_prev = p;
}

static void v_addafter(evnode_t *p, evnode_t *p_ref)
{
	p->p_prev = p_ref;
	p->p_next = p_ref->p_next;
	p_ref->p_next->p_prev = p;
	p_ref->p_next = p;
}

static void v_remove(evnode_t *p)
{
	p->p_prev->p_next = p->p_next;
	p->p_next->p_prev = p->p_prev;
}

static int ev_select(int id)
{
	evnode_t *p_v;

	if(id == 0){
		p_vn_select = &vn_head;
		return -1;
	}

	if(p_vn_select->id == id){
		return 0;
	}

	p_v = vn_head.p_next;
	while(p_v != &vn_head){
		if(p_v->id == id){
			p_vn_select=p_v;
			return 0;
		}
		p_v = p_v->p_next;
	}

	return -1;
}

vam_t *ev_find(int id)
{
	if(ev_select(id)==0){
		return &p_vn_select->v;
	}else{
		return 0;
	}
}
int ev_add(int id, const std::string & val, const std::string name)
{
	vam_t v(new value_tm);
	evnode_t *p_vn;

	p_vn = v_new();
	if(p_vn == 0){
		return -1;
	}
	v->ParseFromString(val);
    p_vn->id = id;
	p_vn->v = v;

	strncpy(p_vn->name, name.c_str(), EVNAMESIZE);
	v_addbefore(p_vn, &vn_head);
	
   // tag_ev_add(id, name);//qss for calc

	return 0;
}

int ev_remove(int id)
{
	ev_select(id);
	
	if(p_vn_select == &vn_head){
		return -1;
	}

	v_remove(p_vn_select);
	v_delete(p_vn_select);
	p_vn_select = &vn_head;

  //  tag_ev_rm(id);//qss for calc

	return 0;
}

void ev_reset()
{
	evnode_t *p_vn, *p_del;

	p_vn_select=&vn_head;

	p_vn = vn_head.p_next;
	while(p_vn != &vn_head){
		p_del = p_vn;
		p_vn = p_vn->p_next;
		v_remove(p_del);
		v_delete(p_del);
	}

  //  tag_ev_reset();//qss for calc
}

evnode_t* ev_gethead()
{
    return &vn_head;
}

void ev_dump()
{
	std::string value;
	evnode_t *p_vn;

	p_vn_select=&vn_head;

	p_vn = vn_head.p_next;
	while(p_vn != &vn_head){
		printf("ev:%d - %s,%d\n", p_vn->id, p_vn->name, p_vn->v->v().i());
		p_vn = p_vn->p_next;
	}
}

int ev_img_size()
{
	int s;
	evnode_t *p_vn;

	s=0;
	p_vn = vn_head.p_next;
	while(p_vn != &vn_head){
		s++;
		p_vn = p_vn->p_next;
	}
	return s;
}

// char *ev_to_img(char *buf)
// {
// 	evnode_t *p_vn;

// 	p_vn = vn_head.p_next;
// 	while(p_vn != &vn_head){
// 		buf+=cmps_zvar(&p_vn->v.v,p_vn->v.t,buf);
// 		p_vn = p_vn->p_next;
// 	}

// 	return buf;
// }

// char *ev_from_img(char *buf)
// {
// 	Int t;
// 	evnode_t *p_vn;

// 	p_vn = vn_head.p_next;
// 	while(p_vn != &vn_head){
// 		buf+=cmps_uzvar(buf,&p_vn->v.v,&t);
// 		p_vn = p_vn->p_next;
// 	}
// 	return buf;
// }

/*
static int bool_convert(val_t *t1, const val_t *t2)
{
	switch(t1->t){
	case T_BOOL:
		t1->v.b=(Bool)t2->v.b;
		break;
	case T_INT:
		t1->v.b=(Bool)t2->v.i;
		break;
	case T_REAL:
		t1->v.b=(Bool)t2->v.f;
		break;
	case T_LREAL:
		t1->v.b=(Bool)t2->v.fl;
		break;
	case T_TIME:
		t1->v.b=(Bool)t2->v.tm;
		break;
	default:
		return -1;
	}

	return 0;
}

static int int_convert(val_t *t1, const val_t *t2)
{
	switch(t1->t){
	case T_BOOL:
		t1->v.i=(Int)t2->v.b;
		break;
	case T_INT:
		t1->v.i=(Int)t2->v.i;
		break;
	case T_REAL:
		t1->v.i=(Int)t2->v.f;
		break;
	case T_LREAL:
		t1->v.i=(Int)t2->v.fl;
		break;
	case T_TIME:
		t1->v.i=(Int)t2->v.tm;
		break;
	default:
		return -1;
	}

	return 0;
}

static int real_convert(val_t *t1, const val_t *t2)
{
	switch(t1->t){
	case T_BOOL:
		t1->v.f=(Real)t2->v.b;
		break;
	case T_INT:
		t1->v.f=(Real)t2->v.i;
		break;
	case T_REAL:
		t1->v.f=(Real)t2->v.f;
		break;
	case T_LREAL:
		t1->v.f=(Real)t2->v.fl;
		break;
	case T_TIME:
		t1->v.f=(Real)t2->v.tm;
		break;
	default:
		return -1;
	}

	return 0;
}

static int lreal_convert(val_t *t1, const val_t *t2)
{
	switch(t1->t){
	case T_BOOL:
		t1->v.fl=(LReal)t2->v.b;
		break;
	case T_INT:
		t1->v.fl=(LReal)t2->v.i;
		break;
	case T_REAL:
		t1->v.fl=(LReal)t2->v.f;
		break;
	case T_LREAL:
		t1->v.fl=(LReal)t2->v.fl;
		break;
	case T_TIME:
		t1->v.fl=(LReal)t2->v.tm;
		break;
	default:
		return -1;
	}

	return 0;
}

static int time_convert(val_t *t1, const val_t *t2)
{
	switch(t1->t){
	case T_BOOL:
		t1->v.tm=(Time)t2->v.b;
		break;
	case T_INT:
		t1->v.tm=(Time)t2->v.i;
		break;
	case T_REAL:
		t1->v.tm=(Time)t2->v.f;
		break;
	case T_LREAL:
		t1->v.tm=(Time)t2->v.fl;
		break;
	case T_TIME:
		t1->v.tm=(Time)t2->v.tm;
		break;
	default:
		return -1;
	}

	return 0;
}

int evdata_convert(val_t *t1, const val_t *t2)
{
	int ret;

	switch(t2->t){
	case T_BOOL:
		ret=bool_convert(t1,t2);
		break;
	case T_INT:
		ret=int_convert(t1,t2);
		break;
	case T_REAL:
		ret=real_convert(t1,t2);
		break;
	case T_LREAL:
		ret=lreal_convert(t1,t2);
		break;
	case T_TIME:
		ret=time_convert(t1,t2);
		break;
	default:
		ret=-1;
	}

	return ret;
}

*/
