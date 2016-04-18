#ifndef FILIAL_H_
#define FILIAL_H_
#include "myavl.h"
#include "avlfil.h"
#include "CatClient.h"
#include "CatProd.h"

typedef struct filial *Filial;

/* Inicializa Filial */
Filial initFilial();
/* Insere um produto e cliente na Filial */
Filial insereFilial(Filial f, Cliente c, Produto p, int mes, int quant);
/* Libertar memória da filial */
void removeFilial(Filial f);
int numprodutos(Filial f, Cliente c, int mes);
CatProds makeCat(Filial *f, CatProds p);

#endif