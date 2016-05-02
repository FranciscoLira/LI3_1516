#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "boolean.h"
#include "catprod.h"
#include "catclient.h"
#include "faturacao.h"
#include "filial.h"
#include "imprime.h"

#define NR_PRODUTOS 200000
#define NR_CLIENTES 20000
#define BufferM 128


/*Verifica se a venda é 0 ou 1*/
int verificaPromo (int promo) {
	if (promo == 0 || promo == 1) return 1;
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
	char* cliente = getCliente(v);
	char* prod = getProduto(v);
	if ( (verificaQuantidade(getQuantidade(v))) && (verificaPromo(getPromo(v))) &&
	        (verificaPreco(getPreco(v))) && (verificaMes(getMes(v))) && (verificaFilial(getFilial(v))) )
		if ((verificaPro(cps, prod)) &&
		        (verificaCat(ccs, cliente))) cont = 1;
	free(cliente);
	free(prod);
	return cont;
}

Emp leituravendas(CatClients ccs , CatProds cps, Filial* f, Emp e, int fich) {
	time_t inicio, fim;
	Vendatmp v = initvendatmp();
	Cliente c = inserec("      ");
	Produto pr = inserep("       ");
	FILE *p;
	char *aux;
	double preco;
	int i, cont, mes, filial, quant, contador = 0;
	char buffer[BufferM];
	if (fich == 3)
		p = fopen("Vendas_5M.txt", "r");
	else if (fich == 2)
		p = fopen("Vendas_3M.txt", "r");
	else
		p = fopen("Vendas_1M.txt", "r");
	if (!p) {
		return NULL;
	}
	cont = 0;
	inicio = time(NULL);
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
			f[filial] = insereFilial(f[filial], c, pr,
			                         getMes(v), getQuantidade(v), getPromo(v), getPreco(v));
			contador++;
		}
	}
	fim = time(NULL);
	printf("\nLido o ficheiro de Vendas. Validadas: %d\n", contador);
	printf("Lido em: %.3f s\n",
	       difftime(fim,inicio));
	return e;
}

/*Lê o ficheiro Produtos.txt*/
CatProds lerprod(CatProds cps, Filial *f, Emp e) {
	time_t inicio, fim;
	FILE *f1;
	char *str=malloc(sizeof(char)*10);
	char* aux;
	Produto p = inserep("      ");
	f1 = fopen("Produtos.txt", "r");
	if (!f1) return NULL;
	inicio = time(NULL);
	while (1) {
		if (fgets(str, 9, f1) != NULL) {
			strtok(str, "\n\r");
			p = alterap(str, p);
			cps = insereProduto(cps, p);
			aux = getStringp(p);
			e = inserePEmp(e, aux);
			free(aux);
			f[0] = insereProds(f[0], p);
			f[1] = insereProds(f[1], p);
			f[2] = insereProds(f[2], p);
		}
		else break;
	}
	fclose(f1);
	free(p);
	fim = time(NULL);
	printf("\nLido Produtos.txt. Nº: %d\n", totalProdutos(cps));
	printf("Lido em: %.3f s\n",
	       difftime(fim,inicio));
	return cps;
}
/*Lê o ficheiro Clientes.txt*/
CatClients lerclient(CatClients cps) {
	time_t inicio, fim;
	FILE *f1;
	char *str=malloc(sizeof(char)*10);
	Cliente p = inserec("     ");
	f1 = fopen("Clientes.txt", "r");
	if (!f1) return NULL;
	inicio = time(NULL);
	while (1) {
		if (fgets(str, 9, f1) != NULL) {
			strtok(str, "\n\r");
			p = alterac(str, p);
			cps = insereCliente(cps, p);
		}
		else break;
	}
	fclose(f1);
	free(p);
	fim = time(NULL);
	printf("\nLido Clientes.txt. Nº: %d\n", totalClientes(cps));
	printf("Lido em: %.3f s\n",
	       difftime(fim,inicio));
	return cps;
}


void clear() {
	if (system("clear") == -1)
		if (system("cls"));
}

