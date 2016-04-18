#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"
#include "Filial.h"
#include "CatProd.h"

struct conjProd {
	char** lista;
	int size;
	int pagina;
};

typedef struct avlp {
	int tamanho;
	AVL root;
}*Trees;

struct prod {
	char nomeprod[10];
};

struct prods {
	Trees cP[26];
};

AVL getAvlP (CatProds cps, int i) {
	return (cps->cP[i]->root);
}

AVL* getTree(CatProds cps) {
	int i;
	AVL* r = (AVL*)malloc(sizeof(AVL)*26);
	for (i = 0; i < 26; i++) {
		r[i] = avlcpy(cps->cP[i]->root);
	}
	return r;
}

Produto inserep(char *x) {
	Produto p = malloc(sizeof(struct prod));
	strcpy(p->nomeprod, x);
	return p;
}

Produto alterap(char *x, Produto p) {
	strcpy(p->nomeprod, x);
	return p;
}

CatProds initCatProds() {
	int i;
	CatProds p = malloc(sizeof(struct prods));
	for (i = 0; i < 26; i++) {
		p->cP[i] = malloc(sizeof(struct avlp));
		p->cP[i]->tamanho = 0;
		p->cP[i]->root = NULL;
	}
	return p;
}

CatProds insereProduto(CatProds cps, Produto p) {
	int i = (p->nomeprod[0] - 65);
	cps->cP[i]->root = insereAVL(cps->cP[i]->root, p->nomeprod, NULL);
	cps->cP[i]->tamanho++;
	return cps;
}

Boolean existeProduto(CatProds cps, Produto p) {
	int i = (p->nomeprod[0] - 65);
	if (i < 0 || i > 25) return false;
	if (existeAVL(cps->cP[i]->root, p->nomeprod))
		return true;
	else return false;
}

int totalProdutos(CatProds cps) {
	int i, r = 0;
	for (i = 0; i < 26; i++) {
		r += cps->cP[i]->tamanho;
	}
	return r;
}

int totalProdutosLetra(CatProds cps, char letra) {
	int i = letra - 65;
	if(i<0 || i>25) return 0;
	return (cps->cP[i]->tamanho);
}

void removeCatProd(CatProds cps) {
	int i;
	if (cps == NULL)return;
	for (i = 0; i < 26; i++) {
		freeTree(cps->cP[i]->root);
		free(cps->cP[i]);
	}
	free(cps);
}

void printarray(char ** l, int n) {
	int i = 0;
	while (i < n)
		printf("%s\n", l[i++]);
	/*Por isto pag a pag and done */
}

int getPagina(ConjProds l) {
	return l->pagina;
}

int getSize(ConjProds l) {
	return l->size;
}

char** getLista(ConjProds l) {
	if(l)
	return l->lista;
	else return NULL;
}

int alteraPaginamais(ConjProds l) {
	return (l->pagina)++;
}

int alteraPaginamenos(ConjProds l) {
	return (l->pagina)--;
}


ConjProds getList (CatProds cps, char letra) {
	int i=0, j=0;
	int k=0;
	ConjProds l = malloc(sizeof(struct conjProd));
	if(letra=='/')
		l->size=totalProdutos(cps);
	else 
		l->size = totalProdutosLetra(cps, letra);
	l->pagina = 1;
	l->lista = malloc(sizeof(char*) * (l->size));
	printf("%d\n",l->size );
	if(letra=='/'){
		for(j=0;j<26;j++)
			l->lista = auxiliarImprime(l->lista, cps->cP[j]->root, &(i));
		return l;
	}
	else {
		k = letra - 'A';
		if(k<0 || k>25) return NULL;
		l->lista = auxiliarImprime(l->lista, cps->cP[k]->root, &(i));
		return l;
	}
}

char* getStringp(Produto p){
	return p->nomeprod;
}	





