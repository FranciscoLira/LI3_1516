#ifndef faturacao_H_
#define faturacao_H_
#include "myavl.h"
#include "CatProd.h"

typedef struct vendatmp *Vendatmp;

typedef struct empresa *Emp;

typedef struct codquant *Codquant;

/*Inicializa a estrutura onde é armazenada a informação de uma venda*/
Vendatmp initvendatmp();

/*Permite obter o preço de uma venda*/
double getPreco(Vendatmp v);

/*Permite obter a quantidade de uma venda*/
int getQuantidade(Vendatmp v);

/*Permite obter o campo promoção, estabelecido como 0 para normal e 1 para promoção*/
int getPromo(Vendatmp v);

/*Permite obter o mês em que certa venda foi feita*/
int getMes(Vendatmp v);

/*Permite obter a informação da Filial em que o produto foi comprado*/
int getFilial(Vendatmp v);

/*Permite obter o código do Produto*/
char* getProduto(Vendatmp v);

/*Permite obter o código do Cliente*/
char* getCliente(Vendatmp v);

/*Permite estabelecer um valor para o preço*/
void setPreco(Vendatmp v, double preco);

/*Permite estabelecer um valor para a quantidade*/
void setQuantidade(Vendatmp v, int quantidade);

/*Permite estabelecer um valor para a promoção, segue o meso critério do get respetivo*/
void setPromo(Vendatmp v, int promo);

/*Permite estabelecer o mês*/
void setMes(Vendatmp v, int mes);

/*Permite estabelecer em que Filial foi vendido o produto*/
void setFilial(Vendatmp v, int filial);

/*Permite estabelecer o Produto numa venda*/
void setProduto(Vendatmp v, char* produto);

/*Permite estabelecer o Cliente numa venda*/
void setCliente(Vendatmp v, char* cliente);

/*Permite saber o valor da faturação (sumatório da quantidade * preço)*/
double getfatfat(Fat a);

/*Permite saber o valor da quantidade de produtos vendidos*/
int getfatquant(Fat a);

/*Permite saber a quantidade de vendas*/
int getfatvendas(Fat a);

/*Permite estabelecer os três parametros de uma faturação*/
void setaddfat(Fat a, double faturacao, int qquantidade, int vendas);

/*Permite saber a lista de quantidedas de uma dada lista de produtos*/
int* getquant(Codquant a);

/*Permite saber qual o codigo nº i da estrutura*/
char* getcodi(Codquant a, int i);

/*Permite saber qual a quantidade nºi da estrutura*/
int getquanti(Codquant a, int i);

/*Inicia uma struct de faturação e estabelece os parametros*/
Fat alocafat(double faturacao, int quantidade, int vendas);

/*Adiciona o campo faturação a um dado produto*/
void addfatnodo(AVL a, Fat f);

/*Faz a inicialização de toda a memória necessária e os devidos campos*/
Emp initEmpresa ();

/*Liberta toda a memória que foi usada para armazenar informação relativamente à faturação*/
void removeEmp(Emp e);

/**/
int inttotalzeroAVL(Emp e);

/*Insere um Produto numa empresa*/
Emp inserePEmp(Emp e, char* p);

/*Insere a informaçõ relativa a uma venda numa empresa*/
Emp insereVenda (Emp e, Vendatmp v);

/*Retorna a faturação de um produto que esteja ja inserido, 
sabendo a filia, o mes se é ou não promoção e o Código do produto*/
Fat produtofat(Emp e, int filial, int mes, int promo, char* produto);

/*Retorna a faturação total distinguindo apenas pelo mes e se é ou não promoção*/
Fat faturacaototal(Emp e, char* codigo, int mes, int promo);

/*Retorna um CatProds que tem todos os elementos que são iguais a zero em todas as AVLs*/
CatProds quantostotalzeroAVL(Emp e);

/*Retorna um CatProds que são os que estão a zero numa lista de AVLs*/
CatProds produtoszero(Emp e, int f);

/*Retorna a faturação total num intervalo de meses*/
Fat varremeses(Emp e, int init, int fim);

/*Inicializa a estrutura onde é armazenada a informação de */
Codquant initcodquant(int n, int filial, Emp e);

/*Ordena os produtos dentro da estrutura*/
Codquant ordenaDecre(AVL r, Codquant cq, int n);

#endif