void imprimeLista(char** lista, int n) {
	int i, t, pag;
	char a;
	Conj_Strings l = NULL;
	l = initConjun(l, lista, n);
	while (a != 'Q' && a != 'q') {
		clear();
		if ((a == 'P' || a == 'p') && (pag < 1 || pag > getpagTotal(l)))
			printf("\nA opção escolhida não é válida!\n\n");
		printf("Numero total de elementos:%d\n", getsize(l));
		printf("O numero de paginas: %.d\n\n", getpagTotal(l));
		printf("                        Página %d\n\n", getpagina(l));
		i = 0;
		while (i < 90) {
			for (t = 0; t < 6; t++) {
				if ((existe(l, i) == 0)) printf("%s    ", getNextString(l, i));
				else break;
				i++;
			}
			if (t != 6) break;
			printf("\n");
		}
		printf("\n\n");
		printf("O que pretende fazer a seguir: \n\n");
		if (getpagina(l) == 1) {
			printf("(Q) SAIR                             (S) PÁGINA SEGUINTE\n            (P) PÁGINA A CONSULTAR\n");
		}
		else {
			if (getpagina(l) != getpagTotal(l)) {
				printf("(Q) SAIR      (A) PÁGINA ANTERIOR    (S) PÁGINA SEGUINTE\n            (P) PÁGINA A CONSULTAR\n");
			}
			else {
				printf("(Q) SAIR                    (A) PÁGINA ANTERIOR\n            (P) PÁGINA A CONSULTAR\n");
			}
		}
		if (scanf("%s", &a) != 0) {;}
		printf("\n");
		if (a == 'S' || a == 's') {
			if (getpagina(l) != getpagTotal(l)) {
				l = incrementapagina(l);
				l = getPaginaSeguinte(l);
			}
		}
		else if (a == 'A' || a == 'a') {
			if (getpagina(l) != 1) {
				l = decrementapagina(l);
				l = getPaginaAnterior(l);
			}
		}
		else if (a == 'P' || a == 'p') {
			printf("Qual é a página que deseja consultar:  \n");
			if (scanf("%d", &pag) == 0) {;}
			if (pag >= 1 && pag <= getpagTotal(l)) {
				l = alteraPagina(l, pag);
				l = getPag(l);
			}
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
	printf("Qual o código que quer saber da faturação?\n");
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
			printf("Mês: %d\n", imes );
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
		imprimeLista(getLista(getList(quantostotalzerofil(e), '/')),
		             totalProdutos(quantostotalzerofil(e)));
	}
	else {
		imprimeLista(getLista(getList(produtoszero(e, i), '/')),
		             totalProdutos(produtoszero(e, i)));
	}
}

void querie5(Filial *f, Cliente c) {
	int mes, filial;
	char* aux = getStringc(c);
	if (tamanho(aux) < 5)
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
	}
	free(aux);
	voltamenu();
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
	time_t inicio, fim;
	inicio = time(NULL);
	c1 = comprou(pr, f, 0);
	c2 = comprou(pr, f, 1);
	n = getListConj(c1);
	p = getListConj(c2);
	tamn = getTamConj(c1);
	tamp = getTamConj(c2);
	fim = time(NULL);
	printf("Tipo N: (Total %d)\n", tamn);
	printf("Clientes: ");
	for (i = 0; i < tamn; i++)
		printf("%s ", n[i]);
	printf("\nTipo P: (Total %d)\n", tamp);
	printf("Clientes: ");
	for (i = 0; i < tamp; i++)
		printf("%s ", p[i]);
	printf("\n");
	printf("Executou em: %f\n",difftime(fim,inicio));
	freeConj(c1); freeConj(c2);
}

void querie9(Filial *f, Cliente c, int mes) {
	int i,j;
	char** codigos;
	char** lista;
	time_t inicio, fim;
	inicio = time(NULL);
	codigos = getCodQMaisComprou(f, mes, c);
	fim = time(NULL);
	for(j=0;codigos[j];j++);
	lista = malloc(sizeof(char*)*j);
	for (i = 0; codigos[i]; i++) {
		lista[i]=malloc(sizeof(char)*(strlen(codigos[i])+10));
		sprintf(lista[i],"%dº:%s", i + 1, codigos[i]);
	}
	imprimeLista(lista,j);
	printf("Executou em: %f\n", difftime(fim,inicio));
}

