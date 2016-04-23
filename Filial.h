#ifndef FILIAL_H_
#define FILIAL_H_
#include "CatClient.h"
#include "CatProd.h"

typedef struct comprou *ConjComprados;
typedef struct filial *Filial;

/* Inicializa Filial */
Filial initFilial();
/* Insere um produto e cliente na Filial */
Filial insereFilial(Filial f, Cliente c, Produto p, int mes, int quant, int m, double preco);
/* Libertar memória da filial */
void removeFilial(Filial f);
/* Insere produtos numa estrutura para auxiliar a obtenção 
   do número de clientes que compraram cada um */
Filial insereProds(Filial f, Produto p);
/* Dá o número de produtos que um cliente comprou num determinado mês */
int numprodutos(Filial f, Cliente c, int mes);
/* Em principio deixará de ser um Catprods */
CatProds makeCat(Filial *f, CatProds p);
/* Dado um produto, uma filial e um tipo de venda (N ou P) devolve
   um ConjComprados com os clientes que o compraram */	
ConjComprados comprou(Produto p, Filial f, int tipo);
/* Permite obter um array de strings com os clientes do conjunto */
char** getListConj(ConjComprados c);
/* Permite obter o numero de clientes no conjunto */
int getTamConj(ConjComprados c);
/* Liberta memoria ocupada por um ConjClientes */
void freeConj(ConjComprados c);
/* Devolve strings com os codigos dos produtos que o Cliente c
   mais comprou num determinado mes (ordenadas de forma decrescente) */
char** getCodQMaisComprou(Filial *f,int mes,Cliente c);
/* Devolve strings com os codigos dos produtos que o Cliente c
   gastou mais dinheiro(ordenadas de forma decrescente) */
char** getCodQMaisComprouAno(Filial *f, Cliente c);
/* Devolve quantos clientes compraram o Produto p na Filial f */
int getQuantosClientes(Filial f, Produto p);

#endif