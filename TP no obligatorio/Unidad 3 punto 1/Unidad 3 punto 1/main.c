/*Realizar una función que invierta los caracteres de una cadena, 
sin utilizar vectores auxiliares y escribir un programa que permita verificar su funcionamiento.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 256

void ingresarCadena(char cadena[], int n, char mensaje[]);
void invertirCadena(char cadena[]);

int main(void) {
	char cadena[TAM];
	char cadena2[TAM];
	ingresarCadena(cadena, TAM, "Ingrese cadena de caracteres: \n");
	invertirCadena(cadena);
	printf("\n\nCadena invertida: %s\n\n", cadena);
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
	if (cadena[i] == '\n')
		cadena[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void invertirCadena(char cadena[]) {
	int i,j, longitud = 0;
	int aux;
	longitud = strlen(cadena);
	for (i = 0, j=longitud-1; i<longitud/2; i++, j--) {
		aux = cadena[i];
		cadena[i] = cadena[j];
		cadena[j] = aux;
	}
}