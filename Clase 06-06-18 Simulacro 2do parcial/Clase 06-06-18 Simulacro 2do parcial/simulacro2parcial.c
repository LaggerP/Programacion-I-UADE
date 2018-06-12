/*SUPONEMOS QUE TENEMOS UN ARCHIVO DE TEXTO CON LOS SIGUIENTES DATOS
APELLIDO,NOMBRE
LEGAJO
E O S // NO HAY MAS DE 2 REGISTROS POR EMPLEADOS. NI UN EMPLEADO MAS DE UNA VEZ EN EL DIA|| PUEDE FALTAR EL DE ENTRADA O EL DE SALIDA
HH: MM
UN ARCHIVO CON LOS SIGUIENTES REGISTROS ORDENADOS POR LA HORA Y LOS MINUTOS

SE PIDE
1- CUANTO TIEMPO ESTU EL EMPLEADO
2- SE PIDE LAS INCONCISTENCIAS SI LAS HAY EJEMPLO ENTRADA SIN SALIDA O SALIDA SIN ENTRADA// LEO UN REGISTRO DEL ARCHIVO LO BUSCO EN LA LISTA, MAS FACIL POR LEGAJO QUE POR NOMBRE...SI NO ESTA LO AGREGO, SI ESTA ACTUALIZO EL DATO DE LA LISTA...SI ME VIENE OTRA ENTRADA INCONCISTENCIA AFUERA//MOSTRASR EN LAS INCONCISTENCIAS EL APELLIDO Y EL LEGAJO
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define LNOM 50

typedef struct
{
	int h, m;
}hora;

typedef struct n
{
	char nombre[LNOM];
	int legajo;
	hora hentrada;
	hora hsalida;
	struct n* psig;
}nodo, *pNodo;

void vincular(pNodo **pini, pNodo nuevo, pNodo *actual, pNodo *anterior);
void listar(pNodo inicio);
void compararhorarios(pNodo *pini, pNodo nuevo);
void sacarEnter(char aux[]);
void listarinc(pNodo inicio);

int main(){
	FILE* arch;
	pNodo inicio = NULL;
	pNodo nuevo = NULL;
	char aux[100];
	int flag=0;
	arch = fopen("Empleados.txt", "rt");
	if (arch == NULL){
		puts("Error,apertura de archivo");
		return 1;
	}
	fgets(aux, 100, arch);
	while (!feof(arch)){
		nuevo = (pNodo)malloc(sizeof(nodo));
		if (nuevo != NULL) {
			sacarEnter(aux);
			strcpy(nuevo->nombre, aux);
			fgets(aux, 100, arch);
			nuevo->legajo = atoi(aux);
			fgets(aux, 100, arch);
			if (aux[0] == 'E') {
				fscanf(arch, "%d:%d", &(nuevo->hentrada.h), &(nuevo->hentrada.m));
				nuevo->hsalida.h = -1;
			}
			else {
				fscanf(arch, "%d:%d", &(nuevo->hsalida.h), &(nuevo->hsalida.m));
				nuevo->hentrada.h = -1;
			}
				 fgets(aux, 100, arch);
		}
		else {
			puts("NO HAY MEMORIA INTENTE MAS TARDE");
			return 1;
		}
		fgets(aux, 100, arch);
		compararhorarios(&inicio, nuevo);
	}
	listar(inicio);
	listarinc(inicio);
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

void compararhorarios(pNodo *pini,pNodo nuevo){
	int flag = 0;
	pNodo actual = *pini, anterior = NULL;
	while (actual != NULL){
		if (actual->legajo == nuevo->legajo){
			flag = 1;
			if (actual->hentrada.h != -1 && nuevo->hsalida.h != -1){
				actual->hsalida.h = nuevo->hsalida.h;
				actual->hsalida.m = nuevo->hsalida.m;
			}
			if (actual->hsalida.h != -1 && nuevo->hentrada.h != -1){
				actual->hentrada.h = nuevo->hentrada.h;
				actual->hentrada.m = nuevo->hentrada.m;
			}
		}
		anterior = actual;
		actual = actual->psig;
	}
	if (flag == 0)
		vincular(&pini, nuevo, &anterior,&actual);
}

void listar(pNodo inicio){
	float tiempoh, tiempom;
	while (inicio != NULL){
		if (inicio->hentrada.h != -1 && inicio->hsalida.h != -1) { // si la persona no es inconsistente 
			tiempoh = inicio->hsalida.h - inicio->hentrada.h;
			tiempom = inicio->hsalida.m - inicio->hentrada.m;
			if (tiempom < 0) {
				tiempom = tiempom + 60;
				tiempoh = tiempoh - 1;
			}
			printf("%s\n%d\n%2.f:%2.f\n", inicio->nombre, inicio->legajo, tiempoh, tiempom);
		}
		inicio = inicio->psig;
	}
}

void listarinc(pNodo inicio){
	printf("Empleados con inconcistencias\n");
	while (inicio != NULL){
		if (inicio->hentrada.h == -1 || inicio->hsalida.h == -1) {
			printf("%s\n%d\n", inicio->nombre, inicio->legajo);
		}
		inicio = inicio->psig;
	}
}

void vincular(pNodo **pini, pNodo nuevo, pNodo *anterior, pNodo *actual){
	if (**pini == NULL){
		nuevo->psig = NULL;
		**pini = nuevo;
	}
	else if (*actual == NULL) {
		(*anterior)->psig = nuevo;
		nuevo->psig = *actual;
	}
}
