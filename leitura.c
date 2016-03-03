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
}*Venda;

int leituravendas(FILE *p2, char **clientes, char **produtos) {
    int i, cont=0,mes,filial,quant;
    Venda v=(Venda)malloc(sizeof(struct venda));
	char *aux, *help=malloc(10);
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
         /*descomentar isto para quem gostar de ver muitas cenas a aparecer no terminal xD
         printf("%s %f %d %s %d %d\n",v->compra,v->preco,v->quantidade, v->cliente, v->mes, v->filial);*/
         /*chamada funçao verifica*/
        }
        return i;
}

int lerclientouprod(char **str, int x){
	FILE *f1;
	if(x==0) f1= fopen("Dados/Clientes.txt","r");
	else  f1 = fopen("Dados/Produtos.txt","r");
	if(f1==NULL) return 0;
	int i=0,r=0;
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
	qvenda = leituravendas(p,clientes,produtos);
	fclose(p);
	printf("Foram lidos %d Clientes, %d Produtos e %d Vendas\n",qclient,qprodut,qvenda);
	printf("EXEMPLO DE CLIENTE: %s\n", clientes[15672]);
	printf("EXEMPLO DE PRODUTO: %s\n", produtos[156098]);
	printf("Vendas lidas:%d\n",qvenda);
	return 0;
}
