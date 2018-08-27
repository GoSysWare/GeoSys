#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "k_util.h"
#include "k_datatype.h"
#include "k_evdata.h"
#include "k_compress.h"

static evnode_t vn_head={&vn_head, &vn_head, 0, "", 0, 0, 0};
static evnode_t *p_vn_select=&vn_head;

void type2str(char *ct, int it)
{
	switch(it){
	case T_NONE:
		strcpy(ct, "NONE");
		break;
	case T_BOOL:
		strcpy(ct, "BOOL");
		break;
	case T_INT:
		strcpy(ct, "INT");
		break;
	case T_REAL:
		strcpy(ct, "REAL");
		break;
	case T_LREAL:
		strcpy(ct, "LREAL");
		break;
	case T_TIME:
		strcpy(ct, "TIME");
		break;
	case T_ANY:
		strcpy(ct, "ANY");
		break;
	default:
		strcpy(ct, "UNKNOWN");
	}
}

void str2type(char *ct, int *it)
{
	if(strcmp(ct, "BOOL")==0){
		*it = T_BOOL;
	}else if(strcmp(ct, "INT")==0){
		*it = T_INT;
	}else if(strcmp(ct, "REAL")==0){
		*it = T_REAL;
	}else if(strcmp(ct, "LREAL")==0){
		*it = T_LREAL;
	}else if(strcmp(ct, "TIME")==0){
		*it = T_TIME;
	}else if(strcmp(ct, "ANY")==0){
		*it = T_ANY;
	}else{
		*it = T_NONE;
	}
}

void var2str(char *str, var_t v, int it)
{
	switch(it){
	case T_NONE:
		*str = 0;
		break;
	case T_BOOL:
		sprintf(str, "%d", v.b);
		break;
	case T_INT:
		sprintf(str, "%d", v.i);
		break;
	case T_REAL:
		sprintf(str, "%g", v.f);
		break;
	case T_LREAL:
		sprintf(str, "%g", v.fl);
		break;
	case T_TIME:
		sprintf(str, "%g", v.tm);
		break;
	case T_ANY:
		*str = 0;
		break;
	default:
		strcat(str, "UNKNOWN");
	}
}

void str2var(char *str, var_t *v, int it)
{
	switch(it){
	case T_NONE:
		break;
	case T_BOOL:
		v->b = atoi(str);
		break;
	case T_INT:
		v->i = atoi(str);
		break;
	case T_REAL:
		v->f = (float)atof(str);
		break;
	case T_LREAL:
		v->fl = atof(str);
		break;
	case T_TIME:
		v->fl = atof(str);
	case T_ANY:
		;
		break;
	default:
		;
	}
}

static evnode_t *v_new()
{
	evnode_t *p_new;
	p_new = k_malloc(sizeof(evnode_t));

	return p_new;
}

static void v_delete(evnode_t *p_vn)
{
	k_free(p_vn);
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
	int t;

	if(id == 0){
		p_vn_select = &vn_head;
		return -1;
	}

	if(p_vn_select->id == id){
		return 0;
	}

	p_v = vn_head.p_next;
	while(p_v != &vn_head){
		t=p_v->id;
		if(p_v->id == id){
			p_vn_select=p_v;
			return 0;
		}
		p_v = p_v->p_next;
	}

	return -1;
}

val_t *ev_find(int id)
{
	if(ev_select(id)==0){
		return &p_vn_select->v;
	}else{
		return ((void*) 0);
	}
}

int ev_add(int id, char *type, char *val, char *name)
{
	int it;
	var_t v;
	evnode_t *p_vn;

	p_vn = v_new();
	if(p_vn == ((void*) 0)){
		return -1;
	}
	
	str2type(type, &it);
	str2var(val, &v, it);
    p_vn->id = id;
	p_vn->v.t = it;
	p_vn->v.v = v;

	strncpy(p_vn->name, name, EVNAMESIZE);
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
	char type[8], value[32];
	evnode_t *p_vn;

	p_vn_select=&vn_head;

	p_vn = vn_head.p_next;
	while(p_vn != &vn_head){
		type2str(type, p_vn->v.t);
		var2str(value, p_vn->v.v, p_vn->v.t);
		printf("ev:%d - %s,%s,%s\n", p_vn->id, p_vn->name, type, value);
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

char *ev_to_img(char *buf)
{
	evnode_t *p_vn;

	p_vn = vn_head.p_next;
	while(p_vn != &vn_head){
		buf+=cmps_zvar(&p_vn->v.v,p_vn->v.t,buf);
		p_vn = p_vn->p_next;
	}

	return buf;
}

char *ev_from_img(char *buf)
{
	Int t;
	evnode_t *p_vn;

	p_vn = vn_head.p_next;
	while(p_vn != &vn_head){
		buf+=cmps_uzvar(buf,&p_vn->v.v,&t);
		p_vn = p_vn->p_next;
	}
	return buf;
}

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
