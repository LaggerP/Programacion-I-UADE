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
#include <string.h>
#include <stdlib.h>



#define TAM 50
#define LARGO 200

#define ALTA 1
#define MOSTRAR 2
#define LISTAR_ORDENADO 3
#define SALIR 4

typedef struct {
	char descripcion[LARGO];
	int codigo;
	int d, m, a;
	int stock; // stock 
	int stockMinimo; //
	int precio;
}producto;

int leerArchivo(producto v[]);
void grabarArchivo(producto v[], int c);
int tamArchivo(FILE * archivo);

int altas(producto v[], int c);
void ingresarCadena(char descripcionAux[], int n, char mensaje[]);

void cargaVector(producto v[], int c);
void listarOrdenado(producto v[], int c);


int main(void) {
	producto vector[TAM];
	int cant = leerArchivo(vector);
	int opc;
	printf(" 1- ALTA\n 2- MOSTRAR DESORDENADO\n 3- MOSTRAR ORDENADO\n 4- SALIR\n\n");
	scanf("%d", &opc);
	fgetc(stdin);
	if (opc == ALTA) 
		cant = altas(vector, cant);
	if (opc == MOSTRAR) 
		cargaVector(vector, cant);
	if (opc == LISTAR_ORDENADO)
		listarOrdenado(vector, cant);
	else if (opc == SALIR)
		printf("Hasta luego!");

	grabarArchivo(vector, cant);
	system("pause");
	return 0;
}

int altas(producto v[], int c) {
	char descripcionAux[LARGO];
	ingresarCadena(descripcionAux, LARGO, "Ingrese descripcion del producto: \n");
	while (c < LARGO && descripcionAux[0] != '\0') {
		strcpy(v[c].descripcion, descripcionAux);
		printf("Ingrese codigo de producto: \n");
		scanf("%d", &v[c].codigo);
		fgetc(stdin);
		printf("Ingrese fecha de la ultima adquisición: (dd/mm/aa)\n");
		scanf("%d/%d/%d", &v[c].d, &v[c].m, &v[c].a);
		fgetc(stdin);
		printf("Ingrese stock: \n");
		scanf("%d", &v[c].stock);
		fgetc(stdin);
		printf("Ingrese stock minimo: \n");
		scanf("%d", &v[c].stockMinimo);
		fgetc(stdin);
		printf("Ingrese precio: \n");
		scanf("%d", &v[c].precio);
		fgetc(stdin);

		c++;
		if (c < LARGO)
			ingresarCadena(descripcionAux, TAM, "Descripcion producto (enter para finalizar):\n ");
	}
	return c;
}

void ingresarCadena(char descripcionAux[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(descripcionAux, LARGO, stdin);
	while (descripcionAux[i] != '\0' && descripcionAux[i] != '\n')
		i++;
	if (descripcionAux[i] == '\n')
		descripcionAux[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void cargaVector(producto v[], int c) {
	int i=0;
	FILE * archivo = fopen("archivoProducto.dat", "rb");
	if (archivo == NULL) {
		printf("Error de apertura \n");
	}
	fgets(v[i].descripcion, LARGO, archivo);
	while (!feof(archivo)) {
		fscanf(archivo, "%d", &v[i].codigo);
		fscanf(archivo, "%d/%d/%d", &v[i].d, &v[i].m, &v[i].a);
		fscanf(archivo, "%d", &v[i].stock);
		fscanf(archivo, "%d", &v[i].stockMinimo);
		fscanf(archivo, "%d", &v[i].precio);
		i++;
		fgets(v[i].descripcion, LARGO, archivo);
	}
	for (i = 0; i < c; i++) {
		printf("Descripcion: %s\n", v[i].descripcion);
		printf("Codigo: %d\n", v[i].codigo);
		printf("Fecha: %d/%d/%d\n", v[i].d, v[i].m, v[i].a);
		printf("Stock: %d\n", v[i].stock);
		printf("Stock minimo: %d\n", v[i].stockMinimo);
		printf("Precio: $%d\n", v[i].precio);
	}
}


//3) Listar en forma ordenada por fecha de ultima adquisición de los productos donde su stock es menor al stock minimo y el monto de reposición de producto.
void listarOrdenado(producto v[], int c) {
	//int i = 0;
	producto fecha; //estructura auxiliar
	FILE * archivo = fopen("archivoProducto.dat", "rb");
	if (archivo == NULL) {
		printf("Error de apertura \n");
	}
	printf("Ingrese la fecha de hoy: (dd/mm/aa)\n");
	scanf("%d/%d/%d", &fecha.d, &fecha.m, &fecha.a);
	fgetc(stdin);
	int diaHoy = (fecha.a) * 10000 + (fecha.m) * 100 + fecha.d;
	/*
	fgets(v[i].descripcion, LARGO, archivo);
	while (!feof(archivo)) {
		fscanf(archivo, "%d", &v[i].codigo);
		fscanf(archivo, "%d/%d/%d", &v[i].d, &v[i].m, &v[i].a);
		fscanf(archivo, "%d", &v[i].stock);
		fscanf(archivo, "%d", &v[i].stockMinimo);
		fscanf(archivo, "%d", &v[i].precio);
		i++;
		fgets(v[i].descripcion, LARGO, archivo);
	}
	*/
	for (int j = 0; j < c; j++) {
		if (v[j].stock < v[j].stockMinimo) {
			if ((v[j].a * 1000 + v[j].m * 100 + v[j].d)<diaHoy ) {
				printf("Fecha: %d/%d/%d\n", v[j].d, v[j].m, v[j].a);
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

void grabarArchivo(producto v[], int c) {
	int i;
	FILE * archivo = fopen("archivoProducto.dat", "wb");
	if (archivo == NULL) {
		printf("Error de apertura \n");
	}
	for (i = 0; i < c; i++)
		fwrite(&v[i], sizeof(producto), 1, archivo);  //va guardando informacion en el archivo 1 a 1
	fclose(archivo);
}

int leerArchivo(producto v[]) {
	int cant = 0;
	FILE * archivo = fopen("archivoProducto.dat", "rb");
	if (archivo == NULL) {
		printf("Error de apertura \n");
		return 0;
	}
	cant = tamArchivo(archivo) / sizeof(producto);
	for (int i = 0; i < cant; i++)
		fread(&v[i], sizeof(producto), 1, archivo); //lee todo los datos del archivo y retorna el tamaño del mismo.
	fclose(archivo);
	return cant;
}


int tamArchivo(FILE * archivo) {
	int t;
	fseek(archivo, 0, SEEK_END); //nos posicionamos en el final del archivo
	t = ftell(archivo);
	fseek(archivo, 0, SEEK_SET);//nos posiciona al principio del archivo
	return t;
}