/*
	//Realizar un programa que diga cuantas veces aparece un numero de forma ordenada.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 10
#define sup 99
#define inf 10

void cargarA(int[], int);
void mostrar(int v[], int c);
void ordenar(int v[], int c);

int main(void) {
	
	int vector[TAM];
	srand((unsigned int)time(NULL));
	cargarA(vector, TAM);
	ordenar(vector, TAM);
	mostrar(vector, TAM);
	system("pause");
	return 0;
}

void cargarA(int v[], int c) {
	int i;
	for (i = 0; i < c; i++) {
		v[i] = rand() % (sup - inf + 1) + inf;
	}
}

void ordenar(int v[], int c) {
	int i, j;
	int aux;
	for (i = 0; i < c; i++) {
		for (j = 0; j < c - 1; j++) {
			if (v[j] > v[j + 1]) {
				aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
		}
	}
}

void mostrar(int v[], int c) {
	int i,j, numeroRepite=0;
	for (i = 0; i < c; i++) {
		for (j = 0; i < c; i++) {
			if (v[i] == v[j]) {
				numeroRepite++;
			}
			printf("%d\n", v[i]);
		}
	}
	printf("Cantidad de veces que se repite un numero: %d \n\n\n\n", numeroRepite);
}

//numeros reales no pueden buscarse por igualdad. Solo por mayor y menores

