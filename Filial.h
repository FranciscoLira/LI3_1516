#ifndef FILIAL_H_
#define FILIAL_H_
#include "myavl.h"
#include "avlfil.h"
#include "CatClient.h"
#include "CatProd.h"

typedef struct comprou *ConjComprados;
typedef struct filial *Filial;

/* Inicializa Filial */
Filial initFilial();
/* Insere um produto e cliente na Filial */
Filial insereFilial(Filial f, Cliente c, Produto p, int mes, int quant, int m);
/* Libertar memória da filial */
void removeFilial(Filial f);
Filial insereProds(Filial f, Produto p);
int numprodutos(Filial f, Cliente c, int mes);
CatProds makeCat(Filial *f, CatProds p);
ConjComprados comprou(Produto p, Filial f, int tipo);
/* Permite obter um array de strings com os clientes do conjunto
   Tem que ser cópia do original? */
char** getListConj(ConjComprados c);
/* Permite obter o numero de clientes no conjunto */
int getTamConj(ConjComprados c);
/* Liberta memoria ocupada por um ConjClientes */
void freeConj(ConjComprados c);
void quickSort(int* quant, char** cod, int l, int r);
int partition(int* quant, char** cod, int l, int r);
void init (int n, char** codigos, int* quant);
void ordenaDecre (AVLfil res, char** codigos, int* quantidades, int n);
AVLfil funcao9(Filial *f, int mes, Cliente c);
AVLfil funcao10(Filial *f);

#endif