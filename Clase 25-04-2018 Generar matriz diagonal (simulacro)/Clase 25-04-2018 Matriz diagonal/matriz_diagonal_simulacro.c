/*
Generar una funcion que permita generar una matriz como la siguiente:

					1	2	3	4	5
					2	3	4	5	4
					3	4	5	4	3
					4	5	4	3	2
					5	4	3	2	1
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


#define COL 5
#define FIL 5

void cargarMatriz();

int main(void) {
	printf("Llene la matriz de 5x5:\n");
	cargarMatriz();
	system("pause");
	return 0;
}

void cargarMatriz() {
	int matriz[COL][FIL];
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < FIL; j++) {
			printf("[%d] [%d]",i,j);
			scanf("%d", &matriz[i][j]);
		}
	}
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < FIL; j++) {
			printf("%2d %d", matriz[i][j]);
		}
	}
}