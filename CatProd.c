#include "CatProd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"

typedef struct avl {
	int tamanho;
	Tree root;
} *AVL;

typedef struct prod {
	char nomeprod[10];
}Prod;

typedef struct prods {
	AVL cP[26];
	int cresceu[26];
}Cat;

void printx(CatProds cps){
	preorder(cps->cP[5]->root);
}

int getKey(Produto p){
	int i;
	int key=0;
	key+=atoi(&(p->nomeprod[2]));
	i=p->nomeprod[1] - 65;
	key+=10000*i;
	return key;
}

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
		p->cP[i]->root = newAvl();
	}
	return p;
}

CatProds insereProduto(CatProds cps, Produto p){
	int i = (p->nomeprod[0] - 65);
	int key = getKey(p);
	cps->cP[i]->root = insertTree(cps->cP[i]->root, key,p->nomeprod, &(cps->cresceu[i]));
	cps->cP[i]->tamanho++;
	return cps;
}

Boolean existeProduto(CatProds cps, Produto p){
	int i = (p->nomeprod[0] - 65);
	Tree node;
	if(i<0 || i>25) return false;
	node=avl_find(cps->cP[i]->root,getKey(p));
	if(node==NULL) return false;
	else return true;
}

int totalProdutos(CatProds cps){
	int i, r=0;
	for(i=0; i<26; i++){
		r+=cps->cP[i]->tamanho;
	}
	return r;
}

int totalProdutosLetra(CatProds cps, char letra){
	int i = letra - 65;
	return (cps->cP[i]->tamanho);
}

void removeCatProd(CatProds cps){
	int i;
	for(i=0; i<26;i++){
		freetree(cps->cP[i]->root);
		free(cps->cP[i]);
	}
	free(cps);
}







