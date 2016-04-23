#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "faturacao.h"

struct vendatmp {
	char* produto;
	double preco;
	int quantidade;
	int promo;
	char* cliente;
	int mes;
	int filial;
};

struct fat {
	int quantidade;
	double faturacao;
	int vendas;
};

typedef struct fatmes {
	AVL codigos[2];
	int totalquantidade[2];
	double totalfat[2];
	int totalvendas[2];
}*Fatmes;

typedef struct fatall {
	union {
		Fatmes f;
		AVL* l;
	} mes[13];
}*Fatall;



struct empresa {
	Fatall filial[3];
};

struct codquant {
	char** codigos;
	int* quant;
};

Vendatmp initvendatmp() {
	Vendatmp r = (Vendatmp)malloc(sizeof(struct vendatmp));
	r->produto = r->cliente = NULL;
	r->preco = 0;
	r->quantidade = r->promo = r->filial = 0;
	return r;
}

char** getcod(Codquant a) {
	return a->codigos;
}

char* getcodi(Codquant a, int i) {
	return a->codigos[i];
}

int* getquant(Codquant a) {
	return a->quant;
}

int getquanti(Codquant a, int i) {
	return a->quant[i];
}





/*Recebe quais os campos a aplicar no fat e aloca memória para ele*/
Fat alocafat(double faturacao, int quantidade, int vendas) {
	Fat r = (Fat)malloc(sizeof(struct fat));
	r->faturacao = faturacao;
	r->quantidade = quantidade;
	r->vendas = vendas;
	return r;
}

double getfatfat(Fat a) {
	return a->faturacao;
}

int getfatquant(Fat a) {
	return a->quantidade;
}

int getfatvendas(Fat a) {
	return a->vendas;
}


void setaddfat(Fat a, double f, int q, int v) {
	if (!a) {
		a = alocafat(0, 0, 0);
	}
	a->faturacao += f;
	a->quantidade += q;
	a->vendas += v;
}

double getPreco(Vendatmp v) {
	return v->preco;
}

int getQuantidade(Vendatmp v) {
	return v->quantidade;
}

int getPromo(Vendatmp v) {
	return v->promo;
}

int getMes(Vendatmp v) {
	return v->mes;
}

int getFilial(Vendatmp v) {
	return v->filial;
}

char* getProduto(Vendatmp v) {
	char* r = (char*)malloc(sizeof(char) * (strlen(v->produto) + 1));
	strcpy(r, v->produto);
	return r;
}

char* getCliente(Vendatmp v) {
	char* r = (char*)malloc(sizeof(char) * (strlen(v->cliente) + 1));
	strcpy(r, v->cliente);
	return r;
}

void setPreco(Vendatmp v, double preco) {
	v->preco = preco;
}

void setQuantidade(Vendatmp v, int quantidade) {
	v->quantidade = quantidade;
}

void setPromo(Vendatmp v, int promo) {
	v->promo = promo;
}

void setMes(Vendatmp v, int mes) {
	v->mes = mes;
}

void setFilial(Vendatmp v, int filial) {
	v->filial = filial;
}

void setProduto(Vendatmp v, char* produto) {
	if (!v->produto) {
		v->produto = (char*)malloc(sizeof(char) * (strlen(produto) + 1));
	}
	strcpy(v->produto, produto);
}

void setCliente(Vendatmp v, char* cliente) {
	if (!v->cliente) {
		v->cliente = (char*)malloc(sizeof(char) * (strlen(cliente) + 1));
	}
	strcpy(v->cliente, cliente);
}


Fatmes initFatmes() {
	int i;
	Fatmes r = (Fatmes)malloc(sizeof(struct fatmes));

	for (i = 0; i < 2; i++) {
		r->codigos[i] = NULL;
		r->totalquantidade[i] = 0;
		r->totalfat[i] = 0;
		r->totalvendas[i] = 0;
	}
	return r;
}

Fatall initFatall() {
	int i;
	Fatall r = (Fatall)malloc(sizeof(struct fatall));
	r->mes[0].l = (AVL*)malloc(sizeof(AVL) * 26);
	for (i = 0; i < 26; i++) {
		r->mes[0].l[i] = NULL;
	}
	for (i = 1; i < 13; i++) {
		r->mes[i].f = initFatmes();
	}
	return r;
}

