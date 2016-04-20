#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlfil.h"

struct meses{
	AVLfil mes[2];
	int nump[2];
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

AVLfil insereDirfil (AVLfil a, char* codigo, char* produto, int mes, int quant, int x) {
	a->dir = insereAVLfil (a->dir, codigo, produto,mes, quant,x);
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

AVLfil insereEsqfil (AVLfil a, char* codigo, char *produto, int mes, int quant, int x) {
	a->esq = insereAVLfil (a->esq, codigo, produto,mes,quant,x);
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

void adicionaQuant(AVLfil a, char* prod, int quant){
	AVLfil aux=a;
	int i;
	while (aux) {
		i = strcmp (prod, aux->codigo);
		if (i == 0)
			aux->numpt += quant;
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
}

void insereprod(AVLfil a,char* cliente, char* produto, int mes, int quant, int x){
	AVLfil aux=a;
	int i, m = mes-1;
	while(aux){
		i=strcmp(cliente, aux -> codigo);
		if(i==0){
			if(!existeAVLfil(aux->produtos[m]->mes[x], produto)){
				aux->produtos[m]->mes[x]=insereAVLfil(aux->produtos[m]->mes[x], produto, "",mes,quant,x);
				aux->numpt += quant;
				aux->produtos[m]->nump[x] += quant; 
				return;
			}
			else{
				aux->numpt +=quant;
				aux->produtos[m]->nump[x]+=quant;
				adicionaQuant(aux->produtos[m]->mes[x],produto,quant);
				return;
			}
		}
		else {
			if (i < 0) aux = aux -> esq;
			else aux = aux -> dir;
		}
	}
}

AVLfil insereAVLfil (AVLfil a, char* codigo, char *produto, int mes, int quant, int x) {
	int m = mes-1, i;
	if (!a) {
		a = malloc (sizeof (struct avlfil));
		a->codigo = (char*)malloc(sizeof(char) * 10); 
		strcpy(a->codigo, codigo);
		a->esq = a->dir = NULL;
		a->altura = 1;
		a->numpt=0;
		if(strcmp("",produto)==0)
			a->numpt += quant;/* Neste caso esta é apenas a quantidade do produto e nao a total */
		else{
			for(i=0;i<12;i++){
				a->produtos[i]=(struct meses*)malloc(sizeof(struct meses));
				a->produtos[i]->mes[0] = NULL;
				a->produtos[i]->mes[1] = NULL;
				a->produtos[i]->nump[0]= 0;
				a->produtos[i]->nump[1]= 0;
			}
			a->produtos[m]->mes[x]=insereAVLfil(a->produtos[m]->mes[x], produto, "",mes,quant,x);
			a->numpt += quant;
			a->produtos[m]->nump[x]+=quant;
		}
		return a;
	}
	if (strcmp (codigo, a->codigo) > 0)
		return insereDirfil (a, codigo,produto,mes,quant,x);
	return insereEsqfil (a, codigo,produto,mes,quant,x);
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

/*faz free de uma avl e de todos os seus nodos*/
void freeTreefil (AVLfil a, int x) {
	int i;
	if (a) {
		freeTreefil (a->esq,x);
		freeTreefil (a->dir,x);
		if(x==0)
			for(i=0;i<12;i++){
				freeTreefil(a->produtos[i]->mes[0],1);
				freeTreefil(a->produtos[i]->mes[1],1);
				free(a->produtos[i]);
			}
		free(a->codigo);
		free (a);
	}
}

 int getnum(AVLfil a,char * c, int mes){
 	int i, total=0;
 	AVLfil aux = a;
 		while (aux) {
		i = strcmp (c, aux->codigo);
		if (i == 0) {
			if (mes > 11)
				return aux->numpt;
			else{
				total+=aux->produtos[mes]->nump[0];
				total+=aux->produtos[mes]->nump[1];
				return total;
			}
		}
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
	return 0;
 }
/* Esta função devolve um Catalogo de produtos com os clientes que fizeram compras
nas 3 filiais para ser imprimido na main (querie 7)*/
CatProds funcaocat(CatProds cps, AVLfil x1, AVLfil x2,AVLfil x3){
	Produto p= inserep("");
	AVLfil a = x1;
	if(a){
 		funcaocat(cps,a->esq,x2,x3);
 		p=alterap(a->codigo,p);
 		if(!existeProduto(cps, p))
 			if(existeAVLfil(x2,a->codigo))
 				if(existeAVLfil(x3,a->codigo))
 					cps=insereProduto(cps,p);
 		funcaocat(cps,a->dir,x2,x3);
 	}
 	return cps;
}

/*Falta tratar do encapsulamento, mas para já nao*/
char** quemComprou(char** lista, char *prod, AVLfil t, int *i, int z, int *tam) {
	int j;
	if (t != NULL) {
		lista = quemComprou(lista,prod, t->esq, i,z,tam);
		for(j=0;j<12;j++){
			if(existeAVLfil(t->produtos[j]->mes[z], prod)){
				lista[*i] = malloc(sizeof(char) * 10);
				strcpy(lista[(*i)++], t->codigo);
				(*tam)++;
			}
		}
		lista = quemComprou(lista,prod, t->dir, i,z,tam);
	}
	return lista;
}

void altera(AVLfil res, char * prod, int quant){
	AVLfil aux = res;
	int i;
	while (aux) {
		i = strcmp (prod, aux->codigo);
		if (i == 0)
			aux->numpt+=quant;
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
}

AVLfil auxp(AVLfil res, AVLfil prod,int mes,int tipo,char *cliente){
	int i;
	AVLfil a=prod;
	while (a) {
		i = strcmp (cliente, a->codigo);
		if (i == 0)
			break;
		if (i > 0)
			a = a->dir;
		else
			a = a->esq;
	}
	a=a->produtos[mes]->mes[tipo];
	res=auxiliarInsere(res,a);
	return res;
}

void inorder(AVLfil a){
	if(a){
		inorder(a->esq);
		printf("%s\n",a->codigo );
		inorder(a->dir);
	}
}

AVLfil auxiliarInsere(AVLfil res, AVLfil prod){
	AVLfil a = prod;
	if(a){
		res = auxiliarInsere(res, a->esq);
		if(!existeAVLfil(res,a->codigo))
			res = insereAVLfil(res,a->codigo,"",0,a->numpt,0);
		else{
			altera(res,a->codigo,a->numpt);
		}
		res = auxiliarInsere(res, a->dir);
	}
	return res;
}

int numAVL(AVLfil res){
	AVLfil aux = res;
	if (aux == NULL) return 0;
	else return 1+(numAVL(aux->esq))+(numAVL(aux->dir));
}

void inseredaAvl(AVLfil res, int* quantidades, char** codigos, int *i) {
	AVLfil aux = res;
	if (aux) {
		inseredaAvl(aux->esq, quantidades, codigos, i);
		codigos[*i] = malloc(sizeof(char)*10);
		strcpy(codigos[*i],res->codigo);
		quantidades[*i] = res->numpt;
		(*i)++;
		inseredaAvl(aux->dir, quantidades, codigos, i);
	}
}
