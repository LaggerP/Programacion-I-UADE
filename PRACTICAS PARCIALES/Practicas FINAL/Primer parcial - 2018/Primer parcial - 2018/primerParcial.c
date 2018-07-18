/**
	Enunciado:
		Un consultorio médico desea llevar el registro de los turnos de un día de
		sus pacientes. La cantidad de pacientes que atiende en un día no supera
		los 40. Para ello dispone de la siguiente información de cada paciente:
				* Apellido y nombre
				* DNI
				* Obra social
				* Turno en horas y minutos
				* Fecha de nacimiento

	Hacer un programa que:
		1 - Cargue un vector con la información suministrada. El orden de
		carga de los pacientes es aleatoria.
		2 - Ordenar información por turnos
		3 - Mostrar los pacientes con edad inferior a 2 años y mayores de 60
		4 - Grabar en un archivo binario los datos de los pacientes de entre 2 y 60 años

	Realizar otro programa  que lea el archivo creado y muestre los datos.

	Para aprobar se requiere tener el 50% de los conceptos de vector de estructuras,
	cadenas y archivos.

	Valor de cada punto
	Punto 1, 2, 3: 2 puntos cada uno
	Punto 4 y 5: 1 punto cada uno
**/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGO 32
#define TAM 40


typedef struct{
	int hh, mm;
}tiempo;

typedef struct {
	int d, m, a;
}fecha;

typedef struct {
	char nomApellido[LARGO];
	int dni;
	char obraSocial[LARGO];
	tiempo hora;
	fecha nacimiento;
}paciente;


void ingresarCadena(char aux[], int n, char mensaje[]);
int alta(paciente v[]);
void ordenarPorTurnos(paciente v[], int c);
void mostrar(paciente v[], int c);


int main(void) {
	paciente vector[TAM];
	int cant = alta(vector);
	ordenarPorTurnos(vector, cant);
	mostrar(vector, cant);
	system("pause");
	return 0;
}

int alta(paciente v[]) {
	char aux[LARGO];
	int cant = 0;
	ingresarCadena(aux, LARGO, "Ingrese apellido y nombre (enter para finaliza)\n");
	while (cant<TAM && aux[0] != '\0') {
		strcpy(v[cant].nomApellido, aux);
		printf("Ingrese DNI:\n");
		scanf("%d", &v[cant].dni);
		fgetc(stdin);
		ingresarCadena(aux, LARGO, "Ingrese obra social:\n");
		strcpy(v[cant].obraSocial, aux);
		printf("Ingrese horario turno:\n");
		scanf("%d:%d", &v[cant].hora.hh, &v[cant].hora.mm);
		fgetc(stdin);
		printf("Ingrese fecha nacimiento (dd/mm/aa):\n");
		scanf("%d/%d/%d", &v[cant].nacimiento.d, &v[cant].nacimiento.m, &v[cant].nacimiento.a);
		fgetc(stdin);
		cant++;
		if (cant < TAM) {
			ingresarCadena(aux, LARGO, "Ingrese apellido y nombre (enter para finaliza)\n");
		}
	}
	return cant;
}

void ingresarCadena(char aux[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(aux, LARGO, stdin);
	while (aux[i]!='\n' && aux[i]!='\0') 
		i++;
	if (aux[i] == '\n')
		aux[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void ordenarPorTurnos(paciente v[], int c) {
	paciente aux;
	for (int i = 0; i < c; i++) {
		if ((v[i].hora.hh) * 60 + v[i].hora.mm > (v[i + 1].hora.hh) * 60 + v[i + 1].hora.mm) {
			aux = v[i];
			v[i + 1] = v[i];
			v[i] = v[i + 1];
		}
	}
}

void mostrar(paciente v[], int c) {
	int i, edad;
	fecha aux;
	FILE * arch = fopen("Pacientes.dat", "wb");
	if (arch = NULL) {
		printf("Error de apertura");
	}
	printf("Ingrese fecha del día de hoy (dd/mm/aa):\n");
	scanf("%d/%d/%d", &aux.d, &aux.m, &aux.a);
	fgetc(stdin);
	for (i = 0; i < c; i++) {
		edad = ((aux.a - v[i].nacimiento.a) * 10000 + (aux.m - v[i].nacimiento.m) * 100 + (aux.d - v[i].nacimiento.d))/10000;
		if (edad < 2 || edad > 60)
			printf("Nombre:%s\nNacimiento: %d/%d/%d\n", v[i].nomApellido, v[i].nacimiento.d, v[i].nacimiento.m, v[i].nacimiento.a);
		else 
			fwrite(&v[i], sizeof(paciente), 1, arch);
	}
	fclose(arch);
}