/*recebe a empresa, a filial em questão, qual a filial(ifil) nprod é quantos produtos há, e o N é o do user */
void querie10(Emp e, Filial* f, int ifil, int nprod, int N) {
	int i, j = 0;
	Filial tmp;
	Produto prod = inserep("      ");
	Codquant r;
	time_t inicio, fim;
	char** lista = (char**)malloc(sizeof(char*)*N * 3);
	inicio = time(NULL);
	tmp = f[ifil - 1];
	r = initcodquant(nprod, ifil, e);
	fim = time(NULL);
	for (i = 0; i < N; i++) {
		prod = alterap(getcodi(r, i), prod);
		lista[j] = malloc(sizeof(char) * (strlen(getcodi(r, i)) + 1));
		sprintf(lista[j++], "%4dº: %s", i + 1, getcodi(r, i));
		lista[j] = malloc(sizeof(char) * 20);
		sprintf(lista[j++], "Qnt: %4d", getquanti(r, i));
		lista[j] = malloc(sizeof(char) * 20);
		sprintf(lista[j++], "NºCl: %2d", getQuantosClientes(tmp, prod));
	}
	imprimeLista(lista, j);
	printf("Executou em: %f\n",difftime(fim,inicio));
}

void querie11(Cliente cl, Filial *f) {
	char** lista;
	int z;
	lista = getCodQMaisComprouAno(f, cl);
	if (lista != NULL)
		for (z = 0; z < 3; z++)
			printf("%dº: %s\n", z + 1, lista[z]);
	else
		printf("Esse cliente não existe ou não realizou compras\n");
}

