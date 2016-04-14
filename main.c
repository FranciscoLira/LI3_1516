#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"
#include "CatProd.h"
#include "CatClient.h"
#include "faturacao.h"

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128 

/*Lê o ficheiro Produtos.txt*/
CatProds lerprod(CatProds cps){
	FILE *f1;
	char str[10];
	Produto p = inserep("");
	f1 = fopen("Dados/Produtos.txt","r");
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
/*Lê o ficheiro Clientes.txt*/
CatClients lerclient(CatClients cps){
	FILE *f1;
	char str[10];
	Cliente p = inserec("");
	f1= fopen("Dados/Clientes.txt","r");
	if(f1==NULL) return 0;
	while(1){
		if(fgets(str,9,f1)!=NULL){
			strtok(str,"\n\r");
			p = alterac(str,p);
			cps = insereCliente(cps,p);
		}
		else break;
	}
	fclose(f1);
	return cps;
}

int auxImprimeDown(int down, int up, int pag, int np) {
	if (pag == 1) down = 0;
	else if (pag == np) down = (pag-1)*90;
	else down = up-90;
	return down;
}

int auxImprimeUp(int up, int pag, int np, int n) {
    if (pag == 1) up = 90;
    else if (pag == np) up = n;
    else up = pag*90;
    return up;
 }



void imprimeLista(CatProds cps, char letra) {
	char a;
	int up, down, j, m, n, pag, t;
	float np;
	ConjProds l = getList(cps,letra);
	char** lista = getLista(l);
	n = getSize(l);
	np = n/90;
	if (n%90) np++;
	down = 0; up = 90;
	while (a != 'Q' || a != 'q') {
		if (system("@cls||clear")==0) {;}
		j = down; m = up;
		if (j == 0 && (a == 'A' || a == 'a')) printf("\nEsta operação não é permitida. Encontra-se na primeira página!\n\n");
		if (m == n && (a == 'S' || a == 's')) printf("\nEsta operação não é permitida. Encontra-se na ultima página!\n\n");
		if (pag < 1 || pag > np) printf("\nA opção escolhida não é válida!\n\n");
		printf("Numero total de elementos:%d\n", n);
		printf("O numero de paginas: %.0f\n\n", np );
		printf("                        Página %d\n\n", getPagina(l));
		while (down < up) {
			for (t = 0; t < 6 && lista[down]; t++) {
				printf("%s    ", lista[down++]);
			}
			printf("\n");
		}
		printf("\n\n");
		printf("O que pretende fazer a seguir: \n\n");
		if (j == 0) {
			printf("(Q) SAIR                             (S) PÁGINA SEGUINTE\n            (P) PÁGINA A CONSULTAR\n");
		}
		else{
			if (j != 0 && m != n){
				printf("(Q) SAIR      (A) PÁGINA ANTERIOR    (S) PÁGINA SEGUINTE\n            (P) PÁGINA A CONSULTAR\n");
			}
			else{
				printf("(Q) SAIR                    (A) PÁGINA ANTERIOR\n            (P) PÁGINA A CONSULTAR\n");
			}
		}
		if(scanf("%s", &a) != 0) {;}
		printf("\n");
		if (a == 'S' || a == 's') {
			if (m != n) alteraPaginamais(l);
		}
		else if (a == 'A' || a == 'a') {
			if (j != 0) alteraPaginamenos(l);
		}
		else if (a == 'P' || a == 'p') {
			printf("Qual é a página que deseja consultar:  \n");
			if (scanf("%d", &pag)==0) {;}
            if (pag >= 1 && pag <= np) {
				if (pag > getPagina(l)) while((pag-getPagina(l) != 0)) alteraPaginamais(l);
				else while((getPagina(l)-pag != 0)) alteraPaginamenos(l);
				}
		}
	    up = auxImprimeUp(up, getPagina(l), np, n);
        down = auxImprimeDown(down, up, getPagina(l), np);
	}
}



void showmenu(){
	if (system("@cls||clear")==0) {;}
	printf("1. Ler todos os ficheiros\n");
	printf("2. Lista de produtos começados por alguma letra(maiúscula)\n");
	printf("3. Total faturado(N e P) com um dado produto num dado mês\n");
	printf("4. Códigos de produtos que ninguém comprou\n");
	printf("5. Tabela com nº total de produtos comprados por um cliente mês a mês\n");
	printf("6. Total de vendas e total faturado num intervalo de meses(Ex:3..7)\n");
	printf("7. Lista ordenada de clientes que realizaram compras em todas as filiais\n");
	printf("8. Dado um produto e uma filial mostra codigos de clientes que o compraram(N e P)\n");
	printf("9. Dado um cliente e um mes, determina lista descendente de produtos mais comprados\n");
	printf("A. Lista dos N produtos mais vendidos no ano. Indica nº und e clientes nas filiais\n");
	printf("B. Dado um cliente, apresenta os 3 produtos em que gastou mais dinheiro\n");
	printf("C. Nº de clientes que não realizaram compras e nº produtos que ninguém comprou\n");
	printf("Q. Quit\n");
}


void interpretador () {
	CatProds cps = NULL;
	CatClients ccl = NULL;
	/*CatClients clientes =NULL;*/
	char letra;
	int verifica = 0;
	char cmd[BufferM];
	showmenu();
	if (fgets(cmd,BufferM,stdin)!=NULL);
	while (cmd[0] != 'Q') {
	switch(cmd[0]) {
		case '1':if(verifica != 0){
					removeCatClient(ccl);
					removeCatProd(cps);
				 }
				 ccl = initCatClients();
				 ccl = lerclient(ccl);
				 printf("\nLido Clientes.txt. Nº: %d\n",totalClientes(ccl));
				 cps = initCatProds();
				 cps = lerprod(cps);
				 printf("\nLido Produtos.txt. Nº: %d\n\n",totalProdutos(cps));
				 verifica++;
				 showmenu();
				 break;
		case '2':if(cps==NULL)
					printf("Precisa de selecionar a leitura primeiro!\n");
				 else{
					printf("Qual será a Letra?\n");
					if(scanf("%c",&letra)==-1);
					imprimeLista(cps, letra);
					 }
				 showmenu();
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
		case 'A':
				break;
		case 'B':
				break;
		case 'C':
				break;
		   }
		if (fgets(cmd,BufferM,stdin)!=NULL);
	}
	removeCatClient(ccl);
	removeCatProd(cps);
}

int main(){
	interpretador();
	return 0;
}