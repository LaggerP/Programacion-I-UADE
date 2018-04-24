#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(void) {
	char opcionCopiado = 's';
	printf("Desea copiar el contenido del archivo .txt en un nuevo archivo .dat? (s/n)\n");
	scanf("%c", &opcionCopiado);
	fgetc(stdin);
	if (opcionCopiado) {
		FILE *archivoTexto, *archivoBinario;
		int contenido = 0;
		archivoTexto = fopen("archivoTexto.txt", "rt");
		archivoBinario = fopen("archivoBinario.dat", "wb");
		if (archivoTexto == NULL) {
			printf("Error de apertura \n");
			return 1;
		}
		if (archivoBinario == NULL) {
			printf("Error de apertura \n");
			return 1;
		}
		while ((contenido = fgetc(archivoTexto)) != EOF)
			fputc(contenido, archivoBinario);
		fclose(archivoTexto);
		fclose(archivoBinario);
	}
	else if (!opcionCopiado)
		printf("Hasta luego!");
	system("pause");
	return 0;
}
