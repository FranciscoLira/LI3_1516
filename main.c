#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128 

 /*Struct que armazena temporariamente os dados que vêm das vendas, uma linha de cada vez*/
typedef struct venda {
	char produto[10];
	double preco;
	int quantidade;
	char promo; 
	char cliente[10];
	int mes;
	int filial;
}*Venda;


/*Função para comparar duas strings, é básicamente a strcmp*/
int cstring_cmp(const void *a, const void *b) 
{
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib); 
}

/*Verifica se os parametros estão corretos, se estiverem escreve no ficheiro*/
int verificaEescreve (Venda v, char **clientes, char **produtos, int qclient, int qprodut, FILE *p) {
	int cont = 0;
	if (verificaFilial(v->filial) && verificaMes(v->mes) && verificaQuantidade(v->quantidade) && 
		verificaPreco(v->preco) && verificaVenda(v->promo)) {
	    if (findLista(v->cliente, clientes, qclient) && findLista(v->produto, produtos, qprodut) cont = 1;
	}
	return cont;
}

int leituravendas(FILE *p2, char **clientes, char **produtos,int qclient,int qprodut) {
	Venda v;
	FILE *p;
	int i, cont=0,mes,filial,quant; char *aux; double preco; char buffer[BufferM];
	v = (Venda)malloc(sizeof(struct venda));
	p = fopen("Dados/Vendasfinal.txt", "w");
	for (i = 0; fgets(buffer,BufferM,p2); i++) {
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
	     filial=atoi(aux); v->preco = preco; v->quantidade = quant; v->mes = mes; v->filial = filial;
         cont += verificaEescreve(v, clientes, produtos,qclient,qprodut, p);
     }   
	fclose(p);	
	return cont;
}

/*Lê o ficheiro */
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
	fclose(f1);
	return r;
}

int main() {
	double valor = 0;
	int j = 0;
	FILE *p;
	char cmd[BufferM];
	int qclient, qprodut, qvenda;
	char *clientes[NR_CLIENTES];
	char *produtos[NR_PRODUTOS];
	char opcional[BufferM];
	p=fopen("Dados/Vendas_1M.txt", "r");
	qclient = lerclientouprod(clientes,0);
	qprodut = lerclientouprod(produtos,1);
	qvenda = leituravendas(p,clientes,produtos,qclient,qprodut,j, opcional, cmd[0], valor);
	fclose(p);
}