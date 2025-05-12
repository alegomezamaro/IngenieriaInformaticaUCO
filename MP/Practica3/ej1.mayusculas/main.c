#include "funciones.h"

/*
Codifica un programa en C que, utilizando funciones, abra un fichero de texto, cuyo nombre se
pedirá al usuario, y genere un nuevo fichero llamado mayusculas-nombreFicheroDeEntrada.txt,
que tenga el mismo contenido que el fichero original pero en mayúsculas.
*/

int main(){
	// Declaramos las variables
	FILE* ficheroEntrada;
	FILE* ficheroSalida;
	char nombreficheroEntrada[TAM];
	char nombreficheroSalida[TAM];

    // Coge los valores de fichero de entrada
	printf("Introduce el nombre del fichero: ");
	scanf("%s", nombreficheroEntrada);

	//Abrir el fichero entrada modo lector, si esta vacío error
	ficheroEntrada = fopen(nombreficheroEntrada, "r");
	if(ficheroEntrada==NULL){
		printf("\nError1, no se pudo abrir el fichero <%s.txt>", nombreficheroEntrada);
		exit(-1);
	}

	//Abre el fichero salida despues de nombrarlo como se desea
	strcpy(nombreficheroSalida, "mayusculas-"); //Nombras mayusculas- el fichero
	strcat(nombreficheroSalida, nombreficheroEntrada); //Añades el numbre del fichero entrada a mayusculas-
	ficheroSalida = fopen(nombreficheroSalida, "w"); //Abres el fichero salida en modo escritura
		if(ficheroSalida==NULL){
		printf("\nError2, no se pudo abrir el fichero <%s.txt>", nombreficheroSalida);
		exit(-1);
	}

	//Llamamos a la función
	convertirMayusculas(ficheroEntrada, ficheroSalida);
	
	//Cerramos los ficheros y retornamos 0
	fclose(ficheroEntrada);
	fclose(ficheroSalida);	
	return 0;
}