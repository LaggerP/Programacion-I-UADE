#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LNOM 32	
#define TAM 1000

typedef struct peliculas {
	char nombrePelicula[LNOM];
	int duracion;
	int costo;
	int d, m, a;
	struct peliculas *pSig;
}infoPelicula;

typedef infoPelicula *pNodo;

void altasPelicula(pNodo *pInicio);
void ordenarPelicula(pNodo *pInicio, pNodo nuevo);
void mostrarPelicula(pNodo inicio);


int main(void) {
	char nombreEliminar[LNOM];
	pNodo inicio = NULL;
	altasPelicula(&inicio);
	mostrarPelicula(inicio);
	printf("Ingrese nombre de pelicula que desea eliminar: ");
	fgets(nombreEliminar, LNOM, stdin);
	//eliminarPelicula(&inicio, nombreEliminar);
	mostrarPelicula(inicio);
	system("pause");
	return 0;
}


void altasPelicula(pNodo *pInicio) {
	int opc;
	int time;
	int cost;
	int dd, mm, aa;
	pNodo nuevo;
	printf("Ingrese 0 para finalizar o cualquier otro numero para cargar: ");
	scanf("%d", &opc);
	fgetc(stdin);
	while (opc != 0) {
		nuevo = (pNodo)malloc(sizeof(infoPelicula));
		if (nuevo == NULL) {
			printf("Intente nuevamente mas tarde.");
			opc=0;
		}
		else {
			printf("Ingrese nombre de pelicula\n");
			fgets(nuevo->nombrePelicula,LNOM, stdin);
			printf("Ingrese duración: \n");
			scanf("%d", &time);
			fgetc(stdin);
			nuevo->duracion = time;
			printf("Ingrese costo: \n");
			scanf("%d", &cost);
			fgetc(stdin);
			nuevo->costo = cost;
			printf("Ingrese fecha (dd/mm/aa): \n");
			scanf("%d/%d/%d", &dd, &mm, &aa);
			fgetc(stdin);
			nuevo->d = dd;
			nuevo->m = mm;
			nuevo->a = aa;
			ordenarPelicula(pInicio, nuevo);
			printf("¿Desea cargar otra pelicula? (0 para finalizar)");
			scanf("%d", &opc);
			fgetc(stdin);
		}
	}
}

void ordenarPelicula(pNodo *pInicio, pNodo nuevo) {
	pNodo actual = *pInicio;
	pNodo anterior = NULL;
	if (actual == NULL || nuevo->nombrePelicula > (*pInicio)->nombrePelicula) {//caso 1 y 2  
		nuevo->pSig = *pInicio;
		*pInicio = nuevo;
	}
	else {
		while (actual != NULL && nuevo->nombrePelicula <= actual->nombrePelicula) { //caso 3 y 4 
			anterior = actual;
			actual = actual->pSig;
		}
		nuevo->pSig = actual;
		anterior->pSig = nuevo;
	}
}

void mostrarPelicula(pNodo inicio) {
	while (inicio != NULL) {
		printf("%s\n", inicio->nombrePelicula);
		printf("%d\n", inicio->duracion);
		printf("%d\n", inicio->costo);
		printf("%d/%d/%d\n", inicio->d, inicio->m, inicio->a);
		inicio = inicio->pSig;
	}
}