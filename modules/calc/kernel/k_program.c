#include <stddef.h>
#include <stdio.h>

#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_program.h"
#include "modules/calc/include/k_project.h"

static enode_t *en_new()
{
	return k_malloc(sizeof(enode_t));
}

static vnode_t *vn_new()
{
	return k_malloc(sizeof(vnode_t));
}

static void en_delete(enode_t *p_en)
{
	k_free(p_en);
}

static void vn_delete(vnode_t *p_vn)
{
	k_free(p_vn);
}

static void en_addbefore(enode_t *p_en, enode_t *p_ref)
{
	p_en->p_prev = p_ref->p_prev;
	p_en->p_next = p_ref;
	p_ref->p_prev->p_next = p_en;
	p_ref->p_prev = p_en;
}

static void en_addafter(enode_t *p_en, enode_t *p_ref)
{
	p_en->p_prev = p_ref;
	p_en->p_next = p_ref->p_next;
	p_ref->p_next->p_prev = p_en;
	p_ref->p_next = p_en;
}

static void en_remove(enode_t *p_en)
{
	p_en->p_prev->p_next = p_en->p_next;
	p_en->p_next->p_prev = p_en->p_prev;
}

static void en_movebefore(enode_t *p_en, enode_t *p_ref)
{
	en_remove(p_en);
	en_addbefore(p_en, p_ref);
}

static void en_moveafter(enode_t *p_en, enode_t *p_ref)
{
	en_remove(p_en);
	en_addafter(p_en, p_ref);
}

static void vn_addbefore(vnode_t *p_vn, vnode_t *p_ref)
{
	p_vn->p_prev = p_ref->p_prev;
	p_vn->p_next = p_ref;
	p_ref->p_prev->p_next = p_vn;
	p_ref->p_prev = p_vn;
}

static void vn_addafter(enode_t *p_vn, enode_t *p_ref)
{
	p_vn->p_prev = p_ref;
	p_vn->p_next = p_ref->p_next;
	p_ref->p_next->p_prev = p_vn;
	p_ref->p_next = p_vn;
}

static void vn_remove(vnode_t *p_vn)
{
	p_vn->p_prev->p_next = p_vn->p_next;
	p_vn->p_next->p_prev = p_vn->p_prev;
}

void prg_exec(prog_t *p_prg)
{
	vnode_t *p_vn;
	enode_t *p_en;
	
	/* ev to fb */
	p_vn = p_prg->vnin_head.p_next;
	while(p_vn != &p_prg->vnin_head){
		memcpy(&p_vn->p_pin->v,&p_vn->p_val->v,sizeof(var_t));
		p_vn = p_vn->p_next;
	}

	/* fb to fb */
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		if(p_en->p_fb != ((void*) 0)){
			p_en->p_fb->h.run(p_en->p_fb); 
		}else{
			memcpy(&p_en->p_vtgt->v, &p_en->p_vsrc->v, sizeof(var_t));
		}
		p_en = p_en->p_next;
	}

	/* fb to ev */
	p_vn = p_prg->vnout_head.p_next;
	while(p_vn != &p_prg->vnout_head){
		memcpy(&p_vn->p_val->v,&p_vn->p_pin->v,sizeof(var_t));
		p_vn = p_vn->p_next;
	}
}

prog_t *prg_new()
{
	prog_t *p_new;

	p_new = k_malloc(sizeof(prog_t));
	if(p_new != ((void*) 0)){
		p_new->en_head.p_prev = &p_new->en_head;
		p_new->en_head.p_next = &p_new->en_head;
		p_new->vnin_head.p_prev = &p_new->vnin_head;
		p_new->vnin_head.p_next = &p_new->vnin_head;
		p_new->vnout_head.p_prev = &p_new->vnout_head;
		p_new->vnout_head.p_next = &p_new->vnout_head;
		p_new->p_en_select = &p_new->en_head;
		p_new->p_vnin_select = &p_new->vnin_head;
		p_new->p_vnout_select = &p_new->vnout_head;
	}

	return p_new;
}

void prg_delete(prog_t *p_prg)
{
	enode_t *p_en, *p_erm;
	vnode_t *p_vn, *p_vrm;

	/* clear enode list */
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_erm = p_en;
		p_en = p_en->p_next;
		if(p_erm->p_fb != ((void*) 0)){
			fb_delete(p_erm->p_fb);
		}
		en_remove(p_erm);
		en_delete(p_erm);
	}	

	/* clear vnode list*/
	p_vn = p_prg->vnin_head.p_next;
	while(p_vn != &p_prg->vnin_head){
		p_vrm = p_vn;
		p_vn = p_vn->p_next;
        vn_remove(p_vrm);
		vn_delete(p_vrm);
	}

	p_vn = p_prg->vnout_head.p_next;
	while(p_vn != &p_prg->vnout_head){
		p_vrm = p_vn;
		p_vn = p_vn->p_next;
		vn_remove(p_vrm);
		vn_delete(p_vrm);
	}

	k_free(p_prg);
}

