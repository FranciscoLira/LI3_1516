#ifndef Imprime_H_
#define Imprime_H_

typedef struct conj_Strings* Conj_Strings;

/*Inicializa a estrutura Conj_Strings*/
Conj_Strings initConjun(Conj_Strings s, char** l, int size);

/*Incrementa a página em uma unidade*/
Conj_Strings incrementapagina(Conj_Strings s);

/*Decrementa a paǵina em uma unidade*/
Conj_Strings decrementapagina(Conj_Strings s);

/*Modifica o número de página para o desejado*/
Conj_Strings alteraPagina(Conj_Strings s, int pag);

/*Permite obter o número da página*/
int getpagina(Conj_Strings s);

/*Permite obter o tamanho da lista*/
int getsize(Conj_Strings s);

/*Permite obter o número de páginas total*/
int getpagTotal(Conj_Strings s);

/*Permite obter o número de elementos que desejamos por página*/
int getSizePag(Conj_Strings s);

/*Permite obter o apontador para a String que vai ser imprimida no ecrã*/
char* getNextString(Conj_Strings s, int i);

/*Permite obter uma página qualquer desejada*/
Conj_Strings getPag(Conj_Strings s);

/*Permite obter a página seguinte*/
Conj_Strings getPaginaSeguinte(Conj_Strings s);

/*Permite obter a página anterior*/
Conj_Strings getPaginaAnterior(Conj_Strings s);

/*Verifica se a String que queremos imprimir existe*/
int existe(Conj_Strings s, int i);

#endif