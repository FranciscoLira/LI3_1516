#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myavlcod.h"

/* Todo o código aqui apresentado foi desenvolvido por Fábio Baião e depois modificado por Francisco Lira */

/*É necessário estarem aqui?(faturacao.c)*/
struct venda {
	/* char produto[10]; */
	double preco;
	int quantidade;
	/* int promo; */
	char cliente[10];
	/* int mes; */
	/* int filial; */
};

struct vendatmp {
	char produto[10]; 
	double preco;
	int quantidade;
	int promo; /*1 se P*/
	char cliente[10];
	int mes; 
	int filial; 
};


struct avlcod {
	int altura;
	char codigo[10]; /*Código do produto, podia ser também do cliente, mas há mais produtos*/
	Venda codigoV; /*dentro deste elementos temos cod cliente, quantidade e preço */
	struct avlcod* esq; 
	struct avlcod* dir;
};

int maxcod (int a, int b){
	return (a > b ? a : b);
}

int alturacod (AVLcod a){
	if (a)
		return a->altura;
	return 0;
}

int diferencacod (AVLcod a, AVLcod b){
	return alturacod (a) - alturacod (b);
}

AVLcod rotacaoEsqcod (AVLcod a){
	AVLcod aux = a->dir;
	a->dir = aux->esq;
	aux->esq = a;
	a->altura = maxcod (alturacod(a->dir), alturacod(a->esq)) + 1;
	aux->altura = maxcod (alturacod(aux->dir), alturacod(aux->esq)) + 1;
	return aux;
}

AVLcod rotacaoDircod (AVLcod a){
	AVLcod aux = a->esq;
	a->esq = aux->dir;
	aux->dir = a;
	a->altura = maxcod (alturacod(a->dir), alturacod(a->esq)) + 1;
	aux->altura = maxcod (alturacod(aux->dir), alturacod(aux->esq)) + 1;
	return aux;
}

AVLcod insereDircod (AVLcod a, Vendatmp codV){
	a->dir = insereAVLcod (a->dir, codV);
	if (diferencacod (a->dir, a->esq) == 2){
		AVLcod aux = a->dir;
		if (diferencacod (aux->dir, aux->esq) > 0)
			return rotacaoEsqcod (a);
		a->dir = rotacaoDircod (a->dir);
		return rotacaoEsqcod (a);
	}
	a->altura = maxcod (alturacod(a->dir), alturacod(a->esq)) + 1;
	return a;
}

AVLcod insereEsqcod (AVLcod a,Vendatmp codV){
	a->esq = insereAVLcod (a->esq, codV);
	if (diferencacod (a->esq, a->dir) == 2){
		AVLcod aux = a->esq;
		if (diferencacod (aux->esq, aux->dir) > 0)
			return rotacaoDircod (a);
		a->esq = rotacaoEsqcod (a->esq);
		return rotacaoDircod (a);
	}
	a->altura = maxcod (alturacod(a->esq), alturacod(a->dir)) + 1;
	return a;
}

Venda castfromtmp(Vendatmp codV){
	Venda r = (Venda)malloc(sizeof(struct venda));
	r->preco = codV->preco;
	r->quantidade = codV->quantidade;
	strcpy(r->cliente, codV->cliente);
}

AVLcod insereAVLcod (AVLcod a, Vendatmp codV){
	if (!a){
		a = malloc (sizeof (struct avlcod));
		strcpy(a->codigo, codV->produto);
		a->esq = a->dir = NULL;
		a->altura = 1;
		a->codigoV = castfromtmp(codV);
		return a;
	}
	if (strcmp (codV->produto, a->codigo) > 0)
		return insereDircod (a, codV);
	return insereEsqcod (a, codV);
}

Boolean existeAVLcod (AVLcod a, Vendatmp v){
        AVLcod aux = a;
        int i;
        while (aux){
                i = strcmp (v->produto, aux->codigo);
                if (i == 0)
                        return true;
                if (i > 0)
                        aux = aux->dir;
                else
                        aux = aux->esq;
        }
        return false;
}


void freeTreecod (AVLcod a){
        if (a){
                freeTreecod (a->esq);
                freeTreecod (a->dir);
                free (a);
        }
}

char** auxiliarImprimecod (char** lista, AVLcod t, int *i) {
	if (t!=NULL) {
		lista = auxiliarImprimecod(lista, t->esq, i);
		lista[*i] =malloc(sizeof(char)*10);
		strcpy(lista[(*i)++], t->codigo);
		lista = auxiliarImprimecod(lista, t->dir, i);
	}
	return lista;
}

int findclienteaux(AVLcod cod, char* cliente){
	int r=0;
	if(strcmp(cliente,cod->codigoV->cliente) == 0){
		r+=cod->codigoV->quantidade;
	}
	if(cod->esq) r+=findclienteaux(cod->esq, cliente);
	if(cod->dir) r+=findclienteaux(cod->dir, cliente);
	return r;

}