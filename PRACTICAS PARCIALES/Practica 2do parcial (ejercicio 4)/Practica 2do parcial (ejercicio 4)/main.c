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
void mostrar(pNodo inicio);
void listarZona(pNodo inicio, char zonaBusqueda);

int main(void) {
	pNodo inicio = 0;
	pNodo nuevo;
	char aux[LARGO];
	char zonaBusqueda;
	FILE * arch = fopen("Deptos.txt", "rt");
	if (arch == NULL) {
		printf("Error de apertura");
	}
	else {
		fgets(aux, LARGO, arch);
		while (!feof(arch)) {
			nuevo = (pNodo)malloc(sizeof(nodo));
			if (nuevo != NULL) {
				sacarEnter(aux);
				//tipo inmueble
				strcpy(nuevo->tipoInmueble, aux);
				//zona inmueble
				fscanf(arch, "%c", &nuevo->zona);
				fgetc(arch);
				//domicilio
				fgets(aux, LARGO, arch);
				sacarEnter(aux);
				strcpy(nuevo->domicilio, aux);
				//cantidad habitaciones
				fscanf(arch, "%d", &nuevo->habitaciones);
				fgetc(arch);
				//cocheras S o N
				fscanf(arch, "%c", &nuevo->cochera);
				//antiguedad inmueble
				fscanf(arch, "%d", &nuevo->antiguedad);
				fgetc(arch);
				//expensas
				fscanf(arch, "%d", &nuevo->expensas);
				fgetc(arch);
				//precio venta
				fscanf(arch, "%d", &nuevo->precioVenta);
				fgetc(arch);
				vincularOrdenado(&inicio, nuevo);
			}
			else {
				printf("intente mas tarde");
				return 1;
			}
			fgets(aux, LARGO, arch);
		}
		
	}
	fclose(arch);
	printf("Ingrese zona que desea visualizar: \n");
	scanf("%c", &zonaBusqueda);
	fgetc(stdin);
	listarZona(inicio, zonaBusqueda);
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

void listarZona(pNodo inicio, char zonaBusqueda) {
	while (inicio != NULL) {
		if (inicio->zona == zonaBusqueda) {
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