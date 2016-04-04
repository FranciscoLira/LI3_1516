#include <CatProds.h>

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


