#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define LNOM 32
#define TAM 100
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


int alta(persona* vector[], int cant);
int baja(persona* vector[], int cant);
void modificaciones(persona* vector[], int cant);
int menu();
void ordenar(persona* vector[], int cant);
void listar(persona* vector[], int cant);
void ingresarcadena(char nom[], int n, char mensaje[]);
void limpiarbuffer();

//archivos
int leerArchivo(persona *vector[]);
void grabarArchivo(persona *vector[], int cant);


int main(void)
{
	persona* vector[TAM];
	int cant = leerArchivo(vector);
	int opc;
	opc = menu();
	while (opc != SALIR)
	{
		switch (opc){
		case ALTA:
			cant = alta(vector, cant);
			ordenar(vector, cant);
			break;
			case BAJA:
				cant = baja(vector, cant);
			break;
		case MODIF:
			modificaciones(vector, cant);
			ordenar(vector, cant);
			break;
		case LISTAR:
			listar(vector, cant);
			break;
		}
		opc = menu();
	}
	grabarArchivo(vector, cant);
	return 0;
}

int alta(persona* vector[], int cant){
	char nom[LNOM];
	ingresarcadena(nom, LNOM, "Nombre: ");
	while (cant < TAM && nom[0] != '\0') {
		vector[cant]= (persona*)malloc(sizeof(persona));
		if (vector[cant]!=NULL){ 
			strcpy(vector[cant]->nombre, nom);
			printf("DNI: ");
			scanf("%d", &vector[cant]->dni);
			fgetc(stdin);
			printf("fecha(d/m/a): ");
			scanf("%d/%d/%d", &vector[cant]->nacim.d, &vector[cant]->nacim.m, &vector[cant]->nacim.a);
			fgetc(stdin);
			cant++;
			if (cant < TAM)
				ingresarcadena(nom, LNOM, "Nom: ");
		}
		else{
			printf("No hay memoria. Intente mas tarde\n");
			nom[0] = '\0';
		}
	}
	return cant;
}

int baja(persona* vector[], int cant){
	int i = 0,j=0,z=0;
	char nom[LNOM], pn[3];
	ingresarcadena(nom, LNOM, "Ingrese nombre a eliminar: ");
	while (i < cant) {
		if (strstr(vector[i]->nombre, nom) != NULL){
			printf("%10d%-*s%02d/%02d/%04d\n", vector[i]->dni, LNOM, vector[i]->nombre, vector[i]->nacim.d, vector[i]->nacim.m, vector[i]->nacim.a);
			ingresarcadena(pn, 3, "Desea eliminar?");
			for(z = 0; z < (int) strlen(pn);z++)
				 pn[z]=(char)towlower(pn[z]);
			if (strcmp(nom, "si")){
				free(vector[i]);
				for (j = i; j < cant - 1; j++)
					vector[j] = vector[j + 1];
				cant--;
			}
			else
				i++;
		}
		else
			i++;
	}
	return cant;
}

void modificaciones(persona* vector[], int cant) {
	char nombreModificar[LNOM], *p;
	int a = 1, i;
	while (a == 1) {
		ingresarcadena(nombreModificar, LNOM, "Ingrese el nombre de la persona a modificar: ");
		i = 0;
		p = strstr(vector[i]->nombre, nombreModificar);
		while (p == NULL && i < cant) {
			i++;
			p = strstr(vector[i]->nombre, nombreModificar);
		}
		while (i == cant) {
			ingresarcadena(nombreModificar, LNOM, "No se encontro nombre a eliminar. Ingrese otro: ");
			i = 0;
			p = strstr(vector[i]->nombre, nombreModificar);
			while (p == NULL && i < cant) {
				i++;
				p = strstr(vector[i]->nombre, nombreModificar);
			}
		}
		ingresarcadena(vector[i]->nombre, LNOM, "Ingrese nuevo nombre: ");
		printf("Ingrese nuevo DNI: ");
		scanf("%d", &vector[i]->dni);
		fgetc(stdin);
		printf("Ingrese nueva fecha de nacimiento (dd/mm/aaaa): ");
		scanf("%d/%d/%d", &vector[i]->nacim.d, &vector[i]->nacim.m, &vector[i]->nacim.a);
		fgetc(stdin);
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

void ordenar(persona* vector[], int cant){
	int p = 1, j, desordenado = 1;
	persona* x;
	while (desordenado) {
		desordenado = 0;
		for (j = 0; j < cant - p; j++)
		{
			if(strcmp(vector[j]->nombre,vector[j + 1]->nombre) < 0)
			{
			x = vector[j];
			vector[j] = vector[j + 1];
			vector[j + 1] = x;
			desordenado = 1;
			}
			p++;
		}
	}
}

void listar(persona* vector[], int cant){
	int i;
	for (i = 0; i < cant; i++)
		printf("%-*s%10d  %02d/%02d/%04d\n", LNOM, vector[i]->nombre,vector[i]->dni, vector[i]->nacim.d, vector[i]->nacim.m, vector[i]->nacim.a);
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

int leerArchivo(persona *vector[]) {
	FILE * arch = fopen("personas.txt", "rt");
	int i=0;
	char nom[LNOM];
	if (arch == NULL) {
		printf("Error de apertura.\n");
		return 0;
	}
	fgets(nom, LNOM, arch);
	while (!feof(arch)) {
		vector[i] = (persona *)malloc(sizeof(persona));
		if (vector[i] != NULL) {
			strcpy(vector[i]->nombre, nom);
			fscanf(arch, "%d", &vector[i]->dni);
			fgetc(arch);
			fscanf(arch, "%d/%d/%d", &vector[i]->nacim.d, &vector[i]->nacim.m, &vector[i]->nacim.a);
			fgetc(arch);
			i++;
			if (i< TAM)
				fgets(nom, LNOM, arch);
		}
	}
	fclose(arch);
	return i;
}

void grabarArchivo(persona *vector[], int cant) {
	int i;
	FILE * arch = fopen("personas.txt", "wt");
	if (arch == NULL) {
		printf("Error de apertura.\n");
		return;
	}
	for (i = 0; i < cant; i++) {
		fputs(vector[i]->nombre, arch);
		fprintf(arch, "\n%d", vector[i]->dni);
		fprintf(arch, "%d/%d/%d\n", vector[i]->nacim.d, vector[i]->nacim.m, vector[i]->nacim.a);
		free(vector[i]);
	}
	fclose(arch);
}