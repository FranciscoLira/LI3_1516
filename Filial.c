#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filial.h"
#include "boolean.h"
#include "avlfil.h"

struct comprou{
	char **lista;
	int tam;
};

struct filial{
	AVLfil clientes[26];
};

Filial initFilial() {
	int i;
	Filial f = malloc(sizeof(struct filial));
	for(i=0;i<26;i++){
		f->clientes[i] = NULL;
	}
	return f;
}

Boolean existeCl(Filial f, char *c){
	int indice = c[0] -65;
	return (existeAVLfil(f->clientes[indice], c));
}
/*Este int m é o P ou N, em que N=0, P=1*/
Filial insereFilial(Filial f, Cliente c, Produto p, int mes, int quant, int m){
	int indice;
	AVLfil aux;
	char *stringp =(char *)malloc(sizeof(char)*10); 
	char *stringc =(char *)malloc(sizeof(char)*10);
	strcpy(stringc, getStringc(c));
	strcpy(stringp, getStringp(p));
	indice = stringc[0] - 65;
	aux = f->clientes[indice];
	if(!existeCl(f, stringc)){
		aux = insereAVLfil(aux,stringc,stringp,mes,quant,m);
		f->clientes[indice] = aux;
	}
	else{
		insereprod(aux, stringc, stringp,mes,quant,m);
	}

	return f;
}

void removeFilial(Filial f){
	int i;
	for (i=0;i<26;i++){
		freeTreefil(f->clientes[i],0);
	}
	free(f);
} 

int numprodutos(Filial f, Cliente c, int mes){
	int num, m = mes - 1;
	char *str = getStringc(c);
	int indice = str[0] - 'A';
	num = getnum(f->clientes[indice],str,m);
	return num;
}

/*Função para querie7... Falar com o professor sobre o facto de utilizar Catprods*/
CatProds makeCat(Filial *f, CatProds p){
	int cl;
	for(cl=0;cl<26;cl++)
		p=funcaocat(p,f[0]->clientes[cl],f[1]->clientes[cl],f[2]->clientes[cl]);
	return p;
}

/* Função útil para a querie8 */
ConjComprados comprou(Produto p, Filial f, int tipo){
	int i=0,tam=0,j; 
	char *str=getStringp(p);
	ConjComprados s=malloc(sizeof(struct comprou));
	char **l =malloc(sizeof(char *)*60); /*Sera alocaçao dinamica, mas pra ja esta assim DEAL WITH IT*/
	for(j=0;j<26;j++)
		l=quemComprou(l,str,f->clientes[j],&i,tipo,&tam);
	s->lista=l;
	s->tam=tam;
	return s;
}

void freeConj(ConjComprados c){
	free(c->lista);
	free(c);
}

char** getListConj(ConjComprados c){
	return c->lista;
}

int getTamConj(ConjComprados c){
	return c->tam;
}
