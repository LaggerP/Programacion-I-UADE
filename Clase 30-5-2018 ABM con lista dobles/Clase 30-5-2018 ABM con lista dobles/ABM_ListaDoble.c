#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LNOM 32

typedef struct persona{
	char nombre[LNOM];
	int dni;
	int d, m, a;
	struct persona *pSig;
	struct persona *pAnt;
}nodo;

typedef nodo *pNodo;

void altas(pNodo *inicio, pNodo *fin);
void vincularOrdenamiento(pNodo *inicio, pNodo *fin, pNodo nuevo);
void ingresarCadena(char nombre[], int n, char mensaje[]);
void mostrar(pNodo inicio);
void eliminar(pNodo *inicio);

int main(void) {
	pNodo inicio = NULL;
	pNodo fin = NULL;
	altas(&inicio, &fin);
	mostrar(inicio);
	eliminar(&inicio);
	mostrar(inicio);
	system("pause");
	return 0;
}

void altas(pNodo *inicio, pNodo *fin) {
	pNodo nuevo;
	char nombre[LNOM];
	ingresarCadena(nombre, LNOM, "Ingrese nombre de la persona (enter para finalizar): ");
	while (nombre[0] != '\0') {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo == NULL) {
			printf("Intente mas tarde.");
			nombre[LNOM] = '\0';
		}
		else {
			strcpy(nuevo->nombre, nombre);
			printf("Ingrese DNI: ");
			scanf("%d", &nuevo->dni);
			fgetc(stdin);
			printf("Ingrese fecha de nacimiento: ");
			scanf("%d/%d/%d", &nuevo->d, &nuevo->m, &nuevo->a);
			fgetc(stdin);
			//vincularOrdenamiento(inicio, fin, nuevo);
			ingresarCadena(nombre, LNOM, "Ingrese otro nombre (enter para finalizar): "); 
		}
	}
}
void vincularOrdenamiento(pNodo *inicio, pNodo *fin, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (inicio == NULL) { //si la lista esta vacia... ||PREGUNTAR COMO FUNCIONA DICHA FUNCION.
		nuevo->pSig = *inicio;
		nuevo->pAnt = NULL;
		*inicio = nuevo;
		*fin = nuevo;
	}
	else if (strcmp(nuevo->nombre, (*inicio)->nombre) < 0) {
		nuevo->pSig = *inicio;
		nuevo->pSig = NULL;
		(*inicio)->pAnt = nuevo;
		*fin = nuevo;
	}
	else if (strcmp(nuevo->nombre, (*inicio)->nombre) > 0) {
		nuevo->pSig = NULL;
		nuevo->pAnt = *fin;
		(*fin)->pSig = nuevo;
		*fin = nuevo;
	}
	else {
	//PREGUNTAR COMO FUNCIONAN ESTAS LINEAS DE CODIGO
		while (strstr(actual->nombre, nuevo->nombre) <= 0)
			actual = actual->pSig;
		anterior = actual->pAnt;
		nuevo->pSig = actual;
		nuevo->pAnt = anterior;
		actual->pAnt = nuevo;
		anterior->pSig = nuevo;
	}
}

void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("%s\n", inicio->nombre);
		printf("%d\n", inicio->dni);
		printf("%d/%d/%d\n", inicio->d, inicio->m, inicio->a);
		inicio = inicio->pSig;
	}
}

void eliminar(pNodo *inicio) {
	char nombreEli[LNOM];
	pNodo anterior = NULL;
	pNodo actual = *inicio;
	ingresarCadena(nombreEli, LNOM, "Ingrese el nombre de la persona que desea eliminar: ");
	if (actual != NULL) { 
		while (actual != NULL && !strstr(nombreEli, actual->nombre)) { //caso 2 y 3
			anterior = actual;
			actual = actual->pSig;
		}
	}
	if (actual != NULL) { //dato encontrado
		if (anterior == NULL)
			*inicio = (*inicio)->pSig;
		else
			anterior->pSig = actual->pSig;
		free(actual);
	} {

	}
}

void ingresarCadena(char nombre[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(nombre, LNOM, stdin);
	while (nombre[i] != '\0' && nombre[i] != '\n')
		i++;
	if (nombre[i] == '\n')
		nombre[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}