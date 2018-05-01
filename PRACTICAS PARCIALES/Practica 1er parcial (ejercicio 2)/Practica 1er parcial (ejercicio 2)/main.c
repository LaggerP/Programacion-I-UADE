/*
		Hacer un programa que permita realizar altas de libros de una biblioteca y guardarlos en un archivo binario.
		El total de los libros no es mayor a 1500.
		Luego mostrar por pantalla los datos de los libros extraidos del archivo teniendo en cuenta lo siguiente: 
		
			Libros publicados hace menos de 5 años
			Libros ordenados alfabeticamente por el nombre de la obra.
			Informar ademas la cantidad de libros de mas de 500 paginas.

		Los datos a ingresar son:
			nombre de la obra
			cantidad de paginas
			editorial
			fecha de publicacion
*/

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 1500
#define LNOM 32

typedef struct {
	char nombreObra[LNOM];
	int paginas, d,m,a;
	char nombreEdi[LNOM];
}biblioteca;

//funciones archivos.
int leerArchivo(biblioteca vector[]);
int tamArchivo(FILE * arch);
void grabarArchivo(biblioteca v[], int c);

//funciones
int altas(biblioteca v[], int c);
void ordenar(biblioteca v[], int c);
void mostrar(biblioteca v[], int c);
void insertarCadena(char nombre[], int n, char mensaje[]);

int main(void) {
	biblioteca vector[TAM];
	int cant = leerArchivo(vector);
	int opc;
	printf("1- Altas 2- Mostrar\n");
	scanf("%d", &opc);
	fgetc(stdin);
	if (opc == 1) {
		cant = altas(vector, cant);
		ordenar(vector, cant);
	}
	if (opc == 2) {
		mostrar(vector, cant);
	}
	grabarArchivo(vector, cant);
	system("pause");
	return 0;
}


int altas(biblioteca v[], int c){
	char nombre[LNOM];
	insertarCadena(nombre, LNOM, "Ingrese nombre de la obra: ");
	while (c < TAM && nombre[0] != '\0') {
		strcpy(v[c].nombreObra, nombre);
		printf("Ingrese cantidad de paginas: ");
		scanf("%d", &v[c].paginas);
		fgetc(stdin);

		printf("Ingrese nombre de la editorial: ");
		scanf("%s", &v[c].nombreEdi);
		fgetc(stdin);

		printf("Ingrese fecha de publicacion (dd/mm/aaaa): ");
		scanf("%d/%d/%d", &v[c].d, &v[c].m, &v[c].a);
		fgetc(stdin);
		c++;
		if (c < TAM) {
			insertarCadena(nombre, LNOM, "Inserte otro nombre de alguna obra (enter para finalizar): ");
		}
	}
	return c;
}

void insertarCadena(char nombre[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(nombre, n, stdin);
	while (nombre[i]!='\0' && nombre[i]!='\n')
		i++;
	if (nombre[i] == '\n')
		nombre[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}


void ordenar(biblioteca v[], int c){
	int i, j;
	biblioteca temporal;
	for (i = 0; i < c - 1; i++) {
		for (j = 0; j < c - 1; j++) {
			if (strcmp(v[j].nombreObra, v[j + 1].nombreObra) > 0) {
				temporal = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temporal;
			}
		}
	}

}

/*
	Libros publicados hace menos de 5 años
	Libros ordenados alfabeticamente por el nombre de la obra.
	Informar ademas la cantidad de libros de mas de 500 paginas.
*/
void mostrar(biblioteca v[], int c) {
	int i, dia, mes, anio;
	printf("Ingrese fecha de hoy: (dd/mm/aaaa) ");
	scanf("%d/%d/%d", &dia, &mes, &anio);
	fgetc(stdin);
	int paginas500 = 0;
	for (i = 0; i < c; i++) {
		if (v[i].paginas > 500)
			paginas500++;
		if (((anio-5)*10000+mes*100+dia) > ((v[i].a * 10000) + (v[i].m * 100) + v[i].d)) {
			printf("Nombre obra: %s\n", v[i].nombreObra);
			printf("Cantidad paginas: %d\n", v[i].paginas);
			printf("Fecha publicacion: %d/%d/%d\n", v[i].d, v[i].m, v[i].a);
			printf("Nombre editorial: %s\n", v[i].nombreEdi);
		}
	}
	printf("Cantidad de libros con mas de 500 paginas! %d ", paginas500);
}

int leerArchivo(biblioteca v[]) {
	int i;
	FILE * arch = fopen("biblioteca.dat", "rb");
	if (arch == NULL) {
		printf("Error de apertura!\n");
		return 1;
	}
	int cant = tamArchivo(arch)/sizeof(biblioteca);
	for (i = 0; i < cant; i++) {
		fread(&v[i], sizeof(biblioteca), 1, arch);
	}
	fclose(arch);
	return cant;
}

int tamArchivo(FILE * arch) {
	int t;
	fseek(arch, 0, SEEK_END);
	t = ftell(arch);
	fseek(arch, 0, SEEK_SET);
	return t;
}

void grabarArchivo(biblioteca v[], int c) {
	int i;
	FILE * arch = fopen("biblioteca.dat", "wb");
	if (arch == NULL) {
		printf("Error de apertura!");
	}
	for (i = 0; i < c; i++) {
		fwrite(&v[i], sizeof(biblioteca), 1, arch);
	}
	fclose(arch);
}