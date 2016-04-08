#ifndef CatProds_H_  
#define CatProds_H_

typedef int Boolean;
#define true 1
#define false 0
typedef struct prods* CatProds;
typedef struct prod* Produto;

/*Insere string em Produto */
Produto inserep(char *x);

/*Altera valor do produto */
Produto alterap(char *x,Produto p);

/* Inicializa Catálogo de Produtos */
CatProds initCatProds();

/* Insere um Produto novo no catálogo */
CatProds insereProduto(CatProds cps, Produto p);

/* Verifica se um produto existe no catálogo de produtos 
Boolean existeProduto(CatProds cps, Produto p*/
/* Dá quantos produtos estão no catálogo */
int totalProdutos(CatProds cps);
void printlindo(CatProds cps);

#endif