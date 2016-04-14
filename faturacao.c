#include "faturacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"
#include "boolean.h"

struct vendatmp {
	char produto[10];
	double preco;
	int quantidade;
	int promo;
	char cliente[10];
	int mes;
	int filial;
};

struct fatmes {
	AVL codigos[2];
	int totalvendas[2];
	double totalfat[2];
};

struct fatall {
	union {
		Fatmes f;
		AVL l;
	} mes[13];
};

/* Fatall a
 a->mes[1].f->...
 a->mes[0].l ...
*/

struct empresa {
	Fatall filial[3];
};

/*inicia um*/
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
	r->mes[0].l = NULL;
	for (i = 1; i < 13; i++) {
		r->mes[i].f = initFatmes();
	}
	return r;
}

Emp initEmpresa(int q) {
	int i;
	Emp r = (Emp)malloc(sizeof(struct empresa));
	for (i = 0; i < q; i++) {
		r->filial[i] = initFatall();
	}
	return r;
}

/*Retorna a faturação de uma certa venda*/
Fat convvendafat(Vendatmp a) {
	Fat r = (Fat)malloc(sizeof(struct fat));
	r->quantidade = a->quantidade;
	r->faturacao = (a->quantidade) * (a->preco);
	return r;
}

void insereVenda(Emp e, Vendatmp v) {
	union FatVFil r;
	r.fa = convvendafat(v);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo] = insereAVL(e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo], v->produto, r);
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalfat[v->promo] += r.fa->faturacao;
	e->filial[(v->filial) - 1]->mes[(v->mes)].f->totalvendas[v->promo] += r.fa->quantidade;
}

Boolean existeVenda(Emp e, Vendatmp v) {
	AVL tmp = e->filial[(v->filial) - 1]->mes[(v->mes)].f->codigos[v->promo];
	return (existeAVL(tmp, v->produto));
}

/*Retorna uma faturação de um dado produto, recebendo a filial (f) o mes (imes) e se é promoção ou não*/
Fat produtofat(Emp e, int f, int imes, int p, char* produto) {
	AVL tmp = e->filial[f]->mes[imes].f->codigos[p];
	Fat r = getfatfromavl(tmp, produto);
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

/*Recebe um mês(imes), um código de produto(codigo) e um int (juntos) que é se queres juntos (1) ou por filial(0) retorna o total em modo n e p, */
Fat* fatglobal(Emp e, int imes, char* codigo, int juntos) {
	int i;
	Fat* f = (Fat*)malloc(sizeof(struct fat) * 6); /*6 porque é um para cada filial e para o modo n e p*/
	for (i = 0; i < 6; i++) {
		f[i] = produtofat(e, (i / 2), imes, (i % 2), codigo);
	}
	/*
	Two or more, use a for

	f[0] = produtofat(e, 0, imes, 0, codigo);
	f[1] = produtofat(e, 0, imes, 1, codigo);
	f[2] = produtofat(e, 1, imes, 0, codigo);
	f[3] = produtofat(e, 1, imes, 1, codigo);
	f[4] = produtofat(e, 2, imes, 0, codigo);
	f[5] = produtofat(e, 2, imes, 1, codigo);
	*/
	return f;
}

/*insere na posição 0 do array, todos os produtos*/
Emp insereProdEmp(Emp e, AVL produtos) {
	int i;
	for (i = 0; i < 3; i++) {
		e->filial[i]->mes[0].l = avlcpyfa(produtos);
	}
	return e;
}
