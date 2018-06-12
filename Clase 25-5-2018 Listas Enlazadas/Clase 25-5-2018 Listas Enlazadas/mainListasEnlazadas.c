/*
*	LISTA ENLAZADAS - VINCULAR AL INICIO DE LA LISTA
*	LISTA ENLAZADAS - VINCULAR AL FINAL DE LA LISTA
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct n {
	int dato;
	struct n *pSig; //puntero a la proxima estructura de la lista
}nodo;

typedef nodo *pNodo; //renombre de la estructura a *pNodo

void vincularAlInicio(pNodo * pInicio, pNodo nuevo);
void vincularAlFinal(pNodo * pInicio, pNodo nuevo);
void vincularOrdenamiento(pNodo * pInicio, pNodo nuevo);
void eliminar(pNodo * pInicio, int x);
void cargarLista(pNodo *pInicio);
void mostrarLista(pNodo copiaInicio);

int main(void) {
	int x;
	pNodo inicio = NULL; 
	cargarLista(&inicio); //inicio pasado por referencia dado que va a ser modificada.
	mostrarLista(inicio); //al no modificarse la lista no hace falta pasarla por referencia.
	printf("Ingrese el numero que desea eliminar: \n");
	scanf("%d", &x);
	fgetc(stdin);
	eliminar(&inicio, x);
	mostrarLista(inicio);
	return 0;
}

void cargarLista(pNodo *pInicio) {
	int x;
	pNodo nuevo;
	printf("Ingrese un numero enter (0 para finalizar): ");
	scanf("%d", &x);
	fgetc(stdin);
	while (x != 0) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL){
			printf("Intente nuevamente mas tarde.");
			x = 0;
		}
		else {
			nuevo->dato = x; //guardo dato ingresado en el nodo.
			//vincularAlInicio(pInicio, nuevo);
			//vincularAlFinal(pInicio, nuevo);
			vincularOrdenamiento(pInicio, nuevo);
			printf("Ingrese un numero enter (0 para finalizar): ");
			scanf("%d", &x);
			fgetc(stdin);
		}
	}
}

void mostrarLista(pNodo copiaInicio) {
	while (copiaInicio != NULL) {
		printf("%d -> ", copiaInicio->dato);
		copiaInicio = copiaInicio->pSig;
	}
}

void vincularAlInicio(pNodo * pInicio, pNodo nuevo) {
	if (*pInicio == NULL) { //cuando la lista esta vacia.
		nuevo->pSig = NULL;
		*pInicio = nuevo;
	}
	else { //cuando la lista no esta vacia (ingreso al inicio de la lista)
		nuevo->pSig = *pInicio;
		*pInicio = nuevo;
	}
}

void vincularAlFinal(pNodo * pInicio, pNodo nuevo) {
	pNodo anterior = NULL;
	pNodo actual = *pInicio;
	if (actual == NULL) { //cuando la lista esta vacia.
		nuevo->pSig = NULL;
		*pInicio = nuevo;
	}
	else {
	//leo hasta el fin de la lista
		while (actual != NULL) {
			anterior = actual;
			actual = actual->pSig;
		}
		nuevo->pSig = NULL;
		anterior->pSig = nuevo;
	}
}

void vincularOrdenamiento(pNodo * pInicio, pNodo nuevo) {
	pNodo actual = *pInicio;
	pNodo anterior = NULL;
	if (actual == NULL  || nuevo->dato < (*pInicio)->dato) {//caso 1 y 2  
		nuevo->pSig = *pInicio; 
		*pInicio = nuevo;
	}
	else {
		while (actual != NULL && nuevo->dato >= actual->dato) { //caso 3 y 4 
			anterior = actual;
			actual = actual->pSig;
		}
		nuevo->pSig = actual;
		anterior->pSig = nuevo;
	}
}


void eliminar(pNodo * pInicio, int x) {
	pNodo anterior = NULL ;
	pNodo actual = *pInicio;
	if (actual != NULL) {
		while (actual != NULL && x != actual->dato) { //caso 2 y 3
			anterior = actual;
			actual = actual->pSig;
		}
	}
	if (actual != NULL) { //dato encontrado
		//if (anterior == NULL) 
			//*pInicio = (*pInicio)->pSig;
		//else
			anterior->pSig = actual->pSig;
		free(actual);
	}
}