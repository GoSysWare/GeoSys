#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "k_functionblock.h"
#include "k_util.h"

static size_t fb_size(fb_t *p_fb)
{
	return sizeof(fb_t) + (p_fb->h.ni + p_fb->h.no + p_fb->h.np) * sizeof(pin_t);
}

fb_t *fb_new(fb_t *p_source)
{
	fb_t *p_fb;
	size_t size;

	size = fb_size(p_source);
	p_fb = k_malloc(size);
	if(p_fb != ((void*) 0)){
		memcpy(p_fb, p_source, size);
	}

	return p_fb;
}

void fb_delete(fb_t *p_fb)
{
	k_free(p_fb);
}

/* n´Ó0¿ªÊ¼ */
pin_t *fb_getpin(fb_t *p_fb, int pintype, unsigned int n)
{
	int np;
	pin_t *p_pin;
	
	if(pintype == PININPUT){
		if(n >= p_fb->h.ni){
			return ((void*) 0);
		}
		np = n;
	}else if(pintype == PINOUTPUT){
		if(n >= p_fb->h.no){
			return ((void*) 0);
		}
		np = n + p_fb->h.ni;		
	}else if(pintype == PINPROPERTY){
		if(n >= p_fb->h.np){
			return ((void*) 0);
		}
		np = n + p_fb->h.ni + p_fb->h.no;
	}else{
		return ((void*) 0);
	}

	p_pin = p_fb->d + np;
	return p_pin;
}

int fb_setpin(fb_t *p_fb, int pintype, unsigned int n, var_t v)
{
	int np;
	pin_t *p_pin;
	
	if(pintype == PININPUT){
		if(n >= p_fb->h.ni){
			return -1;
		}
		np = n;
	}else if(pintype == PINOUTPUT){
		if(n >= p_fb->h.no){
			return 0;
		}
		np = n + p_fb->h.ni;		
		return -1;
	}else if(pintype == PINPROPERTY){
		if(n >= p_fb->h.np){
			return -1;
		}
		np = n + p_fb->h.ni + p_fb->h.no;
	}else{
		return -1;
	}

	p_pin = p_fb->d + np;
	p_pin->v = v;
	return 0;
}

void fb_dump(fb_t *p_fb)
{
	unsigned int i;
	char type[8], value[32];
	printf("fc:%s\n", p_fb->h.fcname);

	printf("input:\n");
	for(i = 0; i < p_fb->h.ni; i++){
		type2str(type, p_fb->d[i].t);
		var2str(value, p_fb->d[i].v, p_fb->d[i].t);
		printf("  %s, %s, %s.\n", p_fb->d[i].pinname, type, value);
	}

	printf("output:\n");
	for(i = 0 + p_fb->h.ni; i < (p_fb->h.no + p_fb->h.ni); i++){
		type2str(type, p_fb->d[i].t);
		var2str(value, p_fb->d[i].v, p_fb->d[i].t);
		printf("  %s, %s, %s.\n", p_fb->d[i].pinname, type, value);
	}

	printf("property:\n");
	for(i = 0 + p_fb->h.ni + p_fb->h.no; i < (p_fb->h.np + p_fb->h.ni + p_fb->h.no); i++){
		type2str(type, p_fb->d[i].t);
		var2str(value, p_fb->d[i].v, p_fb->d[i].t);
		printf("  %s, %s, %s.\n", p_fb->d[i].pinname, type, value);
	}
}

void fb_pins_to_string(fb_t *p_fb, char *str)
{
	unsigned int i;
	char type[8], value[32];

	*str=0;
	/* input */
	for(i = 0; i < p_fb->h.ni; i++){
		type2str(type, p_fb->d[i].t);
		var2str(value, p_fb->d[i].v, p_fb->d[i].t);
		strcat(str,p_fb->d[i].pinname);
		strcat(str,"/");
		strcat(str,type);
		strcat(str,"/");
		strcat(str,value);
		strcat(str,",");
	}
	strcat(str,",");
	strcat(str,";");
	/* output */
	for(i = 0 + p_fb->h.ni; i < (p_fb->h.no + p_fb->h.ni); i++){
		type2str(type, p_fb->d[i].t);
		var2str(value, p_fb->d[i].v, p_fb->d[i].t);
		strcat(str,p_fb->d[i].pinname);
		strcat(str,"/");
		strcat(str,type);
		strcat(str,"/");
		strcat(str,value);
		strcat(str,",");
	}	
	strcat(str,",");
	strcat(str,";");
	/* property */
	for(i = 0 + p_fb->h.ni + p_fb->h.no; i < (p_fb->h.np + p_fb->h.ni + p_fb->h.no); i++){
		type2str(type, p_fb->d[i].t);
		var2str(value, p_fb->d[i].v, p_fb->d[i].t);
		strcat(str,p_fb->d[i].pinname);
		strcat(str,"/");
		strcat(str,type);
		strcat(str,"/");
		strcat(str,value);
		strcat(str,",");
	}
	strcat(str,",");
}

void fb_vars_to_string(fb_t *p_fb, char *str)
{
	unsigned int i;
	char value[32];

	*str=0;
	
	for(i=0; i < (p_fb->h.np+p_fb->h.ni+p_fb->h.no); i++){
		var2str(value, p_fb->d[i].v, p_fb->d[i].t);
		strcat(str,value);
		strcat(str,",");
	}
}
