#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print90(char** lista, int pag) {
	int i, j, m, n, first;
	first = pag * 90 - 90;
	for (i = 0; i < 15; i++) {
		n = i * 15;
		for (j = 0; j < 6; j++) {
			m = n + j;
			printf("%s   \n", lista[first + m]);
		}
		printf("\n");
	}
}

void printtillast(char** lista, int pag, int quantos) {
	int i, j, m, n, first;
	first = pag * 90 - 90;
	for (i = 0; i < 15 && ((first + m) <  ; i++) {
	n = i * 15;
	for (j = 0; j < 6; j++) {
			m = n + j;
			printf("%s   \n", lista[first + m]);
		}
		printf("\n");
	}
}


/*lista é o array, pag é número da pagina, quantos é quantos há*/
void printlista(char** lista, int pag, int quantos) {
	int pagmax = quantos / 90;/*última página*/
	if (quantos % 90) pagmax++;
	if (pag < 1 || pag > pagmax) {
		printf("Impossível aceder à página\n");
	}
	if (pag != pagmax) {
		print90(lista, pag);
	}
	else {
		printtillast(lista, first, last, quantos);
	}

}

int main() {

}