#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "CatProd.h"
#include "myavl.h"

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

/*Função para comparar duas strings, é básicamente a strcmp, é necessária para o qsorte e bsearch*/
int cstring_cmp(const void *a, const void *b){
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib); 
}

/* Verifica se a venda é N ou P*/
int verificaVenda (char promo) {
	if (promo == 'N' || promo == 'P') return 1;
	else return 0;
}

/* Verifica se a filial se encontra entre os valores 1 e 3*/
int verificaFilial (int filial) {
	if (filial >= 1 && filial <=3) return 1;
	else return 0;
}

/* Verifica se a mês se encontra entre os valores 1 e 12*/
int verificaMes (int mes) {
	if (mes >=1 && mes <= 12) return 1;
	else return 0;
}

/* Verifica se as quantidades são positivas (e menores que 200) */
int verificaQuantidade (int quantidade) {
	if (quantidade >= 1 && quantidade <= 200) return 1;
	else return 0;
}

/* Verifica se o preço dos produtos é positivo, menor que 999 ou igual a 0.0 */
int verificaPreco (double preco) {
	if (preco >= 0.0 && preco <= 999.99) return 1;
	else return 0;
}

/*Procura numa lista de "codigos" um certo código, serve para procurar nas listas, usa o bsearch para ser mais eficiente*/
int findLista(char *codigo, char **lista, int n){
	int r=0;
	int *p;
	if(codigo==NULL)return 0;
	p = (int*) bsearch(&codigo, lista, n, sizeof(char*), cstring_cmp);
	if(p) r=1;
	return r;
}

/*Verifica se os parametros estão corretos, se estiverem escreve no ficheiro*/
int verificaEescreve (Venda v, char **clientes, char **produtos, int qclient, int qprodut, FILE *p) {
	int cont = 0;
	if (verificaFilial(v->filial) && verificaMes(v->mes) && verificaQuantidade(v->quantidade) && 
		verificaPreco(v->preco) && verificaVenda(v->promo)) {
		if (findLista(v->cliente, clientes, qclient) && findLista(v->produto, produtos, qprodut)){
			fprintf(p, "%s %.2f %d ", v->produto, v->preco, v->quantidade);
			fprintf(p, "%c %s %d %d\r\n",v->promo, v->cliente, v->mes, v->filial);
			cont = 1;
		}
	} 
	return cont;
}

int clientemesaux(Venda v, int c[], char opcional[]) {
	if (strcmp(opcional,v->cliente) == 0) {
		c[v->mes]++;
		return (v->quantidade);
	}
	else return 0;
}

void clientemes(int clientesmes[], int sum, int valor, double faturacao) {
	int i;
	for (i = 1; i <= 12; i++) {
		sum = sum + clientesmes[i];
		printf("Mes %d: %d \n", i, clientesmes[i]);
	}
	printf("Total de registo de compras do cliente: %d\n", sum);
	printf("Quantidade total: %d\nFaturação total: %f\n", valor, faturacao);
}

void inicializacoes (int clientesmes[], int produtosmesP[], int produtosmesN[], double faturacaoP[], double faturacaoN[]) {
	int i;
	for (i = 0; i <= 12; i++) {
		clientesmes[i] = 0;
		produtosmesN[i] = 0;
		produtosmesP[i] = 0;
		faturacaoN[i] = 0;
		faturacaoP[i] = 0;
	}
}

int produtomesaux(Venda v, int c[], int p[], double faturacaop[], double faturacaon[], char opcional[]) {
	if (strcmp(opcional,v->produto) == 0) {
		if (v->promo == 'N') {
			c[v->mes] = v->quantidade;
			faturacaon[v->mes] = faturacaon[v->mes] + (v->preco*v->quantidade);
			return (v->quantidade);
		}
		else {
			p[v->mes]= v->quantidade;
			faturacaop[v->mes] = faturacaop[v->mes] + (v->preco*v->quantidade);
			return (v->quantidade);
		}
	}
	else return 0;
}

void produtomes(int produtomesP[], int produtomesN[], double faturacaop[], double faturacaon[], int sum, int valor, double faturacao) {
	int i; int j = 0;
	for (i = 1; i <= 12; i++) {
		sum = sum + produtomesP[i] + produtomesN[i];
		faturacao = faturacao + faturacaon[i] + faturacaop[i];
		if(produtomesN[i] != 0) {
			j++; printf("Mes %d N: %d Faturacao N: %f\n", i, produtomesN[i], faturacaon[i]);
		}
		if(produtomesP[i] != 0) {
			j++; printf ("Mes %d P: %d Faturacao P: %f\n", i, produtomesP[i], faturacaop[i]);
		}
	}
	printf("Numero de Clientes: %d\n", j);
	printf("Total de vendas do produto: %d\n", sum);
	printf("Faturação total: %f\n", faturacao);
}


