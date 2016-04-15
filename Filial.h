#ifndef FILIAL_H_
#define FILIAL_H_
#include "CatProd.h"
#include "CatClient.h"

typedef struct filial *Filial;

/* Inicializa Filial */
Filial initFilial();
/* Insere um produto e cliente na Filial */
Filial insereFilial(Filial f, Cliente c, Produto p);
/* Libertar memória da filial */
void removeFilial(Filial f);
int numprodutos(Filial f, Cliente c);

#endif