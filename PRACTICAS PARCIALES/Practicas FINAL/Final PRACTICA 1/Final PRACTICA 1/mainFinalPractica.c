/*
	Dado un archivo de texto, facturas.txt con los siguientes datos:
		Nro de factura (comienza con un #)
		Nro vendedor
		Fecha de factura (aaaa/mm/dd)
		Codigo de artículo
		Cantidad
		Precio unitario

	En cada factura puede haber 1 o más artículos en cuyo caso cada artículo se guarda con código de articulo, cantidad y precio unitario, un vendedor puede tener una o más facturas.
	Se dispone además de un archivo vendedores.txt que contiene nombre y nro de vendedor.
	Se pide informar ordenados alfabéticamente por nombre de vendedor, las comisiones y quién fue el vendedor que más vendió.
	Las comisiones son del 10% sobre el total facturado más un plus del 5% para el vendedor que más vendió.

		Facturas.txt
		#0001
		12562
		2013/12/08

		2561
		13
		12,5

		4598
		56
		3,98

		562123
		6,5
		#0002
		12561
		2013/12/08
		2365
		12
		9,85
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 200


 //se va a poseer una estructura especifica para archivo facturas.txt y otra para vendedores.txt

typedef struct {
	int d, m, a;
}calendario;

typedef struct {
	int codArticulo;
	int cantidad;
	float precio;
}articulo;

typedef struct a {
	char factura[N];
	int vendedor;
	float monto;
	calendario fecha;
	articulo producto;
	struct a *pSig;
}nodoF, *pFactura;

typedef struct b {
	char nombre[N];
	int numeroVendedor;
	float comision;
	struct b *pSig;
}nodoV, *pVendedor;


void sacarEnter(char aux[]);
void vincularInfoFactura(pFactura *inicioF, pFactura nuevoF);
void vincuarInfoVendedor(pVendedor *inicioV, pVendedor nuevoV);
void compararVentaFactura(pFactura inicioF, pVendedor inicioV);
void mostrar(pVendedor inicioV, pFactura inicioF);
int calcularComisionMasAlta(pVendedor inicioV, pFactura inicioF, float masAlta);


int main(void) {
	pFactura inicioF = NULL;
	pFactura nuevoF = NULL;
	pVendedor inicioV = NULL;
	pVendedor nuevoV = NULL;
	int actual; //nos va a decir en donde se encuentra el cursor
	char aux[N];
	char caracter;
	FILE * archF = fopen("facturas.txt", "rt");
	FILE * archV = fopen("vendedores.txt", "rt");
	if (archF == NULL || archV == NULL) {
		printf("Error de apertura");
	}
	// obtenemos los datos del archivo factura
	fgets(aux, N, archF);
	while (!feof(archF)) {
		nuevoF = (pFactura)malloc(sizeof(nodoF));
		if (nuevoF != NULL) {
			sacarEnter(aux);
			strcpy(nuevoF->factura, aux);
			fscanf(archF, "%d", &nuevoF->vendedor);
			fgetc(archF);
			fscanf(archF, "%d/%d/%d", &nuevoF->fecha.d, &nuevoF->fecha.m, &nuevoF->fecha.a);
			fgetc(archF);
			//una vez que se carga el codigo factura/numero vendedor y fecha se comienza a cargar todos los datos de la venta hasta encontrar el proximo #.

			fscanf(archF, "%d", &nuevoF->producto.codArticulo);
			fgetc(archF);
			fscanf(archF, "%d", &nuevoF->producto.cantidad);
			fgetc(archF);
			fscanf(archF, "%f", &nuevoF->producto.precio);
			fgetc(archF);
			nuevoF->monto = nuevoF->monto + (nuevoF->producto.cantidad * nuevoF->producto.precio);
			fgetc(archF);   //   saca el enter del buffer
			actual = ftell(archF);
			caracter = fgetc(archF);//obtenemos posible #
			while (caracter != '#' && !feof(archF)) {
				fseek(archF, actual, SEEK_SET);
				fscanf(archF, "%d", &nuevoF->producto.codArticulo);
				fgetc(archF);
				fscanf(archF, "%d", &nuevoF->producto.cantidad);
				fgetc(archF);
				fscanf(archF, "%f", &nuevoF->producto.precio);
				fgetc(archF);
				nuevoF->monto = nuevoF->monto + (nuevoF->producto.cantidad * nuevoF->producto.precio);
				actual = ftell(archF);
				caracter = fgetc(archF);//obtenemos posible #
			}
			//nuevoV->comision = nuevoF->monto;
		}
		else {
			printf("No hay espacio suficiente para archivo facturas");
		}
		vincularInfoFactura(&inicioF, nuevoF);
		fgets(aux, N, archF);
		
	}
	// se obtienen los datos de los vendedores
	fgets(aux, N, archV);
	while (!feof(archV)) {
		nuevoV = (pVendedor)malloc(sizeof(nodoV));
		if (nuevoV != NULL) {
			sacarEnter(aux);
			strcpy(nuevoV->nombre, aux);
			fscanf(archV, "%d", &nuevoV->numeroVendedor);
			fgetc(archV);
			nuevoV->comision = 0;
		}
		else {
			printf("No hay espacio suficiente para archivo ventas");
		}
		fgets(aux, N, archV);
		compararVentaFactura(inicioF, nuevoV);
		vincuarInfoVendedor(&inicioV, nuevoV);
	}
	mostrar(inicioV, inicioF);
	system("pause");
 	return 0;
}

void vincularInfoFactura(pFactura *inicioF, pFactura nuevoF) {
	pFactura actual = *inicioF;
	pFactura anterior = NULL;
	if (*inicioF == NULL) {
		nuevoF->pSig = NULL;
		*inicioF = nuevoF;
	}
	else if(actual == NULL){
		anterior->pSig = nuevoF;
		nuevoF->pSig = actual;
	}
}

void vincuarInfoVendedor(pVendedor *inicioV, pVendedor nuevoV) {
	pVendedor actual = *inicioV;
	pVendedor anterior = NULL;
	if (actual == NULL) { //inicio lista vacia 
		nuevoV->pSig = NULL;
		*inicioV = nuevoV;
	}
	else if (strcmp((*inicioV)->nombre, nuevoV->nombre) > 0) { //inicio principio de lista lista NO vacia
		nuevoV->pSig = actual;
		*inicioV = nuevoV;
	}
	else {
		while (actual != NULL && strcmp((*inicioV)->nombre, nuevoV->nombre) < 0) { //avanzo por la lista
			anterior = actual;
			actual = actual->pSig;
		}
		if (actual==NULL) { //al final de la lista
			nuevoV->pSig = NULL;
			anterior->pSig = nuevoV;
		}
		else { //entre nodosd
			anterior->pSig = nuevoV;
			nuevoV->pSig = actual;
		}
	}
}

void compararVentaFactura(pFactura inicioF, pVendedor nuevoV) {
	pFactura actual = inicioF;
	pFactura anterior = NULL;
	while (actual != NULL) {
		if (inicioF->vendedor == nuevoV->numeroVendedor) {
			nuevoV->comision =((nuevoV->comision+(actual->producto.cantidad*actual->producto.precio)*10)/100);
			//nuevoV->comision = ((nuevoV->comision) + (actual->monto * 10) / 100);
		}
		anterior = actual;
		actual = actual->pSig;
	}
}

void sacarEnter(char aux[]) {
	char *p = strchr(aux, '\n');
	if (p != NULL)
		*p = '\0';
	else
		while (fgetc(stdin) != '\n')
			;
}


void mostrar(pVendedor inicioV, pFactura inicioF) {
	float masAlta=0;
	while (inicioV != NULL) {
		if (inicioV->comision == 0) {
			printf("==================VENDEDOR SIN COMISIONES:==================\n");
			printf("Nombre:%s\nNumero vendedor: %d\nComisiones: %f\n\n", inicioV->nombre, inicioV->numeroVendedor, inicioV->comision);
		}
		else {
			printf("==================VENDEDOR CON COMISIONES:==================\n\n\n");
			masAlta = (float)calcularComisionMasAlta(inicioV, inicioF, masAlta);
			printf("\t\tVENDEDOR CON MAYOR COMISION:\n");
			printf("Nombre:%s\nNumero vendedor: %d\nComisiones: %f\n\n", inicioV->nombre, inicioV->numeroVendedor, masAlta);
			printf("***************************************************\n\n");
			printf("Nombre:%s\nNumero vendedor: %d\nComisiones: %f\n\n", inicioV->nombre, inicioV->numeroVendedor, inicioV->comision);
		}
		inicioV = inicioV->pSig;
	}
}


int calcularComisionMasAlta(pVendedor inicioV, pFactura inicioF,float masAlta) {
	pVendedor actual = inicioV;
	pVendedor anterior = NULL;
	pVendedor actualSig = actual->pSig;
	pVendedor aux=NULL;
	while (actual != NULL) {
		if (actual->comision > actualSig->comision) {
			aux = actual;
		}
		anterior = actual;
		actual = actual->pSig;
	}
	masAlta = (float)aux->comision;
	return (masAlta) * 0.5;
}



/*			do {
				
				fscanf(archF, "%d", &nuevoF->producto.codArticulo);
				fgetc(archF);
				fscanf(archF, "%d", &nuevoF->producto.cantidad);
				fgetc(archF);
				fscanf(archF, "%f", &nuevoF->producto.precio);
				fgetc(archF);
				caracter = fgetc(archF); //obtenemos posible #
				vincularInfoFactura(&inicioF, nuevoF);
				fseek(archF, caracter, SEEK_SET);
			} while (caracter != '#' && !feof(archF));*/