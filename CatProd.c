#include "CatProd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"

typedef struct conjProds {
	char** lista;
}*lstProd;

typedef struct avlp {
	int tamanho;
	AVL root;
} *Trees;

typedef struct prod {
	char nomeprod[10];
}Prod;

typedef struct prods {
	Trees cP[26];
}Cat;

Produto inserep(char *x){
	Produto p=malloc(sizeof(struct prod));
	strcpy(p->nomeprod,x);
	return p;
}

Produto alterap(char *x,Produto p){
	strcpy(p->nomeprod,x);
	return p;
}

CatProds initCatProds() {
	int i;
	CatProds p=malloc(sizeof(struct prods));
	for (i = 0; i < 26; i++) {
		p->cP[i] = malloc(sizeof(struct avlp));
		p->cP[i]->tamanho = 0;
		p->cP[i]->root = NULL;
	}
	return p;
}

CatProds insereProduto(CatProds cps, Produto p){
	int i = (p->nomeprod[0] - 65);
	cps->cP[i]->root = insereAVL(cps->cP[i]->root,p->nomeprod,NULL);
	cps->cP[i]->tamanho++;
	return cps;
}

Boolean existeProduto(CatProds cps, Produto p){
	int i = (p->nomeprod[0] - 65);
	if(i<0 || i>25) return false;
	if(existeAVL(cps->cP[i]->root,p->nomeprod))
		return true;
	else return false;
}

int totalProdutos(CatProds cps){
	int i, r=0;
	for(i=0; i<26; i++){
		r+=cps->cP[i]->tamanho;
	}
	return r;
}

int totalProdutosLetra(CatProds cps, char letra){
	int i = letra - 65;
	return (cps->cP[i]->tamanho);
}

void removeCatProd(CatProds cps){
	int i;
	if (cps==NULL)return;
	for(i=0; i<26;i++){
		freeTree(cps->cP[i]->root);
		free(cps->cP[i]);
	}
	free(cps);
}
void printarray(char ** l, int n){
	int i=0;
	while(i<n)
		printf("%s\n",l[i++]);
	/*Por isto pag a pag and done */
}
void imprimeLista (CatProds cps, char letra) {
	char a;
	int t, up, down, pag, j, m, constante;
    int n = totalProdutosLetra(cps,letra);
	int i = 0;
	int k = letra - 65;
	lstProd l = malloc(sizeof(struct conjProds));
	l->lista=malloc(sizeof(char*)*n);
	l->lista = auxiliarImprime(l->lista,cps->cP[k]->root, &i);
	printf("Numero Total de elementos: %d\nIntroduza o número de produtos que deseja consultar por página (O recomendado é 700) : ", n);
	if(scanf("%d", &t) != 0) {;}
	printf("\n");
	down = 0; up = t; pag = 1;
	constante = t;
	while (a != 'Q') {
		      printf("                                                                            Página %d\n\n", pag);
		      j=down;
		      m = up;
	          while (down < up) {
		             printf("%s  ", l->lista[down]);
		             down++;
	          }
	          printf("\n\n");
	          printf("O que pretende fazer a seguir: \n\n");
	          if (j == 0) printf("                                                             (Q) SAIR                    (S) PÁGINA SEGUINTE\n");
              else if (j != 0 && m != n)  printf("                                                          (Q) SAIR     (A) PÁGINA ANTERIOR    (S) PÁGINA SEGUINTE\n");
              else printf("                                                             (Q) SAIR                    (A) PÁGINA ANTERIOR\n");
	          if(scanf("%s", &a) != 0) {;}
              if (a == 'S') {
              	             if (up + t > n ) up = n; 
              	             else up = up + constante;
              	             pag++;
              	            }
              else if (a == 'A') {
              	                 up = j; 
              	                 if (j-constante <= 0 ) down = 0; 
              	                 else down = j - constante; 
              	                 pag--;
              	             }
    }
}






