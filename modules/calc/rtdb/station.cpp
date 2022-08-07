#include <stdio.h>
#include <stdlib.h>
#include "modules/calc/include/k_datatype.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_util.h"
#include "helper.h"
#include "rtdb.h"
#include "station.h"

static void name_destroy(void *pd)
{
	k_free(pd);
}

static void tag_destroy(void *pd)
{
	k_free(pd);
}

static int name_compare(void *pd1, void *pd2)
{
	namenode_t *p1, *p2;
	p1=(namenode_t*)pd1;
	p2=(namenode_t*)pd2;
	return strncmp(p1->name, p2->name, EVNAMESIZE);
}

static int tag_compare(void *pd1, void *pd2)
{
	tagnode_t *p1, *p2;
	p1=(tagnode_t*)pd1;
	p2=(tagnode_t*)pd2;
	if(p1->id<p2->id){
		return -1;
	}else if(p1->id>p2->id){
		return 1;
	}else{
		return 0;
	}
}

static RBTREE *nametree_create()
{
	return RBTree_Create();
}

static RBTREE *tagtree_create()
{
	return RBTree_Create();
}

static void nametree_destroy(RBTREE *p_tree)
{
	RBTree_Destroy(p_tree, name_destroy);
}

static void tagtree_destroy(RBTREE *p_tree)
{
	RBTree_Destroy(p_tree, tag_destroy);
}

static int nametree_insert(RBTREE *p_tree, namenode_t *pd)
{
	return RBTree_Insert(p_tree,pd,name_compare);
}

static int tagtree_insert(RBTREE *p_tree, tagnode_t *pd)
{
	return RBTree_Insert(p_tree,pd,tag_compare);
}

static int nametree_delete(RBTREE *p_tree, namenode_t *pd)
{
	return RBTree_Delete(p_tree,pd,name_compare,name_destroy);
}

static int tagtree_delete(RBTREE *p_tree, tagnode_t *pd)
{
	return RBTree_Delete(p_tree,pd,tag_compare,tag_destroy);
}

static namenode_t *nametree_find(RBTREE *p_tree, namenode_t *pd)
{
	return (namenode_t*)RBTree_Find(p_tree, pd, name_compare);
}

static tagnode_t *tagtree_find(RBTREE *p_tree, tagnode_t *pd)
{
	return (tagnode_t*)RBTree_Find(p_tree, pd, tag_compare);
}

static void nametree_begin(RBTREE *p_tree)
{
	RBTree_EnumBegin(p_tree);
}

static void tagtree_begin(RBTREE *p_tree)
{
	RBTree_EnumBegin(p_tree);
}

static namenode_t *nametree_next(RBTREE *p_tree)
{
	return (namenode_t*)RBTree_EnumNext(p_tree);
}

static tagnode_t *tagtree_next(RBTREE *p_tree)
{
	return (tagnode_t*)RBTree_EnumNext(p_tree);
}

void sta_init(station_t *ps)
{
	ps->p_name_tree=nametree_create();
	ps->p_tag_tree=tagtree_create();
	ps->idmax=0;
}

void sta_uninit(station_t *ps)
{
	nametree_destroy(ps->p_name_tree);
	tagtree_destroy(ps->p_tag_tree);
}

int sta_inserttag(station_t *ps, int id, tag_t *ptag)
{
	int ret;
	namenode_t *pn;
	tagnode_t *pt;

	pn=(namenode_t *)k_malloc(sizeof(namenode_t));
	pn->id=id;
	strncpy(pn->name,ptag->name,EVNAMESIZE);
	ret=nametree_insert(ps->p_name_tree,pn);
	if(ret!=CAPI_SUCCESS){
		k_free(pn);
		return ret;
	}

	pt=(tagnode_t *)k_malloc(sizeof(tagnode_t));
	pt->id=id;
	memcpy(&pt->tag,ptag,sizeof(tag_t));
	ret=tagtree_insert(ps->p_tag_tree,pt);
	if(ret!=CAPI_SUCCESS){
		k_free(pt);
		return ret;
	}

	if(ps->idmax<id){
		ps->idmax=id;
	}
	return ret;
}

int sta_deletetag(station_t *ps, int id)
{
	tagnode_t tn, *pt;
	namenode_t nn;

	tn.id=id;
	pt=tagtree_find(ps->p_tag_tree, &tn);
	if(pt==NULL){
		return CAPI_FAILED;
	}

	strncpy(nn.name, pt->tag.name, EVNAMESIZE);

	nametree_delete(ps->p_name_tree, &nn);
	tagtree_delete(ps->p_tag_tree, pt);

	return CAPI_SUCCESS;
}

int sta_gettagid(station_t *ps, char *name)
{
	namenode_t nn, *pn;
	strncpy(nn.name, name, EVNAMESIZE);
	pn=nametree_find(ps->p_name_tree, &nn);
	if(pn!=NULL){
		return pn->id;
	}else{
		return 0;
	}
}

tag_t *sta_findtag(station_t *ps, int id)
{
	tagnode_t nt, *pt;
	nt.id=id;
	pt=tagtree_find(ps->p_tag_tree, &nt);
	return &pt->tag;
}

static int get_cfg_file(int i, char *path)
{
	sprintf(path,"%d.csv",i);

	return 0;
}

