#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 250

void ingresarCadena(char cadena[], int n , char mensaje[]);
void invertirCadena(char cadena[]);
//int longitud(char cadena[]);

int main(void) {
	char cadena[TAM];
	ingresarCadena(cadena, TAM, "Ingrese cadena de caracteres: ");
	invertirCadena(cadena);
	printf("%s \n", cadena);
	system("pause");
	return 0;
}


void ingresarCadena(char cadena[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(cadena, n, stdin);
	while (cadena[i]!='\n' && cadena[i]!='\0') {
		i++;
	}
	if (cadena[i] == '\n')
		cadena[i] = '\0';
	else
		while (fgetc(stdin) != '\0')
			;
}

/*
int longitud(char cadena[]) {
	int i = 0;
	while (cadena[i] != '\0') {
		i++;
	}
	return i;
}
*/

void invertirCadena(char cadena[]) {
	int ini = 0;
	// OTRA MANERA DE REALIZAR SABER EL TAMAÑO DE LA LONGITUD DE LA CADENA ES CON EL USO DE strlen
	//int fin = longitud(cadena) - 1;
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