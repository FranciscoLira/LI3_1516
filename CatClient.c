#include "CatClient.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavl.h"

typedef struct avl {
	int tamanho;
	Tree root;
} *AVL;

typedef struct client {
	char nomeclient[10];
}Cli;

typedef struct clients {
	AVL cP[26];
	int cresceu[26];
}Cat;

void printy(CatClients ccl){
	preorder(ccl->cP[5]->root);
}

int getKeyc(Cliente p){
	int key=0;
	key+=atoi(&(p->nomeclient[1]));
	return key;
}

Cliente inserec(char *x){
	Cliente c = malloc(sizeof(struct client));
	strcpy(c->nomeclient,x);
	return c;
}

Cliente alterac(char *x,Cliente c){
	strcpy(c->nomeclient,x);
	return c;
}

CatClients initCatClients() {
	int i;
	CatClients p=malloc(sizeof(struct clients));
	for (i = 0; i < 26; i++) {
		p->cP[i] = (malloc)(sizeof(struct avl));
		p->cP[i]->tamanho = 0;
		p->cP[i]->root = newAvl();
	}
	return p;
}

CatClients insereCliente(CatClients ccl, Cliente c){
	int i = (c->nomeclient[0] - 65);
	int key = getKeyc(c);
	ccl->cP[i]->root = insertTree(ccl->cP[i]->root, key,c->nomeclient, &(ccl->cresceu[i]));
	ccl->cP[i]->tamanho++;
	return ccl;
}

Boolean existeCliente(CatClients ccl, Cliente c){
	int i = (c->nomeclient[0] - 65);
	Tree node;
	if(i<0 || i>25) return false;
	node=avl_find(ccl->cP[i]->root,getKeyc(c));
	if(node==NULL) return false;
	else return true;
}

int totalClientes(CatClients ccl){
	int i, r=0;
	for(i=0; i<26; i++){
		r+=ccl->cP[i]->tamanho;
	}
	return r;
}

int totalClientesLetra(CatClients ccl, char letra){
	int i = letra - 65;
	return (ccl->cP[i]->tamanho);
}

void removeCatClient(CatClients ccl){
	int i;
	for(i=0; i<26;i++){
		freetree(ccl->cP[i]->root);
		free(ccl->cP[i]);
	}
	free(ccl);
}