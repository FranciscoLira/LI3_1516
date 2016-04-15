#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlfil.h"
#include "Filial.h"

struct avlfil {
	int altura;
	char* codigo;
	AVLfil produtos;
	int nump;
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

AVLfil insereDirfil (AVLfil a, char* codigo, char* produto) {
	a->dir = insereAVLfil (a->dir, codigo, produto);
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

AVLfil insereEsqfil (AVLfil a, char* codigo, char *produto) {
	a->esq = insereAVLfil (a->esq, codigo, produto);
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

void insereprod(AVLfil a,char* cliente, char* produto){
	AVLfil aux=a;
	int i;
	while(aux){
		i=strcmp(cliente, aux -> codigo);
		if(i==0){
			if(!existeAVLfil(aux->produtos, produto)){
				insereAVLfil(aux->produtos, produto, "");
				aux->nump+=1; 
				return;
			}
			else return;
		}
		else{
			 if(i<0) aux = aux -> esq;
			 else aux = aux -> dir;
			}
	}
}

AVLfil insereAVLfil (AVLfil a, char* codigo, char *produto) {
	if (!a) {
		a = malloc (sizeof (struct avlfil));
		a->codigo = (char*)malloc(sizeof(char) * 10); /*Está a fazer de 10,mas pode ser menos*/
		strcpy(a->codigo, codigo);
		a->esq = a->dir = NULL;
		a->altura = 1;
		if(strcmp("",produto)==0) a->produtos=NULL;
		else{
			a->produtos = NULL;
			a->produtos = insereAVLfil(a->produtos, produto, "");
			a->nump = 1;
		}
		return a;
	}
	if (strcmp (codigo, a->codigo) > 0)
		return insereDirfil (a, codigo,produto);
	return insereEsqfil (a, codigo,produto);
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
void freeTreefil (AVLfil a) {
	if (a) {
		freeTreefil (a->esq);
		freeTreefil (a->dir);
		free (a);
	}
}

 int getnum(AVLfil a,char * c){
 	int i;
 	AVLfil aux = a;
 		while (aux) {
		i = strcmp (c, aux->codigo);
		if (i == 0)
			return aux->nump;
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
		}
	return 0;
 }

 void inorder(AVLfil a){
 	if(a){
 		inorder(a->esq);
 		printf("%s\n",a->codigo);
 		inorder(a->dir);
 	}
 }