/*Insere na posição 0 do array, todos os produtos

*/

Emp inserePEmp(Emp e, char* p) {
	int j = p[0] - 'A', i;
	for (i = 0; i < 3; i++) {
		e->filial[i]->mes[0].l[j] = insereAVL(e->filial[i]->mes[0].l[j], p, NULL);
	}
	return e;
}

Emp initEmpresa() {
	int i;
	Emp r = (Emp)malloc(sizeof(struct empresa));
	for (i = 0; i < 3; i++) {
		r->filial[i] = initFatall();
	}
	return r;
	/*insereProdVaziosEmp (r, produtos); tem de ser feito, mas na main pois precisa de receber a AVL Prod*/
}

/*Retorna a faturação de uma certa venda.
  Aloca a memória necessária para ela, se for para fazer copia tem de fazer free depois.*/
Fat convvendafat(Vendatmp tmp) {
	double a = (tmp->quantidade) * (tmp->preco);
	int b = tmp->quantidade;
	Fat r = alocafat(a, b, 1);
	return r;
}

/*Adiciona uma faturação a um nodo da AVL
Aloca memória se for necessário e coloca-a a zero nesse caso,
Apenas soma à anterior se já havia faturação para esse produto*/
void addfatnodo(AVL a, Fat f) {
	if (getextra(a) == NULL) {
		setextra(a, 0, 0, 0);
	}
	getextra(a)->faturacao += f->faturacao;
	getextra(a)->quantidade += f->quantidade;
	getextra(a)->vendas += f->vendas;
}

/*Põe em a a soma das duas faturações*/
/*void addfatfat(Fat a, Fat b) {
	a->faturacao += b->faturacao;
	a->quantidade += b->quantidade;
	a->vendas += b->vendas;
}*/

/*Insere a faturação de um produto(codigo) na lista de 26 AVL*/
void inserefattot(AVL* a, Fat f, char* codigo) {
	int car = codigo[0] - 'A';
	AVL aux = a[car];
	int i;
	while (aux) {
		i = strcmp (codigo, getcodigo(aux));
		if (i == 0)
			addfatnodo(aux, f);
		if (i > 0)
			aux = getdir(aux);
		else
			aux = getesq(aux);
	}
}

/*Insere uma venda na empresa no devido sitio, isto é no mês e na total*/
Emp insereVenda(Emp e, Vendatmp v) {
	Fat r;
	r = convvendafat(v);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo] = insereAVL(e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo], v->produto, r);
	inserefattot(e->filial[(v->filial) - 1]->mes[0].l, r, v->produto);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalfat[v->promo] += r->faturacao;
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalquantidade[v->promo] += r->quantidade;
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalvendas[v->promo] += r->vendas;
	return e;
}


/*Retorna uma faturação de um dado produto, recebendo a filial (f) o mes (imes) e se é ou não promoção
Aloca memória por isso deve ser feito o free*/
Fat produtofat(Emp e, int f, int imes, int p, char* produto) {
	Fat r;
	AVL atmp = e->filial[f - 1]->mes[imes].f->codigos[p];
	Fat ftmp = getfatfromavl(atmp, produto);
	if (ftmp) {
		r = alocafat(ftmp->faturacao, ftmp->quantidade, ftmp->vendas);
	}
	else {
		r = alocafat(0, 0, 0);
	}
	return r;
}

/*Retorna a faturação total de um produto(codigo) num dado mes(imes)
Aloca memória e deve ser feito o free da mesma*/
Fat faturacaototal(Emp e, char* codigo, int imes, int p) {
	int f;
	Fat tmp;
	Fat r = alocafat(0, 0, 0);
	for (f = 1; f < 4; f++) {
		tmp = produtofat(e, f, imes, p, codigo);
		if (tmp) {
			r ->vendas += tmp ->vendas;
			r->faturacao += tmp -> faturacao;
			r->quantidade += tmp -> quantidade;
		}
	}
	return r;
}


