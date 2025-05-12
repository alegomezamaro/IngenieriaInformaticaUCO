#include "funciones.h"

int main(int argc, char* argv[]){

	if(argc != 4){

		printf("\nNúmero de argumentos incorrecto: ./ejercicio.out <fichero binario> <fichero de texto menor> <fichero de texto mayor>\n", argv[0]);
		exit(-1);
	}

	char* fb = argv[1];
	char* ftmin = argv[2];
	char* ftmax = argv[3];

	funcion(fb, ftmin, ftmax);

	return 0;
}