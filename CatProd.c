#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"
#include "CatProd.h"

typedef struct conjProd {
	char** lista;
	int size;
	int pagina;
}Lst;

typedef struct avlp {
	int tamanho;
	AVL root;
} *Trees;

typedef struct prod {
	char nomeprod[10];
}Prod;

typedef struct prods {
	Trees cP[26];
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
		p->cP[i] = malloc(sizeof(struct avlp));
		p->cP[i]->tamanho = 0;
		p->cP[i]->root = NULL;
	}
	return p;
}

CatProds insereProduto(CatProds cps, Produto p){
	int i = (p->nomeprod[0] - 65);
	cps->cP[i]->root = insereAVL(cps->cP[i]->root,p->nomeprod,NULL);
	cps->cP[i]->tamanho++;
	return cps;
}

Boolean existeProduto(CatProds cps, Produto p){
	int i = (p->nomeprod[0] - 65);
	if(i<0 || i>25) return false;
	if(existeAVL(cps->cP[i]->root,p->nomeprod))
		return true;
	else return false;
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
	if (cps==NULL)return;
	for(i=0; i<26;i++){
		freeTree(cps->cP[i]->root);
		free(cps->cP[i]);
	}
	free(cps);
}

void printarray(char ** l, int n){
	int i=0;
	while(i<n)
		printf("%s\n",l[i++]);
	/*Por isto pag a pag and done */
}

int getPagina(ConjProds l) {
	return l->pagina;
}

int getSize(ConjProds l) {
	return l->size;
}

char** getLista(ConjProds l) {
	return l->lista;
}

int alteraPaginamais(ConjProds l) {
	return (l->pagina)++;
}

int alteraPaginamenos(ConjProds l) {
	return (l->pagina)--;
}


ConjProds getList (CatProds cps, char letra) { 
	int i = 0;
	int k;
	ConjProds l = malloc(sizeof(Lst));
    l->size = totalProdutosLetra(cps, letra);
    l->pagina = 1; 
    l->lista = malloc(sizeof(char*)*(l->size));
	k = letra - 'A';
	l->lista = auxiliarImprime(l->lista, cps->cP[k]->root, &(i));
	return l;
}





