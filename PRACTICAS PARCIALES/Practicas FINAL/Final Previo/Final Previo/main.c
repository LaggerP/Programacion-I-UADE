/*
1. Escribir un programa para invertir el orden de las palabras que contiene un archivo de texto cualquiera, cuidando de no invertir las letras que componen cada palabra.
Ejemplo:  "afuera está lloviendo"   –>  "lloviendo está afuera"


2. Desarrollar un programa que permita crear una lista enlazada simple de números enteros utilizando inserción en orden. 
Luego escribir una función para invertir los últimos N nodos de la misma, donde N es un número entero pasado como parámetro. 
No se permite crear nuevos nodos durante el proceso de inversión. Imprimir la lista antes y después del proceso.


*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include <stdlib.h>

#define LARGO 32

void sacarEnter(char aux[]);
void invertirFrase(char frase[]);

int main(void) {
	char aux[LARGO];
	printf("Ingrese frase para invertir: \n");
	fgets(aux, LARGO, stdin);
	sacarEnter(aux);
	printf("Frase sin invertir: %s\n", aux);
	invertirFrase(aux);
	system("pause");
	return 0;
}

/*
Pasos para invertir.

1) saco el largo de la frase.
2) empiezo a iterar con un for desde el final al inicio -> for(int i = strlen(frase);i>=0;i--)
3) si encuentro espacio me adelando en la siguiente posicion y printeo esa letra y despues paso a la otra letra aumentando el posicionador.

*/

void invertirFrase(char frase[]) {
	int aux;
	for (int i = strlen(frase); i >= 0; i--){
		if (frase[i] == ' ') {
			aux = i + 1; //una vez que encontro el espacio se adelante a la siguiente pos del espacio (osea una letra).
			while (frase[aux] != ' ') {
				if (aux == strlen(frase))
					break;
				printf("%c", frase[aux]);
				aux++;
			}
			printf(" ");
		}
		if (i == 0) {
			aux = i;
			while (frase[aux] != ' ') {
				printf("%c", frase[aux]);
				aux++;
			}
		}
	}
}

void sacarEnter(char aux[]) {
	char *p = strchr(aux, '\n');
	if (p != NULL)
		*p = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}