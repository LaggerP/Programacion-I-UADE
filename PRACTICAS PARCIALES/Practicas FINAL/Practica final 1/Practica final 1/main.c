/*
	Ejercicio 1: Realizar un programa que permita cargar una lista doble y poder eliminar un nodo dado y sus siguientes. 
	Después realizar una función que permita recuperar ese nodo perdido y volver a obtener la lista original 
	Ej: 
		Lista original: 1<->2<->3<->4<->5
		Lista con nodo y sus siguientes eliminados: 1<->2<->3
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct n{
	int dato;
	struct n *pSig;
	struct n *pAnt;
}nodo, *pNodo;

void mostrar(pNodo inicio);
void vincularDato(pNodo *inicio, pNodo *fin, pNodo nuevo);
void desvincularNodo(int x, pNodo *inicio);
void vincularNodoPerdido(pNodo* inicio, pNodo *fin);

int main(void) {
	pNodo inicio = NULL;
	pNodo fin = NULL;
	pNodo nuevo = NULL;
	int x;
	printf("Ingrese un numero (0 para finalizar): \n");
	scanf("%d", &x);
	fgetc(stdin);
	while (x != 0){
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL) {
			printf("Intente mas tarde.");
		}else{
			nuevo->dato = x;
			vincularDato(&inicio, &fin, nuevo);
			printf("Ingrese un numero (0 para finalizar): \n");
			scanf("%d", &x);
			fgetc(stdin);
		}
	}
	mostrar(inicio);
	printf("\nIngrese numero que desea desvincular: \n");
	scanf("%d", &x);
	fgetc(stdin);
	desvincularNodo(x, &inicio);
	mostrar(inicio);
	puts("");
	vincularNodoPerdido(&inicio, &fin);
	mostrar(inicio);
	system("pause");
	return 0;
}

void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("%d->", inicio->dato);
		inicio = inicio->pSig;
	}
}

void vincularDato(pNodo *inicio, pNodo *fin, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (*inicio == NULL) { //lista vacia
		nuevo->pSig = NULL;
		nuevo->pAnt = NULL;
		*inicio = nuevo;
		*fin = nuevo;
	}
	else if(nuevo->dato <(*inicio)->dato){ //primer nodo
		nuevo->pSig = *inicio;
		nuevo->pAnt = NULL;
		(*inicio)->pAnt = NULL;
		*inicio = nuevo;
	}
	else if (nuevo->dato >= (*fin)->dato) { //ultimo nodo
		nuevo->pSig = NULL;
		nuevo->pAnt = *fin;
		(*fin)->pSig = nuevo;
		*fin = nuevo;
	}
	else {
		//mientras el dato actual sea mayor igual al dato nuevo se avanza en la lista
		while (nuevo->dato >= actual->dato)
			actual = actual->pSig;
		anterior = actual->pAnt;
		nuevo->pSig = actual;
		nuevo->pAnt = anterior;
		actual->pAnt = nuevo;
		anterior->pSig = nuevo;
	}
}

void desvincularNodo(int x, pNodo *inicio) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	while (actual != NULL) {
		//si se encontro el dato que estoy buscando el nodo siguiente de 'actual' apunta a NULL | tener en cuenta que no se modifico el anterior.
		if (actual->dato == x) 
			actual->pSig = NULL;
		actual = actual->pSig;
	}
}

void vincularNodoPerdido(pNodo* inicio, pNodo *fin) {
	pNodo actual = (*fin)->pAnt;
	pNodo anterior = (*fin);
	int flag = 0;
	while (actual != NULL) {
		if (actual->pSig == NULL && flag == 0) {
			flag = -1;
			actual->pSig = anterior;
		}
		else { //recorro la lista de manera inversa.
			anterior = actual;
			actual = actual->pAnt;
		}
	}
}