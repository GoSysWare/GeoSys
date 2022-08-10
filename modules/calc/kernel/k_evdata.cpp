#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <google/protobuf/text_format.h>

#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_datatype.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_compress.h"


static evnode_t vn_head={&vn_head, &vn_head, 0, "",nullptr};
static evnode_t *p_vn_select=&vn_head;


std::string type2str( v_type it)
{
	const google::protobuf::EnumDescriptor * desc = v_type_descriptor();
	return desc->FindValueByNumber(it)->name();
}

v_type str2type(const std::string& str)
{
	v_type it;
	v_type_Parse(str,&it);
	return it;

}

std::string var2str( const value_tm &v)
{
	return v.SerializeAsString();
}
	

value_tm str2var(const std::string & str)
{
	value_tm v ;
	v.ParseFromString(str);
	return v;

}

void setvar(vam_t vam,value_tm val)
{
	if(vam->v().t() != val.v().t()){
		return ;
	}
	value_t * vt = vam->mutable_v();
	switch (val.v().t())
	{
	case T_NONE:
		break;
	case T_BOOL:
		vt->set_b(val.v().b());
		break;
	case T_INT32:
		vt->set_i(val.v().i());
		break;	
	case T_UINT32:
		vt->set_ui(val.v().ui());
		break;	
	case T_INT64:
		vt->set_ll(val.v().ll());
		break;
	case T_UINT64:
		vt->set_ull(val.v().ull());
		break;	
	case T_FLOAT32:
		vt->set_i(val.v().i());
		break;	
	case T_FLOAT64:
		vt->set_d(val.v().d());
		break;
	case T_TIME:
		vt->set_tm(val.v().tm());
		break;
	case T_STRING:
		vt->set_str(val.v().str());
		break;	
	case T_BYTES:
		vt->set_blob(val.v().blob());
		break;	
	case T_IMAGE:
		vt->set_img(val.v().img());
		break;
	case T_LIDAR:
		vt->set_lidar(val.v().lidar());
		break;
	case T_SONAR:
		vt->set_sonar(val.v().sonar());
		break;
	case T_FILE:
		vt->set_file(val.v().file());
		break;		
	default:
		break;
	}
}

bool setvar(vam_t vam,v_type t, value_tm val)
{
	if(t != val.v().t()){
		return false;
	}
	value_t * vt = vam->mutable_v();
	vt->set_t(val.v().t());
	switch (t)
	{
	case T_NONE:
		break;
	case T_BOOL:
		vt->set_b(val.v().b());
		break;
	case T_INT32:
		vt->set_i(val.v().i());
		break;	
	case T_UINT32:
		vt->set_ui(val.v().ui());
		break;	
	case T_INT64:
		vt->set_ll(val.v().ll());
		break;
	case T_UINT64:
		vt->set_ull(val.v().ull());
		break;	
	case T_FLOAT32:
		vt->set_i(val.v().i());
		break;	
	case T_FLOAT64:
		vt->set_d(val.v().d());
		break;
	case T_TIME:
		vt->set_tm(val.v().tm());
		break;
	case T_STRING:
		vt->set_str(val.v().str());
		break;	
	case T_BYTES:
		vt->set_blob(val.v().blob());
		break;	
	case T_IMAGE:
		vt->set_img(val.v().img());
		break;
	case T_LIDAR:
		vt->set_lidar(val.v().lidar());
		break;
	case T_SONAR:
		vt->set_sonar(val.v().sonar());
		break;
	case T_FILE:
		vt->set_file(val.v().file());
		break;		
	default:
		break;
	}
	return true;
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

vam_t * ev_find_v(int id)
{
	if(ev_select(id)==0){
		return &p_vn_select->v;
	}
	return nullptr;
}

int ev_add(int id, const std::string & str, const std::string & name)
{
	evnode_t *p_vn;

	p_vn = v_new();
	if(p_vn == 0){
		return -1;
	}

    p_vn->id = id;
	p_vn->name = name;
	p_vn->v = std::make_shared<value_tm>(str2var(str));

	v_addbefore(p_vn, &vn_head);
	
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
		std::cout << "ev: " 
			<< p_vn->id 
			<<"- " 
			<<p_vn->name
			<<": "
			<< p_vn->v->ShortDebugString()
			<<std::endl;
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
