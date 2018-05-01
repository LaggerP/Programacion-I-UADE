/*
												-EJERCICIO SIN USO DE ARCHIVOS-
	Enunciado:

		Hacer un programa que permita realizar altas, baja y modificacion de pacientes de una clínica. El total de pacientes no es mayor a 100.
		Luego mostrar por pantalla los datos ingresados, ordenados alfabéticamente por el apellido y nombre.
		Informar además la cantidad de pacientes mayores de 55 años.
		
		Los datos a ingresar son:
			Apellido y nombre
			Número de documento
			Fecha de nacimiento.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LNOM 32
#define TAM 100

typedef struct {
	char nombreApellido[LNOM];
	int dni, d, m, a;
}pacientes;

//funciones
int altas(pacientes v[], int c);
void ingresarCadena(char nombreApellido_aux[], int n, char mensaje[]);
void ordenar(pacientes v[], int c);
void bajas(pacientes v[], int c);
void modificar(pacientes v[], int c);
void mostrar(pacientes v[], int c);

int main(void) {
	pacientes vector[TAM];
	int cant = 0;
	int opc;
	cant = altas(vector, cant);
	ordenar(vector, cant);
	mostrar(vector, cant);
	printf(" 1- Bajas\n 2- Modificar\n 3- Salir\n");
	scanf("%d", &opc);
	fgetc(stdin);
	if (opc == 1)
		bajas(vector, cant);
		ordenar(vector, cant);
		mostrar(vector, cant);
	if (opc == 2)
		modificar(vector, cant);
		ordenar(vector, cant);
		mostrar(vector, cant);
	if (opc == 3)
		printf("Hasta luego!");
	system("pause");
	return 0;
}

int altas(pacientes v[], int c) {
	char nombreApellido_aux[LNOM];
	ingresarCadena(nombreApellido_aux, LNOM, "Apellido y nombre del paciente: ");
	while (c < TAM && nombreApellido_aux[0] != '\0') {
		strcpy(v[c].nombreApellido, nombreApellido_aux);
		printf("Ingrese DNI del paciente: ");
		scanf("%d", &v[c].dni);
		fgetc(stdin);
		printf("Ingrese fecha de nacimiento del paciente: ");
		scanf("%d/%d/%d", &v[c].d, &v[c].m, &v[c].a);
		fgetc(stdin);
		c++;
		if (c<TAM)
			ingresarCadena(nombreApellido_aux, LNOM, "Apellido y nombre del paciente (enter para finalizar): ");
	}
	return c;
}

void ingresarCadena(char nombreApellido_aux[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(nombreApellido_aux, LNOM, stdin);
	while (nombreApellido_aux[i] != '\0' && nombreApellido_aux[i] != '\n')
		i++;
	if (nombreApellido_aux[i] == '\n')
		nombreApellido_aux[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void ordenar(pacientes v[], int c){
	int i, j;
	pacientes aux;
	for (i = 0; i<c - 1; i++){
		for (j = 0; j<c - 1; j++)
			if (strcmp(v[j].nombreApellido, v[j + 1].nombreApellido)>0){
				aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
	}
}


void bajas(pacientes v[], int c) {
	char nombreBaja[LNOM];
	int a = 1;
	int i;
	char *p;
	ingresarCadena(nombreBaja, LNOM, "Ingrese el APELLIDO y NOMBRE de la persona que desea eliminar: ");
	while (a == 1 && c>0) {
		i = 0;
		p = strstr(v[i].nombreApellido, nombreBaja);
		while (p == NULL && i<c) {
			i++;
			p = strstr(v[i].nombreApellido, nombreBaja);
		}
		while (i == c) {
			ingresarCadena(nombreBaja, LNOM, "Persona no encontrada. Ingrese otro Apellido y  Nombre: ");
			i = 0;
			p = strstr(v[i].nombreApellido, nombreBaja);
			if (p == NULL && i<c) {
				i++;
				p = strstr(v[i].nombreApellido, nombreBaja);
			}
		}
		while (i < c) {
			v[i] = v[i + 1];
			i++;
		}
		c--;
		if (c != 0) {
			printf("Desea eliminar a alguien mas? 1- Si   2- No");
			scanf("%d", &a);
			fgetc(stdin);
			if (a==1)
				ingresarCadena(nombreBaja, LNOM, "Ingrese el APELLIDO y NOMBRE de la persona que desea eliminar: ");
		}
	}
}


void modificar(pacientes v[], int c) {
	int i;
	int a = 1;
	char nombreModificar[LNOM];
	char *p;
	while (a == 1) {
		ingresarCadena(nombreModificar, LNOM, "Ingrese el nombre de la persona que desea modificar: ");
		i = 0;
		p = strstr(v[i].nombreApellido, nombreModificar);
		while (p == NULL && i<c) {
			i++;
			p = strstr(v[i].nombreApellido, nombreModificar);
		}
		while (i == c) {
			ingresarCadena(nombreModificar, LNOM, "No se encontro la persona. Ingrese nuevamente un apellido y nombre: ");
			i = 0;
			p = strstr(v[i].nombreApellido, nombreModificar);
			while (p == NULL && i<c) {
				i++;
				p = strstr(v[i].nombreApellido, nombreModificar);
			}
		}
		ingresarCadena(v[i].nombreApellido, LNOM, "Ingrese nuevo apellido y nombre: ");
		printf("Ingrese nuevo DNI: ");
		scanf("%d", &v[i].dni);
		fgetc(stdin);
		printf("Ingrese nueva fecha de nacimiento del paciente: ");
		scanf("%d/%d/%d", &v[i].d, &v[i].m, &v[i].a);
		fgetc(stdin);

		printf("Desea modificar a otra persona? 1- Si  2- No ");
		scanf("%d", &a);
		fgetc(stdin);
	}
}

void mostrar(pacientes v[], int c) {
	int i, mayores55=0;
	int dd, mm, aa;
	printf("Ingrese fecha del dia de hoy: dd/mm/aaaa ");
	scanf("%d/%d/%d", &dd, &mm, &aa);
	fgetc(stdin);
	for (i = 0; i < c; i++) {
		if ((v[i].a * 10000 + v[i].m * 100 + v[i].d) <= ((aa - 55) * 10000 + mm * 100 + dd))
			mayores55++;
		printf(" Apellido y nombre: %s\n DNI: %d\n Fecha de nacimiento: %d/%d/%d\n", v[i].nombreApellido, v[i].dni, v[i].d, v[i].m, v[i].a);
		
	}
	printf("La cantidad de personas mayores a 55 son: %d\n\n", mayores55);
}