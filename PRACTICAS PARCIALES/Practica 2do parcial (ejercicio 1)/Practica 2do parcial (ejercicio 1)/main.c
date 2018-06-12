/*
Enunciado:

Hacer un programa que permita cargar datos de pacientes
de una clínica, desde un archivo de texto.
Los datos a ingresar son:

Apellido y nombre
Número de documento
Fecha de nacimiento
Número de teléfono

No se conoce la cantidad de pacientes registrados en el archivo.
Mostrar luego por pantalla los datos ingresados, ordenados
alfabéticamente por el apellido y nombre.

Informar además la cantidad de pacientes menores de 55 años,
la cantidad de pacientes de entre 55 y 65 años y la cantidad de
mayores de 65 años .

Notar que no se solicita la realización de menú alguno.
Haccer un archivo con datos para probar el programa.

La interpretación del enunciado forma parte del examen por
lo que no se atenderán consultas al respecto. Si nota la falta
de algún dato deberá adoptarlo sin consultar y documentarlo
adecuadamente.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LNOM 32

typedef struct f {
	int d, m, a;
}nacim;

typedef struct n {
	char nombreApellido[LNOM];
	int dni;
	int telefono;
	nacim fNacim;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void insertarEnOrden(pNodo *inicio, pNodo nuevo);
void mostrarLista(pNodo inicio);

int main() {
	pNodo inicio = NULL;
	pNodo nuevo = NULL;
	char aux[100];
	FILE * arch = fopen("Empleados.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura");
	}
	fgets(aux, 100, arch);
	while (!feof(arch)) {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo != NULL) {
			sacarEnter(aux);
			strcpy(nuevo->nombreApellido, aux);
			fgets(aux, 100, arch);
			nuevo->dni = atoi(aux);//pasa de string a int
			fscanf(arch, "%d", &nuevo->telefono);
			fgetc(arch);
			fscanf(arch, "%d/%d/%d", &nuevo->fNacim.d, &nuevo->fNacim.m, &nuevo->fNacim.a);
			fgetc(arch);
			insertarEnOrden(&inicio, nuevo);
		}
		fgets(aux, 100, arch);
	}
	fclose(arch);
	mostrarLista(inicio);
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

void insertarEnOrden(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) { //insertar en lista vacia
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if (strcmp(nuevo->nombreApellido, (*inicio)->nombreApellido) < 0) { //orden alfabetico
		nuevo->pSig = *inicio;
		*inicio = nuevo;
	}
	else {
		actual = *inicio;
		anterior = NULL;
		while (actual != NULL && strcmp(nuevo->nombreApellido, (*inicio)->nombreApellido) >= 0) { // avance en la lista a siguientes nodos
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) { //insertar al final de la lista
			nuevo->pSig = NULL;
			anterior->pSig = nuevo;
		}
		else { //insertar entre nodos
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
	}
}


void mostrarLista(pNodo inicio) {
	int fechaActual=0,a65=0, a55=0, m55=0, m65=0, de55a65=0, fechaPaciente=0;
	nacim fechaHoy;
	printf("Ingrese fecha actual (dd/mm/aaaa):");
	scanf("%d/%d/%d", &fechaHoy.d, &fechaHoy.m, &fechaHoy.a);
	fgetc(stdin);
	fechaActual = ((fechaHoy.a * 10000) + (fechaHoy.m * 100) + fechaHoy.d);
	a65 = fechaActual - (65 * 10000);
	a55 = fechaActual - (55 * 10000);
	while (inicio != NULL) {
		fechaPaciente = ((inicio->fNacim.a * 10000) + (inicio->fNacim.m * 100) + inicio->fNacim.d);
		if (fechaPaciente < a55)
			m55++;
		else if (fechaPaciente > a65)
			m65++;
		else
			de55a65++;
		printf("\nNombre:%s\nDNI:%d\nFecha nacimiento:%d/%d/%d\nTelefono:%d\n ---(nodo siguiente)---> \n", inicio->nombreApellido, inicio->dni, inicio->fNacim.d, inicio->fNacim.m, inicio->fNacim.a, inicio->telefono);
		inicio = inicio->pSig;
	}
	printf("Menores a 55: %d, Mayores a 65: %d, Entre 55 y 65: %d\n", m55, m65, de55a65);
}

