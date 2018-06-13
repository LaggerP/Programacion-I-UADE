/*
Enunciado:
Una inmobiliaria posee los siguientes datos sobre un conjunto de propiedades a vender:
Tipo (Casa, depto, etc)
Zona
Domicilio
Cantidad de Habitaciones
Cochera
Antigüedad
Monto de expensas
Precio de Venta (En pesos)

Se pide:
1.	Generar un archivo con la información de los inmuebles a vender.
No es necesario realizar un programa para esto.
El archivo debe llamarse “Deptos.txt” y puede tener cualquier formato, pero en modo texto.
Los datos no están ordenados.
2.	Hacer un programa que permita leer la información desde el archivo y luego realizar un listado de todos los datos de los departamentos de una zona dada, ordenados por precio de venta.
El programa deberá solicitar el ingreso de la zona a mostrar.
Se debe utilizar administración de memoria dinámica para almacenar los datos debido a que no se conoce la cantidad de propiedades en venta.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGO 32

typedef struct n {
	char tipoInmueble[LARGO];
	char zona;
	char domicilio[LARGO];
	int habitaciones;
	char cochera; //S o N
	int antiguedad;
	int expensas;
	int precioVenta;
	struct n *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void vincularOrdenado(pNodo *inicio, pNodo nuevo);
void listar(pNodo inicio);

int main(void) {
	pNodo inicio = NULL;
	pNodo nuevo;
	char aux[LARGO];
	FILE * arch = fopen("Deptos.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura.");
		return 1;
	}
	else {
		fgets(aux, LARGO, arch);
		while (!feof(arch)) {
			nuevo = (pNodo)malloc(sizeof(nodo));
			if (nuevo != NULL) {
				sacarEnter(aux);
				strcpy(nuevo->tipoInmueble, aux);
				fscanf(arch, "%c", &nuevo->zona);
				fgetc(arch);
				fgets(aux, LARGO, arch);
				sacarEnter(aux);
				strcpy(nuevo->domicilio, aux);
				fscanf(arch, "%d", &nuevo->habitaciones);
				fgetc(arch);
				fscanf(arch, "%c", &nuevo->cochera);
				fgetc(arch);
				fscanf(arch, "%d", &nuevo->antiguedad);
				fgetc(arch);
				fscanf(arch, "%d", &nuevo->expensas);
				fgetc(arch);
				fscanf(arch, "%d", &nuevo->precioVenta);
				fgetc(arch);
				vincularOrdenado(&inicio, nuevo);
			}
			else {
				printf("Sin memoria. Intente mas tarde");
				return 1;
			}
			fgets(aux, LARGO, arch);
		}
	}
	listar(inicio);
	fclose(arch);
	system("pause");
	return 0;
}

void sacarEnter(char aux[]) {
	char *p = strchr(aux, '\n');
	if (p != NULL)
		*p = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void vincularOrdenado(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (actual == NULL) {
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if ((*inicio)->precioVenta > nuevo->precioVenta) {
		nuevo->pSig = actual;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL && actual->precioVenta < nuevo->precioVenta) {
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual == NULL) {
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
		else {
			anterior->pSig = nuevo;
			nuevo->pSig = actual;
		}
	}
}



void listar(pNodo inicio) {
	char cocheraAux;
	printf("Ingrese zona que desea listar:\n");
	scanf("%c", &cocheraAux);
	fgetc(stdin);
	while (inicio != NULL) {
		if (inicio->zona==cocheraAux) {
			printf("Tipo inmueble: %s\n", inicio->tipoInmueble);
			printf("Zona: %c\n", inicio->zona);
			printf("Domicilio: %s\n", inicio->domicilio);
			printf("Habitaciones: %d\n", inicio->habitaciones);
			printf("Cochera: %c\n", inicio->cochera);
			printf("Antiguedad: %d\n", inicio->antiguedad);
			printf("Expensas: %d\n", inicio->expensas);
			printf("Precio Venta: %d\n\n", inicio->precioVenta);
			printf("<-------------------------------------->\n");
		}
		inicio = inicio->pSig;
	}
}