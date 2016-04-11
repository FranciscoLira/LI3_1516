#ifndef faturacao_H_
#define faturacao_H_


#include "boolean.h"


typedef struct vendatmp *Vendatmp;

typedef struct fat *Fat;

typedef struct fatmes *Fatmes;

typedef struct fatall *Fatall;

typedef struct empresa *Emp;

Emp initEmpresa (int quant);
void insereVenda(Emp e, Vendatmp v);
Boolean existeVenda(Emp e, Vendatmp v);

#endif