/*
	-Crear un ABM completo que permita cargar en un archivo binario las siguiente estructura:

				typedef struct{
					int d,m,a;
				}fecha;

				typedef struct{
					char nombre[LNOM];
					int edad;
					struct fecha nacim;
				}persona;

	-Se debe mostrar por pantalla aquellas personas con mayor edad a menor edad (de manera descendente).
	-Se debe poder eliminar a las personas cargadas.
	-Se debe poder modificar a las personas cargadas.
	-Se debe poder cargar los datos en un vector.

*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define LNOM 32
#define TAM 64

//definicion de estructuras

typedef struct {
	int d, m, a;
}fecha;

typedef struct {
	char nombre[LNOM];
	int edad;
	fecha nacim;
}persona;

//funciones del programa principal

int altas(persona v[], int c);
void ingresarCadena(char nom[], int n, char mensaje[]);
void ordenar(persona v[], int c);
void mostrar(persona v[], int c);
void modificar(persona v[], int c);
void eliminar(persona v[], int c);

//funciones de archivos
int leerArchivo(persona v[]);
int tamArchivo(FILE * arch);
void grabarArchivo(persona v[], int c);


//programa principal

int main(void) {
	persona vector[TAM];
	printf("Bienvenido!\n\n");
	int opc;
	int cant = leerArchivo(vector);
	printf("\n 1- CARGAR\n 2- MOSTRAR\n 3- MODIFICAR\n 4- BAJA\n 5- SALIR\n");
	scanf("%d", &opc);
	fgetc(stdin);
	if (opc == 1) {
		cant = altas(vector, cant);
		ordenar(vector, cant);
	}
	if (opc == 2) {
		mostrar(vector, cant);
	}
	if (opc == 3) {
		modificar(vector, cant);
	}
	if (opc == 4) {
		eliminar(vector, cant);
	}
	if (opc == 5) {
		printf("Chau!");
	}
	grabarArchivo(vector, cant);
	system("pause");
	return 0;
}

int altas(persona v[], int c) {
	char nom[LNOM];
	ingresarCadena(nom, LNOM, "Ingrese nombre de la persona: ");
	while (c < TAM && nom[0] != '\0') {
		strcpy(v[c].nombre, nom);
		printf("Ingrese edad de la persona: ");
		scanf("%d", &v[c].edad);
		fgetc(stdin);
		printf("Ingrese fecha de nacimiento de la persona: (dd/mm/aaaa) ");
		scanf("%d/%d/%d", &v[c].nacim.d, &v[c].nacim.m, &v[c].nacim.a);
		fgetc(stdin);
		c++;
		if (c < TAM) {
			ingresarCadena(nom, LNOM, "Ingrese nombre de la persona (enter para finalizar): ");
		}
	}
	return c;
}

void ingresarCadena(char nom[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(nom, LNOM, stdin);
	while (nom[i] != '\n' && nom[i] != '\0')
		i++;
	if (nom[i] == '\n')
		nom[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void ordenar(persona v[], int c) {
	int i, j;
	persona temporal;
	for (i = 1; i < c; i++) {
		for (j = 0; j < c - 1; j++) {
			if (v[j].edad < v[j + 1].edad) {
				temporal = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temporal;
			}
		}
	}
}

void mostrar(persona v[], int c) {
	int i = 0;
	FILE * arch = fopen("persona.dat", "rb");
	if (arch == NULL) {
		printf("Error de apertura \n");
	}
	fgets(v[i].nombre, LNOM, arch);
	while (!feof(arch)) {
		fscanf(arch, "%d", &v[i].edad);
		fscanf(arch, "%d/%d/%d", &v[i].nacim.d, &v[i].nacim.m, &v[i].nacim.a);
		i++;
		fgets(v[i].nombre, LNOM, arch);
	}
	for (i = 0; i < c; i++) {
		printf("\t Nombre: %s \t Edad: %d \t Fecha nacimiento: %d/%d/%d\n", v[i].nombre, v[i].edad, v[i].nacim.d, v[i].nacim.m, v[i].nacim.a);
	}
}

void modificar(persona v[], int c) {
	char nombreModificar[LNOM];
	char *p;
	int a = 1, i;
	while (a == 1) {
		ingresarCadena(nombreModificar, LNOM, "Ingrese el nombre de la persona que desea modificar:\n");
		i = 0;
		p = strstr(v[i].nombre, nombreModificar);
		if (p == NULL) {
			i++;
			p = strstr(v[i].nombre, nombreModificar);
		}
		if (i == c) {
			ingresarCadena(nombreModificar, LNOM, "Persona no encontrada. Ingrese nuevamente un nombre:\n");
			i = 0;
			p = strstr(v[i].nombre, nombreModificar);
			if (p == NULL) {
				i++;
				p = strstr(v[i].nombre, nombreModificar);
			}
		}
		ingresarCadena(v[i].nombre, LNOM, "Ingrese nuevo nombre: ");
		printf("Ingrese nueva edad: ");
		scanf("%d", &v[i].edad);
		fgetc(stdin);
		printf("Ingrese nueva fecha de nacimiento: ");
		scanf("%d/%d/%d", &v[i].nacim.d, &v[i].nacim.m, &v[i].nacim.a);
		fgetc(stdin);
		printf("Desea modificar a otra persona? 1- Si 2- No");
		scanf("%d", &a);
		fgetc(stdin);
	}
}

void eliminar(persona v[], int c) {
	char nombreEliminar[LNOM];
	char*p;
	int a = 1, i;
	while (a == 1 && c > 0) {
		ingresarCadena(nombreEliminar, LNOM, "Ingrese el nombre de la persona que desea eliminar: ");
		i = 0;
		p = strstr(v[i].nombre, nombreEliminar);
		if (p == NULL) {
			i++;
			p = strstr(v[i].nombre, nombreEliminar);
		}
		while (i == c) {
			ingresarCadena(nombreEliminar, LNOM, "No se encontro a la persona que desea eliminar. Ingrese otro nombre: ");
			i = 0;
			p = strstr(v[i].nombre, nombreEliminar);
			if (p == NULL) {
				i++;
				p = strstr(v[i].nombre, nombreEliminar);
			}
		}
		while (i < c) {
			v[i] = v[i + 1];
			i++;
		}
		c--;
		if (c != 0) {
			printf("Desea modificar a otra persona? 1- Si 2- No");
			scanf("%d", &a);
			fgetc(stdin);
			if (a == 1) {
				ingresarCadena(nombreEliminar, LNOM, "Ingrese el nombre de la persona que desea eliminar: ");
			}
		}
	}
}

int leerArchivo(persona v[]) {
	int cant = 0;
	FILE * arch = fopen("persona.dat","rb");
	while (arch == NULL) {
		printf("Error de apertura");
		return 1;
	}
	cant = tamArchivo(arch)/sizeof(persona);
	for (int i = 0; i < cant; i++) {
		fread(&v[i], sizeof(persona), 1, arch);
	}
	fclose(arch);
	return cant;
}

void grabarArchivo (persona v[], int c){
	int i;
	FILE * arch = fopen("persona.dat", "wb");
	while (arch == NULL) {
		printf("Error de apertura!");
	}
	for (i = 0; i < c; i++) {
		fwrite(&v[i], sizeof(persona), 1, arch);
	}
	fclose(arch);
}

int tamArchivo(FILE * arch) {
	int t;
	fseek(arch, 0, SEEK_END);
	t = ftell(arch);
	fseek(arch, 0, SEEK_SET);
	return t;
}