static void prg_setrank(prog_t *p_prg)
{
	int i;
	enode_t *p_en;

	i = 0;
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_en->rank = i;
		i++;
		p_en = p_en->p_next;
	}
}

static void prg_clearmark(prog_t *p_prg)
{
	enode_t *p_en;
	vnode_t *p_vn;

	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_en->mark = 0;
		p_en = p_en->p_next;
	}

	p_vn=p_prg->vnin_head.p_next;
	while(p_vn!=&p_prg->vnin_head){
		p_vn->mark=0;
		p_vn=p_vn->p_next;
	}

	p_vn=p_prg->vnout_head.p_next;
	while(p_vn!=&p_prg->vnout_head){
		p_vn->mark=0;
		p_vn=p_vn->p_next;
	}
}

static void prg_markfbchild(prog_t *p_prg, enode_t *p_en)
{
	p_en->mark = 1;
	while(p_en != &p_prg->en_head){
		if(p_en->p_fb == ((void*) 0)){
			p_en->mark = p_en->p_prev->mark;
			if(p_en->mark){
				p_en->p_entgt->mark = 1;
			}
		}
		p_en = p_en->p_next;
	}
}

static void prg_markfblink(prog_t *p_prg, enode_t *p_enfb)
{
	enode_t *p_en;
	vnode_t *p_vn;

	p_enfb->mark = 1;

	p_en=p_prg->en_head.p_next;
	while(p_en !=&p_prg->en_head){
		if(p_en->p_fb == ((void*) 0)){
			if(p_en->idsrc == p_enfb->id || p_en->idtgt == p_enfb->id){
				p_en->mark = 1;
			}
		}
		p_en=p_en->p_next;
	}

	p_vn=p_prg->vnin_head.p_next;
	while(p_vn!=&p_prg->vnin_head){
		if(p_vn->idfb==p_enfb->id){
			p_vn->mark=1;
		}
		p_vn=p_vn->p_next;
	}

	p_vn=p_prg->vnout_head.p_next;
	while(p_vn!=&p_prg->vnout_head){
		if(p_vn->idfb==p_enfb->id){
			p_vn->mark=1;
		}
		p_vn=p_vn->p_next;
	}
}

int prg_fbadd(prog_t *p_prg, int id, char *libname, char *fcname, char *fbname)
{
	fb_t *p_fb;
	enode_t *p_en;

	p_fb = lib_find(libname, fcname);
	if(((void*) 0) == p_fb){
		return -1;
	}

	p_fb = fb_new(p_fb);
	if(((void*) 0) == p_fb){
		return -1;
	}

	p_en = en_new();
	if(((void*) 0) == p_en){
		fb_delete(p_fb);
		return -1;
	}
	p_en->id = id;
	p_en->p_fb = p_fb;
	strncpy(p_en->fbname, fbname, FBNAMESIZE);

	en_addbefore(p_en, &p_prg->en_head);

	return 0;
}

static int prg_enselect(prog_t *p_prg, int id)
{
	enode_t *p_en;

	if(id == 0){
		p_prg->p_en_select = &p_prg->en_head;
		return -1;
	}

	if(p_prg->p_en_select->id == id){
		return 0;
	}
	
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		if(p_en->id == id){
			p_prg->p_en_select = p_en;
			return 0;
		}
		p_en = p_en->p_next;
	}

	return -1;
}

fb_t *prg_fbfind(prog_t *p_prg, int id)
{
	enode_t *p_en;

	prg_enselect(p_prg, id);
	p_en = p_prg->p_en_select;

	if(p_en == &p_prg->en_head){
		return ((void*) 0);
	}
	
	return p_en->p_fb;
}

int prg_fbremove(prog_t *p_prg, int id)
{
	enode_t *p_en, *p_rm;
	vnode_t *p_vn, *p_vrm;

	prg_enselect(p_prg, id);
	p_en = p_prg->p_en_select;
	p_prg->p_en_select = &p_prg->en_head;
	if(p_en == &p_prg->en_head){
		return -1;
	}
	
	prg_clearmark(p_prg);
	prg_markfblink(p_prg, p_en);

	
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		p_rm = p_en;
		p_en = p_en->p_next;
		if(p_rm->mark){
			if(p_rm->p_fb != ((void*) 0)){
				fb_delete(p_rm->p_fb);
			}
			en_remove(p_rm);
			en_delete(p_rm);
		}
	}

	p_prg->p_vnin_select=&p_prg->vnin_head;
	p_vn=p_prg->vnin_head.p_next;
	while(p_vn!=&p_prg->vnin_head){
		p_vrm=p_vn;
		p_vn=p_vn->p_next;
		if(p_vrm->mark){
			vn_remove(p_vrm);
			vn_delete(p_vrm);
		}
	}

	p_prg->p_vnout_select=&p_prg->vnout_head;
	p_vn=p_prg->vnout_head.p_next;
	while(p_vn!=&p_prg->vnout_head){
		p_vrm=p_vn;
		p_vn=p_vn->p_next;
		if(p_vrm->mark){
			vn_remove(p_vrm);
			vn_delete(p_vrm);
		}
	}

	return 0;
}

