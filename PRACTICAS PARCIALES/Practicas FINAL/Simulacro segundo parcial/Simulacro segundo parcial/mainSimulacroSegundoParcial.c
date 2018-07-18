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

typedef struct {
	int h, m;
}horario;

typedef struct n {
	char nomape[LARGO];
	int legajo;
	char paso[2];
	horario horaE;
	horario horaS;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void compararHorarios(pNodo *inicio, pNodo nuevo);
void vincular(pNodo *inicio, pNodo nuevo);
void listar(pNodo inicio);
void listarInconsistencias(pNodo inicio);

int main(void) {
	pNodo inicio, nuevo = NULL;
	char aux[LARGO];
	FILE * arch = fopen("Empleados.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura");
	}
	fgets(aux, LARGO, arch);
	while (!feof(arch)) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo != NULL) {
			sacarEnter(aux);
			strcpy(nuevo->nomape, aux);
			fscanf(arch, "%d", &nuevo->legajo);
			fgetc(arch);
			fgets(aux, LARGO, arch);
			if (aux[0] == 'E') {
				fscanf(arch, "%d:%d", &nuevo->horaE.h, &nuevo->horaE.m);
				nuevo->horaS.h = -1;
			}
			else {
				fscanf(arch, "%d:%d", &nuevo->horaS.h, &nuevo->horaS.m);
				nuevo->horaE.h = -1;
			}
			
			fgets(aux, LARGO, arch);
		}
		else {
			printf("Sin espacio intente mas tarde");
		}
		fgets(aux, LARGO, arch);
		compararHorarios(&inicio, nuevo);
	}
	listar(inicio);
	listarInconsistencias(inicio);
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
		if (actual->legajo == nuevo->legajo) {
			flag = 1;
			if (actual->horaE.h != -1 && nuevo->horaS.h != -1) { //hubo una entrada previamente
				actual->horaS.h = nuevo->horaS.h;
				actual->horaS.m = nuevo->horaS.m;
			}
			if (actual->horaS.h != -1 && nuevo->horaE.h != -1) { //hubo una salida previamente
				actual->horaE.h = nuevo->horaE.h;
				actual->horaE.m = nuevo->horaE.m;
			}
		}
		anterior = actual;
		actual = actual->pSig;
	}
	if (flag == 0)
		vincular(inicio, nuevo);
}

void vincular(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) {
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else {
		anterior->pSig = nuevo;
		nuevo->pSig = NULL;
	}
}


void listar(pNodo inicio) {
	while (inicio != NULL) {
		if (inicio->horaE.h != -1 && inicio->horaS.h != -1) { //persona sin inconsistencia
			int tiempoTotal = (((inicio->horaE.h) * 60) + inicio->horaE.m - ((inicio->horaS.h) * 60) + inicio->horaS.m);
			printf("Nombre: %s\nLegajo: %d\nPersistencia: %d:%d", inicio->nomape, inicio->legajo, tiempoTotal / 60, tiempoTotal % 60);
		}
		inicio = inicio->pSig;
	}
}

void listarInconsistencias(pNodo inicio) {
	printf("Empleados con inconsistencias:\n");
	while (inicio != NULL) {
		if (inicio->horaE.h == -1 || inicio->horaS.h == -1) {
			
			printf("Nombre: %s\nLegajo: %d\n", inicio->nomape, inicio->legajo);
		}
		inicio = inicio->pSig;
	}
}