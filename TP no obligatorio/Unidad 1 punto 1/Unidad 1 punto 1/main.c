#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int a, b, c;
	printf("Ingrese primer numero:");
	scanf("%d", &a);
	printf("Ingrese segundo numero:");
	scanf("%d", &b);
	printf("Ingrese tercer numero:");
	scanf("%d", &c);
	if (a < b) {
		if (a < c) {
			printf("El primer numero es menor (numero cargado: %d)",a);
		}
	} 
	else if (b < a) {
		if (b < c) {
			printf("El segundo numero es menor (numero cargado: %d)",b);
		}
		else if (c < a) {
			if (c < b) {
				printf("El tercer numero es menor (numero cargado: %d)", c);
			}
		}
	}

	else
		printf("No hay menor estricto \n");

	//cuando se crea el proyecto como proyecto vacio de entrada, poner esto para que no se cierre la ventana.
	//bla funcion system necesita que se agrege un #include <stdlib.h>
	system("pause");
	return 0;
}