#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myavl.h"
#include "faturacao.h"

struct fat {
	int quantidade;
	double faturacao;
};

struct avl {
	int altura;
	char* codigo;
	Fat extra;
	struct avl* esq;
	struct avl* dir;
};

int max(int a, int b) {
	return (a > b ? a : b);
}

int altura(AVL a) {
	if (a)
		return a->altura;
	return 0;
}

int diferenca(AVL a, AVL b) {
	return altura (a) - altura (b);
}

char* getcodigo(AVL a) {
	return a->codigo;
}

AVL getesq(AVL a) {
	return a-> esq;
}

AVL getdir(AVL a) {
	return a-> dir;
}

double getavlfat(AVL a) {
	return a->extra->faturacao;
}

int getavlquant(AVL a) {
	return a->extra->quantidade;
}

void setcodigo(AVL a, char* codigo) {
	a->codigo = (char*)malloc(sizeof(char) * 10);
	strcpy(a->codigo, codigo);
}

/*este também serve para adicionar, não só para setter*/
void setextra(AVL a, double fat, int quant) {
	if (a->extra) {
		a->extra->quantidade += quant;
		a->extra->faturacao += fat;
	}
	else {
		a->extra = alocafat(fat, quant);
	}
}

AVL newAVL() {
	AVL r = (AVL)malloc(sizeof(struct avl));
	r->altura = 0;
	r->esq=r->dir=r->extra=r->codigo = NULL;

	return r;
}

AVL initAVL(int alt, char* codigo, Fat extra, AVL esq, AVL dir) {
	AVL r = (AVL)malloc(sizeof(struct avl));
	r->altura = alt;
	r->codigo = (char*)malloc(sizeof(char) * 10);
	strcpy(r->codigo, codigo);
	r->extra = extra;
	r->dir = dir;
	r->esq = esq;
	return r;
}

AVL rotacaoEsq(AVL a) {
	AVL aux = a->dir;
	a->dir = aux->esq;
	aux->esq = a;
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	aux->altura = max (altura(aux->dir), altura(aux->esq)) + 1;
	return aux;
}

AVL rotacaoDir(AVL a) {
	AVL aux = a->esq;
	a->esq = aux->dir;
	aux->dir = a;
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	aux->altura = max (altura(aux->dir), altura(aux->esq)) + 1;
	return aux;
}

AVL insereDir(AVL a, char* codigo) {
	a->dir = insereAVL (a->dir, codigo, NULL);
	if (diferenca (a->dir, a->esq) == 2) {
		AVL aux = a->dir;
		if (diferenca (aux->dir, aux->esq) > 0)
			return rotacaoEsq (a);
		a->dir = rotacaoDir (a->dir);
		return rotacaoEsq (a);
	}
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	return a;
}

AVL insereEsq(AVL a, char* codigo) {
	a->esq = insereAVL (a->esq, codigo, NULL);
	if (diferenca (a->esq, a->dir) == 2) {
		AVL aux = a->esq;
		if (diferenca (aux->esq, aux->dir) > 0)
			return rotacaoDir (a);
		a->esq = rotacaoEsq (a->esq);
		return rotacaoDir (a);
	}
	a->altura = max (altura(a->esq), altura(a->dir)) + 1;
	return a;
}

/*Insere na AVL um nodo, se houver faturação para lhe aplicar aplica, senão deixa o endereço do campo extra a NULL
Se for receber um Fat, então esse fat já deve ter memória alocada*/
AVL insereAVL(AVL a, char* codigo, Fat v) {
	if (!a) {
		a = initAVL(1, codigo, NULL, NULL, NULL);
		setcodigo(a, a->codigo);
		if (v) {
			setextra(a, getfatfat(v), getfatquant(v));
		}
		return a;
	}
	if (strcmp (codigo, a->codigo) > 0)
		return insereDir (a, codigo);
	return insereEsq (a, codigo);
}


/*retorna um bool para saber se um elemento está ou não na avl*/
Boolean existeAVL(AVL a, char* codigo) {
	AVL aux = a;
	int i;
	while (aux) {
		i = strcmp (codigo, aux->codigo);
		if (i == 0)
			return true;
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
	return false;
}


/*faz fre de uma avl e de todos os seus nodos*/
void freeTree(AVL a) {
	if (a) {
		freeTree (a->esq);
		freeTree (a->dir);
		free(a->codigo);
		free(a);
	}
}

char** auxiliarImprime(char** lista, AVL t, int *i) {
	if (t != NULL) {
		lista = auxiliarImprime(lista, t->esq, i);
		lista[*i] = malloc(sizeof(char) * 10);
		strcpy(lista[(*i)++], t->codigo);
		lista = auxiliarImprime(lista, t->dir, i);
	}
	return lista;
}

/*faz print do valor de um boolean, mais para debug*/
void printbool(Boolean a) {
	if (a) {
		printf("true\n");
	}
	else {
		printf("false\n");
	}
}

/*AQUI é necessário ter dois avlcpy para campos diferentes??*/
AVL avlcpy(AVL a) {
	AVL r = NULL;
	if (a) {
		r = initAVL(a->altura, a->codigo, NULL, avlcpy(a->esq), avlcpy(a->dir));
		if (a->extra) {
		setextra(r, getfatfat(a->extra), getfatquant(a->extra));
		}
	}
	return r;
}
