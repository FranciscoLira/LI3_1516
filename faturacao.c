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
} Vtmp;

struct fat {
	int quantidade;
	double faturacao;
};

struct fatmes {
	AVL codigos[2];
	int totalvendas[2];
	double totalfat[2];
};

struct fatall {
	union {
		Fatmes f;
		AVL* l;
	} mes[13];
};

union FatVFil {
	Fat fa;
	Fil fi;
};

struct avl {
	int altura;
	char* codigo;
	union FatVFil extra;
	struct avl* esq;
	struct avl* dir;
};



/* Exemplo de utilização por causa do Union, pode dar jeito no relatório

 Fatall a
 a->mes[1].f->...
 a->mes[0].l ...
*/

struct empresa {
	Fatall filial[3];
};

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
	/*for(i=0; i<26; i++){
		r->mes[0].l[i] = NULL;
	}*/
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
			e->filial[i]->mes[0].l[j] = avlcpyfa(produtos[j]);
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

/*Retorna a faturação de uma certa venda*/
Fat convvendafat(Vendatmp a) {
	Fat r = (Fat)malloc(sizeof(struct fat));
	r->quantidade = a->quantidade;
	r->faturacao = (a->quantidade) * (a->preco);
	return r;
}

void addfatNodo(AVL a, Fat f) {
	if (a->extra.fa == NULL) {
		a->extra.fa = (Fat)malloc(16);
		a->extra.fa->quantidade = 0;
		a->extra.fa->faturacao = 0;
	}
	a->extra.fa->faturacao += f->faturacao;
	a->extra.fa->quantidade += f->quantidade;
}

void inserefattot(AVL* a, Fat f, char* codigo) {
	int car = codigo[0] - 'A';
	AVL aux = a[car];
	int i;

	while (aux) {
		i = strcmp (codigo, aux->codigo);
		if (i == 0)
			addfatNodo(aux, f);
		if (i > 0)
			aux = aux->dir;
		else
			aux = aux->esq;
	}
}


Emp insereVenda(Emp e, Vendatmp v) {
	union FatVFil r;
	r.fa = convvendafat(v);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo] = insereAVL(e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo], v->produto, r);
	inserefattot(e->filial[(v->filial) - 1]->mes[0].l, r.fa, v->produto);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalfat[v->promo] += r.fa->faturacao;
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalvendas[v->promo] += r.fa->quantidade;
	return e;
}

Boolean existeVenda(Emp e, Vendatmp v) {
	AVL tmp = e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo];
	return (existeAVL(tmp, v->produto));
}

void printfat(Fat a) {
	if (a == NULL) {
		printf("deumerda!\n");
	}
	else {
		printf("%d\n", a->quantidade);
		printf("%f\n", a->faturacao);
	}
}



Fat faturacaoparcial(Emp e, char* codigo, int imes, int i, int j) {
	Fat r = (Fat)malloc(sizeof(struct fat));
	Fat tmp = produtofat(e, i, imes, j, codigo);
	r->faturacao = tmp -> faturacao;
	r->quantidade = tmp -> quantidade;
	return r;
}

/*Retorna uma faturação de um dado produto, recebendo a filial (f) o mes (imes) e se é promoção ou não promoçao*/
Fat produtofat(Emp e, int f, int imes, int p, char* produto) {
	AVL tmp = e->filial[f]->mes[imes].f->codigos[p];
	Fat r = getfatfromavl(tmp, produto);
	return r;
}

Fat faturacaototal(Emp e, char* codigo, int imes) {
	int i, j;
	Fat tmp;
	Fat r = (Fat)malloc(sizeof(struct fat));
	r -> quantidade = 0;
	r -> faturacao = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			tmp = produtofat(e, 0, imes, 0, codigo);
			if (tmp) {
				r -> quantidade += tmp ->quantidade;
				r->faturacao += tmp -> faturacao;
			}
		}
	}
	return r;
}

Fat somaFat(Fat* lista, int q) {
	int i;
	Fat r = lista[0];
	for (i = 0; i < q; i++) {
		r->quantidade += lista[i]->faturacao;
		r->faturacao += lista[i]->faturacao;
	}
	return r;
}


/*Acho que faz o free de tudo*/
void freeEmp (Emp e) {
	int i, j, n;
	for (i = 0; i < 2; i++) {
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