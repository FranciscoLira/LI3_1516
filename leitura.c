#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128 

typedef struct venda {
	char compra[10];
	double preco;
	int quantidade;
	char cliente[10];
	int mes;
	int filial;
	char promo; /*Faltava este*/
}*Venda;


/*Retorna 1 se existir na lista o código*/
int findLista(char* codigo, char **lista, int n){
	int i=0,r=0;
	while (i<n){
		if((strcmp(lista[i++],codigo))==0){
			r=1;
			break;
		}
	}
	return r;
}

/*
	Retorna um bool, se for valida é um senão retorna 0
*/

int verificadorVendas(char **clientes, char **produtos,Venda v, int x){
	int r=0;

	/*r=findLista(v->compra, clientes,x);*/
	return r;
}

int leituravendas(FILE *p2, char **clientes, char **produtos,int qclient,int qprodut) {
    int i, cont=0,mes,filial,quant; /* cont, para quê? Para já nada, mas depois vai contar só as válidas*/
    Venda v=(Venda)malloc(sizeof(struct venda));
	char *aux;
	double preco;
	char buffer[BufferM];
	for (i = 0; fgets(buffer,BufferM,p2); i++){
         aux = strtok(buffer, " ");
         strcpy(v->compra, aux);
         aux = strtok(NULL, " ");
         preco = atof(aux);
         aux = strtok(NULL, " ");
         quant=atoi(aux);
         aux = strtok(NULL, " ");
         strcpy(v->cliente,aux);
         aux = strtok(NULL, " ");
         mes=atoi(aux);
         aux = strtok(NULL, "\n\r");
         filial=atoi(aux);
         v->preco = preco;
         v->quantidade = quant;
         v->mes = mes;
         v->filial = filial;
         /*Falta pegar no código de promo que não sei como é passado À frente*/

         /*descomentar isto para quem gostar de ver muitas cenas a aparecer no terminal xD
         printf("%s %.2f %d %s %d %d\n",v->compra,v->preco,v->quantidade, v->cliente, v->mes, v->filial); */
         
         /*chamada funçao verifica*/
         cont += verificadorVendas(clientes, produtos, v,qclient);
         printf("%d\n",cont );
        }
        return i;
}


int lerclientouprod(char **str, int x){
	FILE *f1;
	int i=0,r=0; /* r, para quê? vai ser alterado ainda? Realmente não era preciso o r, mas ele conta(podia fazer return do i, mas pronto xD)*/
	if(x==0) f1= fopen("Dados/Clientes.txt","r");
	else  f1 = fopen("Dados/Produtos.txt","r");
	if(f1==NULL) return 0;
	while(1){
		str[i]=(char *)malloc(sizeof(char)*12);
		if(fgets(str[i],9,f1)!=NULL)
			strtok(str[i],"\n\r");
		else break;
		i++;r++;
	}
	fclose(f1);
	return r;
}


int main(){
	FILE *p;
	int qclient, qprodut, qvenda;
	char *clientes[NR_CLIENTES];
	char *produtos[NR_PRODUTOS];
	p=fopen("Dados/Vendas_1M.txt", "r");
	qclient = lerclientouprod(clientes,0);
	qprodut = lerclientouprod(produtos,1);
	qvenda = leituravendas(p,clientes,produtos,qclient,qprodut);
	fclose(p);
	printf("Foram lidos %d Clientes, %d Produtos e %d Vendas\n",qclient,qprodut,qvenda);
	printf("EXEMPLO DE CLIENTE: %s\n", clientes[15672]);
	printf("EXEMPLO DE PRODUTO: %s\n", produtos[156098]);
	printf("Vendas lidas:%d\n",qvenda);
	return 0;
}
