#include "funciones.h"

//Comprueba que el fichero de entrada existe
void comprobarFichero(char* nombreFichero){

	//Creamos un fichero al que le asociamos el nombre dado
	//Lo abrimos en modo lectura ya que unicamente queremos saber si existe
	FILE* f = fopen(nombreFichero, "rb");

	//Si el fichero no existe error
	if(f == NULL){
		printf("\nError2, el fichero %s no existe\n", nombreFichero);
		exit(-1);
	}

	//Si existe lo cerramos
	fclose(f);
}

//Actualiza el precio del producto enlazado al codigo
void actualizarPrecio(char* nombreFichero, int codigo, float precio){

	//Generamos una estructura p
	struct producto p;

	//Creamos un fichero al que le asociamos el nombre dado
	//Lo abrimos en modo escritura ya que queremos sobreescribirlo
	FILE* f = fopen(nombreFichero, "rb+");

	//Si el fichero no existe error
	if(f == NULL){
		printf("\nError3, el fichero %s no existe\n", nombreFichero);
		exit(-1);
	}

	//Mientra haya una estructura dentro del fichero binario recorre en busca del codigo dado
	while(fread(&p, sizeof(struct producto), 1, f)==1){
		if(codigo == p.cod){

			//Le damos el nuevo valor
			p.precio = precio;
		}
		fseek(f, -1*sizeof(struct producto), 1);
		fwrite(&p, sizeof(struct producto), 1, f);
	}

	//Cerramos el fichero
	fclose(f);
}