static Int str2mask(char *str,int len)
{
	args_t args;
	int i;
	Int mask=0;

	str2args('+',str,len,&args);
	for(i=0;i<args.c;i++){
		if(strncmp(args.v[i].d,"on",sizeof("on"))==0){
			mask|=AM_ON;
		}else if(strncmp(args.v[i].d,"off",sizeof("off"))==0){
			mask|=AM_OFF;
		}else if(strncmp(args.v[i].d,"lo",sizeof("lo"))==0){
			mask|=AM_LO;
		}else if(strncmp(args.v[i].d,"lolo",sizeof("lolo"))==0){
			mask|=AM_LOLO;
		}else if(strncmp(args.v[i].d,"hi",sizeof("hi"))==0){
			mask|=AM_HI;
		}else if(strncmp(args.v[i].d,"hihi",sizeof("hihi"))==0){
			mask|=AM_HIHI;
		}
	}

	return mask;
}

static void addmask(int *first, char *line, char *mask)
{
	if(*first){
		*first=0;
		strcpy(line,mask);
	}else{
		strcat(line,"+");
		strcat(line,mask);
	}
}

static void mask2str(tag_t *tag, char *line)
{
	int first=1;

	strcpy(line,"");
	if(tag->mask & AM_ON){
		addmask(&first,line,"on");	
	}
	if(tag->mask & AM_OFF){
		addmask(&first,line,"off");	
	}
	if(tag->mask & AM_LO){
		addmask(&first,line,"lo");	
	}
	if(tag->mask & AM_LOLO){
		addmask(&first,line,"lolo");	
	}
	if(tag->mask & AM_HI){
		addmask(&first,line,"hi");	
	}
	if(tag->mask & AM_HIHI){
		addmask(&first,line,"hihi");	
	}
}

static void parse_line(station_t *ps, char *line, int len)
{
	args_t args;
	int id_tag;
	tag_t tag;

	if(line[0]=='#'){
		return;
	}
	
	str2args(',',line,len,&args);
	
	if(strncmp(args.v[0].d, "station",sizeof("station"))==0){
		strncpy(ps->name, args.v[1].d, STANAMESIZE);
		return;
	}

	if(strncmp(args.v[0].d, "tag",sizeof("tag"))==0){
		id_tag=atoi(args.v[1].d);
		strncpy(tag.name,args.v[2].d,EVNAMESIZE);
		strncpy(tag.desc,args.v[3].d,DESCSIZE);
		strncpy(tag.eu,args.v[4].d,EUSIZE);
        tag.type = str2type(args.v[5].d);
		tag.mask=str2mask(args.v[6].d,MAXARGLENGTH);
		tag.group=atoi(args.v[7].d);
		tag.min=(float)atof(args.v[8].d);
		tag.max=(float)atof(args.v[9].d);
		tag.lo=(float)atof(args.v[10].d);
		tag.lolo=(float)atof(args.v[11].d);
		tag.hi=(float)atof(args.v[12].d);
		tag.hihi=(float)atof(args.v[13].d);
		tag.flag |= FG_CONFIG;
		sta_inserttag(ps,id_tag,&tag);
	}
}

void sta_loadcfg(int id, station_t *ps)
{
	FILE *fp;
	char path[256];
	char line[1024];

	if(get_cfg_file(id,path)==0){
		fp=fopen(path,"r");
		if(fp!=NULL){
			while(fgets(line,sizeof(line),fp)!=NULL){
				parse_line(ps,line,sizeof(line));
			}
			fclose(fp);
		}
	}
}

static int make_line(int id_tag,tag_t *tag, char *line)
{
    std::string type;
	char mask[32];

	if(!(tag->flag & FG_CONFIG)){
		return -1;
	}
	
	tag->name[EVNAMESIZE-1]=0;
	tag->desc[DESCSIZE-1]=0;
	tag->eu[EUSIZE-1]=0;

    type = type2str((v_type)tag->type);
	mask2str(tag,mask);
	sprintf(line,"tag,%d,%s,%s,%s,%s,%s,%d,%f,%f,%f,%f,%f,%f\n",
		id_tag,
		tag->name,
		tag->desc,
		tag->eu,
        type.data(),
		mask,
		tag->group,
		tag->min,
		tag->max,
		tag->lo,
		tag->lolo,
		tag->hi,
		tag->hihi);

	return 0;
}

void sta_savecfg(int id, station_t *ps)
{
	FILE *fp;
	char path[256];
	char line[1024];
	tagnode_t *pt;

	get_cfg_file(id,path);
	fp=fopen(path,"w");
	if(fp!=NULL){
		ps->name[STANAMESIZE-1]=0;
		sprintf(line,"station,%s\n",ps->name);
		fputs(line,fp);
		sprintf(line,"#tag,id,name,desc,eu,type,mask,group,min,max,lo,lolo,hi,hihi\n");
		fputs(line,fp);
		tagtree_begin(ps->p_tag_tree);
		pt=tagtree_next(ps->p_tag_tree);
		while(pt!=NULL){
			if(make_line(pt->id,&pt->tag,line)==0){
				fputs(line,fp);
			}
			pt=tagtree_next(ps->p_tag_tree);
		}
		fclose(fp);
	}
}
