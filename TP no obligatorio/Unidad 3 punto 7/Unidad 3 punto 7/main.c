/*
Realizar una función que inserte una sub-cadena en una cadena a partir de una posición dada, para cada uno de los siguientes casos: 
	Sin usar funciones de biblioteca standard
	Usando funciones de biblioteca standard  
Escribir un programa que permita verificar el funcionamiento de ambas funciones.
*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 64

void ingresarCadena(char cadena[], int n, char mensaje[]);
int ingresarSubCadena(char cadena[], int n, char subCadena[]);

int main(void) {
	char cadena[TAM], subCadena[TAM];
	ingresarCadena(cadena, TAM, "Ingrese cadena de caracteres: \n");
	ingresarSubCadena(cadena, TAM, subCadena);
	printf("La cadena concatenada quedria: %s", cadena);
	system("pause");
	return 0;
}

void ingresarCadena(char cadena[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(cadena, n, stdin);
	while (cadena[i] != '\n' && cadena[i] != '\0')
		i++;
	if (cadena[i] == '\n')
		cadena[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

// pasos a realizar para ingresar subcadena

//	1)copiar cadena a cadena auxiliar
//	2)cortar cadena segun posicion
//	3)concatenar cadena cortada inicio con sub cadena
//	4)concatenar cadena cortada final con subcadena

int ingresarSubCadena(char cadena[], int n, char subCadena[]) {
	int posicionCadena = 0;
	int i,j;
	int longitud = strlen(cadena);
	char cadenaAuxiliar[TAM];
	char cadenaAuxiliar2[TAM];
	printf("Ingrese posicion en donde desea ingresar la nueva cadena: \n");
	scanf("%d", &posicionCadena);
	fgetc(stdin);
	ingresarCadena(subCadena, TAM, "Ingrese sub cadena:\n");
	for (i = 0; i <= posicionCadena; i++) {
		cadenaAuxiliar[i] = cadena[i];
		for (j = longitud; j >= longitud - posicionCadena; j--)
			cadenaAuxiliar2[j] = cadena[j];
	}

	strcat(cadenaAuxiliar, subCadena);
	strcat(cadenaAuxiliar, cadenaAuxiliar2);
	strcpy(cadena, cadenaAuxiliar);
	return 0;
}

