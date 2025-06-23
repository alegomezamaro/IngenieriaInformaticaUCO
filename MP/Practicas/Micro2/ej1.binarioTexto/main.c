#include "funciones.h"

//Pasar el fichero binario con estructura producto a un fichero de texto

int main(int argc , char *argv[]){

	//Verificamos que se han pasado bien los argumentos
	if(argc != 3){
		printf("\nSe han introducido los parametros de forma incorrecta, pasarlos de forma: \n%s <nombre-fichero-binario.bin> <nombre-fichero-texto.txt>\n", argv[1]);
		exit(-1);
	}

	//Definimos las variables respecto a los argumentos
	char *nombreFicheroBinario = argv[1];
	char *nombreFicheroTexto = argv[2];

	//Llamamos a las funciones
	comprobarExistenciaFichBin(nombreFicheroBinario);
	comprobarExistenciaFichTexto(nombreFicheroTexto);
	GeneraFicheroTexto(nombreFicheroBinario, nombreFicheroTexto);

	//Retornamos 0 y finalizamos el programa
	return 0;
}