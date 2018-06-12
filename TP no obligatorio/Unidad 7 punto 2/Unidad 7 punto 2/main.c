#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct n {
	int dato;
	struct n *pSig;
}nodo;

typedef nodo *pNodo;

void apilar(pNodo * pInicio, int e);
void desapilar(pNodo * pInicio);
void tope(pNodo * pInicio);
int pilaVacia(pNodo * pInicio);
void inicializarPila(pNodo * pInicio);

int main(void) {
	int x, e;
	pNodo inicio = NULL;
	printf("Ingrese numero a apilar (0 para finalizar): ");
	scanf("%d", &e);
	fgetc(stdin);
	apilar(&inicio,e);
	printf("Desea desapilar? (1- SI | 2- NO): \n");
	if (x == 1) {
		desapilar(inicio);
	}
	else if (x == 2) {
		tope(inicio);
		pilaVacia(inicio);
	}
	system("pause");
	return 0;
}


void apilar(pNodo * pInicio, int e) {
	pNodo nuevo = NULL;
	while (e != 0) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL) {
			printf("Intente mas tarde");
			e = 0;
		}
		else {
			nuevo->dato = e;
			printf("Ingrese otro numero (0 para finalizar): ");
			scanf("%d", &e);
			fgetc(stdin);
		}
	}
}

void desapilar(pNodo * pInicio) {
	pNodo actual = *pInicio;
	pNodo anterior = NULL;
	if (actual->pSig != NULL) {
		anterior = actual;
		actual = actual->pSig;
	}
	else if (actual->pSig == NULL) {
		anterior->pSig = NULL;
		free(actual);
	}
}

void tope(pNodo * pInicio) {
	pNodo actual = *pInicio;
	pNodo anterior = NULL;
	if (actual->pSig != NULL) {
		anterior = actual;
		actual = actual->pSig;
	}
	else if (actual->pSig == NULL) {
		printf("%d", actual->dato);
	}
}

int pilaVacia(pNodo * pInicio) {
	if (pInicio == NULL) {
		return 0;
	}
	return 1;
}
void inicializarPila(pNodo * pInicio) {


}