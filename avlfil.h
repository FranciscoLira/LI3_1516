#ifndef AVLFIL_H_
#define AVLFIL_H_
#include "boolean.h"
#include "CatProd.h"

typedef struct avlfil* AVLfil;
AVLfil insereAVLfil (AVLfil a, char* x, char *y, int i, int j, int k, double w);
Boolean existeAVLfil (AVLfil a, char* x);
void freeTreefil (AVLfil a, int x);
void insereprod(AVLfil a, char *c,char* p, int m, int q, int x, double w);
int getnum(AVLfil a,char * c, int mes);
CatProds funcaocat(CatProds cps, AVLfil x1, AVLfil x2,AVLfil x3);
char** quemComprou(char** lista, char *prod, AVLfil t, int *i, int z, int *tam);
AVLfil auxiliarInsere(AVLfil res, AVLfil prod);
AVLfil auxp(AVLfil res, AVLfil prod,int m,int t,char *c);
void altera(AVLfil res, char* p, int q);
void alteracl(AVLfil res, char* p, char* c);
int numAVL(AVLfil res);
void inseredaAvlfil(AVLfil res, int* q, char** c, int *i);
AVLfil insereCl(AVLfil a, char *c, char *cl, int m, int q, int x);
int quantosClientes(AVLfil t, char* p);

#endif