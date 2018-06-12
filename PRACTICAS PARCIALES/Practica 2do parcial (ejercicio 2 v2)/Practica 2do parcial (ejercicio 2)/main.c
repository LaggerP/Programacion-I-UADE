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

#define LARGO 32


typedef struct hora {
	int h, m;
}horario;

typedef struct n {
	char NombreApellido[LARGO];
	int legajo;
	char paso; //E o S
	horario entrada, salida;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void compararHorarios(pNodo *inicio, pNodo nuevo);
void vincular(pNodo **inicio, pNodo nuevo, pNodo *actual, pNodo *anterior);
void listarPermanencia(pNodo inicio);
void listarInconsistencias(pNodo inicio, FILE * arch);


int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo;
	char aux[10];
	FILE * arch = fopen("Empleados.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura");
		return 1;
	}
	else {
		fgets(aux, 100, arch);
		while (!feof(arch)) {
			nuevo = (pNodo)malloc(sizeof(nodo));
			if (nuevo != NULL) {
				sacarEnter(aux);
				strcpy(nuevo->NombreApellido, aux);
				fscanf(arch, "%d", &nuevo->legajo);
				fgetc(arch);
				fgets(aux, 100, arch);
				if (aux[0] == 'E') {
					fscanf(arch, "%d:%d", &nuevo->entrada.h, &nuevo->entrada.m);
					fgetc(arch);
					nuevo->salida.h = -1;//Se encontro solo entrada - generacion de inconsistencia.
				}
				else if (aux[0] == 'S') {
					fscanf(arch, "%d:%d", &nuevo->salida.h, &nuevo->salida.m);
					fgetc(arch);
					nuevo->entrada.h = -1;//Se encontro solo salida - generacion de inconsistencia.
				}
			}
			else {
				printf("Espacio insuficiente");
				return 1;
			}
			fgets(aux, 100, arch);
			compararHorarios(&inicio, nuevo);
		}
	}
	listarPermanencia(inicio);
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
		
		if (actual->legajo == nuevo->legajo) { //si el legajo es igual
			flag = 1;
			if (actual->entrada.h!= -1 && nuevo->salida.h!= -1){ // ingreso de una entrada 
				actual->salida.h = nuevo->salida.h;
				actual->salida.m = nuevo->salida.h;
			}
			else if (actual->salida.h!= -1 && nuevo->entrada.h!= -1) { // ingreso de una salida 
				actual->entrada.h = nuevo->entrada.h;
				actual->entrada.m = nuevo->entrada.m;
			}
		}
		anterior = actual;
		actual = actual->pSig;
	}
	if (flag == 0) //si actual es = a NULL significa que la lista esta vacia por lo que que hay que vincular.
		vincular(&inicio, nuevo, &actual, &anterior);
}


void vincular(pNodo **inicio, pNodo nuevo, pNodo *actual, pNodo *anterior) {
	if (**inicio == NULL) {
		nuevo->pSig = NULL;
		(**inicio) = nuevo;
	}
	else if (*actual == NULL) {
		(*anterior)->pSig = nuevo;
		nuevo->pSig = *actual;
	}
}

void listarPermanencia(pNodo inicio) {
	int tiempoTotal = 0;
	while (inicio != NULL) {
		if (inicio->salida.h != -1 && inicio->entrada.h != -1) { // si hay horario de entrada y salida
			tiempoTotal = (inicio->salida.h * 60 + inicio->salida.m) - (inicio->entrada.h * 60 + inicio->entrada.m);
			printf("Nombre: %s\n LU: %d\n Permanencia: %d:%d\n", inicio->NombreApellido, inicio->legajo, tiempoTotal / 60, tiempoTotal % 60);
		}
		inicio = inicio->pSig;
	}
}


void listarInconsistencias(pNodo inicio, FILE * arch) {
	char caracter;
	printf("---------------------------------\n");
	printf("Personas con inconsistencias: \n\n");
	caracter = fgetc(arch);
	while (inicio != NULL) {
		if (inicio->salida.h == -1 || inicio->entrada.h == -1) {
			if (caracter == 'E')
				printf("Personas sin salidas:\n LU: %d\n Nombre: %s\n", inicio->legajo, inicio->NombreApellido);
			else
				printf("Personas sin entradas:\n LU: %d\n Nombre: %s\n", inicio->legajo, inicio->NombreApellido);
			caracter = fgetc(arch);
		}
		inicio = inicio->pSig;
	}
}
