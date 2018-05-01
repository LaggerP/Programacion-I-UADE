/*
		-EJERCICIO CON USO DE ARCHIVOS-
		Enunciado:

			Hacer un programa que permita realizar altas, baja y modificacion de pacientes de una clínica. El total de pacientes no es mayor a 100.
			Luego mostrar por pantalla los datos ingresados, ordenados alfabéticamente por el apellido y nombre.
			Informar además la cantidad de pacientes mayores de 55 años.

		Los datos a ingresar son:
			Apellido y nombre
			Número de documento
			Fecha de nacimiento.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 100
#define LNOM 32

typedef struct {
	char nombreApellido[LNOM];
	int dni, d, m, a;
}paciente;


int altas(paciente v[], int c);
void ingresarCadena(char nombreApellido_aux[], int n, char mensaje[]);
void ordenar(paciente v[], int c);
void mostrar(paciente v[], int c);
void modificar(paciente v[], int c);
void baja(paciente v[], int c);

int leerArchivo(paciente v[]);
int tamArchivo(FILE * arch);
void grabarArchivo(paciente v[], int c);

int main(void) {
	paciente vector[TAM];
	int opc, cant = leerArchivo(vector);
	printf(" 1- altas\n 2- mostrar\n 3- modificar\n 4- eliminar\n 5- salir\n");
	scanf("%d", &opc);
	fgetc(stdin);
	if (opc == 1) {
		cant = altas(vector, cant);
		ordenar(vector, cant);
	}
	if(opc==2)
		mostrar(vector, cant);
	if (opc == 3) 
		modificar(vector, cant);
	if (opc == 4)
		baja(vector, cant);
	if (opc == 5)
		printf("Hasta luego!");
	grabarArchivo(vector,cant);
	system("pause");
	return 0;
}

int altas(paciente v[], int c) {
	char nombreApellido_aux[LNOM];
	ingresarCadena(nombreApellido_aux, LNOM, "Ingrese apellido y nombre de la persona: ");
	while (c < TAM && nombreApellido_aux[0] != '\0') {
		strcpy(v[c].nombreApellido, nombreApellido_aux);
		printf("Ingrese DNI del paciente: ");
		scanf("%d", &v[c].dni);
		fgetc(stdin);
		printf("Ingrese fecha de nacimiento del paciente (dd/mm/aaaa): ");
		scanf("%d/%d/%d", &v[c].d, &v[c].m, &v[c].a);
		fgetc(stdin);
		c++;
		if (c < TAM) {
			ingresarCadena(nombreApellido_aux, LNOM, "Ingrese apellido y nombre de la persona (enter para salir): ");
		}
	}
	return c;
}

void ingresarCadena(char nombreApellido_aux[], int n, char mensaje[]) {
	int i = 0;
	printf("%s", mensaje);
	fgets(nombreApellido_aux, LNOM, stdin);
	while (nombreApellido_aux[i] != '\0' && nombreApellido_aux[i] != '\n') 
		i++;
	if (nombreApellido_aux[i] == '\n')
		nombreApellido_aux[i] = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}

void ordenar(paciente v[], int c) {
	int i, j;
	paciente aux;
	for (i = 1; i < c; i++) {
		for (j = 1; j <c-1; j++){
			if (strcmp(v[j].nombreApellido, v[j + 1].nombreApellido) > 0) {
				aux = v[j];
				v[j] = v[j + 1];
				v[j + 1] = aux;
			}
		}
	}
}

void mostrar(paciente v[], int c) {
	int i=0, dd,mm,aa, mayores55 = 0;
	printf("Ingrese la fecha de hoy (dd/mm/aaaa): ");
	scanf("%d/%d/%d", &dd, &mm, &aa);
	fgetc(stdin);
	FILE * arch = fopen("paciente.dat" ,"rb");
	if (arch == NULL) {
		printf("Error de apertura");
	}
	fgets(v[i].nombreApellido, LNOM, arch);
	while (!feof(arch)) {
		fscanf(arch, "%d", &v[i].dni);
		fscanf(arch, "%d/%d/%d", &v[i].d, &v[i].m, &v[i].a);
		i++;
		fgets(v[i].nombreApellido, LNOM, arch);
	}

	for (int j = 0; j < c; j++) {
		if ((v[j].a * 10000 + v[j].m * 100 + v[j].d) <= ((aa - 55) * 10000 + mm * 100 + dd))
			mayores55++;
		printf("Apellido y nombre: %s\t DNI: %d\t Fecha nacimiento: %d/%d/%d\n", v[j].nombreApellido, v[j].dni, v[j].d, v[j].m, v[j].a);
	}
	printf("Paciente mayores a 55: %d\n", mayores55);
}

/*
void mostrar(paciente v[], int c) {
	int dd, mm, aa, mayores55=0;
	printf("Ingrese la fecha de hoy (dd/mm/aaaa): ");
	scanf("%d/%d/%d", &dd, &mm, &aa);
	fgetc(stdin);
	for (int i = 0; i < c; i++) {
		if ((v[i].a * 10000 + v[i].m * 100 + v[i].d) <= ((aa - 55) * 10000 + mm * 100 + dd))
			mayores55++;
		printf("Apellido y nombre: %s\t DNI: %d\t Fecha nacimiento: %d/%d/%d\n", v[i].nombreApellido, v[i].dni, v[i].d, v[i].m, v[i].a);
	}
	printf("Paciente mayores a 55: %d\n", mayores55);
}
*/
void modificar(paciente v[], int c) {
	char nombreModificar[LNOM];
	char * p;
	int i, a = 1;
	while (a == 1) {
		ingresarCadena(nombreModificar, LNOM, "Ingrese el nombre de la persona que desea modificar: ");
		i = 0;
		p = strstr(v[i].nombreApellido, nombreModificar);
		while (p == NULL && i < c) {
			i++;
			p = strstr(v[i].nombreApellido, nombreModificar);
		}
		while (i == c) {
			ingresarCadena(nombreModificar, LNOM, "Nombre no encontrado, intente con otro: ");
			i = 0;
			p = strstr(v[i].nombreApellido, nombreModificar);
			while (p == NULL && i < c) {
				i++;
				p = strstr(v[i].nombreApellido, nombreModificar);
			}
		}
		ingresarCadena(v[i].nombreApellido, LNOM, "Ingrese nuevo nombre: ");
		printf("Ingrese nuevo DNI: ");
		scanf("%d", &v[i].dni);
		fgetc(stdin);
		printf("Ingrese nueva fecha de nacimiento (dd/mm/aaaa): ");
		scanf("%d/%d/%d", &v[i].d, &v[i].m, &v[i].a);
		fgetc(stdin);
			
		printf("Desea modificar a alguien mas? 1- Si  2- No ");
		scanf("%d", &a);
		fgetc(stdin);
	}
}


