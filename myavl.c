#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myavl.h"
#include "faturacao.h"
#include "CatProd.h" 

/* Todo o código aqui apresentado foi desenvolvido por Fábio Baião */

struct avl {
	int altura;
	char* codigo;
	Fat extra;
	struct avl* esq;
	struct avl* dir;
};

int max (int a, int b){
	return (a > b ? a : b);
}

int altura (AVL a){
	if (a)
		return a->altura;
	return 0;
}

int diferenca (AVL a, AVL b){
	return altura (a) - altura (b);
}

AVL rotacaoEsq (AVL a){
	AVL aux = a->dir;
	a->dir = aux->esq;
	aux->esq = a;
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	aux->altura = max (altura(aux->dir), altura(aux->esq)) + 1;
	return aux;
}

AVL rotacaoDir (AVL a){
	AVL aux = a->esq;
	a->esq = aux->dir;
	aux->dir = a;
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	aux->altura = max (altura(aux->dir), altura(aux->esq)) + 1;
	return aux;
}

AVL insereDir (AVL a, char* codigo){
	a->dir = insereAVL (a->dir, codigo,NULL);
	if (diferenca (a->dir, a->esq) == 2){
		AVL aux = a->dir;
		if (diferenca (aux->dir, aux->esq) > 0)
			return rotacaoEsq (a);
		a->dir = rotacaoDir (a->dir);
		return rotacaoEsq (a);
	}
	a->altura = max (altura(a->dir), altura(a->esq)) + 1;
	return a;
}

AVL insereEsq (AVL a, char* codigo){
	a->esq = insereAVL (a->esq, codigo,NULL);
	if (diferenca (a->esq, a->dir) == 2){
		AVL aux = a->esq;
		if (diferenca (aux->esq, aux->dir) > 0)
			return rotacaoDir (a);
		a->esq = rotacaoEsq (a->esq);
		return rotacaoDir (a);
	}
	a->altura = max (altura(a->esq), altura(a->dir)) + 1;
	return a;
}

AVL insereAVL (AVL a, char* codigo, Fat v){
	if (!a){
		a = malloc (sizeof (struct avl));
		a->codigo = strdup (codigo);
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
Boolean existeAVL (AVL a, char* codigo){
	AVL aux = a;
	int i;
	while (aux){
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
Fat getfatfromavl(AVL a, char* codigo){
	AVL aux = a;
	int i;
	while(aux){
		i = strcmp(codigo, aux->codigo);
		if(i==0) return aux->extra;
		if(i>0) aux = aux->dir;
		else aux = aux->esq; 
	}
	return	false;
}

/*faz fre de uma avl e de todos os seus nodos*/
void freeTree (AVL a){
	if (a){
		freeTree (a->esq);
		freeTree (a->dir);
		free (a);
	}
}

char** auxiliarImprime(char** lista, AVL t, int *i) {
	if (t!=NULL) {
		lista = auxiliarImprime(lista, t->esq, i);
		lista[*i] = malloc(sizeof(char)*10);
		strcpy(lista[(*i)++], t->codigo);
		lista = auxiliarImprime(lista, t->dir, i);
	}
	return lista;
}

/*faz print do valor de um boolean, mais para debug*/
void printbool(Boolean a){
	if (a){
		printf("true\n");
	}
	else{
		printf("false\n");
	}
}