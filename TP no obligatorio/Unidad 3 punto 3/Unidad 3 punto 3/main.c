/*
Realizar una función que calcule y devuelva la cantidad de palabras 
(separadas por uno o más guiones) que tiene una frase y escribir un programa que permita verificar su funcionamiento.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 256

void ingresarCadena(char cadena[], int n, char mensaje[]);
int separarCadena(char cadena[]);

int main(void){
	char cadena[TAM];
	ingresarCadena(cadena, TAM, "Ingrese palabra separada con uno o mas guiones (-): \n");
	separarCadena(cadena);
	printf("La cantidad de palabras existentes son de: %d\n", separarCadena(cadena));
	system("pause");
	return 0;
}


void ingresarCadena(char cadena[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(cadena, TAM, stdin);
	while (cadena[i] != '\n' && cadena[i] != '\0') {
		i++;
	}
	if (cadena[i] != '\n')
		cadena[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}


/*
int separarCadena(char cadena[]) {
	int i, cant_palabras = 0;
	int longitud = strlen(cadena);
	for (i = 0; i < longitud; i++) {
		if (cadena[i] == '-' && i > 0 && cadena[i-1] != '-') {
			cant_palabras++;
		}
		if (cadena[i] == '--' && i > 0 && cadena[i - 1] != '--') {
			cant_palabras++;
		}
	}
	return cant_palabras;
}*/


int separarCadena(char cadena[]) {
	int i, cant_palabras = 0;
	int longitud = strlen(cadena);
	for (i = 0; i < longitud; i++) {
		if (cadena[i] == '-' && cadena[i - 1] != '-') {
			cant_palabras++;
		}
		if (cadena[i] == '--'  && cadena[i - 1] != '--') {
			cant_palabras++;
		}
	}
	return cant_palabras;
}