/*
	Hacer un programa que permita:

		-Invertir cadena de caracteres.
		-Cortar cadena segun posicion dada.
		-Guardar cadena en archivo de texto binario.
		-Mostrar por pantalla las dos cadenas.

*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>	
#include <string.h>
#include <stdlib.h>

#define LARGO 64
#define TAM 1

void altaCadena(char cadena[], int c);
void invertirCadena(char cadena[]);
void cortarCadena(char cadena[]);
void mostrar(char cadena[], int c);

int main(void) {
	int opc;
	char cadena[LARGO];
	printf("1- Invertir cadena\t 2- Cortar cadena\t 3- Salir\n");
	scanf("%d", &opc);
	fgetc(stdin);
	if (opc == 1) {
		altaCadena(cadena, TAM);
		mostrar(cadena, TAM);
	}
	if (opc == 2) {
		altaCadena(cadena,TAM);
		mostrar(cadena,TAM);
	}
	if (opc == 3)
		printf("Chau\n");
	system("pause");
	return 0;
}

void altaCadena(char cadena[], int c) {
	FILE * arch = fopen("cadena.dat", "wb");
	if (arch == NULL) {
		printf("Error de apertura");
	}
	printf("Ingrese cadena: ");
	fgets(cadena, LARGO, stdin);
	//invertirCadena(cadena);
	cortarCadena(cadena);
	fputs(cadena, arch);
	fclose(arch);
}

void invertirCadena(char cadena[]) {
	int inicio = 0;
	int final = strlen(cadena) - 1;
	char aux;
	while (inicio < final) {
		aux = cadena[inicio];
		cadena[inicio] = cadena[final];
		cadena[final] = aux;
		inicio++;
		final--;
	}
}

void cortarCadena(char cadena[]) {
	int longitud = strlen(cadena);
	int posicion;
	char cadenaCortada[LARGO];
	printf("Ingrese posicion desde la que desea cortar la cadena (numero tiene que ser <= a %d): ", longitud);
	scanf("%d", &posicion);
	fgetc(stdin);
	if (posicion <= longitud) {
		printf("%s\n", strcpy(cadenaCortada, &cadena[posicion]));
	}
	
}
void mostrar(char cadena[], int c) {
	int i;
	FILE * arch = fopen("cadena.dat", "rb");
	if (arch == NULL) {
		printf("Error de apertura");
	}
	while (!feof(arch)) {
		fgets(cadena, LARGO, arch);
	}
	for (i = 0; i < c; i++) {
		printf("Cadena: %s ", cadena);
	}
}
