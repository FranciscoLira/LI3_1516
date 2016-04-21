#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "boolean.h"
#include "myavl.h"
#include "avlfil.h"
#include "CatProd.h"
#include "CatClient.h"
#include "faturacao.h"
#include "Filial.h"

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128

struct vendatmp {
	char produto[10];
	double preco;
	int quantidade;
	int promo;
	char cliente[10];
	int mes;
	int filial;
};

/*Verifica se a venda é N ou P*/
int verificaVenda (char promo) {
	if (promo == 'N' || promo == 'P') return 1;
	else return 0;
}

/*Verifica se a filial se encontra entre os valores 1 e 3*/
int verificaFilial (int filial) {
	if (filial >= 1 && filial <= 3) return 1;
	else return 0;
}

/*Verifica se a mês se encontra entre os valores 1 e 12*/
int verificaMes (int mes) {
	if (mes >= 1 && mes <= 12) return 1;
	else return 0;
}

/*Verifica se as quantidades são positivas (e menores que 200)*/
int verificaQuantidade (int quantidade) {
	if (quantidade >= 1 && quantidade <= 200) return 1;
	else return 0;
}

/*Verifica se o preço dos produtos é positivo, menor que 999 ou igual a 0.0*/
int verificaPreco (double preco) {
	if (preco >= 0.0 && preco <= 999.99) return 1;
	else return 0;
}

Boolean verificaPro(CatProds cps, char* c) {
	Produto p = inserep(c);
	if ((existeProduto(cps, p))) {
		free(p);
		return true;
	}
	free(p);
	return false;
}

Boolean verificaCat(CatClients ccs, char* c) {
	Cliente cl = inserec(c);
	if ((existeCliente(ccs, cl))) {
		free(cl);
		return true;
	}
	free(cl);
	return false;
}

/*Verifica se os parametros estão corretos, se estiverem escreve no ficheiro*/
int verifica (Vendatmp v, CatProds cps, CatClients ccs) {
	int cont = 0;
	if ((verificaPro(cps, getProduto(v))) &&
	        (verificaCat(ccs, getCliente(v)))) cont = 1;
	return cont;
}


Emp leituravendas(CatClients ccs , CatProds cps, Filial* f) {
	Vendatmp v;
	Emp e = initEmpresa();
	Cliente c = inserec("");
	Produto pr = inserep("");
	FILE *p;
	char *aux;
	double preco;
	int i, cont, mes, filial, quant, contador = 0;
	char buffer[BufferM];
	v = (Vendatmp)malloc(sizeof(struct vendatmp));
	p = fopen("Dados/Vendas_1M.txt", "r");
	e = insereProdVaziosEmp(e, getTree(cps));
	cont = 0;
	for (i = 0; fgets(buffer, BufferM, p); i++) {
		aux = strtok(buffer, " ");
		setProduto(v, aux);
		alterap(aux, pr);
		aux = strtok(NULL, " ");
		preco = atof(aux);
		aux = strtok(NULL, " ");
		quant = atoi(aux);
		aux = strtok(NULL, " ");
		if (aux[0] == 'N') {
			setPromo(v, 0);
		}
		else {
			setPromo(v, 1);
		}
		aux = strtok(NULL, " ");
		setCliente(v, aux);
		alterac(aux, c);
		aux = strtok(NULL, " ");
		mes = atoi(aux);
		aux = strtok(NULL, "\n\r");
		filial = atoi(aux);
		setPreco(v, preco);
		setQuantidade(v, quant);
		setMes(v, mes);
		setFilial(v, filial);
		cont = verifica(v, cps, ccs);
		if (cont == 1) {
			filial--;
			e = insereVenda(e, v);
			f[filial] = insereFilial(f[filial], c, pr, getMes(v), getQuantidade(v), getPromo(v));
			contador++;
		}
	}
	printf("\nLido o ficheiro de Vendas. Validadas: %d\n", contador);
	return e;
}

