/*
Se dispone de un archivo de texto con los registros de ingreso y egreso
de los empleados de un establecimiento con el siguiente formato:

Apellido, Nombre
Legajo
E (entrada) o S (salida)
HH:MM

Se pide hacer un programa que muestre la permanencia de cada uno de los
empleados, sabiendo que el ingreso y el egreso suceden dentro de un mismo día
Listar además las posibles inconsistencias:

Ingreso sin egreso
Egreso sin ingreso
Más de un ingreso o egreso consecutivos
No se conoce la cantidad de empleados
No hay más de dos registros por empleado
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LNOM 32

typedef struct h {
	int h, m;
}hora;

typedef struct n {
	char nombreApellido[LNOM];
	int legajo;
	hora entrada, salida;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void compararHorarios(pNodo *inicio, pNodo nuevo);
void vincularNodo(pNodo **inicio, pNodo nuevo, pNodo *anterior, pNodo *actual);
void listarPermanencias(pNodo inicio);
void listarInconsistencias(pNodo inicio, FILE * arch);
//RegistrosE-S

int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo = NULL;
	char aux[100];
	FILE * arch = fopen("RegistrosE-S.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura.");
		return 1;
	}
	fgets(aux, 100, arch);
	while (!feof(arch)) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo != NULL) {
			sacarEnter(aux);
			strcpy(nuevo->nombreApellido, aux);
			fscanf(arch, "%d", &nuevo->legajo);
			fgetc(arch);
			fgets(aux, 100, arch);
			if (aux[0] == 'E') {
				fscanf(arch, "%d:%d", &nuevo->entrada.h, &nuevo->entrada.m);
				fgetc(arch);
				nuevo->salida.h = -1;
			}
			else {
				fscanf(arch, "%d:%d", &nuevo->salida.h, &nuevo->salida.m);
				fgetc(arch);
				nuevo->entrada.h = -1;
			}
				//fgets(aux, 100, arch);
		}
		else {
			printf("Intente mas tarde.");
			return 1;
		}
		fgets(aux, 100, arch);
		compararHorarios(&inicio, nuevo);
	}
	listarPermanencias(inicio);
	listarInconsistencias(inicio, arch);
	fclose(arch);
	system("pause");
	return 0;
}

void sacarEnter(char aux[]) {
	char *p = strchr(aux, '\n');
	if (p != NULL)
		*p = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void compararHorarios(pNodo *inicio, pNodo nuevo) {
	int flag = 0;
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	while (actual != NULL) {
		if (actual->legajo == nuevo->legajo) { //si ingresa significa que el legajo fue cargado anteriormente
			flag = 1;
			if (actual->entrada.h != -1 && nuevo->salida.h != -1) {
				actual->salida.h = nuevo->salida.h;
				actual->salida.m = nuevo->salida.m;
			}
			else if (actual->salida.h != -1 && nuevo->entrada.h != -1) {
				actual->entrada.h = nuevo->entrada.h;
				actual->entrada.m = nuevo->entrada.m;
			}
		}
		// voy avanzando en la lista
		anterior = actual;
		actual = actual->pSig;
	}
	if (flag == 0)
		vincularNodo(&inicio, nuevo, &anterior, &actual);
}

void vincularNodo(pNodo **inicio, pNodo nuevo, pNodo *anterior, pNodo *actual) {
	if (**inicio == NULL) { //inicio de lista
		nuevo->pSig = NULL;
		**inicio = nuevo;
	}
	else if (*actual == NULL) { //fin de lista
		(*anterior)->pSig = nuevo;
		nuevo->pSig = *actual;
	}
}

void listarPermanencias(pNodo inicio) {
	int tiempoTotal;
	while (inicio != NULL) {
		if (inicio->entrada.h != -1 && inicio->salida.h != -1) {
			tiempoTotal = (inicio->salida.h * 60 + inicio->salida.m) - (inicio->entrada.h * 60 + inicio->entrada.m);
			printf("%s\n%d\n%d:%d\n", inicio->nombreApellido, inicio->legajo, tiempoTotal / 60, tiempoTotal % 60);
		}
		inicio = inicio->pSig;
	}
}

void listarInconsistencias(pNodo inicio, FILE * arch) {
	printf("Personas con inconsistencias: \n");
	char caracter;
	caracter = fgetc(arch);
	while (inicio != NULL) {
		if (inicio->entrada.h == -1 || inicio->salida.h == -1) {
			if (caracter == 'E')
				printf("INGRESO SIN SALIDA:\n%s\n%d\n", inicio->nombreApellido, inicio->legajo);
			else
				printf("INGRESO SIN ENTRADA:\n%s\n%d\n", inicio->nombreApellido, inicio->legajo);
			caracter = fgetc(arch);
		}
		inicio = inicio->pSig;
	}
}