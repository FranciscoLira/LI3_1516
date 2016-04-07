#include "CatProd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "avltree.h"

typedef struct avl {
    int tamanho;
    avl_tree_t *root;
} *AVL;

typedef struct prod {
    char nomeprod[10];
}Prod;

typedef struct prods {
    AVL cP[26];
}Cat;

Produto inserep(char *x){
    Produto p=malloc(sizeof(struct prod));
    strcpy(p->nomeprod,x);
    return p;
}

Produto alterap(char *x,Produto p){
    strcpy(p->nomeprod,x);
    return p;
}

CatProds initCatProds() {
	int i;
    CatProds p=malloc(sizeof(struct prods));
    for (i = 0; i < 26; i++) {
        p->cP[i] = (malloc)(sizeof(struct avl));
        p->cP[i]->tamanho = 0;
        p->cP[i]->root = avl_create();
    }
    return p;
}

CatProds insereProduto(CatProds cps, Produto p){
    int i = (p->nomeprod[0] - 65);
    avl_insert(cps->cP[i]->root,p->nomeprod);
    cps->cP[i]->tamanho++;
    return cps;
}

Boolean existeProduto(CatProds cps, Produto p){
    int i = (p->nomeprod[0] - 65);
    avl_node_t *node;
    node=avl_find(cps->cP[i]->root,p->nomeprod);
    if(node==NULL) return false;
    else return true;
}

int totalProdutos(CatProds cps){
    int i, r=0;
    for(i=0; i<26; i++)
        r+=cps->cP[i]->tamanho;
    return r;
}