/*Cria o apontador para FILE e insere as linhas válidas*/
int leituravendas(FILE *p2, char **clientes, char **produtos,int qclient,int qprodut, int c, char opcional[], char q, double valor) {
	Venda v;
	FILE *p;
	int i, cont=0,mes,filial,quant;
	char *aux;
	double preco;
	char buffer[BufferM];
	int clientesmes[13];
	int sum = 0;
	double faturacao = 0;
	int k = 0;
	int produtomesP[13];
	int produtomesN[13];
	double faturacaoP[13];
	double faturacaoN[13];
	inicializacoes(clientesmes, produtomesP, produtomesN, faturacaoP, faturacaoN);
	v = (Venda)malloc(sizeof(struct venda));
	if(c == 0) p = fopen("Dados/Vendasfinal.txt", "w");
	else p = fopen("Dados/Vendasfinal.txt", "r");
	for(i = 0; fgets(buffer,BufferM,p2); i++){
		aux = strtok(buffer, " ");
		strcpy(v->produto, aux);
		aux = strtok(NULL, " ");
		preco = atof(aux);
		aux = strtok(NULL, " ");
		quant = atoi(aux);
		aux = strtok(NULL, " ");
		v->promo=aux[0];
		aux = strtok(NULL, " ");
		strcpy(v->cliente,aux);
		aux = strtok(NULL, " ");
		mes=atoi(aux);
		aux = strtok(NULL, "\n\r");
		filial=atoi(aux); v->preco = preco; v->quantidade = quant; v->mes = mes; v->filial = filial;
		if(c == 0) cont += verificaEescreve(v, clientes, produtos,qclient,qprodut, p);
		else{
			switch(q){
				case 'A':k =	clientemesaux(v, clientesmes, opcional);
								valor = valor + k;
								faturacao = faturacao + (k*v->preco);
								break;
				case 'B':k = 	produtomesaux(v,produtomesN, produtomesP, faturacaoP, faturacaoN, opcional);
								break;
				case 'D': valor = 	valor + v->quantidade;
									break;
				case 'E': valor = 	valor + (v->preco*v->quantidade);
									break;
			}
		}
	}
	fclose(p);
	if(c == 1){
		switch(q){
			case 'A':	clientemes(clientesmes,sum, valor, faturacao);
						break;
			case 'B':	produtomes(produtomesP, produtomesN, faturacaoP, faturacaoN, sum, valor, faturacao);
						break;
			case 'D':	printf("O numero de unidades vendidas foi de: %.0f\n",valor);
						break;
			case 'E':	printf("A faturação total foi de: %f\n", valor);
						break;
		}
	}
	else printf("O número de Vendas válidas é: %d\n", cont);
	return cont;
}


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

/*
int main(){
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
	j = 1;
	printf("EXEMPLO DE CLIENTE: %s\n", clientes[15672]);
	printf("EXEMPLO DE PRODUTO: %s\n", produtos[156098]);
	printf("A. TESTAR CLIENTE \nB. TESTAR PRODUTO\nC. TODOS OS VALORES LIDOS\nD. UNIDADES VENDIDAS\nE. FATURAÇAO TOTAL\nQ. SAIR\n");
	if (fgets(cmd,BufferM,stdin)!=NULL) {;} Maneira manhosa de tirar warnings, se alguem souber como tirar que diga...tambem podemos usar scanf mas tambem da warning
	while (cmd[0] != 'Q') {
		   valor = 0;
		   switch(cmd[0]) {
			  case 'A': printf("Por favor introduza o cliente que deseja consultar: ");
					  if(scanf("%s", opcional)!= 0) {;}
					  qvenda = leituravendas(p,clientes,produtos,qclient,qprodut,j, opcional, cmd[0], valor);
					  break;
			  case 'B': printf("Por favor introduza o produto que deseja consultar: ");
					  if(scanf("%s", opcional)!= 0) {;}
					  qvenda = leituravendas(p,clientes,produtos,qclient,qprodut,j, opcional, cmd[0], valor);
					  break;       
			  case 'C': printf("Foram lidos %d Clientes, %d Produtos e %d Vendas\n",qclient,qprodut,qvenda);
						break;
			  case 'D': qvenda = leituravendas(p,clientes,produtos,qclient,qprodut,j, opcional, cmd[0], valor);
						break;
			  case 'E': qvenda = leituravendas(p,clientes,produtos,qclient,qprodut,j, opcional, cmd[0], valor);
						break;
		   }
	if (fgets(cmd,BufferM,stdin)!=NULL) {;}
	}
	return 0;
}
*/

int main(){
	CatProds cps,c;
	Produto p = inserep("FZ1927");
	cps = initCatProds();
	cps = lerclientouprod(cps,1);
	printx(cps);
	printf("%d\n",totalProdutosLetra(cps,'F'));
	if(existeProduto(cps,p)) printf("EXISTE\n");
	removeCatProd(cps);
	return 0;
}