/*Faz o free de toda a memória que for alocada para guardar a informação da filial*/
void removeEmp (Emp e) {
	int i, j, n;
	for (i = 0; i < 3; i++) {
		for (n = 0; n < 26; n++) {
			freeTree(e->filial[i]->mes[0].l[n]);
		}
		for (j = 1; j < 13; j++) {
			freeTree(e->filial[i]->mes[j].f->codigos[0]);
			freeTree(e->filial[i]->mes[j].f->codigos[1]);
			free(e->filial[i]->mes[j].f);
		}
		free(e->filial[i]->mes[0].l);
		free(e->filial[i]);
	}
	free(e);
}

/*Retorna um int que são os que estão a zero numa AVL e preenche que um cat r com esses produtos*/
int quantoszeroAVL(AVL a, CatProds r) {
	int q = 0;
	Produto p;
	if (a) {
		if (getavlquant(a) == 0) {
			q++;
			p = inserep(getcodigo(a));
			r = insereProduto(r, p);
		}
		q += quantoszeroAVL(getesq(a), r);
		q += quantoszeroAVL(getdir(a), r);
	}
	return q;
}

/*Retorna um conjunto de produtos que são os que estão a zero*/
CatProds produtoszero(Emp e, int f) {
	int q = 0, car;
	CatProds r = initCatProds();
	for (car = 0; car < 26; car++) {
		q += quantoszeroAVL(e->filial[f - 1]->mes[0].l[car], r);
	}
	return r;
}

/*Retorna um int que diz quantos elementos iguais há nas três AVLs tendo esses elementos de ser iguais a zero*/
int intquantoszeroAVL(AVL a, AVL b, AVL c) {
	int q = 0;
	if (a) {
		if (getavlquant(a) == 0)
			if (getavlquant(b) == 0 && getavlquant(c) == 0)
				q++;
		q += intquantoszeroAVL(getesq(a), getesq(b), getesq(c));
		q += intquantoszeroAVL(getdir(a), getdir(b), getdir(c));
	}
	return q;
}

/*Retorna um int que é a quantidade de elementos com a faturação a zero em todas as filiais*/
int inttotalzeroAVL(Emp e) {
	int q = 0, car;
	AVL a, b, c;
	for (car = 0; car < 26; car++) {
		a = e->filial[0]->mes[0].l[car];
		b = e->filial[1]->mes[0].l[car];
		c = e->filial[2]->mes[0].l[car];
		q += intquantoszeroAVL(a, b, c);
	}
	return q;
}

/*retorna um int que é a quantidade de elementos iguais, e preenche o r com os devidos valores
todos os produtos ficam no catalogo tal como a quantidade total*/
int quantosauxAVL(AVL a, AVL b, AVL c, CatProds r) {
	int q = 0;
	Produto p;
	if (a) {
		if (getavlquant(a) == 0)
			if (getavlquant(b) == 0 && getavlquant(c) == 0) {
				q++;
				p = inserep(getcodigo(a));
				r = insereProduto(r, p);
			}
		q += quantosauxAVL(getesq(a), getesq(b), getesq(c), r);
		q += quantosauxAVL(getdir(a), getdir(b), getdir(c), r);
	}
	return q;
}

/*Retorna um CatProds que tem todos os elementos que são iguais a zero em todas as AVLs*/
CatProds quantostotalzeroAVL(Emp e) {
	int q = 0, car;
	AVL a, b, c;
	CatProds r = initCatProds();
	for (car = 0; car < 26; car++) {
		a = e->filial[0]->mes[0].l[car];
		b = e->filial[1]->mes[0].l[car];
		c = e->filial[2]->mes[0].l[car];
		q += quantosauxAVL(a, b, c, r);
	}
	return r;
}


/*foi para debug
AVL* primeiraAVL(Emp e){
	return e->filial[2]->mes[0].l;
}
*/

/*Retorna a faturação total num intervalo de meses*/
Fat varremeses(Emp e, int init, int fim) {
	int i, f, j;
	Fat r = alocafat(0, 0, 0);
	Fatmes tmp;
	for (f = 0; f < 3; f++) {
		for (i = init; i < fim + 1; i++) {
			tmp = e->filial[f]->mes[i].f;
			for (j = 0; j < 2; j++) {
				setaddfat(r, tmp->totalfat[j], tmp->totalquantidade[j], tmp->totalvendas[j]);
			}
		}
	}
	return r;
}

