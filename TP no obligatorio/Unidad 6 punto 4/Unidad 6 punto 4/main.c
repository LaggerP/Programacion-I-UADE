/*
	Realizar un  programa que permita grabar un archivo los datos de lluvia caída durante un año únicamente en los días que haya llovido, 
	con el siguiente formato por cada línea (<dia>; <mes>; <lluvia caída en mm>). 
	La cantidad de lluvia caida no supera los 999 mm por día. 
	Mostrar en formato matricial tal que la columna indica el mes y las filas corresponden a los dias del mes. 
	Además mostrar la lluvia promedio caida en los meses pares.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COL 12-1
#define FIL 31-1
#define TAM 10
#define LLUVIAMAX 999

void cargarMatriz(int dia, int mes, int pp, int cantt);
void leer_el_archivo(int dia, int mes, int pp, int cantt);

int main(void) {
	int cant = FIL * COL;
	int dia = 0, mes = 0, pp = 0;
	cargarMatriz(dia, mes, pp, cant);
	leer_el_archivo(dia,mes,pp,cant);
	system("pause");
	return 0;
}

void cargarMatriz(int dia, int mes, int pp, int cant) {
	int i = 0;
	FILE * arch = fopen("archivoPunto4.txt", "wt");
	if (arch == NULL) {
		printf("error de apertura!");
		return;
	}
	int salir = 1;
	while (i < cant && !salir) {
		printf("Ingrese dia / mes / cantidad de pp (en mm): \n");
		fprintf(arch,"%d,%d,%d", dia, mes, pp);
		fgetc(stdin);
		i++;
		printf("0 para salir");
		scanf("%d", &salir);
		fgetc(stdin);
	}
	fclose(arch);
	return 0;
}


void leer_el_archivo(int dia, int mes, int pp, int cant) {
	FILE * arch = fopen("archivoPunto4.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura.\n");
		return;
	}
	fscanf(arch, "%d,%d,%d", &dia, &mes, &pp);
	fgetc(stdin);
	while (!feof(arch)) {
		fscanf(arch, "%d,%d,%d", &dia, &mes, &pp);
		fgetc(stdin);
	}
	fclose(arch);
}