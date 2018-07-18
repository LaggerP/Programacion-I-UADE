/**
    Facultad de Ingeniería y Ciencias Exactas
    Departamento de Tecnología Informática
    3.4.071 Programación I
    Examen: 2do pacial								Fecha: 13/6/2018

    Nombre del alumno: 
    LU: 1078187

    Enunciado:
    Una concesionaria de autovías registra la siguiente información de sus peajes en un archivo de texto:
    * Patente
    * Horario de pase por cabina de peaje (hh:mm)
    * Nombre Estación de peaje
    * Número de cabina

    Hacer un programa que:
    1 - Cargue en una lista la información desde el archivo de texto necesaria 
		para realizar el informe requerido.
    2 - Listar cada patente con las distintas estaciones por las que pasó, indicando para cada una de las estaciones:
		a - cantidad de veces que pasó
		b - número de cabina con la hora y minutos por la que pasó por primera vez. 
		c - hora y minutos de la última vez que estuvo en la estación.
    Para aprobar se requiere tener el 50% de los conceptos de listas, archivo de texto y cadenas.

    Valor de cada punto
    Punto 1: 2 puntos  
    Punto 2 a: 2 puntos
	Punto 2 b: 2 puntos
	Punto 2 c: 2 puntos
 	Estructuración: 2 puntos

	mostrar ordenado por patente y estacion
**/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LARGO 32


typedef struct h {
	int h, m;
}horario;

typedef struct n {
	char patente[LARGO];
	horario tiempo;
	horario salida;
	char nombre[LARGO];
	int numCabina;
	int cantPase;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void comprobarPatente(pNodo *inicio, pNodo nuevo);
void vincular(pNodo *inicio, pNodo nuevo);
void mostrar(pNodo inicio);

int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo = NULL;
	char aux[32];
	FILE * arch = fopen("Peaje180613.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura");
		return 1;
	}
	else {
		fgets(aux, LARGO, arch);
		while (!feof(arch)) {
			nuevo = (pNodo)malloc(sizeof(nodo));
			if (nuevo != NULL) {
				sacarEnter(aux);
				strcpy(nuevo->patente, aux);
				fscanf(arch, "%d:%d", &nuevo->tiempo.h, &nuevo->tiempo.m);
				fgetc(arch);
				fgets(aux, LARGO, arch);
				sacarEnter(aux);
				strcpy(nuevo->nombre, aux);
				fscanf(arch, "%d", &nuevo->numCabina);
				fgetc(arch);
			}
			else {
				printf("Intente mas tarde");
			}
			fgets(aux, LARGO, arch);
			comprobarPatente(&inicio, nuevo);
		}
	}
	mostrar(inicio);
	system("pause");
	return 0;
}


void sacarEnter(char aux[]) {
	char *p = strchr(aux, '\n');
	if (p != NULL) {
		*p = '\0';
	}
	else{
		while (fgetc(stdin) != '\n')
			;
	}
	
}

void comprobarPatente(pNodo *inicio, pNodo nuevo) {
	int flag = 0;
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	int cantPases = 0;
	while (actual != NULL &&flag==0) {
		/*
			¿Qué nos permite hacer esto?
				Si la patente fue ingresada anteriormente solamente va a enlazar los datos restantes (No vuelve a guardar la patente).
				También nos va a contar la cantidad de veces que esa patente paso por esa estación
		*/
		if (strcmp(actual->patente,nuevo->patente)==0) {  //si las patentes son iguales
			
			if (strcmp(actual->nombre, nuevo->nombre) == 0) {
				actual->cantPase = cantPases+1; //cuenta la cantidad de veces que paso por esa misma estación.
				flag = 1;
				// actualizar ultimo horario
				actual->salida.h = nuevo->tiempo.h;
				actual->salida.m = nuevo->tiempo.m;

			}
		}
		anterior = actual;
		actual = actual->pSig;
	}
	if (flag == 0) {
		vincular(inicio, nuevo);
	}
}

void vincular(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (*inicio == NULL) { //lista vacia
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if (strcmp(actual->patente, nuevo->patente) > 0) { //si patente nueva es mayor que la actual - se inserta en el inicio  
		nuevo->pSig = actual;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL && strcmp(actual->patente, nuevo->patente) <= 0) { //mientras actual no sea igual a NULL y el actual sea mayor al nuevo se avanza en la lista
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) { //a final de la lista
			anterior->pSig = nuevo;
			nuevo->pSig = NULL;
		}
		else {
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
	}
}

void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("Patente: %s\n Estacion: %s\n Hora entrada: %d:%d-> Hora salida: %d:%d\n Cabina: %d\n Cant veces: %d\n=======================================\n", inicio->patente, inicio->nombre, inicio->tiempo.h, inicio->tiempo.m, inicio->salida.h, inicio->salida.m, inicio->numCabina, inicio->cantPase);
		inicio = inicio->pSig;
	}
}