void baja(paciente v[], int c) {
	char nombreBaja[LNOM];
	int a = 1,i;
	char *p;
	while (a == 1 && c > 0) {
		ingresarCadena(nombreBaja, LNOM, "Ingrese el nombre de la persona que quiere eliminar: \n");
		i = 0;
		p = strstr(v[i].nombreApellido, nombreBaja);
		while (p == NULL && i<c) {
			i++;
			p = strstr(v[i].nombreApellido, nombreBaja);
		}
		while (i == c) {
			ingresarCadena(nombreBaja, LNOM, "Nombre no encontrado. Ingrese otro nombre: \n");
			i = 0;
			p = strstr(v[i].nombreApellido, nombreBaja);
			while (p == NULL && i<c) {
				i++;
				p = strstr(v[i].nombreApellido, nombreBaja);
			}
		}
		while (i < c) {
			v[i] = v[i + 1];
			i++;
		}
		c--;
		if (c != 0) {
			printf("Desea eliminar a otra persona? 1- Si  2- No ");
			scanf("%d", &a);
			fgetc(stdin);
			if (a == 1)
				ingresarCadena(nombreBaja, LNOM, "Ingrese el nombre de la persona que quiere eliminar: \n");
		}
	}
}
int leerArchivo(paciente v[]) {
	int i;
	FILE * arch = fopen("paciente.dat", "rb");
	if (arch == NULL) {
		printf("Error de apertura\n");
		return 1;
	}
	int cant = tamArchivo(arch)/sizeof(paciente);
	for (i = 0; i < cant; i++) {
		fread(&v[i], sizeof(paciente), 1, arch);
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


void grabarArchivo(paciente v[], int c) {
	int i;
	FILE * arch = fopen("paciente.dat", "wb");
	if (arch == NULL) 
		printf("Error de apertura");
	for (i = 0; i < c; i++)
		fwrite(&v[i], sizeof(paciente), 1, arch);
	fclose(arch);
}