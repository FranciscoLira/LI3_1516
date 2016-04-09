#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatProd.h"
#include "myavl.h"
#include "CatClient.h"

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128 

/*Lê o ficheiro */
CatProds lerclientouprod(CatProds cps, int x){
	FILE *f1;
	char str[10];
	Produto p = inserep("");
	if(x==0) f1= fopen("Dados/Clientes.txt","r");
	else f1 = fopen("Dados/Produtos.txt","r");
	if(f1==NULL) return 0;
	while(1){
		if(fgets(str,9,f1)!=NULL){
			strtok(str,"\n\r");
			p = alterap(str,p);
			cps = insereProduto(cps,p);
		}
		else break;
	}
	fclose(f1);
	return cps;
}

int main(){
	CatProds cps;
	Produto p = inserep("FZ1998");
	cps = initCatProds();
	cps = lerclientouprod(cps,1);
	printx(cps);
	printf("%d\n",totalProdutos(cps));
	if(existeProduto(cps,p)) printf("EXISTE\n");
	removeCatProd(cps);
	return 0;
}