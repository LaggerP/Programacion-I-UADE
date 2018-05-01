/*
Leer y mostrar en pantalla los datos de un archivo binario
(puede estar cargado a mano, no es necesario hacer una función para guardarlo) que devuelva primero el nombre,
luego el monto total de las ventas y luego la última fecha de las ventas. El output deberá estar ordenado,
de manera descendente, por el monto total de las ventas.

Un ejemplo de los datos del archivo:

Rodriguez, Pablo Juan
1000.00
10/04/2010
2938.20
23/05/2010
Dominguez, Ana laura
453.00
20/06/2011
Lopez, Jorge Domingo
5300.20
19/07/2011
1469.60
23/05/2011
800.00
10/04/2012

Ejemplo de qué debería devolver el sistema:

Lopez, Jorge Domingo 	Monto total de ventas: 7569.80		Fecha de última venta: 10/04/2012
Rodriguez, Pablo Juan	Monto total de ventas: 3938.20		Fecha de última venta: 23/05/2010
Dominguez, Ana Laura	Monto total de ventas: 453.00		Fecha de última venta: 20/06/2011
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LNOM 32
#define TAM 10


typedef struct {
	int d, m, a;
} fecha;

typedef struct {
	char nombre[LNOM];
	int monto;
	fecha fVentas;
}persona;

int altas(persona v[], int c);
void ingresarCadena(char nom[], int n, char mensaje[]);
void ordenarDescendente(persona v[], int c);
void mostrar(persona v[], int c);

int leerArchivo(persona v[]);
int tamArchivo(FILE * arch);
void grabarArchivo(persona v[], int c);


int main(void) {
	persona vector[TAM];
	printf("|--------------------------BIENVENIDO--------------------------|\n");
	int cant = leerArchivo(vector);
	cant = altas(vector, cant);
	ordenarDescendente(vector, cant);
	mostrar(vector, cant);
	grabarArchivo(vector, cant);
	system("pause");
	return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////// FUNCIONES //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int altas(persona v[], int c) {
	char nom[LNOM];
	ingresarCadena(nom, LNOM, "Ingrese nombre: ");
	while (c < TAM && nom[0] != '\0' ) {
		strcpy(v[c].nombre, nom);
		printf("Ingrese monto: ");
		scanf("%d", &v[c].monto);
		fgetc(stdin);
		printf("Ingrese fecha: (dd/mm/aaaa) ");
		scanf("%d/%d/%d", &v[c].fVentas.d, &v[c].fVentas.m, &v[c].fVentas.a);
		fgetc(stdin);
		c++;
		if (c < TAM)
			ingresarCadena(nom, LNOM, "Ingrese nombre (enter para finalizar): ");
	}
	return c;
}

void ingresarCadena(char nom[], int n, char mensaje[]) {
	printf("%s",mensaje);
	fgets(nom, LNOM, stdin);
	int i = 0;
	while (nom[i] != '\0' && nom[i] != '\n')
		i++;
	if (nom[i] == '\n')
		nom[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}
//ORDENAR DE FORMA DESCENDIENTE TENIENDO EN CUENTA EL MONTO DE VENTA.
void ordenarDescendente(persona v[], int c) {
	FILE * arch = fopen("archivoVentas.dat", "rb");
	if (arch == NULL)
		printf("Error de apertura!\n");
	persona temp;
	for (int i = 1; i < c; i++) {
		for (int j = 0; j < c - 1; j++) {
			if (v[j].monto < v[j + 1].monto) {
				temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}
	}
}

void mostrar(persona v[], int c) {
	int j;
	for (j = 0; j < c; j++) {
		printf("Nombre: %s \t Monto total de ventas: %d\t Fecha ultima venta: %d/%d/%d\n", v[j].nombre, v[j].monto, v[j].fVentas.d, v[j].fVentas.m, v[j].fVentas.a);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////  MANEJO DE ARCHIVOS /////////////////////////////////////////////////////////////////////////////////////////////////////////

int leerArchivo(persona v[]) {
	int cant = 0;
	FILE * arch = fopen("archivoVentas.dat", "rb");
	if (arch == NULL) {
		printf("Error de apertura\n");
		return 1;
	}
	cant = tamArchivo(arch);
	for (int i = 0; i < cant; i++)
		fread(&v[i], sizeof(persona), 1, arch);
	fclose(arch);
	return cant;
}

int tamArchivo(FILE * arch) {
	int t;
	fseek(arch, 0, SEEK_END); //nos posiciona al final del archivo;
	t = ftell(arch); //nos devuelve el tamaño del archivo en bytes
	fseek(arch, 0, SEEK_SET); //nos posiciona al principio del archivo
	return t;
}

void grabarArchivo(persona v[], int c) {
	int i;
	FILE * arch = fopen("archivoVentas.dat", "wb");
	if (arch == NULL)
		printf("Error de apertura\n");
	for (i = 0; i < c; i++)
		fwrite(&v[i], sizeof(persona), 1, arch);
	fclose(arch);
}