#include "faturacao.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myavlcod.h"

/* Struct que armazena temporariamente os dados que vêm das vendas, uma linha de cada vez */

/*É necessário estarem aqui?(myavlcod.c)*/
struct vendatmp {
	char produto[10]; 
	double preco;
	int quantidade;
	int promo; /*1 se P*/
	char cliente[10];
	int mes; 
	int filial; 
};

struct venda {
	/* char produto[10]; */
	double preco;
	int quantidade;
	/* int promo; */
	char cliente[10];
	/* int mes; */
	/* int filial; */
};

struct fatmes{
	AVLcod codigos[2];
	float totalvendas[2];
	float totalfat[2];
};

struct fatall{
	Fatmes mes[12];
};

/*quantas filiais há e um endereço para cada uma*/
struct empresa{
	Fatall* filial;
	int quant;
};

Fatmes initFatmes(){
	int i;
	Fatmes r = (Fatmes)malloc(sizeof(struct fatmes));
	for(i=0;i<2;i++){
		r->codigos[i]=NULL;
		r->totalvendas[i]=0;
		r->totalfat[i]=0;
	}
	return r;
}

Fatall initFatall(){
	int i;
	Fatall r = (Fatall)malloc(sizeof(struct fatall));
	for(i=0; i<12; i++){
		r->mes[i]=initFatmes();
	}
	return r;
}

Emp initEmpresa (int quant){
	int i=quant;
	Emp r = (Emp)malloc(sizeof(struct empresa));
	r->quant=quant;
	for(i=0; i<quant; i++){
		r->filial[i] = (Fatall)malloc(quant*sizeof(struct fatall));
		r->filial[i]=initFatall();
	}
	return r;
}

void insereVenda(Emp e, Vendatmp v){
	insereAVLcod(e->filial[(v->filial)-1]->mes[(v->mes)-1]->codigos[v->promo],v);
	e->filial[(v->filial)-1]->mes[(v->mes)-1]->totalfat[v->promo]+=v->preco;
	e->filial[(v->filial)-1]->mes[(v->mes)-1]->totalvendas[v->promo]+=v->quantidade;
}

Boolean existeVenda(Emp e, Vendatmp v){
	AVLcod tmp = e->filial[(v->filial)-1]->mes[(v->mes)-1]->codigos[v->promo];
	return (existeAVLcod(tmp,v));
}

/*Dado um mês e um código de produto, ambos válidos, determinar e apresentar
o número total de vendas e o total facturado com esse produto em tal mês,
distinguindo os totais em modo N e os totais em modo P. O utilizador deverá
decidir se pretende o resultado global ou os valores totais filial a filial. */

/*Recebe qual a filial(f) e qual o mes(imes)*/
void printtotais(Emp e, int f,int imes){
	printf("Modo N:\n");
	printf("\tTotal de vendas:%f\n",e->filial[f]->mes[imes]->totalvendas[0]);
	printf("\tTotal faturado:%f\n",e->filial[f]->mes[imes]->totalfat[0]);
	printf("Modo P:\n");
	printf("\tTotal de vendas:%f\n",e->filial[f]->mes[imes]->totalvendas[1]);
	printf("\tTotal faturado:%f\n",e->filial[f]->mes[imes]->totalfat[0] );
}

/*Retorna a quantidade total de produtos comprados pelo cliente*/
int findcliente(AVLcod cod, char* cliente){
	return(findclienteaux(cod,cliente));
	}

