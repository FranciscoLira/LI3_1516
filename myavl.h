#ifndef AVL_H_
#define AVL_H_
#include "boolean.h"

typedef struct avl *AVL;
typedef struct fat *Fat;

int max(int a, int b);
int altura(AVL a);
int diferenca(AVL a, AVL b);
char* getcodigo(AVL a);
void setcodigo(AVL a, char* codigo);
AVL getesq(AVL a);
AVL getdir(AVL a);
/*set para futuro??*/
double getavlfat(AVL a);
int getavlquant(AVL a);
void setextra(AVL a, double fat, int quant, int vendas);
AVL newAVL();
AVL insereAVL(AVL a, char* codigo, Fat v);
int existequantAVL(AVL a, char* codigo);
Boolean existeAVL(AVL a, char* codigo);
Fat getfatfromavl(AVL a, char* codigo);
void freeTree(AVL a);
char** auxiliarImprime(char** lista, AVL t, int *i);
void printbool(Boolean a);
AVL avlcpy(AVL a);
/*int quantosnodos(AVL* a);*/
void inseredaAvl(AVL r, int* quantidades, char** codigos, int *i);

#endif