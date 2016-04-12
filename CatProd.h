#ifndef CatProds_H_  
#define CatProds_H_
#include "myavl.h"


typedef struct prods* CatProds;
typedef struct prod* Produto;
typedef struct conjProd* ConjProds;

/*Insere string em Produto */
Produto inserep(char *x);

/*Altera valor do produto */
Produto alterap(char *x,Produto p);

/* Inicializa Catálogo de Produtos */
CatProds initCatProds();

/* Insere um Produto novo no catálogo */
CatProds insereProduto(CatProds cps, Produto p);

/* Verifica se um produto existe no catálogo de produtos */
Boolean existeProduto(CatProds cps, Produto p);

/* Dá quantos produtos estão no catálogo */
int totalProdutos(CatProds cps);

/* Dá quantos produtos existem com uma dada letra */
int totalProdutosLetra(CatProds cps, char letra);

/* Temp */
void removeCatProd(CatProds cps);

int getPagina(ConjProds l);

int getSize(ConjProds l);

char** getLista(ConjProds l);

int alteraPaginamais(ConjProds l);

int alteraPaginamenos(ConjProds l);

ConjProds getList (CatProds cps, char letra);

#endif