int prg_viadd(prog_t *p_prg, int id, int idev, int idfb, int pin)
{
	vnode_t vn, *p_new;
	fb_t *p_fb;

	vn.id = id;
	
	vn.idev = idev;
	vn.p_val = ev_find(idev);
	if(vn.p_val == ((void*) 0)){
		return -1;
	}

	vn.idfb = idfb;
	p_fb = prg_fbfind(p_prg, idfb);
	if(p_fb == ((void*) 0)){
		return -1;
	}
	vn.p_pin = fb_getpin(p_fb, PININPUT, pin);
	if(vn.p_pin == ((void*) 0)){
		return -1;
	}
	
	p_new = vn_new();
	if(p_new == ((void*) 0)){
		return -1;
	}

	memcpy(p_new, &vn, sizeof(vnode_t));

	vn_addbefore(p_new, &p_prg->vnin_head);
   // tag_in_add(id, idev);//qss for calc
	return 0;
}

int prg_voadd(prog_t *p_prg, int id, int idev, int idfb, int pin)
{
	vnode_t vn, *p_new;
	fb_t *p_fb;

	vn.id = id;
	
	vn.idev = idev;
	vn.p_val = ev_find(idev);
	if(vn.p_val == ((void*) 0)){
		return -1;
	}

	vn.idfb = idfb;
	p_fb = prg_fbfind(p_prg, idfb);
	if(p_fb == ((void*) 0)){
		return -1;
	}
	vn.p_pin = fb_getpin(p_fb, PINOUTPUT, pin);
	if(vn.p_pin == ((void*) 0)){
		return -1;
	}
	
	p_new = vn_new();
	if(p_new == ((void*) 0)){
		return -1;
	}

	memcpy(p_new, &vn, sizeof(vnode_t));

	vn_addbefore(p_new, &p_prg->vnout_head);
 //   tag_out_add(id, idev);//qss for calc
	return 0;
}

static int prg_vninselect(prog_t *p_prg, int id)
{
	vnode_t *p_vn;

	if(id == 0){
		p_prg->p_vnin_select = &p_prg->vnin_head;
		return -1;
	}

	if(p_prg->p_vnin_select->id == id){
		return 0;
	}
	
	p_vn = p_prg->vnin_head.p_next;
	while(p_vn != &p_prg->vnin_head){
		if(p_vn->id == id){
			p_prg->p_vnin_select = p_vn;
			return 0;
		}
		p_vn = p_vn->p_next;
	}

	return -1;
}

static int prg_vnoutselect(prog_t *p_prg, int id)
{
	vnode_t *p_vn;

	if(id == 0){
		p_prg->p_vnout_select = &p_prg->vnout_head;
		return -1;
	}

	if(p_prg->p_vnout_select->id == id){
		return 0;
	}
	
	p_vn = p_prg->vnout_head.p_next;
	while(p_vn != &p_prg->vnout_head){
		if(p_vn->id == id){
			p_prg->p_vnout_select = p_vn;
			return 0;
		}
		p_vn = p_vn->p_next;
	}

	return -1;
}

int prg_viremove(prog_t *p_prg, int id)
{
	vnode_t *p_rm;

	prg_vninselect(p_prg, id);

	if(p_prg->p_vnin_select == &p_prg->vnin_head){
		return -1;
	}
	
	p_rm = p_prg->p_vnin_select;
	p_prg->p_vnin_select = &p_prg->vnin_head;
	
	vn_remove(p_rm);
	vn_delete(p_rm);
  //  tag_in_rm(id);//qss for calc
	return 0;
}

int prg_voremove(prog_t *p_prg, int id)
{
	vnode_t *p_rm;

	prg_vnoutselect(p_prg, id);

	if(p_prg->p_vnout_select == &p_prg->vnout_head){
		return -1;
	}
	
	p_rm = p_prg->p_vnout_select;
	p_prg->p_vnout_select = &p_prg->vnout_head;
	
	vn_remove(p_rm);
	vn_delete(p_rm);
  //  tag_out_rm(id);//qss for calc
	return 0;
}

