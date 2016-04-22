#ifndef Imprime_H_
#define Imprime_H_

typedef struct conj_Strings* Conj_Strings;

Conj_Strings initConjun(Conj_Strings s, char** l, int size);

Conj_Strings alteraPaginamais(Conj_Strings s);

Conj_Strings alteraPaginamenos(Conj_Strings s);

Conj_Strings alteraPagina(Conj_Strings s, int pag);

int getPagina(Conj_Strings s);

int getSize(Conj_Strings s);

int getpagTotal(Conj_Strings s);

int getSizePag(Conj_Strings s);

char* getNextString(Conj_Strings s, int i);

Conj_Strings getPag(Conj_Strings s);

Conj_Strings getPaginaSeguinte(Conj_Strings s);

Conj_Strings getPaginaAnterior(Conj_Strings s);

int calculaTamanho(char** lista);

#endif