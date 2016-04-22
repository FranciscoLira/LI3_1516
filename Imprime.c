#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Imprime.h"


struct conj_Strings {
	char** lista;
	int size;
	int pagina;
	int pageSize;
    char** listapagina;
    int pagTotal;
};

Conj_Strings initConjun(Conj_Strings s, char** l, int size, char* exemplo) {
	int i;
	s = (Conj_Strings) malloc(sizeof(struct conj_Strings));
	s->size = size;
	s->pageSize = 90;
	s->lista = l;
	l[s->size] = NULL;
	s->pagina = 1;
	s->pagTotal = s->size/s->pageSize;
	if (s->size % s->pageSize) s->pagTotal++;
	s->listapagina = (char**)malloc(sizeof(char*)*s->pageSize);
	for (i = 0; i < s->pageSize; i++) {
		s->listapagina[i] = (char*)malloc(sizeof(strlen(exemplo)+1));
	}
	s->listapagina = s->lista;
	s->pagina = 1;
	s->pagTotal = s->size/s->pageSize;
	if (s->size % s->pageSize) s->pagTotal++;
	return s;
}

Conj_Strings alteraPaginamais2(Conj_Strings s) {
	s->pagina++;
	return s;
}

Conj_Strings alteraPaginamenos2(Conj_Strings s) {
	s->pagina--;
	return s;
}

Conj_Strings alteraPagina2(Conj_Strings s, int pag) {
	s->pagina = pag;
	return s;  
}

int getPagina2(Conj_Strings s) {
	return s->pagina;
}

int getSize2(Conj_Strings s) {
	return s->size;
}

int getpagTotal2(Conj_Strings s) {
	return s->pagTotal;
}

int getSizePag2(Conj_Strings s) {
	return s->pageSize;
}

char* getNextString2(Conj_Strings s, int i) {
 	return s->listapagina[i];
}

Conj_Strings getPag2(Conj_Strings s) {
	s->listapagina += s->pageSize*(s->pagina-1);
	return s;
}

Conj_Strings getPaginaSeguinte2(Conj_Strings s) {
	s->listapagina += s->pageSize;
	return s;
}

Conj_Strings getPaginaAnterior2(Conj_Strings s) {
	s->listapagina -=  s->pageSize;
	return s;
}


int existe(Conj_Strings s, int i) {
 	if (s->listapagina[i]) return 0;
 	else return 1;
}

