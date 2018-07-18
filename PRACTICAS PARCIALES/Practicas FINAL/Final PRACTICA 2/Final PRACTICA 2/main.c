/*
	Se tiene un archivo de texto con los nombres y calificaciones de un grupo de alumnos,
	del que no se conoce el tamaño. Cada línea del archivo de texto puede contener un
	nombre de alumno o una calificación, en este último caso dicha calificación pertenece al
	último nombre leído. La cantidad de calificaciones puede variar entre alumnos, debido a
	los recuperatorios y trabajos prácticos que cada uno realizó.

	Se solicita imprimir un listado de alumnos con su respectivo promedio, ordenado en
	forma descendente por promedio.

	Ejemplo del archivo de entrada:
		BERMUDEZ, Julián Marcelo
		8
		4
		7
		CERQUETTI, Micaela Valeria
		2
		7
		5
		4
		CABRERA, Lautaro Hernán
		9
		6
		[......]
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define LARGO 32

typedef struct a {
	char nombre[LARGO];
	float promedio;
	struct a *pSig;
}nodo, *pNodo;

void sacarEnter(char aux[]);
void vincularEnOrden(pNodo *inicio, pNodo nuevo);
void mostrar(pNodo inicio);

int main(void) {
	pNodo inicio=NULL, nuevo = NULL;
	char aux[LARGO];
	float nota=0;
	int proxNota=0;
	int cantNotas = 0;
	int actual = 0;
	FILE * arch = fopen("alumnos.txt", "rt");
	if (arch == NULL) {
		printf("Error apertura.\n");
	}
	else {
		fgets(aux, LARGO, arch);
		while (!feof(arch)) {
			nuevo = (pNodo)malloc(sizeof(nodo));
			if (nuevo != NULL) {
				sacarEnter(aux);
				strcpy(nuevo->nombre, aux);
				cantNotas = 1;
				nuevo->promedio = 0;
				fscanf(arch, "%f", &nota);
				fgetc(arch);
				nuevo->promedio = nuevo->promedio + nota;
				actual = ftell(arch);
				proxNota = fgetc(arch); //leo un caracter para ver si es numero
				while ((proxNota>='0'&& proxNota<='9') && !feof(arch)){
					fseek(arch, actual, SEEK_SET);
					fscanf(arch, "%f", &nota);
					fgetc(arch);
					nuevo->promedio = nuevo->promedio + nota;
					cantNotas++;
					actual = ftell(arch);
					proxNota = fgetc(arch); //leo un caracter para ver si es numero
				} 
				nuevo->promedio = nuevo->promedio / cantNotas;
				fgets(aux, LARGO, arch);
				vincularEnOrden(&inicio, nuevo);
			}
			else {
				printf("No hay espacio.\n");
			}
		}
	}
	mostrar(inicio);
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

void vincularEnOrden(pNodo *inicio, pNodo nuevo) {
	pNodo actual = *inicio;
	pNodo anterior = NULL;
	if (*inicio == NULL) {
		nuevo->pSig = NULL;
		*inicio = nuevo;
	}
	else if(nuevo->promedio > actual->promedio){
		nuevo->pSig = actual;
		*inicio = nuevo;
	}
	else {
		while (actual != NULL && nuevo->promedio < actual->promedio) {
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


void mostrar(pNodo inicio) {
	while (inicio != NULL) {
		printf("Nombre:%s\nPromedio: %f\n",inicio->nombre ,inicio->promedio);
		inicio = inicio->pSig;
	}
}




/*f (isalpha(aux[0])) {
					sacarEnter(aux);
					strcpy(nuevo->nombre, aux);
					nuevo->promedio = 0;
					cantNotas = 0;
				}else if(isalnum(aux[0])){
					sscanf(aux, "%f", &nota);
					nuevo->promedio = nuevo->promedio + nota;
					cantNotas++;
				}*/