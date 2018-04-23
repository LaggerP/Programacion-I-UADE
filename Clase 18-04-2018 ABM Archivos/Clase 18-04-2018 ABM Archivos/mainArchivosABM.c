#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LNOM 32
#define TAM 100

//MENU opciones
#define ALTA 1
#define BAJA 2
#define MODIFICAR 3
#define MOSTRAR 4
#define SALIR 5

typedef struct {
	int d, m, a;
}fecha;

typedef struct {
	char nombre[LNOM];
	int dni;
	fecha nacim;
}persona;

/*prototipos*/

int altas(persona v[], int c);
void ordenar(persona v[], int c);
int bajas(persona v[], int c);
void modificar(persona v[], int c);
void mostrar(persona v[], int c);
int menu(void);
void ingresarCadena(char nom[], int n, char mensaje[]);
int leerArchivo(persona v[]);
void grabarArchivo(persona v[], int c);
int tamArchivo(FILE * archivo);

int main(void) {
	persona vector[TAM];
	int cant = 0, opc;
	cant = leerArchivo(vector);
	opc = menu();
	while (opc != SALIR) {
		switch (opc) {
		case ALTA:
			cant = altas(vector, cant);
			ordenar(vector, cant);
			break;
		case BAJA:
			cant = bajas(vector, cant);
			break;
		case MODIFICAR:
			modificar(vector, cant);
			ordenar(vector, cant);
			break;
		case MOSTRAR:
			mostrar(vector, cant);
			break;
		}
		opc = menu();
		grabarArchivo(vector, cant);
	}
	system("pause");
	return 0;
}


int altas(persona v[], int c) {
	char nom[LNOM];
	ingresarCadena(nom, LNOM, "Nombre: \n");
	while (c < TAM && nom[0] != '\0') { // c < TAM && nom[0] != '\0')
		strcpy(v[c].nombre, nom);
		printf("Ingrese dni: ");
		scanf("%d", &v[c].dni);
		fgetc(stdin);
		printf("Ingrese fecha (dd/mm/aaaa): ");
		scanf("%d/%d/%d", &v[c].nacim.d, &v[c].nacim.m, &v[c].nacim.a);
		fgetc(stdin);
		c++;
		if (c < TAM) {
			ingresarCadena(nom, LNOM, "Nombre: ");
		}
	}
	return c;
}

//funcion ordenar con archivos
void ordenar(persona v[], int c) {
	int cant;
	int i = 1, j, desordenado = 1;
	persona r1, r2;
	FILE * archivo = fopen("agenda.dat", "r+b");
	if (archivo == NULL)
		printf("Error de apertura");
	cant = tamArchivo(archivo);
	while (desordenado) {
		desordenado = 0;
		for (j = 0; j < cant - i; j++) {
			fseek(archivo, j * sizeof(persona), SEEK_SET);
			fread(&r1, sizeof(persona), 1, archivo);
			fread(&r2, sizeof(persona), 1, archivo);
			if (strcmp(r1.nombre, r2.nombre) > 0) {
				fseek(archivo, j * sizeof(persona), SEEK_SET);
				fwrite(&r2, sizeof(persona), 1, archivo);
				fwrite(&r1, sizeof(persona), 1, archivo);
				desordenado = 1;
			}
		}
		i++;
	}
}

int bajas(persona v[], int c) {
	char *p, nomEliminar[LNOM];
	int a = 1, i; //i recorre estructura
	ingresarCadena(nomEliminar, LNOM, "Ingresar persona a eliminar: ");
	while (a == 1 && c > 0) {
		i = 0;
		p = strstr(v[i].nombre, nomEliminar);
		while (p == NULL && i<c) {
			i++;
			p = strstr(v[i].nombre, nomEliminar);
		}
		while (i == c) {
			ingresarCadena(nomEliminar, LNOM, "No se encontro ningun resultado. Ingresar persona a eliminar: ");
			i = 0;
			p = strstr(v[i].nombre, nomEliminar);
			while (p == NULL && i<c) {
				i = i + 1;
				p = strstr(v[i].nombre, nomEliminar);
			}
		}
		while (i<c) {
			v[i] = v[i + 1];
			i = i + 1;
		}
		c--;
		if (c != 0) {
			printf("Desea eliminar a otra persona?: \n1- Si\n2- No\nOpcion: ");
			scanf("%d", &a);
			if (a == 1)
				ingresarCadena(nomEliminar, LNOM, "Ingresar persona a eliminar: ");
		}
	}
	return c;
}

void modificar(persona v[], int c) {
	char nombreModificar[LNOM], *p;
	int a = 1, i;
	while (a == 1) {
		ingresarCadena(nombreModificar, LNOM, "Ingresar persona a modificar: ");
		i = 0;
		p = strstr(v[i].nombre, nombreModificar);
		while (p == NULL && i < c) {
			i++;
			p = strstr(v[i].nombre, nombreModificar);
		}
		while (i == c) {
			ingresarCadena(nombreModificar, LNOM, "No se encontraron resultados. Ingresar persona a modificar: ");
			i = 0;
			p = strstr(v[i].nombre, nombreModificar);
			while (p == NULL && i < c) {
				i++;
				p = strstr(v[i].nombre, nombreModificar);
			}
		}
		ingresarCadena(v[i].nombre, LNOM, "Ingresar nuevo nombre: ");
		printf("Ingresar nuevo DNI: ");
		scanf("%d", &v[i].dni);
		printf("Ingresar nueva fecha de nacimiento (d/m/a): ");
		scanf("%d/%d/%d", &v[i].nacim.d, &v[i].nacim.m, &v[i].nacim.a);
		printf("Desea modificar a otra persona?\n1- Si\n2- No\nOpcion: ");
		scanf("%d", &a);
	}
}

void mostrar(persona v[], int c) {
	int i;
	for (i = 0; i < c; i++) {
		printf("%10d %-*s %02d/%02d/%04d \n", v[i].dni, LNOM, v[i].nombre, v[i].nacim.d, v[i].nacim.m, v[i].nacim.a);
	}
}

int menu(void) {
	int opc, codError;
	printf("1- Altas\n");
	printf("2- Bajas\n");
	printf("3- Modificar\n");
	printf("4- Mostrar\n");
	printf("5- Salir\n");
	do {
		printf("Opcion: ");
		codError = scanf("%d", &opc);
		fgetc(stdin);
	} while (codError != 1 || opc  < ALTA || opc > SALIR);
	return opc;
}

void ingresarCadena(char nom[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(nom, LNOM, stdin);
	while (nom[i] != '\n' && nom[i] != '\0') {
		i++;
	}
	if (nom[i] == '\n')
		nom[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void grabarArchivo(persona v[], int c) {
	int i;
	FILE * archivo = fopen("agenda.dat", "wb");
	if (archivo == NULL) {
		printf("Error de apertura \n");
		return;
	}
	for (i = 0; i < c; i++) {
		fwrite(&v[i], sizeof(persona), 1, archivo);
	}
	fclose(archivo);
}

int leerArchivo(persona v[]) {
	int cant = 0;
	FILE * archivo = fopen("agenda.dat", "rb");
	if (archivo == NULL) {
		printf("Error de apertura \n");
		return 0;
	}
	cant = tamArchivo(archivo) / sizeof(persona);
	for (int i = 0; i < cant; i++) {
		fread(&v[i], sizeof(persona), cant, archivo);
	}
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