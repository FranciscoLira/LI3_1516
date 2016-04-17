#ifndef FILIAL_H_
#define FILIAL_H_
#include "CatProd.h"
#include "CatClient.h"

typedef struct comprou *ConjComprados;
typedef struct filial *Filial;

/* Inicializa Filial */
Filial initFilial();
/* Insere um produto e cliente na Filial */
Filial insereFilial(Filial f, Cliente c, Produto p, int mes, int quant, int m);
/* Libertar memória da filial */
void removeFilial(Filial f);
int numprodutos(Filial f, Cliente c, int mes);
CatProds makeCat(Filial *f, CatProds p);
ConjComprados comprou(Produto p, Filial f, int tipo);
char** getListConj(ConjComprados c);
int getTamConj(ConjComprados c);
void freeConj(ConjComprados c);

#endif