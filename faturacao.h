#ifndef faturacao_H_
#define faturacao_H_
#include "boolean.h"
#include "CatClient.h"

typedef struct vendatmp *Vendatmp;

typedef struct fatmes *Fatmes;

typedef struct fatall *Fatall;

typedef struct empresa *Emp;

double getPreco(Vendatmp v);

int getQuantidade(Vendatmp v);

int getPromo(Vendatmp v);

int getMes(Vendatmp v);

int getFilial(Vendatmp v);

char* getProduto(Vendatmp v);

char* getCliente(Vendatmp v);

void setPreco(Vendatmp v, double preco);

void setQuantidade(Vendatmp v, int quantidade);

void setPromo(Vendatmp v, int promo);

void setMes(Vendatmp v, int mes);

void setFilial(Vendatmp v, int filial);

void setProduto(Vendatmp v, char* produto);

void setCliente(Vendatmp v, char* cliente);

Emp insereProdVaziosEmp(Emp e, AVL* produtos);

/*Faz a inicialização de toda a memória necessária e os devidos campos*/
Emp initEmpresa ();

Emp insereVenda (Emp e, Vendatmp v);

Boolean existeVenda (Emp e, Vendatmp v);

Fat* fatglobal(Emp e, int imes, char* codigo, int juntos);

#endif