/*Lê o ficheiro Produtos.txt*/
CatProds lerprod(CatProds cps, Filial *f) {
	FILE *f1;
	char str[10];
	Produto p = NULL;
	f1 = fopen("Dados/Produtos.txt", "r");
	if (f1 == NULL) return 0;
	while (1) {
		if (fgets(str, 9, f1) != NULL) {
			strtok(str, "\n\r");
			free(p);
			p = inserep(str);
			cps = insereProduto(cps, p);
			f[0] = insereProds(f[0], p);
			f[1] = insereProds(f[1], p);
			f[2] = insereProds(f[2], p);
		}
		else break;
	}
	fclose(f1);
	printf("\nLido Produtos.txt. Nº: %d\n", totalProdutos(cps));
	return cps;
}
/*Lê o ficheiro Clientes.txt*/
CatClients lerclient(CatClients cps) {
	FILE *f1;
	char str[10];
	Cliente p = NULL;
	f1 = fopen("Dados/Clientes.txt", "r");
	if (f1 == NULL) return 0;
	while (1) {
		if (fgets(str, 9, f1) != NULL) {
			strtok(str, "\n\r");
			free(p);
			p = inserec(str);
			cps = insereCliente(cps, p);
		}
		else break;
	}
	fclose(f1);
	printf("\nLido Clientes.txt. Nº: %d\n", totalClientes(cps));
	return cps;
}

int auxImprimeDown(int down, int up, int pag, int np) {
	if (pag == 1) down = 0;
	else if (pag == np) down = (pag - 1) * 90;
	else down = up - 90;
	return down;
}

int auxImprimeUp(int up, int pag, int np, int n) {
	if (pag == 1) up = 90;
	else if (pag == np) up = n;
	else up = pag * 90;
	return up;
}

void clear() {
	if (system("clear") == -1)
		if (system("cls"));
}

void imprimeLista(CatProds cps, char letra) {
	char a;
	int up, down, j, m, pag, t;
	int n;
	float np;
	ConjProds l;
	char** lista;
	if (letra != '/')
		if ((letra - 65) < 0 || (letra - 65) > 25) {
			printf("Letra maiúscula!\n");
			return;
		}
	l = getList(cps, letra);
	lista = getLista(l);
	n = getSize(l);
	if (n) {
		np = n / 90;
		if (n % 90) np++;
		down = 0; up = 90;
		lista[n] = NULL;
		while (a != 'Q' && a != 'q') {
			clear();
			j = down; m = up;
			if (j == 0 && (a == 'A' || a == 'a'))
				printf("\nEsta operação não é permitida. Encontra-se na primeira página!\n\n");
			if (m == n && (a == 'S' || a == 's'))
				printf("\nEsta operação não é permitida. Encontra-se na ultima página!\n\n");
			if ((a == 'P' || a == 'p') && (pag < 1 || pag > np))
				printf("\nA opção escolhida não é válida!\n\n");
			printf("Numero total de elementos:%d\n", n);
			printf("O numero de paginas: %.0f\n\n", np );
			printf("                        Página %d\n\n", getPagina(l));
			while (down < up) {
				for (t = 0; t < 6; t++) {
					if (lista[down]) printf("%s    ", lista[down++]);
				}
				printf("\n");
			}
			printf("\n\n");
			printf("O que pretende fazer a seguir: \n\n");
			if (j == 0) {
				printf("(Q) SAIR                             (S) PÁGINA SEGUINTE\n            (P) PÁGINA A CONSULTAR\n");
			}
			else {
				if (j != 0 && m != n) {
					printf("(Q) SAIR      (A) PÁGINA ANTERIOR    (S) PÁGINA SEGUINTE\n            (P) PÁGINA A CONSULTAR\n");
				}
				else {
					printf("(Q) SAIR                    (A) PÁGINA ANTERIOR\n            (P) PÁGINA A CONSULTAR\n");
				}
			}
			if (scanf("%s", &a) != 0) {;}
			printf("\n");
			if (a == 'S' || a == 's') {
				if (m != n) alteraPaginamais(l);
			}
			else if (a == 'A' || a == 'a') {
				if (j != 0) alteraPaginamenos(l);
			}
			else if (a == 'P' || a == 'p') {
				printf("Qual é a página que deseja consultar:  \n");
				if (scanf("%d", &pag) == 0) {;}
				if (pag >= 1 && pag <= np) {
					if (pag > getPagina(l))
						while ((pag - getPagina(l) != 0))
							alteraPaginamais(l);
					else
						while ((getPagina(l) - pag != 0))
							alteraPaginamenos(l);
				}
			}
			up = auxImprimeUp(up, getPagina(l), np, n);
			down = auxImprimeDown(down, up, getPagina(l), np);
		}
	}
}

