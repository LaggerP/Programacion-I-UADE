/*
	Vector dinámico.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void cargarVector(int *pVector, int cant);
void mostrarVector(int *pVector, int cant);

int main(void) {
	int *pVector;
	int cant; //contador de cantidad de variables
	srand((unsigned int)time(NULL));
	cant = rand() % (10 - 5 + 1) + 5;
	pVector = (int *)malloc(sizeof(int)*cant);
	if (pVector != NULL) {
		cargarVector(pVector, cant);
		mostrarVector(pVector, cant);
		free(pVector);
	}
	system("pause");
	return 0;
}

void cargarVector(int *pVector, int cant) {
	int i = 0;
	while (i < cant) {
		pVector[i] = rand() % (999 - 100 + 1) + 100;
		i++;
	}
}

void mostrarVector(int *pVector, int cant) {
	int i = 0;
	while (i < cant) {
		printf("%4d\n", pVector[i]);
		i++;
	}
}