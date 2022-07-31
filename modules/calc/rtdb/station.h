#ifndef station_h
#define station_h

#include "CapiGlobal.h"
#include "BinTree.h"
#include "RBTree.h"
#include "rtdb.h"
// #ifdef __cplusplus
// extern "C" {
// #endif

	typedef struct NameNode{
		char name[EVNAMESIZE];
		int id;
	}namenode_t;

	typedef struct TagNode{
		int id;
		tag_t tag;
	}tagnode_t;

	#define STANAMESIZE	32
	typedef struct Station{
		RBTREE *p_name_tree;
		RBTREE *p_tag_tree;
		char name[STANAMESIZE];
		int idmax;
	}station_t;

void sta_init(station_t *ps);
void sta_uninit(station_t *ps);
int sta_inserttag(station_t *ps, int id, tag_t *ptag);
int sta_deletetag(station_t *ps, int id);
int sta_gettagid(station_t *ps, char *name);
tag_t *sta_findtag(station_t *ps, int id);
void sta_loadcfg(int id, station_t *ps);
void sta_savecfg(int id, station_t *ps);

// #ifdef __cplusplus
// }
// #endif
#endif