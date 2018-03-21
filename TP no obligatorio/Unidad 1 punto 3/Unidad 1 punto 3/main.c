#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int calculcadorGastos(int *cantViajes, int *totalGasto);

int main(void) {
	int cantViajes = 0, totalGasto=0;
	printf("Ingrese la cantidad de viajes que realizo: \n");
	scanf("%d", &cantViajes);
	int calculadorGastos(cantViajes, totalGasto);
	printf("La cantidad de dinero que debe pagar es: $%d", calculadorGastos);
	system("pause");
	return 0;
}


int calculcadorGastos(int *cantViajes, int *totalGasto) {

	if (*cantViajes<=20) {
		*totalGasto = *cantViajes * 4.5;
	}
	else if (*cantViajes > 20 && *cantViajes <= 30) {

		*totalGasto = 20 * 4.5 + (*cantViajes - 20) * 3.60;
	}
	else if (*cantViajes > 30 && *cantViajes <= 40) {
		*totalGasto = 20 * 4.5 + (*cantViajes - 20) * 3.60 + (*cantViajes - 40) * 3.15;
	}
	else if (*cantViajes > 40) {
		*totalGasto = 20 * 4.5 + (*cantViajes - 20) * 3.60 + (*cantViajes - 40) * 3.15 + (*cantViajes - 41) * 2.70;
	}
	return totalGasto;
}