#ifndef AVL_H_
#define AVL_H_

typedef int Boolean;
#define true 1
#define false 0

typedef struct avlcod *AVLcod;
typedef struct venda {
	/* char produto[10]; */
	double preco;
	int quantidade;
	/* int promo; */
	char cliente[10];
	/* int mes; */
	/* int filial; */
}*Venda;

typedef struct vendatmp *Vendatmp;

int maxcod (int a, int b);
int alturacod (AVLcod a);
int diferencacod (AVLcod a, AVLcod b);
AVLcod rotacaoEsqcod (AVLcod a);
AVLcod rotacaoDircod (AVLcod a);
AVLcod insereDircod (AVLcod a, Vendatmp codV);
AVLcod insereEsqcod (AVLcod a, Vendatmp codV);
AVLcod insereAVLcod (AVLcod a, Vendatmp codV);
Boolean existeAVLcod (AVLcod a, Vendatmp v);
void freeTreecod (AVLcod a);
char** auxiliarImprimecod (char **lista,AVLcod t, int *i);
int findclienteaux(AVLcod cod, char* cliente);

#endif
