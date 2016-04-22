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

Conj_Strings initConjun(Conj_Strings s, char** l, int size) {
	int i;
	s = (Conj_Strings) malloc(sizeof(struct conj_Strings));
	s->size = size;
	s->pageSize = 90;
	s->lista = l;
	s->listapagina = (char**)malloc(sizeof(char*)*s->pageSize);
	for (i = 0; i < s->pageSize; i++) 
		s->listapagina[i] = (char*)malloc(sizeof(char)*10);
	s->pagina = 1;
	s->pagTotal = s->size/s->pageSize;
	if (s->size % s->pageSize) s->pagTotal++;
}

Conj_Strings alteraPaginamais(Conj_Strings s) {
	s->pagina++;
	return s;
}

Conj_Strings alteraPaginamenos(Conj_Strings s) {
	s->pagina--;
	return s;
}

Conj_Strings alteraPagina(Conj_Strings s, int pag) {
	s->pagina = pag;
	return s;  
}

int getPagina(Conj_Strings s) {
	return s->pagina;
}

int getSize(Conj_Strings s) {
	return s->size;
}

int getpagTotal(Conj_Strings s) {
	return s->pagTotal;
}

int getSizePag(Conj_Strings s) {
	return s->pageSize;
}

char* getNextString(Conj_Strings s, int i) {
 	char* temp = (char*)malloc(sizeof(char)*10);
 	strcpy(temp,s->listapagina[i]);
 	return temp;
}

Conj_Strings getPag(Conj_Strings s) {
	int up, down;
	if (s->pagina == 1) {
		up = s->pageSize;
		down = 0;
	}
	else if (s->pagina == s->pagTotal) {
		up = s->size;
		down = (s->pagina - 1) * s->pageSize;
	}
	else {
		up = s->pagina * s->pageSize;
		down = up - s->pageSize;
	}
	s->listapagina[0] = s->lista[down];
	s->listapagina[s->pageSize] = s->lista[up];
	return s;
}

Conj_Strings getPaginaSeguinte(Conj_Strings s) {
	char* temp;
	if (s->pagina  == s->pagTotal) {
		s->listapagina[0] = s->listapagina[s->pageSize];
		s->listapagina[s->pageSize] = s->lista[s->size];
	}
	else {
		s->listapagina[0] = s->listapagina[s->pageSize];
		temp = s->listapagina[s->pageSize];
		s->listapagina[s->pageSize] = temp + s->pageSize;
	}
	return s;
}

Conj_Strings getPaginaAnterior(Conj_Strings s) {
	char* temp;
	if (s->pagina == s->pagTotal) {
		s->listapagina[s->pageSize] = s->lista[s->size-((s->pagTotal-1)*(s->pageSize))];
		s->listapagina[0] = s->listapagina[s->pageSize] - s->pageSize;
	}
	else {
		temp = s->listapagina[s->pageSize];
		s->listapagina[s->pageSize] = temp;
		s->listapagina[0] = s->listapagina[s->pageSize] - s->pageSize;
	}
	return s;
}

int calculaTamanho(char** lista) {
	int c = 0;
	int i = 0;
	while(lista[i]) {
		c++;
		i++;
	}
}