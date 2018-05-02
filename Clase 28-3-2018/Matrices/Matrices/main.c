//matrices
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define FIL 4
#define COL 4

void matriz_ya_generada();
void generarMatriz();
void sumarMatriz();
void ordenarMatriz();

int main() {
	//matriz_ya_generada();
	//generarMatriz();
	//sumarMatriz();
	ordenarMatriz();
	system("pause");
	return 0;
}

void matriz_ya_generada() {
	int matriz[FIL][COL] = { { 1,2,3 },{ 3,2,1 },{ 1,3,3 } };
	int f, c;
	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("%3d", matriz[f][c]);
		}
		printf("\n");
	}
}

void generarMatriz() {
	int matriz[FIL][COL];
	int f, c;
	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("Ingrese matriz [%d][%d]: ", f+1,c+1);
			scanf("%d", &matriz[f][c]);
			fgetc(stdin);
		}
	}
	printf("\n\n");
	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("%3d", matriz[f][c]);
		}
		printf("\n");
	}
}


void sumarMatriz() {
	int matriz1[FIL][COL];
	int matriz2[FIL][COL];
	int matrizFinal[FIL][COL];
	int f, c;
	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("Ingrese posicion [%d][%d] de primera matriz: ", f + 1, c + 1);
			scanf("%d", &matriz1[f][c]);
			fgetc(stdin);
			printf("Ingrese posicion [%d][%d] de segunda matriz: ", f + 1, c + 1);
			scanf("%d", &matriz2[f][c]);
			fgetc(stdin);
			matrizFinal[f][c] = matriz1[f][c] + matriz2[f][c];
		}
	}
	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("%3d", matrizFinal[f][c]);
		}
		printf("\n");
	}
}


void ordenarMatriz() {
	int matriz[FIL][COL];
	int f, c,i,j,x,y;
	int aux;
	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("Ingrese matriz [%d][%d]: ", f + 1, c + 1);
			scanf("%d", &matriz[f][c]);
		}
	}
	for (i = 0; i < f; i++) {
		for (j = 0; j < c ; j++) {
			for (x = 0; x < f; x++) {
				for (y = 0; y < c ; y++) {
					if (matriz[i][j] < matriz[x][y]) {
						aux = matriz[i][j];
						matriz[i][j] = matriz[x][y];
						matriz[x][y] = aux;
					}
				}
			}
		}
	}

	for (f = 0; f < FIL; f++) {
		for (c = 0; c < COL; c++) {
			printf("%3d", matriz[f][c]);
		}
		printf("\n");
	}
}