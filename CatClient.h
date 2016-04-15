#ifndef CatClients_H_
#define CatClients_H_
#include "CatProd.h"

typedef struct clients* CatClients;
typedef struct client* Cliente;

AVL getAvlC (CatClients ccs, int i);

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
void removeCatClient(CatClients ccl);

#endif