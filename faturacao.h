#ifndef faturacao_H_
#define faturacao_H_
#include "myavl.h"
#include "CatProd.h"

typedef struct vendatmp *Vendatmp;

typedef struct empresa *Emp;

typedef struct codquant *Codquant;

double getfatfat(Fat a);
int getfatquant(Fat a);
int getfatvendas(Fat a);
void setaddfat(Fat a, double f, int q, int v);
int* getquant(Codquant a);
char* getcodi(Codquant a, int i);
int getquanti(Codquant a, int i);
Vendatmp initvendatmp();

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
Emp inserePEmp(Emp e, char* p);
/*Faz a inicialização de toda a memória necessária e os devidos campos*/
Emp initEmpresa ();
Fat alocafat(double faturacao, int quantidade, int vendas);
void addfatnodo(AVL a, Fat f);
Emp insereVenda (Emp e, Vendatmp v);
void printfat(Fat a);
Fat produtofat(Emp e, int f, int imes, int p, char* produto);
Fat faturacaototal(Emp e, char* codigo, int imes, int p);
void removeEmp(Emp e);
CatProds quantostotalzeroAVL(Emp e);
int inttotalzeroAVL(Emp e);
CatProds produtoszero(Emp e, int f);
/*AVL* primeiraAVL(Emp e);*/
Fat varremeses(Emp e, int init, int fim);
Codquant ordenaDecre(AVL r, Codquant cq, int n);
Codquant initcodquant(int n, int ifil, Emp e);

#endif