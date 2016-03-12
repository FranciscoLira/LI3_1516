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

/* Verifica se o preço dos produtos é positivo/igual a 0.0 */
int verificaPreco (double preco) {
	if (preco >= 0.0 && preco <= 999.99) return 1;
	else return 0;
}

/* Verifica se ambos os codigos existem */
int codigosExistem (char *c1, char *c2) {
	if (c1 != NULL && c2 != NULL) return 1;
	else return 0;
}

/*Procura numa lista de "codigos" um certo código, serve para procurar nas listas, usa o bsearch para ser mais eficiente*/
int findLista(char *codigo, char **lista, int n){
	int r=0;
	int *p;
	p = (int*) bsearch(&codigo, lista, n, sizeof(char*), cstring_cmp);
	if(p) r=1;
	return r;
}

/*Verifica se os parametros estão corretos, se estiverem escreve no ficheiro*/
int verificaEescreve (Venda v, char **clientes, char **produtos, int qclient, int qprodut, FILE *p) {
	if (verificaFilial(v->filial) && verificaMes(v->mes) && verificaQuantidade(v->quantidade) && 
		verificaPreco(v->preco) && verificaVenda(v->promo) && codigosExistem(v->produto, v->cliente)) {
	    if (findLista(v->cliente, clientes, qclient) && findLista(v->produto, produtos, qprodut)){
		    fprintf(p, "%s %.2f %d ", v->produto, v->preco, v->quantidade);
		    fprintf(p, "%c %s %d %d\r\n",v->promo, v->cliente, v->mes, v->filial);
	    }
    } 
	else {
		return 0;
	}
	return 1;
}

/*Cria o apontador para FILE e insere as linhas válidas*/
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