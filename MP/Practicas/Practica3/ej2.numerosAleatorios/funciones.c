#include "funciones.h"

void numerosAleatorios (FILE* f, int n, int min, int max){ //Genera una cantidad n de numeros aleatorios en el intervalo min-max
	//Definimos las variables
	int numero;
	srand(time(NULL));

	//Introducimos los numeros aleatorios en el fichero
	for (int i = 0; i < n; ++i){
		numero = min + rand()%(max - min + 1);
		fprintf(f, "%d, ", numero);
	}
}


