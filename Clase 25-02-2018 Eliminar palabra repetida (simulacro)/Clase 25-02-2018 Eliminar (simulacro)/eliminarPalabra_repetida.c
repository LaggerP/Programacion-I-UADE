/*
	Hacer un programa que permita ingresar una frase y elimine las palabras repetidas,
	dejando una ocurrencia en lugar que aparace por primera vez.

	Ejemplo:

		ANTES--> La mañana esta lluviosa. La tarde esta nublada y la noche esta estrellada
		DESPUES--> La mañana esta lluviosa. Tarde nublada y noche estrellada

		Biblioteca <ctype.h>
			toupper(caracter)
			tolower(caracter)
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>

#define TAM 64

//funciones
void ingresarCadena(char cadena[], int n, char mensaje[]);
void separarCadena(char cadena[], char cadenaAux[]);
//int eliminarRepetidos(char cadena[], char cadenaAux[]);


int main(void) {
	char cadena[TAM];
	char cadenaAux[TAM];
	ingresarCadena(cadena, TAM, "Ingrese cadena de caracteres:\n");
	separarCadena(cadena, cadenaAux);
	//eliminarRepetidos(cadena, cadenaAux);
	//printf("1) %s\n\n", cadena);
	system("pause");
	return 0;
}

void ingresarCadena(char cadena[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(cadena, n, stdin);
	while (cadena[i] != '\0' && cadena[i] != '\n')
		i++;
	if (cadena[i] == '\n')
		cadena[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void separarCadena(char cadena[], char cadenaAux[]) {
	int longitud = strlen(cadena);
	
	
}





/*
int separarCadena(char cadena[], char cadenaAux[]) {
	strcpy(cadenaAux, cadena);
	int longitud = strlen(cadenaAux);
	int i;
	char separador[] = " "; //delimitador
	int tokenPosition;
	char *primerToken= &cadenaAux[0];
	char *palabraSeparada = strtok(cadenaAux, separador); //palabraSeparada es un token
	while (palabraSeparada != NULL) {
		tokenPosition = palabraSeparada - primerToken;
		printf("\n%s\n", palabraSeparada);
		//printf("%d\n", tokenPosition);
		for (i = 0; i < longitud; i++) {
			char *palabra_a_comparar = cadena[i];
			if (strstr(palabra_a_comparar, palabraSeparada) == 0) {
				cadena[i] = cadena[i + 1];
			}
		}
		palabraSeparada = strtok(NULL, separador);
	}
	return 0;
}


*/
/*
int eliminarRepetidos(char cadena[]) {
	int longitud = strlen(cadena);
	int i = 0;
	char palabra[TAM];
	while (i <= longitud) {
		strcpy(palabra, cadena[i]);
		if (strcmp(cadena, palabra) == 0){
			cadena[i] = cadena[i + 1];
			strcat()
		}
		i++;
	}
	return 0;
}

*/