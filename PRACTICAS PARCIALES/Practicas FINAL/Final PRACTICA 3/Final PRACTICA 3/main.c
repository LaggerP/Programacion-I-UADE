/*
	Desarrollar un programa que permita crear una lista enlazada simple de números enteros utilizando
	inserción en orden. Luego escribir una función para invertir los últimos N nodos de la misma, donde
	N es un número entero pasado como parámetro. No se permite crear nuevos nodos durante el proceso
	de inversión. Imprimir la lista antes y después del proceso.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct a {
	int dato;
	struct a *pSig;
}nodo, *pNodo;

void mostrar(pNodo inicio);
void vincularOrdenado(pNodo *inicio, pNodo nuevo);
void invertir(pNodo *inicio);

int main(void) {
	pNodo inicio = NULL, nuevo = NULL;
	int num;
	printf("Ingrese un numero (-1 para finalizar):\n");
	scanf("%d", &num);
	fgetc(stdin);
	while (num != -1) {
		nuevo = (pNodo)malloc(sizeof(nodo));
			if (nuevo != NULL) {
				nuevo->dato = num;
				vincularOrdenado(&inicio, nuevo);
				printf("Ingrese un numero (-1 para finalizar):\n");
				scanf("%d", &num);
				fgetc(stdin);
			}
			else {
				printf("No hay espacio.");
				num = -1;
			}
	}
	mostrar(inicio);
	invertir(&inicio);
	mostrar(inicio);
	system("pause");
	return 0;
}

void vincularOrdenado(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (*inicio == NULL) {
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if (nuevo->dato < actual->dato) {
		nuevo->pSig = actual;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL && nuevo->dato > actual->dato) {
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) {
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
		else {
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
	}
}

void invertir(pNodo *inicio) {
	int aux;
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	pNodo aux;
	pNodo actualSig = actual->pSig;
	*inicio = NULL;
	printf("Ingrese el numero de referencia para invertir los nodos\n");
	scanf("%d", &aux);
	fgetc(stdin);
	while (actual != NULL) {
		if (aux == actual->dato) {
			aux = actual->pSig;
			actual->pSig = actualSig;
			actualSig->pSig = actual;
			actual = aux;
		}
		anterior = actual;
		actual = actual->pSig;
	}
}


void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("%d->", inicio->dato);
		inicio = inicio->dato;
	}
}

