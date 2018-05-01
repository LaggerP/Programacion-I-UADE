#include <stdio.h>

#define TAM 10

void cargar(int [], int);
void ordenar(int[], int);
void mostrar(int[], int);

int main(void) {
	int vector[TAM];
	cargar(vector, TAM);
	ordenar(vector, TAM);
	mostrar(vector, TAM);
	return 0;
}

void mostrar(int v[], int c) {
	int i;
	for (i = 0; i < c; i++) {
		printf("[%d]: %d", i+1, v[i]);
	}
}


void cargar(int v[], int c) {
	int i;
	for (i = 0; i < c; i++) {
		printf("Ingrese numero para posición [%d]", i + 1);
		scanf("%d", &v[i]);
	}
}
void ordenar(int v[], int c) {
	int i;
	int aux;
	for (i = 0; i < c; i++) {
		for (int j = 0; j < c - 1; i++) {
			if (v[j] > v[j + 1]) {
				int aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
		}
	}
}

/*
								OTRA MANERA DE ORDENAMIENTO POR BURBUJEO.

void ordenar(int v[], int c) {
	int hayCambio = 1, j, p = 1; int aux;
	while (hayCambio) {
		hayCambio = 0;
		for (j = 0; j < c - p; j++) {
			if (v[j] > v[j + 1]) {
				int aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
		}
		p++;
	}
}
*/
