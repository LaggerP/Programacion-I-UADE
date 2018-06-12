#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct n {
	int dato;
	struct n *pSig; //puntero a la proxima estructura de la lista
	struct n *pAnt;
}nodo;

typedef nodo *pNodo; //renombre de la estructura a *pNodo

void vincularAlInicio(pNodo * pInicio, pNodo nuevo);
void vincularAlFinal(pNodo * pInicio, pNodo nuevo);
void vincularOrdenamiento(pNodo * pInicio, pNodo * pFin, pNodo nuevo);
void eliminar(pNodo * pInicio, int x);
void cargarLista(pNodo *pInicio, pNodo * pFin);
void mostrarLista(pNodo copiaInicio);
void modificar(pNodo * pInicio, int x);

int main(void) {
	int x, numModificar;
	pNodo inicio = NULL;
	pNodo fin=NULL;
	cargarLista(&inicio, &fin); //inicio pasado por referencia dado que va a ser modificada.
	mostrarLista(inicio); //al no modificarse la lista no hace falta pasarla por referencia.
	printf("Ingrese el numero que desea modificar: \n");
	scanf("%d", &numModificar);
	fgetc(stdin);
	modificar(&inicio, numModificar);
	mostrarLista(inicio);
	printf("Ingrese el numero que desea eliminar: \n");
	scanf("%d", &x);
	fgetc(stdin);
	eliminar(&inicio, x);
	mostrarLista(inicio);
	return 0;
}

void cargarLista(pNodo *pInicio, pNodo *pFin) {
	int x;
	pNodo nuevo;
	printf("Ingrese un numero enter (0 para finalizar): ");
	scanf("%d", &x);
	fgetc(stdin);
	while (x != 0) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL) {
			printf("Intente nuevamente mas tarde.");
			x = 0;
		}
		else {
			nuevo->dato = x; //guardo dato ingresado en el nodo.
							 //vincularAlInicio(pInicio, nuevo);
							 //vincularAlFinal(pInicio, nuevo);
			vincularOrdenamiento(pInicio, pFin, nuevo);
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

void vincularOrdenamiento(pNodo * pInicio, pNodo *pFin, pNodo nuevo) {
	pNodo actual = *pInicio;
	pNodo anterior = NULL;
	if (*pInicio == NULL) {//caso lista vacia
		nuevo->pSig = NULL;
		nuevo->pAnt = NULL;
		*pInicio = nuevo;
		*pFin = nuevo;
	}
	else if (nuevo->dato <(*pInicio)->dato){ //caso 1er nodo
		nuevo->pSig = *pInicio;
		nuevo->pAnt = NULL;
		(*pInicio)->pAnt = nuevo;
		*pFin = nuevo;
	}
	else if (nuevo->dato >= (*pFin)->dato) { //caso ultimo nodo
		nuevo->pSig = NULL;
		nuevo->pAnt = *pFin;
		(*pFin)->pSig = nuevo;
		*pFin = nuevo;
	}
	else{
		while (actual->dato >= nuevo->dato)
			actual = actual->pSig;
		anterior = actual->pAnt;
		nuevo->pSig = actual;
		nuevo->pAnt = anterior;
		actual->pAnt = nuevo;
		anterior->pSig = nuevo;
	}
}

void modificar(pNodo * pInicio, int numModificar) {
	pNodo anterior = NULL;
	pNodo actual = *pInicio;
	int num_aModificar;
	printf("Ingrese nuevo numero: \n");
	scanf("%d", &num_aModificar);
	fgetc(stdin);
	if (actual != NULL) {
		while (actual != NULL && numModificar != actual->dato) { //mientras el dato no se encuentre 
			anterior = actual;
			actual = actual->pSig;
		}
	}
	if (actual != NULL) { //si el dato se encontro.
		if (anterior == NULL) {
			*pInicio = (*pInicio)->pSig;
		}
		else if(anterior != NULL && numModificar == actual->dato) {
			actual->dato = num_aModificar;
		}
	}
}

void eliminar(pNodo * pInicio, int x) {
	pNodo anterior = NULL;
	pNodo actual = *pInicio;
	if (actual != NULL) {
		while (actual != NULL && x != actual->dato) { //caso 2 y 3
			anterior = actual;
			actual = actual->pSig;
		}
	}
	if (actual != NULL) { //dato encontrado
		if (anterior == NULL)
			*pInicio = (*pInicio)->pSig;
		else
			anterior->pSig = actual->pSig;
		free(actual);
	}
}