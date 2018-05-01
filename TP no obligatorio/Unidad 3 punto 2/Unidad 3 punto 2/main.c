/*
Realizar una función que determine si una cadena de caracteres es capicúa, 
sin utilizar vectores auxiliares y escribir un programa que permita verificar su funcionamiento. 
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 250

void ingresarCadena(char cadena[], int n, char mensaje[]);
void cadenaCapicua(char cadena[]);
void invertirCadena(char cadena[]);

int main(void){
	printf("\t\t\t\tPROGRAMA QUE COMPRUEBA SI PALABRAS SON CAPICUAS\n\n");
	char cadena[TAM];
	ingresarCadena(cadena, TAM, "Ingrese la palabra que desee comprobar\n");
	cadenaCapicua(cadena);
	system("pause");
}

void ingresarCadena(char cadena[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(cadena, n, stdin);
	while (cadena[i] != '\n' && cadena[i] != '\0') {
		i++;
	}
	if (cadena[i] == '\n')
		cadena[i] = '\0';
	else
		while (fgetc(stdin)!='\0')
			;
}

void cadenaCapicua(char cadena[]) {
	char aux[TAM];
	strcpy(aux, cadena);
	invertirCadena(aux);
	if (strcmp(cadena,aux)==0) {
		printf("||||--> Las cadenas son capicuas <--||||\n");
	}
	else
		printf("||||--> Las cadenas NO son capicuas <--||||\n");
}


void invertirCadena(char cadena[]) {
	int ini = 0;
	int fin = strlen(cadena) - 1;
	char aux;
	while (ini < fin) {
		aux = cadena[ini];
		cadena[ini] = cadena[fin];
		cadena[fin] = aux;
		ini++;
		fin--;
	}
}