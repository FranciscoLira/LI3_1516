#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Filial.h"
#include "boolean.h"
#include "avlfil.h"

struct filial{
	AVLfil clientes[26];
};

Filial initFilial() {
	int i;
	Filial f = malloc(sizeof(struct filial));
	for(i=0;i<26;i++){
		f->clientes[i] = NULL;
	}
	return f;
}

Boolean existeCl(Filial f, char *c){
	int indice = c[0] -65;
	return (existeAVLfil(f->clientes[indice], c));
}

Filial insereFilial(Filial f, Cliente c, Produto p){
	int indice;
	AVLfil aux;
	char *stringp =(char *)malloc(sizeof(char)*10); 
	char *stringc =(char *)malloc(sizeof(char)*10);
	strcpy(stringc, getStringc(c));
	strcpy(stringp, getStringp(p));
	indice = stringc[0] - 65;
	aux = f->clientes[indice];
	if(!existeCl(f, stringc)){
		aux = insereAVLfil(aux,stringc,stringp);
		f->clientes[indice] = aux;
	}
	else{
		insereprod(aux, stringc, stringp);
	}

	return f;
}

void removeFilial(Filial f){
	int i;
	for (i=0;i<26;i++){
		/*FALTA FAZER FREE DAS ARVORES DE PRODUTOS NAO ESQUECER*/
		freeTreefil(f->clientes[i]);
	}
	free(f);
} 

int numprodutos(Filial f, Cliente c){
	int num;
	char *str = getStringc(c);
	int indice = str[0] - 'A';
	num = getnum(f->clientes[indice],str);
	return num;
}

/* (fazer)Função útil para a querie8 */
