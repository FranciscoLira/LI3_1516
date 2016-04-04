#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef int bool;
#define true 1
#define false 0

// (faturaçao organizada por mes)
typedef struct prods* CatProds;
struct prods {
	AVL catalogoProd[26];
};

typedef struct avl {
	int tamanho;
	avl_tree_t root;
} *AVL;

typedef struct prod* Produto;
struct prod {
 	char* nomeprod;
};