int prg_lkadd(prog_t *p_prg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt)
{
	enode_t en, *p_en, *p_mv;
	enode_t *p_src, *p_tgt;
	
	/* get link map */
	prg_enselect(p_prg, fbsrc);
	p_src = p_prg->p_en_select;
	if(p_src == &p_prg->en_head){
		return -1;
	}
	if(p_src->p_fb == ((void*) 0)){
		return -1;
	}
	en.p_vsrc = fb_getpin(p_src->p_fb, PINOUTPUT, pinsrc);
	if(en.p_vsrc == ((void*) 0)){
		return -1;
	}

	prg_enselect(p_prg, fbtgt);
	p_tgt = p_prg->p_en_select;
	if(p_tgt == &p_prg->en_head){
		return -1;
	}
	if(p_tgt->p_fb == ((void*) 0)){
		return -1;
	}
	en.p_vtgt = fb_getpin(p_tgt->p_fb, PININPUT, pintgt);
	if(en.p_vtgt == ((void*) 0)){
		return -1;
	}

	if(en.p_vsrc->t != en.p_vtgt->t){		
		return -1;
	}

	en.id = id;
	en.idsrc = fbsrc;
	en.p_ensrc = p_src;
	en.idtgt = fbtgt;
	en.p_entgt = p_tgt;
	en.p_fb = ((void*) 0);

	p_en = en_new();
	if(p_en == ((void*) 0)){
		return -1;
	}
	memcpy(p_en, &en, sizeof(enode_t));
	en_addafter(p_en, p_src);

	prg_setrank(p_prg);
	//
	if(p_src->rank > p_tgt->rank){
		p_en = p_src->p_next;
		en_movebefore(p_src, p_tgt);
		while(p_en->p_fb == ((void*) 0) && p_en != &p_prg->en_head){
			p_mv = p_en;
			p_en = p_en->p_next;
			en_moveafter(p_mv, p_src);
		}
	}

	return 0;
}

int prg_lkremove(prog_t *p_prg, int id)
{
	enode_t *p_rm;

	prg_enselect(p_prg, id);
	p_rm = p_prg->p_en_select;
	p_prg->p_en_select = &p_prg->en_head;
	if(p_rm == &p_prg->en_head){ 
		return -1;
	}	

	if(p_rm->p_fb != ((void*) 0)){
		fb_delete(p_rm->p_fb);
	}
	en_remove(p_rm);
	en_delete(p_rm);

	return 0;
}

void prg_dump(prog_t *p_prg)
{
	vnode_t *p_vn;
	enode_t *p_en;

	printf("vi:\n");
	p_vn = p_prg->vnin_head.p_next;
	while(p_vn != &p_prg->vnin_head){
		printf("  id:%d ev:%d fb:%d pin:%s\n", p_vn->id, p_vn->idev, p_vn->idfb, p_vn->p_pin->pinname);
		p_vn = p_vn->p_next;
	}
	
	printf("en:\n");
	p_en = p_prg->en_head.p_next;
	while(p_en != &p_prg->en_head){
		if(p_en->p_fb != ((void*) 0)){
			printf("  fb:%d - %s, fc:%s\n", p_en->id, p_en->fbname, p_en->p_fb->h.fcname);
		}else{
			printf("  lk:%d , src.pin:%d.%s tgt.pin:%d.%s\n", 
				p_en->id, p_en->idsrc, p_en->p_vsrc->pinname, p_en->idtgt, p_en->p_vtgt->pinname);
		}
		p_en = p_en->p_next;
	}

	printf("vo:\n");
	p_vn = p_prg->vnout_head.p_next;
	while(p_vn != &p_prg->vnout_head){
		printf("  id:%d ev:%d fb.pin:%d.%s\n", p_vn->id, p_vn->idev, p_vn->idfb, p_vn->p_pin->pinname);
		p_vn = p_vn->p_next;
	}
}

int prg_checkloop(prog_t *p_prg, int idSrc, int idTgt)
{
	enode_t *p_src, *p_tgt;

	if(idSrc==idTgt){
		return -1;
	}

	prg_enselect(p_prg, idSrc);
	p_src = p_prg->p_en_select;
	prg_enselect(p_prg, idTgt);
	p_tgt = p_prg->p_en_select;
	if(p_src == &p_prg->en_head || p_tgt == &p_prg->en_head){
		return -1;
	}

	prg_setrank(p_prg);
	if(p_src->rank > p_tgt->rank){
		prg_clearmark(p_prg);
		prg_markfbchild(p_prg, p_tgt);
		if(p_src->mark){
			/* have loop */
			return -1;
		}
	}
	
	/* no loop */
	return 0;
}
