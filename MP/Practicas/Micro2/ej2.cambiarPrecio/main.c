#include "funciones.h"

int main(int argc, char* argv[]){
	//Verificamos que se hayan pasado la cantidad de datos correctos por terminal
	if(argc != 2){
		printf("\nError1 al acceder al programa, debe hacerlo de forma %s <nombre-fichero.bin>\n", argv[0]);
		exit(-1);
	}

	//Definimos las variables
	char* nombreFichero = argv[1];
	int codigo;
	float precio;

	//Llamamos a la funcion que comprueba si el fichero existe
	comprobarFichero(nombreFichero);

	//Una vez comprobamos que el fichero abre correctamente pedimos el codigo y el precio del producto
	printf("\nIntroduce el codigo del producto al que deseas modificarle el precio: ");
	scanf("%i", &codigo);
	printf("\nIntroduce el nuevo precio para el producto: ");
	scanf("%f", &precio);

	//Llamamos a la funcion que actualiza el precio de el producto que tiene el codigo pedido
	actualizarPrecio(nombreFichero, codigo, precio);

	//Retornamos 0 finalizando el programa
	return 0;
}