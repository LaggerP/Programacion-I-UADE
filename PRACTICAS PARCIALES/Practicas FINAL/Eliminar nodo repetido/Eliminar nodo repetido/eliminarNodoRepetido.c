/*Desarrollar un programa para crear una lista simple de números enteros utilizando inserción
al final. Luego se solicita eliminar de la lista los nodos que estén repetidos (considerando
para ello el número entero almacenado en cada nodo), dejando sólo uno de
cada uno. Los nodos que se conserven deben mantener el orden original. Imprimir la
lista antes y después de la eliminación.*/

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct n {
	int dato;
	struct n *pSig;
}nodo, *pNodo;

void vincular(pNodo *inicio, pNodo nuevo);
void mostrar(pNodo inicio);
void eliminarRepetidos(pNodo *inicio);

int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo = NULL;
	int x;
	printf("Ingrese un numero (-1 para terminar):\n");
	scanf("%d", &x);
	fgetc(stdin);
	while (x != -1) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL) {
			printf("Intente mas tarde.");
			return 1;
		}
		else {
			nuevo->dato = x;
			vincular(&inicio, nuevo);
			printf("Ingrese un numero (-1 para terminar):\n");
			scanf("%d", &x);
			fgetc(stdin);
		}
	}
	printf("Lista sin nodos eliminados:\n");
	mostrar(inicio);
	eliminarRepetidos(&inicio);
	printf("Lista con nodos eliminados:\n");
	mostrar(inicio);
	system("pause");
	return 0;
}

void vincular(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) { //insertar al inicio con lista vacia.
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL) {//avanzo hasta el final de la lista
			anterior = actual;
			actual = actual->pSig;
		}
		anterior->pSig = nuevo;
		nuevo->pSig = NULL;
	}
}


void eliminarRepetidos(pNodo *inicio) {
	pNodo actual = *inicio;
	pNodo actualAux = NULL;
	pNodo anterior = NULL;
	pNodo borrarNodo = NULL;
	int valor;
	while (actual != NULL) {
		valor = actual->dato;
		actualAux = actual->pSig;
		anterior = actual;
		while (actualAux != NULL) {
			if (valor != actualAux->dato) {
				anterior = actualAux;
				actualAux = actualAux->pSig;
			}
			else if (anterior != NULL) {//no efecto
				borrarNodo = actualAux;
				anterior->pSig = actualAux->pSig;
				actualAux = actualAux->pSig;
				free(borrarNodo);
			}
			else {
				borrarNodo = actualAux;
				anterior->pSig = actualAux->pSig;
				actualAux = actualAux->pSig;
				free(borrarNodo);
			}
		}
		actual = actual->pSig;
	}
}


void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("%d->", inicio->dato);
		inicio = inicio->pSig;
	}
}