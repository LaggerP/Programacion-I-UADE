/*
	Realizar un programa que permita:
		- dar de ALTA un nodo en un archivo (deben estar ordenados de manera ascendente).
		- dar de BAJA un nodo especificandolo mediante teclado.
		- poder MODIFICAR un nodo especificandolo mediante teclado.
		- insertar lista de nodos en el archivo de texto "listaDeNodos.txt".
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct n {
	int dato;
	struct n *pSig;
}nodo, *pNodo;

void vincularOrdenado(pNodo *inicio, pNodo nuevo);
void mostrar(pNodo inicio);
void bajaModificacionNodo(pNodo *inicio);
void insertarEnArchivo(pNodo inicio);

int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo = NULL;
	int aux;
	printf("Ingrese numero - (-1 para finalizar):");
	scanf("%d", &aux);
	fgetc(stdin);
	while (aux != -1) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL) {
			printf("Intente mas tarde - no hay memoria");
			aux = -1;
		}
		else {
			nuevo->dato = aux;
			vincularOrdenado(&inicio, nuevo);
			printf("Ingrese numero - (-1 para finalizar):");
			scanf("%d", &aux);
			fgetc(stdin);
		}
	}
	mostrar(inicio);
	bajaModificacionNodo(&inicio);
	mostrar(inicio);
	insertarEnArchivo(inicio);
	system("pause");
	return 0;
}

void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("%d-> ", inicio->dato);
		inicio = inicio->pSig;
	}
}

void vincularOrdenado(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) { //lista vacia.
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if (actual->dato > nuevo->dato) { //insercion en primer nodo
		nuevo->pSig = actual;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL && actual->dato < nuevo->dato) { //avanzo en la lista
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) { //nodo final
			anterior->pSig = nuevo;
			nuevo->pSig = NULL;
		}
		else {
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
	}
}

void bajaModificacionNodo(pNodo *inicio) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	int datoAux;
	printf("Ingrese numero a eliminar (-1 para modificar):\n");
	scanf("%d", &datoAux);
	fgetc(stdin);
	if (actual != NULL && datoAux != -1) { //eliminacion de nodo
		while (actual != NULL && datoAux != actual->dato) {
			anterior = actual;
			actual = actual->pSig;
		}
		if (datoAux == actual->dato) {
			anterior->pSig = actual->pSig;
			free(actual);
			actual = anterior->pSig;
		}
	}
	else { //modificacion de dato de nodo
		printf("Ingrese numero que desea modificar:\n");
		scanf("%d", &datoAux);
		fgetc(stdin);
		if (actual != NULL) {
			while (actual != NULL && datoAux != actual->dato) {
				anterior = actual;
				actual = actual->pSig;
			}
			if (datoAux == actual->dato) {
				printf("Ingrese nuevo dato:\n");
				scanf("%d", &datoAux);
				fgetc(stdin);
				actual->dato = datoAux;
			}
		}
	}
}

void insertarEnArchivo(pNodo inicio) {
	FILE * arch = fopen("listaDeNodos.txt", "wt");
	if (arch == NULL) {
		printf("Error de apertura.");
	}
	else {
		while (inicio != NULL) {
			fprintf(arch, "%d\n", inicio->dato);
			inicio = inicio->pSig;
		}
	}
}