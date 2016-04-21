#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CatClient.h"
#include "Filial.h"


typedef struct avlc {
	int tamanho;
	AVL root;
}*Trees;

struct client {
	char* nomeclient;
};

struct clients {
	Trees cP[26];
};

Cliente inserec(char *x) {
	Cliente c = malloc(sizeof(struct client));
	c->nomeclient = malloc(sizeof(char)*strlen(x)+1);
	strcpy(c->nomeclient, x);
	return c;
}

Cliente alterac(char *x, Cliente c) {
	strcpy(c->nomeclient, x);
	return c;
}

CatClients initCatClients() {
	int i;
	CatClients p = NULL;
	p = malloc(sizeof(struct clients));
	for (i = 0; i < 26; i++) {
		p->cP[i] = malloc(sizeof(struct avlc));
		p->cP[i]->tamanho = 0;
		p->cP[i]->root = NULL;
	}
	return p;
}

CatClients insereCliente(CatClients ccl, Cliente c) {
	int i = (c->nomeclient[0] - 65);
	ccl->cP[i]->root = insereAVL(ccl->cP[i]->root, c->nomeclient, NULL);
	ccl->cP[i]->tamanho++;
	return ccl;
}

Boolean existeCliente(CatClients ccl, Cliente c) {
	int i = (c->nomeclient[0] - 65);
	if (i < 0 || i > 25) return false;
	if (existeAVL(ccl->cP[i]->root, c->nomeclient)){
		return true;
	}
	else return false;
}

int totalClientes(CatClients ccl) {
	int i, r = 0;
	if (ccl == NULL)return 0;
	for (i = 0; i < 26; i++) {
		r += ccl->cP[i]->tamanho;
	}
	return r;
}

int totalClientesLetra(CatClients ccl, char letra) {
	int i = letra - 65;
	return (ccl->cP[i]->tamanho);
}

void removeCatClient(CatClients ccl) {
	int i;
	if (ccl == NULL)return;
	for (i = 0; i < 26; i++) {
		freeTree(ccl->cP[i]->root);
		free(ccl->cP[i]);
	}
	free(ccl);
}

char* getStringc(Cliente c){
	return c->nomeclient;
}