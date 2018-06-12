#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct n {
	int dato;
	struct n *pSig;
}nodo, *pNodo;


void cargar(pNodo *inicio);
void vincularOrdenado(pNodo *inicio, pNodo nuevo);
void mostrar(pNodo inicio);
void mostrarInvertido(pNodo inicio);
void invertir(pNodo * inicio);

int main(void) {
	pNodo inicio = NULL;
	cargar(&inicio);
	mostrar(inicio);

	invertir(&inicio);
	mostrarInvertido(inicio);
	system("pause");
	return 0;
}

void cargar(pNodo *inicio) {
	int x;
	pNodo nuevo;
	printf("Ingrese numero (0 para finalizar): ");
	scanf("%d", &x);
	fgetc(stdin);
	while (x != 0) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL) {
			printf("Intente mas tarde");
			x = 0;
		}
		else {
			nuevo->dato = x; //guardo dato ingresado en el nodo.
			vincularOrdenado(inicio, nuevo);
			printf("Ingrese otro numero (0 para finalizar): ");
			scanf("%d", &x);
			fgetc(stdin);
		}
	}
}

void vincularOrdenado(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) { //vincular al principio con lista vacia
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if ((*inicio)->dato > nuevo->dato) { //vincular al principio con lista NO vacia
		nuevo->pSig = *inicio;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL) { // mientras no se encuentre
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) { //insertar al final
			anterior->pSig = nuevo;
			nuevo->pSig = NULL;
		}
		else { //entre nodos
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
	}
}

void invertir(pNodo * inicio) {
	pNodo actual = *inicio;
	*inicio = NULL; //primer nodo null
	pNodo aux;
	while (actual != NULL) {
		aux = actual->pSig;
		actual->pSig = *inicio;
		*inicio = actual;
		actual = aux;
	}
}

void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("%d -->", inicio->dato);
		inicio = inicio->pSig;
	}
}

void mostrarInvertido(pNodo inicio) {
	printf("\nLista invertida: \n");
	while (inicio != NULL) {
		printf("%d -->", inicio->dato);
		inicio = inicio->pSig;
	}
}