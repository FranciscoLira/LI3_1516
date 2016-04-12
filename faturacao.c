#include "faturacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"
#include "boolean.h"

struct vendatmp{
	char produto[10];
	double preco;
	int quantidade;
	int promo;
	char cliente[10];
	int mes;
	int filial;
};

struct fat{
	double faturacao;
	int quantidade;
};

struct fatmes{
	AVL codigos[2];
	int totalvendas[2];
	double totalfat[2];
};

struct fatall{
	Fatmes mes[12];
};

struct empresa{
	Fatall filial[3];
};

/*inicia um*/
Fatmes initFatmes(){
	int i;
	Fatmes r = (Fatmes)malloc(sizeof(struct fatmes));
	for(i=0;i<2;i++){
		r->codigos[i]=NULL;
		r->totalvendas[i]=0;
		r->totalfat[i]=0;
	}
	return r;
}

Fatall initFatall(){
	int i;
	Fatall r = (Fatall)malloc(sizeof(struct fatall));
	for(i=0; i<12; i++){
		r->mes[i]=initFatmes();
	}
	return r;
}

Emp initEmpresa(int q){
	int i;
	Emp r = (Emp)malloc(sizeof(struct empresa));
	for(i=0; i<q; i++){
		r->filial[i] = initFatall();
	}
	return r;
}

/*Retorna a faturação de uma certa venda*/
Fat convvendafat(Vendatmp a){
	Fat r = (Fat)malloc(sizeof(struct fat));
	r->quantidade=a->quantidade;
	r->faturacao=(a->quantidade)*(a->preco);
	return r;
}



void insereVenda(Emp e, Vendatmp v){
	Fat r = convvendafat(v);
	insereAVL(e->filial[(v->filial)-1]->mes[(v->mes)-1]->codigos[v->promo],v->produto,r);
	e->filial[(v->filial)-1]->mes[(v->mes)-1]->totalfat[v->promo]+=r->faturacao;
	e->filial[(v->filial)-1]->mes[(v->mes)-1]->totalvendas[v->promo]+=r->quantidade;
}

Boolean existeVenda(Emp e, Vendatmp v){
	AVL tmp = e->filial[(v->filial)-1]->mes[(v->mes)-1]->codigos[v->promo];
	return (existeAVL(tmp,v->produto));
}

/*Retorna uma faturação de um dado produto, recebendo a filial (f) o mes (imes) e se é promoção ou não*/
Fat produtofat(Emp e, int f, int imes, int p, char* produto){
	AVL tmp = e->filial[f]->mes[imes]->codigos[p];
	Fat r = getfatfromavl(tmp, produto); 
	return r;
}

Fat somaFat(Fat* lista, int q){
	int i;
	Fat r = lista[0];
	for(i=0; i<q; i++){
		r->quantidade += lista[i]->faturacao;
		r->faturacao += lista[i]->faturacao;
	}
	return r;
}