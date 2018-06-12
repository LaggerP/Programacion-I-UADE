#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include <stdlib.h>

#define LNOM 32
#define ALTA 1
#define BAJA 2
#define MODIF 3
#define LISTAR 4
#define SALIR 5
//LOS SIGUIENTES DEFINE SON PARA EL MENU DE MODIFICACIONES
#define NOMBRE 1
#define DNI 2
#define FECHANACIM 3
#define EXIT 4

typedef struct {
	int d, m, a;
}fecha;

typedef struct {
	char nombre[LNOM];
	int dni;
	fecha nacim;
}persona;


//modificacion para uso de listas simples

typedef struct n {
	persona dato; //datos de una persona
	struct n *pSig;
}nodo;

typedef nodo *pNodo;

void alta(pNodo* ini);
void baja(pNodo* ini);
void modificaciones(pNodo* ini);
int menu();
void listar(pNodo ini);
void ingresarcadena(char nom[], int n, char mensaje[]);
void vincularOrdenamiento(pNodo * ini, pNodo nuevo);

void limpiarbuffer();

int main(void)
{
	pNodo ini=NULL; //declaracion de la inicializacion de la lista
	int opc;
	opc = menu();
	while (opc != SALIR)
	{
		switch (opc)
		{
		case ALTA:
			alta(&ini);
			break;
			case BAJA:
			baja(&ini);
			break;
		case MODIF:
			modificaciones(&ini);
			break;
		case LISTAR:
			listar(ini);
			break;
		}
		opc = menu();
	}
	return 0;
}

void alta(pNodo* ini){
	pNodo nuevo;
	char nom[LNOM];
	ingresarcadena(nom, LNOM, "Nombre: ");
	while (nom[0] != '\0') {
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo!=NULL){ 
			strcpy(nuevo->dato.nombre, nom);
			printf("DNI: ");
			scanf("%d", &nuevo->dato.dni);
			fgetc(stdin);
			printf("fecha(d/m/a): ");
			scanf("%d/%d/%d", &nuevo->dato.nacim.d, &nuevo->dato.nacim.m, &nuevo->dato.nacim.a);
			fgetc(stdin);
			vincularOrdenamiento(ini, nuevo);
			ingresarcadena(nom, LNOM, "Nombre (enter para finalizar): ");
		}
		else{
			printf("No hay memoria. Intente mas tarde\n");
			nom[0] = '\0';
		}
	}
}

void vincularOrdenamiento(pNodo * ini, pNodo nuevo) {
	pNodo actual = *ini;
	pNodo anterior = NULL;
	if (actual == NULL || strcmp(nuevo->dato.nombre, (*ini)->dato.nombre)<0) {//caso 1 y 2  
		nuevo->pSig = *ini;
		*ini = nuevo;
	}
	else {
		while (actual != NULL && strcmp(nuevo->dato.nombre, (*ini)->dato.nombre)>=0) { //caso 3 y 4 
			anterior = actual;
			actual = actual->pSig;
		}
		nuevo->pSig = actual;
		anterior->pSig = nuevo;
	}
}

void baja(pNodo* ini){
	pNodo actual = *ini; //para no perder la lista cuando la recorro
	pNodo anterior = NULL;
	pNodo lib;
	int i = 0,j=0,z=0;
	char nom[LNOM], pn[3];
	ingresarcadena(nom, LNOM, "Ingrese nombre a eliminar: ");
	while (actual != NULL) {
		if (strstr(actual->dato.nombre, nom) != NULL){
			printf("%10d%-*s%02d/%02d/%04d\n", actual->dato.dni, LNOM, actual->dato.nombre, actual->dato.nacim.d, actual->dato.nacim.m, actual->dato.nacim.a); 
			ingresarcadena(pn, 3, "Desea eliminar? (si/no)\n");
			for (z = 0; z < (int)strlen(pn);z++)
				pn[z] = (char)towlower(pn[z]);
			if (strcmp(nom, "si")){
				if (actual == (*ini)) {
					(*ini) = (*ini)->pSig;
					lib = actual;
					actual = (*ini);
					free(lib);
				}
				else {
					anterior->pSig = actual->pSig;
					free(actual);
					actual = anterior->pSig;
				}
			}
			else {
				anterior = actual;//avanzo en la lista
				actual = actual->pSig; 
			}
				
		}
		else {
			anterior = actual;//avanzo en la lista
			actual = actual->pSig; 
		}
	}
}

void modificaciones(pNodo* ini) {
	pNodo anterior = NULL;
	pNodo actual = *ini;
	char nuevoNombre[LNOM];
	char nom[LNOM];
	ingresarcadena(nom, LNOM, "Ingrese nombre a modificar: ");
	if (actual != NULL) {
		while (actual != NULL && strstr(actual->dato.nombre, nom) != NULL) { //mientras el dato no se encuentre 
			anterior = actual;
			actual = actual->pSig;
		}
	}
	if (actual != NULL) { //si el dato se encontro.
		if (anterior == NULL) {
			*ini = (*ini)->pSig;
		}
		else if (anterior != NULL && strcmp(nom, actual->dato.nombre)==0) {
			ingresarcadena(nuevoNombre, LNOM, "Ingrese nuevo nombre: ");
			strcpy(actual->dato.nombre, nuevoNombre);
			printf("Ingrese nuevo DNI: ");
			scanf("%d", &actual->dato.dni);
			fgetc(stdin);
			printf("fecha(d/m/a): ");
			scanf("%d/%d/%d", &actual->dato.nacim.d, &actual->dato.nacim.m, &actual->dato.nacim.a);
			fgetc(stdin);
		}
	}

}

int menu(){
	int opc, codError;
	printf("1 - ALTA\n");
	printf("2 - BAJA\n");
	printf("3 - MODIF\n");
	printf("4 - LISTAR\n");
	printf("5 - SALIR\n");
	do {
		printf("opcion: ");
		codError = scanf("%d", &opc);
		while (fgetc(stdin) != '\n')
			;
	} while (codError != 1 || opc < ALTA || opc > SALIR);
	return opc;
}

void listar(pNodo ini){
	while (ini != NULL){
		printf("%-*s%10d  %02d/%02d/%04d\n",LNOM,ini->dato.nombre, ini->dato.dni, ini->dato.nacim.d, ini->dato.nacim.m, ini->dato.nacim.a);
		ini = ini->pSig;
	}

}

void ingresarcadena(char nom[], int n, char mensaje[]){
	int i = 0;
	printf("%s", mensaje);
	fgets(nom, n, stdin);
	while (nom[i] != '\0'&&nom[i] != '\n')
		i++;
	if (nom[i] == '\n')
		nom[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void limpiarbuffer(){
	while (fgetc(stdin) != '\n')
		;
}