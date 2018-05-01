/*

Busqueda binaria planteada por la profesora:


	int busquedaBinaria(int v[], int c, int dato_a_buscar) {
		int pos = -1;
		int ini = 0; //posicion inicial del vector
		int fin = c - 1; //posicion final del vector
		int medio;
		while (ini <= fin && pos == -1) {
			medio = (ini + fin) / 2;
			if (v[medio] == dato_a_buscar) {
				pos = medio;
			}
			else if (dato_a_buscar < v[medio]) {
				fin = medio - 1;
			}
			else
				ini = medio + 1;
		}
		return pos;
	}


*/
