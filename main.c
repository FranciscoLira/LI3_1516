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

void imprimeLista(CatProds cps, char letra) {
	char a;
	int up, down, j, m, i, n;
	ConjProds l = getList(cps,letra);
	char** lista = getLista(l);
	n = getSize(l);
    printf("Numero total de elementos:%d\n", getSize(l));
	down = 0; up = 90;
	while (a != 'Q') {
		  printf("                        Página %d\n\n", getPagina(l));
		  j = down; m = up;
	      while (down < up) {printf("%s    %s    %s    %s    %s    %s\n", lista[down], lista[down+1], lista[down+2], lista[down+3], lista[down+4], lista[down+5]); down+= 6;}
	      printf("\n\n");
	      printf("O que pretende fazer a seguir: \n\n");
	      if (j == 0) printf("(Q) SAIR                             (S) PÁGINA SEGUINTE\n");
              else if (j != 0 && m != n)  printf("(Q) SAIR      (A) PÁGINA ANTERIOR    (S) PÁGINA SEGUINTE\n");
                   else printf("(Q) SAIR                    (A) PÁGINA ANTERIOR\n");
	      if(scanf("%s", &a) != 0) {;}
	      printf("\n");
          if (a == 'S') {
          	 if (m == n) printf("Esta operação não é permitida! Encontra-se na ultima página.");
             else {
             	  if (up + 90 > n ) up = n; 
              	  else up = up + 90;
              	  alteraPaginamais(l);
              	  }
           }
              else if (a == 'A') {
              	   if (j == 0) printf("Esta operação não é permitida! Encontra-se na primeira página.");
              	   else {        
              	   	    up = j; 
              	        if (j-90 <= 0 ) down = 0; 
              	        else down = j - 90; 
              	        alteraPaginamenos(l);
              	        }
              	}
    }
}

void showmenu(){
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