int tamanho(char * str) {
	int i, r;
	i = r = 0;
	while (str[i] != '\0') {
		r++;
		i++;
	}
	return r;
}

void showmenu() {
	clear();
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
void voltamenu() {
	char cl[6];
	cl[0] = 'x';
	printf("Para voltar ao menu: Q\n");
	while (fgets(cl, 5, stdin))
		if (cl[0] == 'Q' || cl[0] == 'q')
			break;
}

void querie3(Emp e) {
	int imes, juntos, p, i;
	Fat ftmp;
	char buffer[BufferM];
	clear();
	printf("3. Total faturado(N e P) com um dado produto num dado mês\n");
	printf("Qual o código que quer saber a faturação?\n");
	if (scanf("%s", buffer) == -1);
	printf("Qual o mês que quer saber a faturação?\n");
	if (scanf("%d", &imes) == -1);
	printf("Quer o resultado global ou filial a filial?\n");
	printf("0 - Filial a filial\n1 - Global\n");
	if (scanf("%d", &juntos) == -1);
	clear();
	printf("Produto:\"%s\"\n", buffer);
	if (juntos) {
		for (p = 0; p < 2; p++) {
			ftmp = faturacaototal(e, buffer, imes, p);
			if (p == 0) printf("Modo Normal:\n");
			else printf("Modo Promoção:\n");
			printf("\tQuantidade:\t%d\n\tFaturação:\t%.2f\n\n", getfatvendas(ftmp), getfatfat(ftmp));
		}
		free(ftmp);
	}
	else {
		for (i = 1; i < 4; i++) {/*filial*/
			printf("Filial nº%d:\n", i);
			for (p = 0; p < 2; p++) {/*promoção*/
				ftmp = produtofat(e, i, imes, p, buffer);
				if (p % 2 == 0) printf("\tModo Normal:\n");
				else printf("\tModo Promoção:\n");
				printf("\t\tQuantidade:\t%d\n\t\tFaturação:\t%.2f\n\n", getfatvendas(ftmp), getfatfat(ftmp));
			}
		}
		free(ftmp);
	}
}

void querie4(Emp e) {
	int i;
	clear();
	printf("4. Códigos de produtos que ninguém comprou\n");
	printf("Qual a filial que quer saber?\n");
	printf("0 - Geral\n1 - Filial 1\n2 - Filial 2\n3 - Filial 3\n");
	if (scanf("%d", &i) == -1);
	while (i < 0 || i > 3) {
		printf("Opção inválida.\n");
		printf("Qual a filial que quer saber?\n");
		printf("0 - Geral\n1 - Filial 1\n2 - Filial 2\n3 - Filial 3\n");
		if (scanf("%d", &i) == -1);
	}
	if (!i) {
		imprimeLista(quantostotalzeroAVL(e), '/');
	}
	else {
		imprimeLista(produtoszero(e, i), '/');
	}
}

void querie5(Filial *f, Cliente c) {
	int mes, filial;
	if (tamanho(getStringc(c)) < 5)
		printf("O cliente não é válido\n");
	else {
		printf("    MES\tFILIAL1\tFILIAL2\tFILIAL3\n\n");
		for (mes = 1; mes < 13; mes++) {
			printf("%7d\t", mes);
			for (filial = 0; filial < 3; filial++)
				printf("%7d\t", numprodutos(f[filial], c, mes));
			printf("\n");
		}
		printf("\n");
		voltamenu();
	}
}

void querie6(Emp e) {
	int i, p;
	Fat tmp;
	clear();
	printf("6. Total de vendas e total faturado num intervalo de meses(Ex:3..7)\n");
	printf("Qual o mes apartir do qual quer saber a faturaçao?\n");
	if (scanf("%d", &i) == -1);
	printf("Até que mês?\n");
	if (scanf("%d", &p) == -1);
	printf("\n[%d,%d]\n", i, p);
	tmp = varremeses(e, i, p);
	printf("Quantidade:\t%d\n", getfatvendas(tmp));
	printf("Faturação\t%.2f\n", getfatfat(tmp));
}

void querie8(Produto pr, Filial f) {
	ConjComprados c1, c2;
	char** n; int tamn, tamp, i;
	char** p;
	c1 = comprou(pr, f, 0);
	c2 = comprou(pr, f, 1);
	n = getListConj(c1);
	p = getListConj(c2);
	tamn = getTamConj(c1);
	tamp = getTamConj(c2);
	printf("Tipo N: (nº %d)\n", tamn);
	printf("Clientes: ");
	for (i = 0; i < tamn; i++)
		printf("%s ", n[i]);
	printf("\nTipo P: (nº %d)\n", tamp);
	printf("Clientes: ");
	for (i = 0; i < tamp; i++)
		printf("%s ", p[i]);
	printf("\n");
	freeConj(c1); freeConj(c2);
}

void querie9(Filial *f, Cliente c, int mes) {
	int n, i;
	char** codigos;
	int* quantidades;
	AVLfil res = NULL;
	res = funcao9(f, mes, c);
	n = numAVL(res);
	codigos = (char**)malloc(sizeof(char*)*n);
	quantidades = (int*)malloc(sizeof(int) * n);
	ordenaDecrefil(res, codigos, quantidades, n);
	printf("Produtos:\n");
	for (i = 0; i < n; i++) {
		printf("%s\n", codigos[i]);
	}
	printf("\n");
}

/*recebe a empresa, a filial em questão, qual a filial(ifil) nprod é quantos produtos há, e o N é o do user */
void querie10(Emp e, Filial* f, int ifil, int nprod, int N) {
	int i;
	Filial tmp = f[ifil - 1];
	Produto prod = inserep("             ");
	/*AVLfil res = NULL;*/
	AVL avq = NULL;
	Codquant r;
	/*res = funcao10(f);*/
	r = initcodquant(nprod);
	avq = juntaquantidades(e, ifil - 1);
	ordenaDecre(avq, r, nprod);
	for (i = 0; i < N; i++) {
		prod = alterap(getcodi(r, i), prod);
		printf("%s\n", getcodi(r, i));
		printf("%d\n", getquanti(r, i));
		printf("%d\n", getQuantosClientes(tmp, prod));
	}
}


void interpretador () {
	clock_t timeinit, timeend;
	int fil, mes, z;
	CatProds cps = NULL, cp7 = NULL;
	CatClients ccl = NULL;
	Emp e = NULL;
	Filial f[3];
	char client[10], pro[10];
	Cliente cl = inserec("");
	Produto prod = inserep("");
	char letra, cmd[BufferM];
	int verifica = 0;
	showmenu();
	if (fgets(cmd, BufferM, stdin) != NULL);
	while (cmd[0] != 'Q') {
		switch (cmd[0]) {
		case '1': timeinit = clock();
			if (verifica != 0) {
				removeCatClient(ccl);
				removeCatProd(cps);
				removeEmp(e);
				removeFilial(f[0]);
				removeFilial(f[1]);
				removeFilial(f[2]);
				printf("Leitura anterior removida\n");
			}
			for (z = 0; z < 3; z++) {
				f[z] = initFilial();
			}
			ccl = initCatClients();
			ccl = lerclient(ccl);
			cps = initCatProds();
			cps = lerprod(cps, f);
			e = leituravendas(ccl, cps, f);
			verifica++;
			timeend = clock();
			printf("passaram %.3f seg\n", (double)(timeend - timeinit) / CLOCKS_PER_SEC);
			voltamenu();
			showmenu();
			break;
		case '2': if (cps == NULL) {
				printf("Precisa de selecionar a leitura primeiro!\n");
				showmenu();
			}
			else {
				printf("Qual será a Letra?\n");
				if (scanf("%c", &letra) == -1);
				imprimeLista(cps, letra);
			}
			showmenu();
			break;
		case '3': if (e == NULL) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			else querie3(e);
			voltamenu();
			showmenu();
			break;
		case '4': if (e == NULL) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			else querie4(e);
			showmenu();

			break;
		case '5': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
				break;
			}
			printf("Qual é o cliente?\n");
			if (fgets(client, 6, stdin) == NULL)break;
			cl = alterac(client, cl);
			querie5(f, cl);
			showmenu();
			break;
		case '6': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
			}
			else {
				querie6(e);
				voltamenu();
			}
			showmenu();
			break;
		case '7': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			else {
				timeinit = clock();
				cp7 = initCatProds();
				cp7 = makeCat(f, cp7);
				timeend = clock();
				printf("passaram %.3f seg\n", (double)(timeend - timeinit) / CLOCKS_PER_SEC);
				imprimeLista(cp7, '/');
			}
			showmenu();
			break;
		case '8': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			else {
				printf("Qual é o produto?\n");
				if (fgets(pro, 7, stdin) == NULL)break;
				if (tamanho(pro) == 6)
					prod = alterap(pro, prod);
				printf("Qual é a filial?\n");
				if (scanf(" %d", &fil));
				fil--;
				timeinit = clock();
				if (fil > -1 && fil < 3)
					querie8(prod, f[fil]);
				timeend = clock();
				printf("passaram %.3f seg\n", (double)(timeend - timeinit) / CLOCKS_PER_SEC);
				voltamenu();
				showmenu();
			}
			break;
		case '9': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			else {
				printf("Qual é o Cliente?\n");
				if (fgets(client, 6, stdin) == NULL)break;
				if (tamanho(client) == 5)
					cl = alterac(client, cl);
				printf("Qual é o mes?\n");
				if (scanf("%d", &mes));
				mes--;
				timeinit = clock();
				if (mes > -1 && mes < 12)
					querie9(f, cl, mes);
				timeend = clock();
				printf("passaram %f seg\n", (double)(timeend - timeinit) / CLOCKS_PER_SEC);
				voltamenu();
				showmenu();
			}
			break;
		case 'A': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			printf("Qual a filial de que quer saber os valores?\n");
			if (scanf("%d", &fil));
			timeinit = clock();
			querie10(e, f, fil, 171008, 20);
			timeend = clock();
			printf("passaram %.3f seg\n", (double)(timeend - timeinit) / CLOCKS_PER_SEC);
			voltamenu();
			showmenu();
			break;
		case 'B':
			break;
		case 'C': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			printf("O número de produtos que ninguém comprou é: %d\n", inttotalzeroAVL(e));
			/*
			printf("O número de clientes registados quenunca realizaram compras é: %d\n",
			clientesaZ(f));*/
			break;
		}
		if (fgets(cmd, BufferM, stdin) != NULL);
	}
	if (verifica != 0) {
		removeCatClient(ccl);
		removeCatProd(cps);
		removeFilial(f[0]);
		removeFilial(f[1]);
		removeFilial(f[2]);
		removeEmp(e);
	}
}

int main() {
	interpretador();
	return 0;
}
