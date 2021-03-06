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
	double faturacao;
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

AVLfil insereDirfil (AVLfil a, char* codigo, char* produto, int mes, int quant, int x, double preco) {
	a->dir = insereAVLfil (a->dir, codigo, produto,mes, quant,x,preco);
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

AVLfil insereEsqfil (AVLfil a, char* codigo, char *produto, int mes, int quant, int x, double preco) {
	a->esq = insereAVLfil (a->esq, codigo, produto,mes,quant,x,preco);
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

void adicionaQuant(AVLfil a, char* prod, int quant, int preco){
	AVLfil aux=a;
	int i;
	while (aux) {
		i = strcmp (prod, aux->codigo);
		if (i == 0){
			aux->faturacao += preco*quant;
			aux->numpt += quant;
		}
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
}

void insereprod(AVLfil a,char* cliente, char* produto, int mes, int quant, int x, double preco){
	AVLfil aux=a;
	int i, m = mes-1;
	while(aux){
		i=strcmp(cliente, aux -> codigo);
		if(i==0){
			if(!existeAVLfil(aux->produtos[m]->mes[x], produto)){
				aux->produtos[m]->mes[x]=insereAVLfil(aux->produtos[m]->mes[x], 
				produto, "",mes,quant,x,preco);
				aux->numpt += quant;
				aux->faturacao += quant*preco;
				aux->produtos[m]->nump[x] += quant; 
				return;
			}
			else{
				aux->numpt += quant;
				aux->produtos[m]->nump[x]+=quant;
				adicionaQuant(aux->produtos[m]->mes[x],produto,quant,preco);
				return;
			}
		}
		else {
			if (i < 0) aux = aux -> esq;
			else aux = aux -> dir;
		}
	}
}

AVLfil insereAVLfil (AVLfil a, char* codigo, char *produto, int mes, int quant, int x, double preco) {
	int m = mes-1, i;
	if (!a) {
		a = malloc (sizeof (struct avlfil));
		a->codigo = (char*)malloc(sizeof(char) * 10); 
		strcpy(a->codigo, codigo);
		a->esq = a->dir = NULL;
		a->altura = 1;
		a->numpt=0;
		a->faturacao=preco*quant;
		if(strcmp("",produto)==0){
			a->numpt += quant;/* Neste caso esta é apenas a quantidade do produto e nao a total */
		}
		else{
			for(i=0;i<12;i++){
				a->produtos[i]=(struct meses*)malloc(sizeof(struct meses));
				a->produtos[i]->mes[0] = NULL;
				a->produtos[i]->mes[1] = NULL;
				a->produtos[i]->nump[0]= 0;
				a->produtos[i]->nump[1]= 0;
			}
			a->produtos[m]->mes[x]=insereAVLfil(a->produtos[m]->mes[x], produto, "",mes,quant,x,preco);
			a->numpt += quant;
			a->produtos[m]->nump[x]+=quant;
		}
		return a;
	}
	if (strcmp (codigo, a->codigo) > 0)
		return insereDirfil (a, codigo,produto,mes,quant,x,preco);
	return insereEsqfil (a, codigo,produto,mes,quant,x,preco);
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
		if(x==10){
			if(a->numpt!=0){
				freeTreefil(a->produtos[0]->mes[0],1);
				free(a->produtos[0]);
			}
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
	Produto p= inserep("      ");
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
				lista = realloc(lista, 8*((*i)+1));
				lista[*i] = malloc(sizeof(char) * (strlen(prod)+1));
				strcpy(lista[(*i)++], t->codigo);
				(*tam)++;
			}
		}
		lista = quemComprou(lista,prod, t->dir, i,z,tam);
	}
	return lista;
}

AVLfil alocastrmes(AVLfil a){
	a->produtos[0]= malloc(sizeof(struct meses));
	a->produtos[0]->mes[0]=NULL;
	return a;
}

AVLfil inserenoscl(char* client, AVLfil a){
	AVLfil aux = a->produtos[0]->mes[0];
	a->produtos[0]->mes[0]=insereAVLfil(aux, client, "",0,0,0,0);
	return a;
}

void alteracl(AVLfil res, char * prod, char* client){
	AVLfil aux = res;
	int i;
	while (aux) {
		i = strcmp (prod, aux->codigo);
		if (i == 0){
			if(aux->numpt==0) aux = alocastrmes(aux);
			if(!existeAVLfil(aux->produtos[0]->mes[0],client)){
				aux = inserenoscl(client,aux);
				aux->numpt+=1;
			}
		}
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
}

void altera(AVLfil res, char * prod, int quant, double faturacao){
	AVLfil aux = res;
	int i;
	while (aux) {
		i = strcmp (prod, aux->codigo);
		if (i == 0){
			aux->faturacao+=faturacao;
			aux->numpt+=quant;
		}
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
	if(a){
	a=a->produtos[mes]->mes[tipo];
	res=auxiliarInsere(res,a);
	}
	return res;
}

AVLfil auxiliarInsere(AVLfil res, AVLfil prod){
	AVLfil a = prod;
	if(a){
		res = auxiliarInsere(res, a->esq);
		if(!existeAVLfil(res,a->codigo)){
			res = insereAVLfil(res,a->codigo,"",0,a->numpt,0,0);
			altera(res,a->codigo,0,a->faturacao);
		}
		else{
			altera(res,a->codigo,a->numpt, a->faturacao);
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

void inseredaAvlfil(AVLfil res, int* quantidades, char** codigos, int *i) {
	AVLfil aux = res;
	if (aux) {
		inseredaAvlfil(aux->esq, quantidades, codigos, i);
		codigos[*i] = malloc(sizeof(char)*10);
		strcpy(codigos[*i],res->codigo);
		quantidades[*i] = res->numpt;
		(*i)++;
		inseredaAvlfil(aux->dir, quantidades, codigos, i);
	}
}

void inseredaAvlfat(AVLfil res, double* quantidades, char** codigos, int *i) {
	AVLfil aux = res;
	if (aux) {
		inseredaAvlfat(aux->esq, quantidades, codigos, i);
		codigos[*i] = malloc(sizeof(char)*10);
		strcpy(codigos[*i],res->codigo);
		quantidades[*i] = res->faturacao;
		(*i)++;
		inseredaAvlfat(aux->dir, quantidades, codigos, i);
	}
}

int quantosClientes(AVLfil t, char* prod){
	AVLfil aux = t;
	int i;
	while (aux) {
		i = strcmp (prod, aux->codigo);
		if (i == 0)
			return aux->numpt;
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
	return 0;
}
