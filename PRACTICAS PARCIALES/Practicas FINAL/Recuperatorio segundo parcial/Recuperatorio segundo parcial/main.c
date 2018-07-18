/*
	Se dispone de un archivo de texto "ControlEntrada.txt" con la siguiente estructura:
		
		Nombre
		Movimiento(I: ingreso - E: egreso)
		hora:minutos (ingreso/egreso)

	Se pide realizar un programa que muestre por pantalla un listado con
	los nombres de todas aquellas personas que registren alguna de las siguientes
	inconsistencias: 
		sólo ingresaron.
		sólo egresaron.
		ingresaron o egresaron más de una vez consecutiva y cuál fue la inconsistencia.
	
	Informar además el porcentaje de personas que:
		Sólo ingresaron
		Sólo egresaron
		y la cantidad total de todas las inconsistencias.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGO 32

typedef struct {
	int hh, mm;
}horario;

typedef struct n {
	char nombre[LARGO];
	char paso[2];
	horario horaE;
	horario horaS;
	int cantMov;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void vincular(pNodo **inicio, pNodo nuevo, pNodo *anterior, pNodo *actual);
void comprobarHorario(pNodo *inicio, pNodo nuevo);
void listarInconsistencias(pNodo inicio);
void listarTodo(pNodo inicio);

int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo = NULL;
	char aux[LARGO];
	FILE * arch = fopen("ControlEntradas.txt", "rt");
	if (arch == NULL) {
		printf("Error en la apertura");
	}
	fgets(aux, LARGO, arch);
	while (!feof(arch)) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo != NULL) {
			nuevo->cantMov = 0;
			sacarEnter(aux);
			strcpy(nuevo->nombre, aux);
			fgets(aux, LARGO, arch);
			sacarEnter(aux);
			strcpy(nuevo->paso, aux);
			if (aux[0] == 'E') {
				fscanf(arch, "%d:%d", &nuevo->horaE.hh, &nuevo->horaE.mm);
				fgetc(arch);
				nuevo->cantMov = nuevo->cantMov + 1;
				nuevo->horaS.hh = -1;
			}
			else {
				fscanf(arch, "%d:%d", &nuevo->horaS.hh, &nuevo->horaS.mm);
				fgetc(arch);
				nuevo->cantMov = nuevo->cantMov + 1;
				nuevo->horaE.hh = -1;
			}
			
		}
		else {
			printf("No hay espacio intente mas tarde.");
		}
		fgets(aux, LARGO, arch);
		comprobarHorario(&inicio, nuevo);
	}
	listarInconsistencias(inicio);
	listarTodo(inicio);
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

void comprobarHorario(pNodo *inicio, pNodo nuevo) {
	int flag = 0;
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	while (actual != NULL) {
		if (strcmp(actual->nombre, nuevo->nombre) == 0) {
			flag = -1;
			if (actual->horaE.hh != -1 && nuevo->horaS.hh != -1) { //ya hubo una entrada antes 
				actual->horaS.hh = nuevo->horaS.hh;
				actual->horaS.mm = nuevo->horaS.mm;
			}
			else if (actual->horaS.hh != -1 && nuevo->horaE.hh != -1) { //ya hubo una salida antes
				actual->horaE.hh = nuevo->horaE.hh;
				actual->horaE.mm = nuevo->horaE.mm;
			}
		}
		anterior = actual;
		actual = actual->pSig;
	}
	if (flag == 0) 
		vincular(&inicio, nuevo, &anterior, &actual);
}

void vincular(pNodo **inicio, pNodo nuevo, pNodo *anterior, pNodo *actual) {
	if (**inicio == NULL) {
		nuevo->pSig = NULL;
		**inicio = nuevo;
	}
	else if (*actual == NULL) {
		(*anterior)->pSig = nuevo;
		nuevo->pSig = *actual;
	}
}

void listarInconsistencias(pNodo inicio) {
	printf("<<---Personas con inconsistencias--->>:\n");
	while (inicio != NULL) {
		if (inicio->horaE.hh == -1 || inicio->horaS.hh == -1) {
			printf("Nombre: %s\n Movimiento: %s\n", inicio->nombre, inicio->paso);
		}
		inicio = inicio->pSig;
	}
}

void listarTodo(pNodo inicio) {
	printf("<<---TODAS LAS PERSONAS--->>:\n");
	while (inicio != NULL) {
		printf("Nombre: %s\n %d", inicio->nombre, inicio->cantMov);
		inicio = inicio->pSig;
	}
}
