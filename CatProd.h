#ifndef CatProds_H_  
#define CatProds_H_
#include "avltree.h"

typedef int Boolean;
#define true 1
#define false 0
typedef struct avl {
	int tamanho;
	avl_tree_t *root;
} *AVL;


struct prod {
 	char nomeprod[10];
};
typedef struct prods* CatProds;

struct prods {
	AVL cP[26];
};
typedef struct prod* Produto;



Produto inserep(char *x);
Produto alterap(char *x,Produto p);
CatProds initCatProds();
CatProds insereProduto(CatProds cps, Produto p);

#endif