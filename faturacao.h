#ifndef faturacao_H_
#define faturacao_H_
#include "myavlcod.h"

/*É necessário estarem aqui?(myavlcod.c)*/
typedef struct vendatmp *Vendatmp;

typedef struct venda *Venda;

typedef struct fatmes *Fatmes;

typedef struct fatall *Fatall;


typedef struct empresa *Emp;

Fatmes initFatmes();
Fatall initFatall();
Emp initEmpresa (int quant);
void insereVenda(Emp e, Vendatmp v);
Boolean existeVenda(Emp e, Vendatmp v);

#endif