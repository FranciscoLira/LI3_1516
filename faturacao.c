#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "faturacao.h"

struct vendatmp {
	char produto[10];
	double preco;
	int quantidade;
	int promo;
	char cliente[10];
	int mes;
	int filial;
};

struct fat {
	int quantidade;
	double faturacao;
};

struct avl {
	int altura;
	char* codigo;
	Fat extra;
	struct avl* esq;
	struct avl* dir;
};

typedef struct fatmes {
	AVL codigos[2];
	int totalvendas[2];
	double totalfat[2];
}*Fatmes;

typedef struct fatall {
	union {
		Fatmes f;
		AVL* l;
	} mes[13];
}*Fatall;

/* Exemplo de utilização por causa do Union, pode dar jeito no relatório

 Fatall a
 a->mes[1].f->...
 a->mes[0].l ...
*/

struct empresa {
	Fatall filial[3];
};

double getfatfat(Fat a) {
	return (a->faturacao);
}

int getfatquant(Fat a) {
	return a->quantidade;
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
	return v->produto;
}

char* getCliente(Vendatmp v) {
	return v->cliente;
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
	strcpy(v->produto, produto);
}

void setCliente(Vendatmp v, char* cliente) {
	strcpy(v->cliente, cliente);
}


Fatmes initFatmes() {
	int i;
	Fatmes r = (Fatmes)malloc(sizeof(struct fatmes));

	for (i = 0; i < 2; i++) {
		r->codigos[i] = NULL;
		r->totalvendas[i] = 0;
		r->totalfat[i] = 0;
	}
	return r;
}

Fatall initFatall() {
	int i;
	Fatall r = (Fatall)malloc(sizeof(struct fatall));
	r->mes[0].l = (AVL*)malloc(sizeof(AVL) * 26);
	for (i = 0; i < 26; i++) {
		r->mes[0].l[i] = newAVL();
	}
	for (i = 1; i < 13; i++) {
		r->mes[i].f = initFatmes();
	}
	return r;
}

/*Insere na posição 0 do array, todos os produtos

*/
Emp insereProdVaziosEmp(Emp e, AVL* produtos) {
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 26; j++) {
			e->filial[i]->mes[0].l[j] = avlcpy(produtos[j]);
		}
	}
	return e;
}

Emp initEmpresa () {
	int i;
	Emp r = (Emp)malloc(sizeof(struct empresa));
	for (i = 0; i < 3; i++) {
		r->filial[i] = initFatall();
	}
	return r;
	/*insereProdVaziosEmp (r, produtos); tem de ser feito, mas na main pois precisa de receber a AVL Prod*/
}

/*Recebe quais os campos a aplicar no fat e aloca memória para ele*/
Fat alocafat(double faturacao, int quantidade) {
	Fat r = (Fat)malloc(sizeof(struct fat));
	r->faturacao = faturacao;
	r->quantidade = quantidade;
	return r;
}

/*Retorna a faturação de uma certa venda.
  Aloca a memória necessária para ela, se for para fazer copia tem de fazer free depois.*/
Fat convvendafat(Vendatmp tmp) {
	double a = (tmp->quantidade) * (tmp->preco);
	int b = tmp->quantidade;
	Fat r = alocafat(a, b);
	return r;
}

/*Adiciona uma faturação a um nodo da AVL
Aloca memória se for necessário e coloca-a a zero nesse caso,
Apenas soma à anterior se já havia faturação para esse produto*/
void addfatnodo(AVL a, Fat f) {
	if (a->extra == NULL) {
		a->extra = alocafat(0, 0);
	}
	a->extra->faturacao += f->faturacao;
	a->extra->quantidade += f->quantidade;
}

/*Insere a faturação de um produto(codigo) na lista de 26 AVL*/
void inserefattot(AVL* a, Fat f, char* codigo) {
	int car = codigo[0] - 'A';
	AVL aux = a[car];
	int i;
	while (aux) {
		i = strcmp (codigo, aux->codigo);
		if (i == 0)
			addfatnodo(aux, f);
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
}

/*Insere uma venda na empresa no devido sitio, isto é no mês e na total*/
Emp insereVenda(Emp e, Vendatmp v) {
	Fat r;
	r = convvendafat(v);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo] = insereAVL(e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo], v->produto, r);
	inserefattot(e->filial[(v->filial) - 1]->mes[0].l, r, v->produto);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalfat[v->promo] += r->faturacao;
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalvendas[v->promo] += r->quantidade;
	return e;
}


/*Para debug*/
void printfat(Fat a) {
	if (a == NULL) {
		printf("deumerda!\n");
	}
	else {
		printf("%d\n", a->quantidade);
		printf("%f\n", a->faturacao);
	}
}

/*Retorna uma faturação de um dado produto, recebendo a filial (f) o mes (imes) e se é ou não promoção
Aloca memória por isso deve ser feito o free*/
Fat produtofat(Emp e, int f, int imes, int p, char* produto) {
	Fat r;
	AVL atmp = e->filial[f - 1]->mes[imes].f->codigos[p];
	Fat ftmp = getfatfromavl(atmp, produto);
	if (ftmp) {
		r = alocafat(ftmp->faturacao, ftmp->quantidade);
	}
	else {
		r = alocafat(0, 0);
	}
	return r;
}

/*Retorna a faturação total de um produto(codigo) num dado mes(imes)
Aloca memória e deve ser feito o free da mesma*/
Fat faturacaototal(Emp e, char* codigo, int imes, int p) {
	int f;
	Fat tmp;
	Fat r = alocafat(0, 0);
	for (f = 1; f < 4; f++) {
		tmp = produtofat(e, f, imes, p, codigo);
		if (tmp) {
			r -> quantidade += tmp ->quantidade;
			r->faturacao += tmp -> faturacao;
		}
	}
	return r;
}


/*Faz o free de toda a memória que for alocada para guardar a informação da filial*/
void freeEmp (Emp e) {
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
		free(e->filial[i]);
	}
	free(e);
}

int quantoszeroAVL(AVL a) {
	if (a) {
		if (getavlquant(a) == 0) {
			return (quantoszeroAVL(getesq(a)) + quantoszeroAVL(getdir(a)) + 1);
		}
		else {
			return quantoszeroAVL(getesq(a)) + quantoszeroAVL(getdir(a));
		}
	}
	else return 0;
}

int produtoszero(Emp e, int f) {
	int q = 0, car;
	for (car = 0; car < 26; car++) {
		q += quantoszeroAVL(e->filial[f - 1]->mes[0].l[car]);
	}
	return q;
}