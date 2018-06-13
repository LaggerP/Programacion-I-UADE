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
#include <stdlib.h>
#include <string.h>

#define LARGO 32

typedef struct fecha {
	int d, m, a;
}fNacim;

typedef struct n {
	char nombreApellido[LARGO];
	int dni;
	fNacim nacimiento;
	int telefono;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void vincularEnOrden(pNodo *inicio, pNodo nuevo);
void listarPacientes(pNodo inicio);

int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo;
	char aux[LARGO];
	FILE * arch = fopen("Pacientes.txt", "rt");
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
				strcpy(nuevo->nombreApellido, aux);
				fscanf(arch, "%d", &nuevo->dni);
				fgetc(arch);
				fscanf(arch, "%d/%d/%d", &nuevo->nacimiento.d, &nuevo->nacimiento.m, &nuevo->nacimiento.a);
				fgetc(arch);
				fscanf(arch, "%d", &nuevo->telefono);
				fgetc(arch);
			}
			fgets(aux, LARGO, arch);
			vincularEnOrden(&inicio, nuevo);
		}
	}
	listarPacientes(inicio);
	system("pause");
	return 0;
}

void sacarEnter(char aux[]) {
	char *p = strchr(aux, '\n');
	if (p != NULL) {
		*p = '\0';
	}
	else
		while (fgetc(stdin) != '\n')
			;
}

void vincularEnOrden(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) { //insertar al inicio de lista vacia
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if (strcmp(actual->nombreApellido, nuevo->nombreApellido)>0) { //ingresa al inicio de lista NO vacia
		nuevo->pSig = actual;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL && strcmp(actual->nombreApellido, nuevo->nombreApellido) < 0) { //recorre lista
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) { //ingresa al final
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
		else {
			anterior->pSig = nuevo; //ingreso entre nodos
			nuevo->pSig = actual;
		}
	}
}

void listarPacientes(pNodo inicio) {
	int menores55=0, mayores65=0, entre55y65=0, a55, a65;
	int diaHoy = 0;
	fNacim nacim;
	printf("Ingrese la fecha del dia de hoy: (dd/mm/aaaa)\n");
	scanf("%d/%d/%d", &nacim.d, &nacim.m, &nacim.a);
	fgetc(stdin);
	diaHoy = ((nacim.a * 10000) + (nacim.m * 100) + nacim.d);
	a55 = diaHoy - (55 * 10000);
	a65 = diaHoy - (65 * 10000);
	while (inicio != NULL) {
		int fechaPaciente = ((inicio->nacimiento.a * 10000) + (inicio->nacimiento.m * 100) + inicio->nacimiento.d);
		if (fechaPaciente < a55)
			menores55++;
		else if (fechaPaciente > a65)
			mayores65++;
		else
			entre55y65++;
		printf("Nombre: %s\n DNI: %d\n Fecha nacimiento: %d/%d/%d\n Telefono: %d\n", inicio->nombreApellido, inicio->dni, inicio->nacimiento.d, inicio->nacimiento.m, inicio->nacimiento.a, inicio->telefono);
		inicio = inicio->pSig;
	}
	printf("----------------------------------\n");
	printf("PACIENTES MENORES A 55: %d\nPACIENTES MAYORES A 65: %d\nPACIENTES ENTRE 55 Y 65: %d\n", menores55, mayores65, entre55y65);
}