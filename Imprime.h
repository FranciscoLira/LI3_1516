#ifndef Imprime_H_
#define Imprime_H_

typedef struct conj_Strings* Conj_Strings;

Conj_Strings initConjun(Conj_Strings s, char** l, int size);

Conj_Strings alteraPaginamais2(Conj_Strings s);

Conj_Strings alteraPaginamenos2(Conj_Strings s);

Conj_Strings alteraPagina2(Conj_Strings s, int pag);

int getPagina2(Conj_Strings s);

int getSize2(Conj_Strings s);

int getpagTotal2(Conj_Strings s);

int getSizePag2(Conj_Strings s);

char* getNextString2(Conj_Strings s, int i);

Conj_Strings getPag2(Conj_Strings s);

Conj_Strings getPaginaSeguinte2(Conj_Strings s);

Conj_Strings getPaginaAnterior2(Conj_Strings s);

int existe(Conj_Strings s, int i);

#endif