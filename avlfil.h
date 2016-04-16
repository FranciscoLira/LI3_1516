#ifndef AVLFIL_H_
#define AVLFIL_H_
#include "boolean.h"

typedef struct avlfil* AVLfil;
AVLfil insereAVLfil (AVLfil a, char* codigo, char *produto, int mes, int quant);
Boolean existeAVLfil (AVLfil a, char* codigo);
void freeTreefil (AVLfil a);
void insereprod(AVLfil a, char *cliente,char* produto, int mes, int quant);
int getnum(AVLfil a,char * c, int mes);
void inorder(AVLfil a);

#endif