/*
Realizar una funci�n que reciba una cadena y coloque en may�scula la primera letra siguiente a un espacio eliminando dichos espacios.
Escribir un programa que permita verificar su funcionamiento.

Ejemplo:

Cadena original:  Platero es peque�o, peludo, suave; tan blando por fuera, que se dir�a todo de algod�n, que no lleva huesos. S�lo los espejos de azabache de sus ojos son duros cual dos escarabajos de cristal negro.
Cadena final: PlateroEsPeque�o,Peludo,Suave;TanBlandoPorFuera,QueSeDir�aTodoDeAlgod�n,QueNoLlevaHuesos.S�loLosEspejosDeAzabacheDeSusOjosSonDurosCualDosEscarabajosDeCristalNegro.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define LARGO 64

void ingresarCadena(char cadena[], int n, char mensaje[]);
void modificarCadena_Mayus(char cadena[]);

int main(void) {
	char cadena[LARGO];
	ingresarCadena(cadena, LARGO, "Ingrese cadena deseada:\n");
	modificarCadena_Mayus(cadena);
	printf("La cadena quedaria: %s\n", cadena);
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

void modificarCadena_Mayus(char cadena[]) {
	int i;
	int j = 0;
	int longitud = strlen(cadena);
	char anterior = ' ';
	for (i = 0; i<longitud; i++) {
		if (cadena[i] != ' ') {
			if (anterior == ' ') {   // Si esta en el rango de las minisculas, la lleva al rango de las mayuculas
				if (cadena[i] >= 97 && cadena[i] <= 122)
					cadena[j++] = cadena[i] - 32;
			}
			else
				cadena[j++] = cadena[i]; //saca el espacio entre palabras
		}
		anterior = cadena[i];
	}
	cadena[j] = 0;
}
