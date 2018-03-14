#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

 

int main(void) {
	int a, b;
	printf("Ingrese un numero:");
	scanf("%d", &a);
	printf("Ingrese un nuevo numero:");
	scanf("%d", &b);
	printf("%d + %d = %d \n", a,b, a+b);
	//cuando se crea el proyecto como proyecto vacio de entrada, poner esto para que no se cierre la ventana.
	//bla funcion system necesita que se agrege un #include <stdlib.h>
	system("pause"); 
	return 0;
}