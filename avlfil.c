#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlfil.h"


struct meses {
	AVLfil mes;
	int nump;
};

struct avlfil {
	int altura;
	char* codigo;
	struct meses* produtos[12];
	int numpt;
	struct avlfil* esq;
	struct avlfil* dir;
};

int maxfil (int a, int b) {
	return (a > b ? a : b);
}

int alturafil (AVLfil a) {
	if (a)
		return a->altura;
	return 0;
}

int diferencafil (AVLfil a, AVLfil b) {
	return alturafil (a) - alturafil (b);
}

AVLfil rotacaoEsqfil (AVLfil a) {
	AVLfil aux = a->dir;
	a->dir = aux->esq;
	aux->esq = a;
	a->altura = maxfil (alturafil(a->dir), alturafil(a->esq)) + 1;
	aux->altura = maxfil (alturafil(aux->dir), alturafil(aux->esq)) + 1;
	return aux;
}

AVLfil rotacaoDirfil (AVLfil a) {
	AVLfil aux = a->esq;
	a->esq = aux->dir;
	aux->dir = a;
	a->altura = maxfil (alturafil(a->dir), alturafil(a->esq)) + 1;
	aux->altura = maxfil (alturafil(aux->dir), alturafil(aux->esq)) + 1;
	return aux;
}

AVLfil insereDirfil (AVLfil a, char* codigo, char* produto, int mes, int quant) {
	a->dir = insereAVLfil (a->dir, codigo, produto, mes, quant);
	if (diferencafil (a->dir, a->esq) == 2) {
		AVLfil aux = a->dir;
		if (diferencafil (aux->dir, aux->esq) > 0)
			return rotacaoEsqfil (a);
		a->dir = rotacaoDirfil (a->dir);
		return rotacaoEsqfil (a);
	}
	a->altura = maxfil (alturafil(a->dir), alturafil(a->esq)) + 1;
	return a;
}

AVLfil insereEsqfil (AVLfil a, char* codigo, char *produto, int mes, int quant) {
	a->esq = insereAVLfil (a->esq, codigo, produto, mes, quant);
	if (diferencafil (a->esq, a->dir) == 2) {
		AVLfil aux = a->esq;
		if (diferencafil (aux->esq, aux->dir) > 0)
			return rotacaoDirfil (a);
		a->esq = rotacaoEsqfil (a->esq);
		return rotacaoDirfil (a);
	}
	a->altura = maxfil (alturafil(a->esq), alturafil(a->dir)) + 1;
	return a;
}

void insereprod(AVLfil a, char* cliente, char* produto, int mes, int quant) {
	AVLfil aux = a;
	int i, m = mes - 1;
	while (aux) {
		i = strcmp(cliente, aux -> codigo);
		if (i == 0) {
			if (!existeAVLfil(aux->produtos[m]->mes, produto)) {
				aux->produtos[m]->mes = insereAVLfil(aux->produtos[m]->mes, produto, "", mes, quant);
				aux->numpt += quant;
				aux->produtos[m]->nump += quant;
				return;
			}
			else {
				aux->numpt += quant;
				aux->produtos[m]->nump += quant;
				return;
			}
		}
		else {
			if (i < 0) aux = aux -> esq;
			else aux = aux -> dir;
		}
	}
}

AVLfil insereAVLfil (AVLfil a, char* codigo, char *produto, int mes, int quant) {
	int m = mes - 1, i;
	if (!a) {
		a = malloc (sizeof (struct avlfil));
		a->codigo = (char*)malloc(sizeof(char) * 10); /*Está a fazer de 10,mas pode ser menos*/
		strcpy(a->codigo, codigo);
		a->esq = a->dir = NULL;
		a->altura = 1;
		if (strcmp("", produto) == 0);
		else {
			for (i = 0; i < 12; i++) {
				a->produtos[i] = (struct meses*)malloc(sizeof(struct meses));
				a->produtos[i]->mes = NULL;
				a->produtos[i]->nump = 0;
			}
			a->produtos[m]->mes = insereAVLfil(a->produtos[m]->mes, produto, "", mes, quant);
			a->numpt += quant;
			a->produtos[m]->nump += quant;
		}
		return a;
	}
	if (strcmp (codigo, a->codigo) > 0)
		return insereDirfil (a, codigo, produto, mes, quant);
	return insereEsqfil (a, codigo, produto, mes, quant);
}



/*retorna um bool para saber se um elemento está ou não na avl*/
Boolean existeAVLfil (AVLfil a, char* codigo) {
	AVLfil aux = a;
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
void freeTreefil (AVLfil a, int x) {
	int i;
	if (a) {
		freeTreefil (a->esq, x);
		freeTreefil (a->dir, x);
		if (x == 0)
			for (i = 0; i < 12; i++) {
				freeTreefil(a->produtos[i]->mes, 1);
				free(a->produtos[i]);
			}
		free(a->codigo);
		free (a);
	}
}

int getnum(AVLfil a, char * c, int mes) {
	int i;
	AVLfil aux = a;
	while (aux) {
		i = strcmp (c, aux->codigo);
		if (i == 0) {
			if (mes > 11)
				return aux->numpt;
			else
				return aux->produtos[mes]->nump;
		}
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
	return 0;
}

CatProds funcaocat(CatProds cps, AVLfil x1, AVLfil x2, AVLfil x3) {
	Produto p = inserep("");
	AVLfil a = x1;
	if (a) {
		funcaocat(cps, a->esq, x2, x3);
		p = alterap(a->codigo, p);
		if (!existeProduto(cps, p))
			if (existeAVLfil(x2, a->codigo))
				if (existeAVLfil(x3, a->codigo))
					cps = insereProduto(cps, p);
		funcaocat(cps, a->dir, x2, x3);
	}
	return cps;
}