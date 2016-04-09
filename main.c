#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatProd.h"
#include "myavl.h"
#include "CatClient.h"

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128 
/*
void interpretador () {

	printf("1. Ler todos os ficheiros\n");
	printf("2. Lista de produtos começados por alguma letra(maiúscula)\n");
	printf("3. Total faturado(N e P) com um dado produto num dado mês\n");
	printf("4. Códigos de produtos que ninguém comprou\n");
	printf("5. Tabela com nº total de produtos comprados por um cliente mês a mês\n");
	printf("6. Total de vendas e total faturado num intervalo de meses(Ex:3..7)\n");
	printf("7. Lista ordenada de clientes que realizaram compras em todas as filiais\n");
	printf("7. \n");
	while (cmd[0] != 'Q') {
		valor = 0;
		switch(cmd[0]) {
			case '1':
					break;
			case '2':
					break;       
			case '3': 
					break;
			case '4': 
					break;
			case '5': 
					break;
			case '6':
					break;
			case '8':
					break;
			case '9':
					break;
			case '10':
					break;
			case '11':
					break;
			case '12':
					break;
		   }
	if (fgets(cmd,BufferM,stdin)!=NULL) {;}
	}
}
*/
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
	printf("%d\n",totalProdutos(cps));
	if(existeProduto(cps,p)) printf("EXISTE\n");
	imprimeLista(cps, 'A');
	removeCatProd(cps);
	return 0;
}