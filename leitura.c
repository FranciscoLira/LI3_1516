#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128 

typedef struct venda {
	char produto[10];
	double preco;
	int quantidade;
	char promo; 
	char cliente[10];
	int mes;
	int filial;
}*Venda;

int cstring_cmp(const void *a, const void *b) 
{ 
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib); 
}

int findLista(char *codigo, char **lista, int n){
	int r=0;
	int *p;
	p = (int*) bsearch(&codigo, lista, n, sizeof(char*), cstring_cmp);
	if(p) r=1;
	return r;
}

int verificaEescreve (Venda v, char **clientes, char **produtos, int qclient, int qprodut, FILE *p) {
	if (findLista(v->cliente, clientes, qclient) && findLista(v->produto, produtos, qprodut)){
		fprintf(p, "%s %.2f %d ", v->produto, v->preco, v->quantidade);
		fprintf(p, "%c %s %d %d\r\n",v->promo, v->cliente, v->mes, v->filial);
	}
	else {
		return 0;
	}
	return 1;
}

int leituravendas(FILE *p2, char **clientes, char **produtos,int qclient,int qprodut) {
	int i, cont=0,mes,filial,quant; 
	Venda v=(Venda)malloc(sizeof(struct venda));
	char *aux;
	double preco;
	char buffer[BufferM];
	FILE *p;
	p = fopen("Dados/Vendasfinal.txt", "w");
	for (i = 0; fgets(buffer,BufferM,p2); i++){
	aux = strtok(buffer, " ");
	strcpy(v->produto, aux);
	aux = strtok(NULL, " ");
	preco = atof(aux);
	aux = strtok(NULL, " ");
	quant=atoi(aux);
	aux = strtok(NULL, " ");
	v->promo=aux[0];
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
	cont += verificaEescreve(v, clientes, produtos,qclient,qprodut, p);
	}
	fclose(p);
	return cont;
}

int lerclientouprod(char **str, int x){
	FILE *f1;
	int i=0,r=0;
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
	qsort(str, r, sizeof(char *), cstring_cmp);
	printf("Sorted\n");
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
	return 0;
}