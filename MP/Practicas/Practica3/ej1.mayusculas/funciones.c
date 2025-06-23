#include "funciones.h"

void convertirMayusculas(FILE *ficheroEntrada, FILE *ficheroSalida){ //Crea el mismo fichero en mayuscula

	//Definimos las variables
	int caracter;

	//Iguala caracter a el primer caracter del fichero
	caracter = fgetc(ficheroEntrada);

	//Convierte en mayuscula el fichero
	while(caracter != EOF){ // Coge los elementos de uno en uno hasta EOF (End Of File)
		fputc(toupper(caracter), ficheroSalida);
		caracter = fgetc(ficheroEntrada);
	}
}