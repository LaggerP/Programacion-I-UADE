/*
Escribir un programa que rellene una matriz de enteros de MAX x MAX con números al
azar comprendidos entre 12 y 95, tal que ningún número esté repetido. El valor de MAX
debe declararse con una directiva ‪#‎define‬, y el programa debe funcionar aunque este
valor se modifique. Imprimir por pantalla la matriz obtenida.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 5

void mostrarMatriz(int matriz[N][N]);
void cargarMatriz(int matriz[N][N]);
void eliminarRepetidos(int matriz[N][N]);

int main(void) {
	int matriz[N][N];
	srand((int)time(NULL));
	cargarMatriz(matriz);
	mostrarMatriz(matriz);
	eliminarRepetidos(matriz);
	mostrarMatriz(matriz);
	system("pause");
	return 0;
}

void cargarMatriz(int matriz[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			matriz[i][j] = rand() % (95 - 13) + 1;
		}
	}
}

void eliminarRepetidos(int matriz[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int ii = 0; ii < N; ii++) {
				for (int jj = 0; jj < N; jj++) {
					if (matriz[i][j] == matriz[ii][jj]) {
						printf("\n\n\t\tNUMEROS CAMBIADOS");
						printf("\n\t%d\n", matriz[i][j]);
						matriz[i][j] = rand() % (95 - 13) + 1;
					}
				}
			}

		}
	}
}

void mostrarMatriz(int matriz[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%4d", matriz[i][j]);
		}
		printf("\n");
	}
}