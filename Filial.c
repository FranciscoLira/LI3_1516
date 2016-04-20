#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filial.h"

/*Estrutura que serve para guardar os clientes que compraram
um determinado produto*/
struct comprou{
	char **lista;
	int tam;
};
/*Estrutura principal*/
struct filial{
	AVLfil clientes[26];
	AVLfil prods;
};
/*Aloca memória necessária para a estrutura principal, a restante é alocada em avlfil.c*/
Filial initFilial() {
	int i;
	Filial f = malloc(sizeof(struct filial));
	f->prods = NULL;
	for (i = 0; i < 26; i++) {
		f->clientes[i] = NULL;
	}
	return f;
}
Filial insereProds(Filial f, Produto p){
	char* l = malloc(10);
	strcpy(l,getStringp(p));
	f->prods = insereAVLfil(f->prods,l,"",0,0,0);
	free(l);
	return f;
}
/*Verifica se um cliente ja esta na estrutura*/
Boolean existeCl(Filial f, char *c){
	int indice = c[0] -65;
	return (existeAVLfil(f->clientes[indice], c));
}
/*Insere na estrutura. Este int m é o P ou N, em que N=0, P=1*/
Filial insereFilial(Filial f, Cliente c, Produto p, int mes, int quant, int m){
	int indice;
	AVLfil aux;
	char *stringp = (char *)malloc(sizeof(char) * 10);
	char *stringc = (char *)malloc(sizeof(char) * 10);
	strcpy(stringc, getStringc(c));
	strcpy(stringp, getStringp(p));
	indice = stringc[0] - 65;
	aux = f->clientes[indice];
	if(!existeCl(f, stringc)){
		aux = insereAVLfil(aux,stringc,stringp,mes,quant,m);
		f->clientes[indice] = aux;
		altera(f->prods,stringp,quant);
	}
	else{
		insereprod(aux, stringc, stringp,mes,quant,m);
		altera(f->prods,stringp,quant);
	}
	free(stringp); free(stringc);
	return f;
}
/*Remove toda a estrutura da memória*/
void removeFilial(Filial f){
	int i;
	for (i = 0; i < 26; i++) {
		freeTreefil(f->clientes[i], 0);
	}
	free(f);
} 
/*Devolve o número de produtos que um cliente comprou num mes*/
int numprodutos(Filial f, Cliente c, int mes){
	int num, m = mes - 1;
	char *str = getStringc(c);
	int indice = str[0] - 'A';
	num = getnum(f->clientes[indice], str, m);
	return num;
}
/*Função para querie7... Falar com o professor sobre o facto de utilizar Catprods*/
CatProds makeCat(Filial *f, CatProds p) {
	int cl;
	for (cl = 0; cl < 26; cl++)
		p = funcaocat(p, f[0]->clientes[cl], f[1]->clientes[cl], f[2]->clientes[cl]);
	return p;
}
/* Função útil para a querie8;
   Retorna um Conjunto com os clientes que compraram um produto(N(0) ou P(1))*/
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
/*Free do conjunto de clientes(nao completo ainda!!)*/
void freeConj(ConjComprados c){
	free(c->lista);
	free(c);
}
/* Permite obter um array de strings com os clientes*/
char** getListConj(ConjComprados c){
	return c->lista;
}
/* Permite obter o numero de clientes no conjunto */
int getTamConj(ConjComprados c){
	return c->tam;
}

void quickSort(int* quant, char** cod, int l, int r) {
   int j;
   if( l < r ) {
       j = partition(quant, cod, l, r);
       quickSort(quant, cod, l, j-1);
       quickSort(quant, cod, j+1, r);
   }
}


int partition(int* quant, char** cod, int l, int r) {
   int pivot, i, j, t;
   char* t2 = malloc(10);
   pivot = quant[l];
   i = l; j = r+1;
	while(1) {
   	do ++i; while( quant[i] >= pivot && i <= r );
   	do --j; while( quant[j] < pivot );
   	if( i >= j ) break;
   	t = quant[i]; quant[i] = quant[j]; quant[j] = t;
   	strcpy(t2,cod[i]); strcpy(cod[i],cod[j]); strcpy(cod[j],t2);
   }
   t = quant[l]; quant[l] = quant[j]; quant[j] = t;
   strcpy(t2,cod[l]); strcpy(cod[l],cod[j]); strcpy(cod[j],t2);
   free(t2);
   return j;
}

void init (int n, char** codigos, int* quant) {
     codigos = (char**)malloc(sizeof(char*)*n);
	 quant = (int*)malloc(sizeof(int)*n);
}

void ordenaDecre (AVLfil res, char** codigos, int* quantidades, int n) {
	 int i;
	 i = 0;
	 inseredaAvl(res, quantidades, codigos, &i);
	 quickSort(quantidades, codigos, 0, n-1);
}

AVLfil funcao9(Filial *f, int mes, Cliente c){
	char* str=malloc(10);
	int i, j, k;
	AVLfil res = NULL;
	strcpy(str,getStringc(c));
	k=str[0]-65;
	for(i=0;i<3; i++)
		for(j=0;j<2;j++)
			res = auxp(res, f[i]->clientes[k], mes,j,str);
    free(str);
	return res;
}

AVLfil funcao10(Filial *f){
	int i;
	AVLfil res = NULL;
	for(i=0;i<3;i++)
		res = auxiliarInsere(res,f[i]->prods);
	return res;
}

