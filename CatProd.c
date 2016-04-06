#include "CatProd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avl.h"


typedef struct avl {
	int tamanho;
	avl_tree_t *puta;
} *AVL;

struct prods {
	AVL catalogoProd[26];
};

struct prod {
 	char* nomeprod;
};

CatProds initCatProds() {
	int i;
    CatProds p;
    for (i = 0; i < 26; i++) {
        p->catalogoProd[i] = (malloc)(sizeof(struct avl));
        p->catalogoProd[i]->tamanho = 0;
        p->catalogoProd[i]->puta = avl_create();
    }
    return p;
}