Fat somafat(Fat a, Fat b, Fat c) {
	Fat r = alocafat(0, 0, 0);
	if (!a) {
		r->faturacao += a->faturacao;
		r->quantidade += a->quantidade;
		r->vendas += a->vendas;
	}
	if (b) {
		r->faturacao += b->faturacao;
		r->quantidade += b->quantidade;
		r->vendas += b->vendas;
	}
	if (c) {
		r->faturacao += c->faturacao;
		r->quantidade += c->quantidade;
		r->vendas += b->vendas;
	}
	return r;
}

void somasavlsquant(AVL a, AVL b, AVL c) {
	if (a) {
		Fat tmp = somafat(getextra(a), getextra(b), getextra(c));
		setextra(a, tmp->faturacao, tmp->quantidade, tmp->vendas);
		somasavlsquant(getesq(a), getesq(b), getesq(c));
		somasavlsquant(getdir(a), getdir(b), getdir(c));
	}
}

/*Dada uma avl a e uma avl b junta tudo na avl a*/
AVL juntaavls(AVL a, AVL b) {
	if (b) {
		a = insereAVL(a, getcodigo(b), getextra(b));
		a = juntaavls(a, getesq(b));
		a = juntaavls(a, getdir(b));
	}
	return a;
}


int partition(int* quant, char** cod, int l, int r) {
	int pivot, i, j, t;
	char* t2 = malloc(sizeof(char)*10);
	pivot = quant[l];
	i = l; j = r + 1;
	while (1) {
		do ++i; while ( quant[i] >= pivot && i <= r );
		do --j; while ( quant[j] < pivot );
		if ( i >= j ) break;
		t = quant[i]; quant[i] = quant[j]; quant[j] = t;
		strcpy(t2, cod[i]); strcpy(cod[i], cod[j]); strcpy(cod[j], t2);
	}
	t = quant[l]; quant[l] = quant[j]; quant[j] = t;
	strcpy(t2, cod[l]); strcpy(cod[l], cod[j]); strcpy(cod[j], t2);
	free(t2);
	return j;
}


void quickSort(int* quant, char** cod, int l, int r) {
	int j;
	if ( l < r ) {
		j = partition(quant, cod, l, r);
		quickSort(quant, cod, l, j - 1);
		quickSort(quant, cod, j + 1, r);
	}
}

/*Ordena os produtos dentro da estrutura */
Codquant ordenaDecre(AVL r, Codquant cq, int n) {
	int i = 0;
	char** codigos = getcod(cq);
	int* quantidade = getquant(cq);
	inseredaAvl(r, quantidade, codigos, &i);
	quickSort(quantidade, codigos, 0, n - 1);
	return cq;
}

/*Junta as 26 avls de produtos que estavam ordenadas por letras*/
AVL juntaquantidades(Emp e, int f) {
	int j;
	AVL r;
	AVL copia[26];
	for (j = 0; j < 26; j++) {
		copia[j] = newAVL();
	}
	/*for (j = 0; j < 26; j++) {
		copia[j] = avlcpy(e->filial[0]->mes[0].l[j]);
		somasavlsquant(copia[j], e->filial[1]->mes[0].l[j], e->filial[2]->mes[0].l[j]);
	}
	*/
	r = avlcpy(e->filial[f]->mes[0].l[0]);
	for (j = 1; j < 26; j++) {
		copia[j] = avlcpy(e->filial[f]->mes[0].l[j]);
		r = juntaavls(r, copia[j]);
	}
	return r;
}

Codquant initcodquant(int n, int ifil, Emp e) {
	AVL avq;
	Codquant r = (Codquant)malloc(sizeof(struct codquant));
	r->quant = (int*)malloc(sizeof(int) * n);
	r->codigos = (char**)malloc(sizeof(char*)*n);
	avq = juntaquantidades(e, ifil - 1);
	ordenaDecre(avq, r, n);
	return r;
}