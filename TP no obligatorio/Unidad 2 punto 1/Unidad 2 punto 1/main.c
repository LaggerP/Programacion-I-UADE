#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define FIL 4
#define COL 4

void cargar(int matriz[FIL][COL]);

int main(void) {
	int matriz[FIL][COL];
	cargar(matriz);
	system("pause");
	return 0;
}

void cargar(int matriz[FIL][COL]){
	int f, c;
	printf("Ingrese numero: \n");
	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			scanf("[%d][%d]", &f, &c);
			printf("%3d", matriz[f][c]);
		}
		printf("\n");
	}
}

/*
void ordenarFila(int matriz[FIL][COL], int f){

	int p, j, aux;
	for (p=1;p<COL;p++){
		for (j = 0; j < COL - 1; p++) {
			if (matriz[f][j] > matriz[f][j+1]) {
				//intercambio
			}
		}
	}
}
*/
