#ifndef AVL_H_
#define AVL_H_
#include "faturacao.h"
#include "boolean.h"
#include "CatProd.h"

typedef struct avl *AVL;

int max (int a, int b);
int altura (AVL a);
int diferenca (AVL a, AVL b);
AVL rotacaoEsq (AVL a);
AVL rotacaoDir (AVL a);
AVL insereDir (AVL a, char* codigo);
AVL insereEsq (AVL a, char* codigo);
AVL insereAVL (AVL a, char* codigo, Fat v);
Boolean existeAVL (AVL a, char* codigo);
void freeTree(AVL a);
ConjProds auxiliarImprime(ConjProds l, AVL t);
void printbool(Boolean a);


#endif