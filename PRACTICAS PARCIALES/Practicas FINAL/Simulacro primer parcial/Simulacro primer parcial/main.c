/*
Una empresa que comercializa no mas de 50 productos, requiere:

1) Generar un archivo binario con la siguiente información de cada uno de sus productos
-Codigo
-Descripción
-Fecha de ultima adquisición
-Stock
-Stock minimo
-Precio unitario

2) Leer el archivo y cargar los datos en un vector.

3) Listar en forma ordenada por fecha de ultima adquisición de los productos donde su stock es menor al stock minimo y el monto de reposición de producto.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LARGO 64
#define TAM 50
typedef struct b {
	int d, m, a;
}fecha;

typedef struct n {
	int codigo;
	char descripcion[LARGO];
	fecha adquisicion;
	int stock;
	int stockMinimo;
	int precio;
}producto;

void ingresarCadena(char descripcion[], int n, char mensaje[]);
void altas(producto v[], int i);
void mostrar(producto v[], int c);
int leerArchivo(producto v[]);
int tamArchivo(FILE * archivo);

int main(void) {
	producto vector[TAM];
	int cant = leerArchivo(vector);
	altas(vector, cant);
	mostrar(vector, cant);
	system("pause");
	return 0;
}

void altas(producto v[], int i) {
	char descripcionAux[LARGO];
	FILE * archivo = fopen("archivoProducto.dat", "wb");
	if (archivo == NULL) {
		printf("Intente mas tarde\n");
	}
	ingresarCadena(descripcionAux, LARGO, "Ingrese descripcion del producto (enter para finalizar):\n");
	while (i < TAM && descripcionAux[0] != '\0') {
		strcpy(v[i].descripcion, descripcionAux);
		printf("Ingrese codigo:\n");
		scanf("%d", &v[i].codigo);
		fgetc(stdin);
		printf("Ingrese fecha de adquisicion (dd/mm/aa): \n");
		scanf("%d/%d/%d", &v[i].adquisicion.d, &v[i].adquisicion.m, &v[i].adquisicion.a);
		fgetc(stdin);
		printf("Ingrese stock: \n");
		scanf("%d", &v[i].stock);
		fgetc(stdin);
		printf("Ingrese stock minimo: \n");
		scanf("%d", &v[i].stockMinimo);
		fgetc(stdin);
		printf("Ingrese precio: \n");
		scanf("%d", &v[i].precio);
		fgetc(stdin);
		fwrite(&v[i], sizeof(producto), 1, archivo);
		i++;
		if (i<TAM)
			ingresarCadena(descripcionAux, LARGO, "Ingrese descripcion del producto (enter para finalizar):\n");
	}
}


void mostrar(producto v[], int c) {
	producto fecha;
	FILE * archivo = fopen("archivoProducto.dat", "rb");
	if (archivo == NULL) {
		printf("Error de apertura");
	}
	printf("Ingrese la fecha del dia de hoy (dd/mm/aa):\n");
	scanf("%d/%d/%d", &fecha.adquisicion.d, &fecha.adquisicion.m, &fecha.adquisicion.a);
	fgetc(stdin);
	int diaHoy = (fecha.adquisicion.a) * 10000 + (fecha.adquisicion.m) * 100 + fecha.adquisicion.d;
	for (int j = 0; j < c; j++) {
		if (v[j].stock < v[j].stockMinimo) {
			if ((v[j].adquisicion.a + v[j].adquisicion.m + v[j].adquisicion.d) < diaHoy) {
				printf("Fecha: %d/%d/%d\n", v[j].adquisicion.d, v[j].adquisicion.m, v[j].adquisicion.a);
				printf("Descripcion: %s\n", v[j].descripcion);
				printf("Codigo: %d\n", v[j].codigo);
				printf("Stock: %d\n", v[j].stock);
				printf("Stock minimo: %d\n", v[j].stockMinimo);
				printf("Precio: $%d\n", v[j].precio);
			}
		}
	}
	fclose(archivo);
}

void ingresarCadena(char descripcion[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(descripcion, LARGO, stdin);
	while (descripcion[i] != '\n' && descripcion[i] != '\0') 
		i++;
	if (descripcion[i] == '\n')
		descripcion[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}


int leerArchivo(producto v[]) {
	int cant = 0;
	FILE * archivo = fopen("archivoProducto.dat", "rb");
	if (archivo == NULL) {
		printf("Error de apertura");
	}
	cant = tamArchivo(archivo) / sizeof(producto);
	for (int i = 0; i < cant; i++)
		fread(&v[i], sizeof(producto), 1, archivo); //se va leyendo un producto a producto del archivo
	fclose(archivo);
	return cant;
}

int tamArchivo(FILE * archivo) {
	int t;
	fseek(archivo, 0, SEEK_END); //colocamos el cursor al final del archivo para poder despues decir el tamaño
	t = ftell(archivo); //nos va a decir el tamaño del archivo
	fseek(archivo, 0 ,SEEK_SET); //colocamos devuelta el cursor al inicio del archivo
	return t;
}