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

int main(void) {
	
	int vector[TAM];
	srand((unsigned int)time(NULL));
	cargarA(vector, TAM);
	ordernar(vector, TAM);
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


/*

Busqueda binaria planteada por la profesora:


	int busquedaBinaria(int v[], int c, int dato_a_buscar) {
		int pos = -1;
		int ini = 0; //posicion inicial del vector
		int fin = c - 1; //posicion final del vector
		int medio;
		while (ini <= fin && pos == -1) {
			medio = (ini + fin) / 2;
			if (v[medio] == dato_a_buscar) {
				pos = medio;
			}
			else if (dato_a_buscar < v[medio]) {
				fin = medio - 1;
			}
			else
				ini = medio + 1;
		}
		return pos;
	}


*/

//numeros reales no pueden buscarse por igualdad. Solo por mayor y menores

