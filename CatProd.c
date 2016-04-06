#include "CatProd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"

typedef int Boolean;
#define true 1
#define false 0

typedef struct avl {
	int tamanho;
	avl_tree_t root;
} *AVL;

typedef struct prods* CatProds;
struct prods {
	AVL catalogoProd[26];
};

typedef struct prod* Produto;
struct prod {
 	char* nomeprod;
};

CatProds initCatProds() {
	int i;
    CatProds p;
    AVL r;
    for (i = 0; i < 26; i++) {
        p->catalogoProd[i] = (malloc)(sizeof(struct avl));
        p->catalogoProd[i]->tamanho = 0;
        p->catalogoProd[i]->root = avl_create();
    }
    return p;
}


