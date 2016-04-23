#ifndef CatClients_H_
#define CatClients_H_
#include "boolean.h"

typedef struct clients* CatClients;

typedef struct client* Cliente;

/*Insere string em Cliente */
Cliente inserec(char *x);

/*Altera valor do Cliente */
Cliente alterac(char *x, Cliente c);

/* Inicializa Catálogo de Clientes */
CatClients initCatClients();

/* Insere um Cliente novo no catálogo */
CatClients insereCliente(CatClients ccl, Cliente c);

/* Verifica se um cliente existe no catálogo de clientes */
Boolean existeCliente(CatClients ccl, Cliente c);

/* Dá quantos clientes estão no catálogo */
int totalClientes(CatClients ccl);

/* Dá quantos clientes existem com uma dada letra */
int totalClientesLetra(CatClients ccl, char letra);

/* Remove Catálogo de Clientes da memória */
void removeCatClient(CatClients ccl);

/* Devolve string que representa o Cliente c dado */
char* getStringc(Cliente c);

/* Liberta memória ocupada pelo Cliente c dado */
void freeCliente(Cliente c);

#endif