void interpretador () {
	char** l;
	time_t inicio, fim;
	int fil, mes, z, j, fich;
	CatProds cps = NULL, cp7 = NULL;
	CatClients ccl = NULL;
	Emp e = NULL;
	Filial f[3];
	char client[10], pro[10];
	Cliente cl = inserec("     ");
	Produto prod = inserep("      ");
	char letra, cmd[BufferM];
	int verifica = 0;
	showmenu();
	if (fgets(cmd, BufferM, stdin) != NULL);
	while (cmd[0] != 'Q' && cmd[0] != 'q') {
		switch (cmd[0]) {
		case '1': if (verifica != 0) {
				removeCatClient(ccl);
				removeCatProd(cps);
				removeEmp(e);
				for (z = 0; z < 3; z++)
					removeFilial(f[z]);
				printf("Leitura anterior removida\n");
			}
			for (z = 0; z < 3; z++) {
				f[z] = initFilial();
			}
			clear();
			printf("Para facilitar a leitura");
			printf(", insira os ficheiros na pasta atual.\n");
			printf("Serão lidos os ficheiros Produtos.txt e Clientes.txt default.\n");
			printf("Selecione qual ficheiro de vendas pretende ler:\n");
			printf("[1] Ler Vendas_1M.txt\n");
			printf("[2] Ler Vendas_3M.txt\n");
			printf("[3] Ler Vendas_5M.txt\n");
			printf("Se inserir um número inválido é lido Vendas_1M.txt\n");
			if (scanf(" %d", &fich) == -1) {
				printf("Erro ao ler opção\n");
				voltamenu();
				showmenu();
				break;
			}
			ccl = initCatClients();
			ccl = lerclient(ccl);
			if (ccl == NULL) {
				printf("O ficheiro Clientes.txt não está na pasta atual\n");
				voltamenu();
				showmenu();
				break;
			}
			cps = initCatProds();
			e = initEmpresa();
			cps = lerprod(cps, f, e);
			if (cps == NULL) {
				printf("O ficheiro Produtos.txt não está na pasta atual\n");
				removeCatClient(ccl);
				voltamenu();
				showmenu();
				break;
			}
			e = leituravendas(ccl, cps, f, e, fich);
			if (e == NULL) {
				printf("O ficheiro Vendas solicitado não está na pasta atual\n");
				removeCatClient(ccl);
				removeCatProd(cps);
				voltamenu();
				showmenu();
				break;
			}
			verifica++;
			voltamenu();
			showmenu();
			break;
		case '2': if (cps == NULL) {
				printf("Precisa de selecionar a leitura primeiro!\n");
				voltamenu();
				showmenu();
			}
			else {
				clear();
				printf("2. Lista de produtos começados por alguma letra(maiúscula)\n");
				printf("Qual será a Letra?\n");
				while (1) {
					if (scanf(" %c", &letra) == -1);
					if (letra - 65 < 0 || letra - 65 > 26)
						printf("Letra maiúscula!\n");
					else break;
				}
				j = getSize(getList(cps, letra));
				l = getLista(getList(cps, letra));
				imprimeLista(l, j);
			}
			showmenu();
			break;
		case '3': if (e == NULL) {
				printf("Precisa de selecionar a leitura primeiro\n");
			}
			else {
				printf("3. Total faturado(N e P) com um dado produto num dado mês\n");
				querie3(e);
			}
			voltamenu();
			showmenu();
			break;
		case '4': if (e == NULL) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
			}
			else {
				clear();
				printf("4. Códigos de produtos que ninguém comprou\n");
				querie4(e);
			}
			showmenu();

			break;
		case '5': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
				showmenu();
				break;
			}
			else {
				clear();
				printf("5. Tabela com nº total de produtos comprados por um cliente mês a mês\n");
				printf("Qual é o cliente?\n");
				if (fgets(client, 6, stdin) == NULL)break;
				cl = alterac(client, cl);
				querie5(f, cl);
				showmenu();
				break;
			}
		case '6': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
			}
			else {
				clear();
				printf("6. Total de vendas e total faturado num intervalo de meses(Ex:3..7)\n");
				querie6(e);
				voltamenu();
			}
			showmenu();
			break;
		case '7': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
			}
			else {
				clear();
				printf("7. Lista ordenada de clientes que realizaram compras em todas as filiais\n");
				cp7 = initCatProds();
				cp7 = makeCat(f, cp7);
				imprimeLista(getLista(getList(cp7, '/')), totalProdutos(cp7));
				free(cp7);
			}
			showmenu();
			break;
		case '8': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
				showmenu();
			}
			else {
				clear();
				printf("8. Dado um produto e uma filial mostra codigos de clientes que o compraram(N e P)\n");
				printf("Qual é o produto?\n");
				if (fgets(pro, 7, stdin) == NULL)break;
				if (tamanho(pro) == 6){
					prod = alterap(pro, prod);
				}
				printf("Qual é a filial?\n");
				if (scanf(" %d", &fil));
				fil--;
				if (fil > -1 && fil < 3){
					querie8(prod, f[fil]);
				}
				else{
					printf("Filial inválida\n");
				}
				voltamenu();
				showmenu();
			}
			break;
		case '9': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
				showmenu();
			}
			else {
				clear();
				printf("9. Dado um cliente e um mes, determina lista descendente de produtos mais comprados\n");
				printf("Qual é o Cliente?\n");
				if (fgets(client, 6, stdin) == NULL)break;
				if (tamanho(client) == 5)
					cl = alterac(client, cl);
				printf("Qual é o mes?\n");
				if (scanf("%d", &mes));
				mes--;
				if (mes > -1 && mes < 12)
					querie9(f, cl, mes);
				voltamenu();
				showmenu();
			}
			break;
		case 'A': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				showmenu();
			}
			else {
				clear();
				printf("A. Lista dos N produtos mais vendidos no ano. Indica nº und e clientes nas filiais\n");
				printf("Qual a filial de que quer saber os valores?\n");
				if (scanf("%d", &fil));
				if (fil > 3 || fil < 1) {
					printf("A filial não é válida!\n");
					voltamenu();
					showmenu();
					break;
				}
				printf("Quantos valores quer saber?\n");
				if (scanf("%d", &j));
				querie10(e, f, fil, 171008, j);
				voltamenu();
				showmenu();
				break;
			}
		case 'B': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
				showmenu();
				break;
			}
			else {
				clear();
				printf("B. Dado um cliente, apresenta os 3 produtos em que gastou mais dinheiro\n");
				printf("Qual será o cliente?\n");
				if (fgets(client, 6, stdin) == NULL)break;
				inicio = time(NULL);
				if (tamanho(client) == 5) {
					cl = alterac(client, cl);
					querie11(cl, f);
				}
				else
					printf("O cliente não é válido!\n");
			}
			fim = time(NULL);
			printf("passaram %.3f seg\n",
			       difftime(fim,inicio));
			voltamenu();
			showmenu();
			break;
		case 'C': if (verifica == 0) {
				printf("Precisa de selecionar a leitura primeiro\n");
				voltamenu();
				showmenu();
			}
			else {
				inicio = time(NULL);

				printf("O número de produtos que ninguém comprou é: %d\n",
				       inttotalzerofil(e));
				cp7 = initCatProds();
				cp7 = makeCat(f, cp7);
				printf("O número de clientes registados que nunca realizaram compras é: %d\n",
				       totalClientes(ccl) - totalProdutos(cp7));
				fim = time(NULL);
				printf("Executou em: %.3f seg\n",
				       difftime(fim,inicio));
				free(cp7);
				voltamenu();
				showmenu();
				break;
			}
		}
		if (fgets(cmd, BufferM, stdin) != NULL);
	}
	if (verifica != 0) {
		removeCatClient(ccl);
		removeCatProd(cps);
		for (z = 0; z < 3; z++)
			removeFilial(f[z]);
		removeEmp(e);
	}
}

int main() {
	interpretador();
	return 0;
}
