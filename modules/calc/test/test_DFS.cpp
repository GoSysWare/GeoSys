#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 100 /*最大顶点数设为100*/
/*---图的邻接矩阵表示---*/
typedef struct {
  int vexs[MAX_VERTEX_NUM];                 /*顶点向量*/
  int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; /*邻接距阵*/
  int vexnum, arcnum;                       /*顶点数和边数*/
  int kind; /*---图的类型（1：有向图 0：无向图）---*/
} Mgraph;

bool InitMgraph(Mgraph *mgraph, int vexnum, int arcnum, int kind) {
  if (!mgraph) {
    return false;
  }
  /*---初始化边的一些基本信息---*/
  mgraph->vexnum = vexnum;
  mgraph->arcnum = arcnum;
  mgraph->kind = kind;
  int i;
  int j;
  for (i = 0; i < MAX_VERTEX_NUM; i++) {
    mgraph->vexs[i] = 0;
    for (j = 0; j < MAX_VERTEX_NUM; j++) {
      mgraph->arcs[i][j] = 0;
    }
  }

  return true;
}

bool CreatMgraph(Mgraph *mgraph) {
  if (!mgraph) {
    return false;
  }
  int i, j;
  for (i = 0; i < mgraph->vexnum; i++) {
    mgraph->vexs[i] = i;
  }

  int count = 0;

  while (count < mgraph->arcnum) {
    scanf("%d,%d", &i, &j);
    if (mgraph->kind == 0) {
      mgraph->arcs[i][j] = 1;
      mgraph->arcs[j][i] = 1;

    } else
      mgraph->arcs[i][j] = 1;

    count++;
  }
  return true;
}

void printMgraph(Mgraph *mgraph) {
  printf("++++++++++++++++++++++++\n");
  printf("+++++图的基本信息+++++++\n");
  printf("+顶点数：%d             \n", mgraph->vexnum);
  printf("+边数  ：%d             \n", mgraph->arcnum);
  printf("邻接矩阵：\n");

  int i;
  int j;
  for (i = 0; i < mgraph->vexnum; i++) {
    for (j = 0; j < mgraph->vexnum; j++) {
      printf(" %d", mgraph->arcs[i][j]);
    }
    printf("\n");
  }
}
void DFS(Mgraph *m, int i, int visited[]) {
  printf("%d", m->vexs[i]);
  visited[i] = 1;
  for (int j = 0; j < m->vexnum; j++) {
    if (m->arcs[i][j] == 1 && visited[j] == 0) {
      DFS(m, j, visited);
    }
  }
}

void DFST(Mgraph *m) {
  int visited[m->vexnum];

  for (int i = 0; i < m->vexnum; i++) {
    visited[i] = 0;
  }

  for (int i = 0; i < m->vexnum; i++) {
    if (visited[i] == 0)
      DFS(m, i, visited);
  }
}

void BFST(Mgraph *m) {
  int u, v, w;
  int visited[m->vexnum];
  int Q[m->vexnum + 1];
  int r, f;
  r = 0;
  f = 0;

  for (int i = 0; i < m->vexnum; i++) {
    visited[i] = 0;
  }
  for (int i = 0; i < m->vexnum; i++) {
    if (!visited[i]) {
      printf("%d", m->vexs[i]);
      visited[i] = 1;
      Q[r] = i;
      r = (r + 1) % (m->vexnum + 1);
      while (r != f) {

        u = Q[f];
        f = (f + 1) % (m->vexnum + 1);

        for (int j = 0; j < m->vexnum; j++) {
          if (m->arcs[u][j] == 1 && visited[j] == 0) {
            visited[j] = 1;
            printf("%d", m->vexs[j]);
            Q[r] = j;
            r = (r + 1) % (m->vexnum + 1);
          }
        }
      }
    }
  }
}

int main() {

  Mgraph *m1;
  m1 = (Mgraph *)malloc(sizeof(Mgraph));
  int num, s, kind;
  scanf("%d", &kind);
  scanf("%d,%d", &num, &s);
  InitMgraph(m1, num, s, kind);
  CreatMgraph(m1);
  printMgraph(m1);
  DFST(m1);

  BFST(m1);

  return 0;
}
