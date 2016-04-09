#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myavl.h"

/* Todo o código aqui escrito foi obtido nos slides da Unidade Curricular Algoritmos e Complexidade */

typedef enum balancefactor { LH , EH , RH } BalanceFactor;

typedef struct treenode{
	BalanceFactor bf;
	TreeKey key;
	TreeInfo info[10];
	struct treenode *left;
	struct treenode *right;
} TreeNode;

Tree newAvl() {
	Tree t = NULL;
	return t;
}

Tree rotateRight(Tree t) {
	Tree aux;
	if ((! t) || (! t->left)) {
		printf("Erro\n");
	}
	else {
		aux = t->left;
		t->left = aux->right;
		aux->right = t;
		t = aux;
	}
	return t;
}

Tree insertTree(Tree t, TreeKey e, TreeInfo *i, int *cresceu) {
	if (t==NULL) {
		t = (Tree)malloc(sizeof(struct treenode));
		t->key = e;
		strcpy(t->info,i);
		t->right = t->left = NULL;
		t->bf = EH;
		*cresceu = 1;
	}
	else if (e==t->key) {
		strcpy(t->info,i); /* actualiza¸c~ao do valor associado `a chave */
	}
	else if (e>t->key)
		t = insertRight(t,e,i,cresceu);
	else
		t = insertLeft(t,e,i,cresceu);
	return(t);
}

Tree insertRight(Tree t, TreeKey e, TreeInfo *i, int *cresceu) {
	t->right = insertTree(t->right,e,i,cresceu);
	if (*cresceu){
		switch (t->bf) {
			case LH:
			t->bf = EH;
			*cresceu = 0;
			break;
			case EH:
			t->bf = RH;
			*cresceu = 1;
			break;
			case RH:
			t = balanceRight(t);
			*cresceu = 0;
		}
	}
	return t;
}

Tree balanceRight(Tree t) {
	if (t->right->bf==RH) {
		/* Rotacao simples a esquerda */
		t = rotateLeft(t);
		t->bf = EH;
		t->left->bf = EH;
	}
	else {
/* Dupla rotacao */
		t->right = rotateRight(t->right);
		t = rotateLeft(t);
		switch (t->bf) {
			case EH:
			t->left->bf = EH;
			t->right->bf = EH;
			break;
			case LH:
			t->left->bf = EH;
			t->right->bf = RH;
			break;
			case RH:
			t->left->bf = LH;
			t->right->bf = EH;
		}
		t->bf = EH;
	}
	return t;
}

Tree rotateLeft(Tree t) {
	Tree aux;
	if ((! t) || (! t->right))
		printf("Erro\n");
	else {
		aux = t->right;
		t->right = aux->left;
		aux->left = t;
		t = aux;
	}
	return t;
}

Tree insertLeft(Tree t, TreeKey e, TreeInfo *i, int *cresceu) {
	t->left = insertTree(t->left,e,i,cresceu);
	if (*cresceu){
		switch (t->bf) {
			case RH: t->bf = EH;
			*cresceu = 0;
			break;
			case EH: t->bf = LH;
			*cresceu = 1;
			break;
			case LH: t = balanceLeft(t);
			*cresceu = 0;
		}
	}
	return t;
}

Tree balanceLeft(Tree t) {
	if (t->left->bf==LH) {
		/* Rotação simples à esquerda */
		t = rotateRight(t);
		t->bf = EH;
		t->right->bf = EH;
	}
	else {
		/* Dupla rotação */
		t->left = rotateLeft(t->left);
		t = rotateRight(t);
		switch (t->bf) {
			case EH: t->right->bf = EH;
			t->left->bf = EH;
			break;
			case LH: t->right->bf = EH;
			t->left->bf = RH;
			break;
			case RH: t->right->bf = LH;
			t->left->bf = EH;
		}
		t->bf = EH;
	}
	return t;
}

void preorder(Tree t){
	if(t!=NULL){
		preorder(t->left);
		printf("%s\n",t->info);
		preorder(t->right);
	}
}

Tree avl_find(Tree t, int key){
	Tree aux=t;
	while(aux){
		if(aux->key==key) return aux;
		else if(key>aux->key) aux=aux->right;
		else aux=aux->left;
	}
	return NULL;
}

void freetree(Tree t){
	if(t){
		freetree(t->left);
		freetree(t->right);
		free(t);
	}
}

char** auxiliarImprime(char** lista, Tree t, int *i) {
	if (t!=NULL) {
		lista = auxiliarImprime(lista, t->left, i);
		lista[*i] =malloc(sizeof(char)*10);
		strcpy(lista[(*i)++], t->info);
		lista = auxiliarImprime(lista, t->right, i);
	}
	return lista;
}
