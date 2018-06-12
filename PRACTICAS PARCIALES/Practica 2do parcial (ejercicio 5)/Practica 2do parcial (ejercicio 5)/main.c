/*
	Realizar un programa que permita cargar una estructura en un archivo de texto y despues leerlo.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n {
	int dato;
	struct n *pSig;
}nodo, *pNodo;

void cargar(pNodo * inicio);
void grabarEnArchivo(pNodo nuevo);
void insertarEnOrden(pNodo *inicio, pNodo nuevo);
void mostrar(pNodo inicio);
void eliminar(pNodo *inicio);
void eliminarDelArchivo();

int main(void) {
	pNodo inicio = NULL;
	cargar(&inicio);
	mostrar(inicio);
	eliminar(&inicio);
	mostrar(inicio);
	eliminarDelArchivo();
	system("pause");
	return 0;
}

void cargar(pNodo * inicio) {
	pNodo nuevo;
	int x;
	printf("Ingrese un numero (0 para finalizar).\n");
	scanf("%d", &x);
	fgetc(stdin);
	while (x != 0) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo != NULL) {
			nuevo->dato = x;
			grabarEnArchivo(nuevo);
			insertarEnOrden(inicio, nuevo);
		}
		else {
			printf("Error. Intente mas tarde");
		}
		printf("Ingrese otro numero (0 para finalizar).\n");
		scanf("%d", &x);
		fgetc(stdin);
	}
}

void grabarEnArchivo(pNodo nuevo) {
	FILE * arch = fopen("ejercicio5.txt", "at");
	if (arch == NULL) {
		printf("error de apertura");
	}
	else {
		fprintf(arch, "%d\n", nuevo->dato);
		fclose(arch);
	}
}

void insertarEnOrden(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) { //insertar al inicio de lista vacia
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if ((*inicio)->dato > nuevo->dato) { //insertar al inicio de una lista NO vacia
		nuevo->pSig = actual;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL && actual->dato < nuevo->dato) { // recorrer lista
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) { //insertar al final de la lista
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
		else {//entre nodos
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
	}
}

void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("%d -->", inicio->dato);
		inicio = inicio->pSig;
	}
}

void eliminar(pNodo *inicio) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	int x;
	printf("Ingrese el numero que desea eliminar: \n");
	scanf("%d", &x);
	fgetc(stdin);
	if (actual != NULL) {
		while (actual != NULL && actual->dato != x) {
			anterior = actual;
			actual = actual->pSig;
		}
	}
	if (actual != NULL) {
		anterior->pSig = actual->pSig;
		free(actual);
	}

}

void eliminarDelArchivo() {
	int x=0;
	int numero=0;
	printf("Ingrese el numero que desea eliminar: \n");
	scanf("%d", &x);
	fgetc(stdin);
	FILE * arch2 = fopen("archivofinal.txt", "wt");
	FILE * arch = fopen("ejercicio5.txt", "rt");
	if (arch == NULL || arch2 == NULL)
		printf("error de apertura");
	else {
		fscanf(arch, "%d", &numero);
		fgetc(arch);
		while (!feof(arch)) {
			if (numero != x) {
				fputc(numero, arch2);
			}
		}
		printf("No se encontro ningun numero igual al solicitado.");
	}
	fclose(arch);
	fclose(arch2);
}
