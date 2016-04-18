#ifndef AVLFIL_H_
#define AVLFIL_H_
#include "boolean.h"
#include "faturacao.h"
#include "CatProd.h"

typedef struct avlfil* AVLfil;
AVLfil insereAVLfil (AVLfil a, char* codigo, char *produto, int mes, int quant, int x);
Boolean existeAVLfil (AVLfil a, char* codigo);
void freeTreefil (AVLfil a, int x);
void insereprod(AVLfil a, char *cliente,char* produto, int mes, int quant, int x);
int getnum(AVLfil a,char * c, int mes);
CatProds funcaocat(CatProds cps, AVLfil x1, AVLfil x2,AVLfil x3);
char** quemComprou(char** lista, char *prod, AVLfil t, int *i, int z, int *tam);
AVLfil auxiliarInsere(AVLfil res, AVLfil prod);
void inorder(AVLfil a);
AVLfil auxp(AVLfil res, AVLfil prod,int mes,int tipo,char *cliente);
void altera(AVLfil res, char * prod, int quant);
int numAVL(AVLfil res);
void inseredaAvl(AVLfil res, int* quantidades, char** codigos, int *i);

#endif