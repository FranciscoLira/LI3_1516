#ifndef AVL_H_
#define AVL_H_
#include "boolean.h"


typedef struct fat *Fat;
typedef struct avl *AVL;

int max(int a, int b);
int altura(AVL a);
int diferenca(AVL a, AVL b);
char* getcodigo(AVL a);
void setcodigo(AVL a, char* codigo);
AVL getesq(AVL a);
AVL getdir(AVL a);
double getavlfat(AVL a);
int getavlquant(AVL a);
void setcodigo(AVL a, char* codigo);
void setextra(AVL a, double fat, int quant);
AVL newAVL();
AVL insereAVL(AVL a, char* codigo, Fat v);
Boolean existeAVL(AVL a, char* codigo);
Fat getfatfromavl(AVL a, char* codigo);
void freeTree(AVL a);
char** auxiliarImprime(char** lista, AVL t, int *i);
void printbool(Boolean a);
AVL avlcpy(AVL a);

#endif