#include "funciones.h"

//Comprueba si un fichero binario se genera correctamente 
void comprobarExistenciaFichBin(char *nombreFicheroBinario){
	//Abrimos el fichero binario
	FILE *ficheroBinario;

	//Verificamos que se abra correctamente, sino error
	if((ficheroBinario = fopen(nombreFicheroBinario, "rb")) == NULL){
		printf("\nError1, el fichero binario no se ha abierto correctamente\n");
		exit(-1);
	}

	//Cerramos el fichero
	fclose(ficheroBinario);
}

//Comprueba si un fichero de texto se genera correctamente
void comprobarExistenciaFichTexto(char *nombreFicheroTexto){

	FILE *fichero;
	if((fichero = fopen(nombreFicheroTexto, "r")) != NULL){
		printf("Error2, el fichero de texto ya existe\n");
		fclose(fichero);
		exit(-1);
	}
}

//Genera un fichero de texto con los datos del fichero binario
void GeneraFicheroTexto(char *nombreFicheroBinario, char *nombreFicheroTexto){
	struct producto p;

	//Abrimos el fichero binario y generamos el de texto
	FILE *ficheroBinario;
	FILE *ficheroTexto;

	//Verificamos que se abra correctamente, sino error
	if((ficheroBinario = fopen(nombreFicheroBinario, "rb")) == NULL){
		printf("\nError3, el fichero binario no se ha abierto correctamente\n");
		exit(-1);
	}

	//Verificamos que se abra correctamente, sino error
	if((ficheroTexto = fopen(nombreFicheroTexto, "w"))== NULL){
		printf("\nError4, el fichero texto no se ha abierto correctamente\n");
		exit(-1);
	}

	//Mientras se puedan leer mas estructuras en el fichero binario, pegarlas en el fichero de texto
	while(fread(&p, sizeof(struct producto), 1, ficheroBinario) == 1){
		fprintf(ficheroTexto, "%s\n%d\n%f\n%i\n", p.nombre, p.cod, p.precio, p.unidades);
	}

	//Cerramos ambos ficheros y avisamos de que se ha acabado el proceso
	fclose(ficheroBinario);
	fclose(ficheroTexto);
}