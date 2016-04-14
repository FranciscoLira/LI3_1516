#ifndef faturacao_H_
#define faturacao_H_
#include "boolean.h"
#include "CatClient.h"

typedef struct vendatmp *Vendatmp;

typedef struct fatmes *Fatmes;

typedef struct fatall *Fatall;

typedef struct empresa *Emp;

/*Faz a inicialização de toda a memória necessária e os devidos campos*/
Emp initEmpresa ();

void insereVenda (Emp e, Vendatmp v);

Boolean existeVenda (Emp e, Vendatmp v);

Fat* fatglobal(Emp e, int imes, char* codigo, int juntos);

#endif