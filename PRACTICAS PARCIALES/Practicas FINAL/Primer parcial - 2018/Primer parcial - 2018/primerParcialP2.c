//SEGUNDO PROGRAMA DE LA CONSIGNA DEL PARCIAL


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LARGO 32
typedef struct {
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


int main(void) {
	paciente aux;
	FILE * arch = fopen("Pacientes.dat", "rb");
	if (arch == NULL) {
		printf("Error de apertura");
	}
	fread(&aux, sizeof(paciente), 1, arch);
	while (!feof(arch)) {
		printf("Nombre: %s\nDNI: %d\nObra Social: %s\n, Hora: %d:%d\n Nacimiento: %d/%d/%d", aux.nomApellido, aux.dni, aux.obraSocial, aux.hora.hh, aux.hora.mm, aux.nacimiento.d, aux.nacimiento.m, aux.nacimiento.a);
		fread(&aux, sizeof(paciente), 1, arch);
	}
	fclose(arch);
	system("pause");
	return 0;
}