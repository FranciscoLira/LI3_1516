#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myavl.h"
#include "faturacao.h"
#include "CatProd.h"

struct avl {
	int altura;
	char* codigo;
	union Merda extra;
	struct avl* esq;
	struct avl* dir;
};

int max (int a, int b) {
	return (a > b ? a : b);
}

int altura (AVL a) {
	if (a)
		return a->altura;
	return 0;
}

int diferenca (AVL a, AVL b) {
	return altura (a) - altura (b);
}

AVL rotacaoEsq (AVL a) {
	AVL aux = a->dir;
	a->dir = aux->esq;
	aux->esq = a;
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	aux->altura = max (altura(aux->dir), altura(aux->esq)) + 1;
	return aux;
}

AVL rotacaoDir (AVL a) {
	AVL aux = a->esq;
	a->esq = aux->dir;
	aux->dir = a;
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	aux->altura = max (altura(aux->dir), altura(aux->esq)) + 1;
	return aux;
}

AVL insereDir (AVL a, char* codigo) {
	union Merda x;
	x.fi = NULL;
	a->dir = insereAVL (a->dir, codigo, x);
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

AVL insereEsq (AVL a, char* codigo) {
	union Merda x;
	x.fi = NULL;
	a->esq = insereAVL (a->esq, codigo, x);
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

AVL insereAVL (AVL a, char* codigo, union Merda v) {
	if (!a) {
		a = malloc (sizeof (struct avl));
		a->codigo = (char*)malloc(sizeof(char) * 10); /*Está a fazer de 10,mas pode ser menos*/
		strcpy(a->codigo, codigo);
		a->esq = a->dir = NULL;
		a->altura = 1;
		a->extra = v;
		return a;
	}
	if (strcmp (codigo, a->codigo) > 0)
		return insereDir (a, codigo);
	return insereEsq (a, codigo);
}

/*retorna um bool para saber se um elemento está ou não na avl*/
Boolean existeAVL (AVL a, char* codigo) {
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

/*retorna a faturação de um produto, recebendo a avl e o produto a procurar*/
Fat getfatfromavl(AVL a, char* codigo) {
	AVL aux = a;
	int i;
	while (aux) {
		i = strcmp(codigo, aux->codigo);
		if (i == 0) return aux->extra.fa;
		a->codigo = (char*)malloc(sizeof(char) * 10); /*Está a fazer de 10,mas pode ser menos*/
		if (i > 0) aux = aux->dir;
		else aux = aux->esq;
	}
	return	false;
}

/*faz fre de uma avl e de todos os seus nodos*/
void freeTree (AVL a) {
	if (a) {
		freeTree (a->esq);
		freeTree (a->dir);
		free (a);
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
AVL avlcpyfa(AVL a) {
	AVL r;
	if (a) {
		r = (AVL) malloc(sizeof(struct avl));
		r->codigo = a->codigo;
		r->altura = a->altura;
		if (a->extra.fa) {
			r->extra.fa = (Fat)malloc(/*sizeof(struct fat)*/16);/*16 é o tamanho da struct fat, posso deixar 16??*/
			r->extra.fa->faturacao = a->extra.fa->faturacao;
			r->extra.fa->quantidade = a->extra.fa->quantidade;
		}
		else {
			r->extra.fa = NULL;
		}
		r->esq = avlcpyfa(a->esq);
		r->dir = avlcpyfa(a->dir);
	}
	else {
		r = NULL;
	}
	return r;
}

/*
AVL avlcpyfi(AVL a) {
	AVL r;
	if (a) {
		r = (AVL) malloc(sizeof(struct avl));
		r->codigo = a->codigo;
		r->altura = a->altura;
		if (a->extra.fi) {
			r->extra.fi = (Fil)malloc(sizeof(struct fil));
			r->extra.fi->faturacao = a->extra.fi->faturacao;
			r->extra.fi->quantidade = a->extra.fi->quantidade;
		}
		else {
			r->extra.fi = NULL;
		}
		r->esq = avlcpy(a->esq);
		r->dir = avlcpy(a->dir);
	}
	else {
		r = NULL;
	}
}
*/