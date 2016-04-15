#ifndef AVL_H_
#define AVL_H_
#include "boolean.h"

typedef struct avl *AVL;

typedef struct fat *Fat;

typedef struct fil *Fil;

union FatVFil;

int max (int a, int b);
int altura (AVL a);
int diferenca (AVL a, AVL b);
AVL rotacaoEsq (AVL a);
AVL rotacaoDir (AVL a);
AVL insereDir (AVL a, char* codigo);
AVL insereEsq (AVL a, char* codigo);
AVL insereAVL (AVL a, char* codigo, union FatVFil v);
Boolean existeAVL (AVL a, char* codigo);
/*Não conhece o type fat??
  Se a função for para faturação*/
Fat getfatfromavl(AVL a, char* codigo);
void freeTree(AVL a);
char** auxiliarImprime(char** lista, AVL t, int *i);
void printbool(Boolean a);
AVL avlcpyfa(AVL a);
void freeExtra(AVL a);
union FatVFil getextra(AVL a, char *c);

#endif