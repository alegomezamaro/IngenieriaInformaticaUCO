#include "ej12f.h"
#define TAM_cad 100
/*
Dada una cadena c, diseña una función recursiva que cuente la cantidad de veces que aparece un
carácter x en c.
	Ejemplo: para c = “elementos de programacion” y x = 'e', el resultado es 4.
*/

int main(){
	//Definimos las variables
	char cadena[TAM_cad];
	char x;
	int resultado;

	//Lectura de datos de entrada
	printf("\nEscribe la cadena de caracteres: ");

	//Usamos fgets para poder añadir espacios en blanco
	fgets(cadena, TAM_cad, stdin);
	if(cadena[strlen(cadena)-1]=='\n'){
		cadena[strlen(cadena)-1]='\0';
	}
	printf("\nCadena leida: <%s>", cadena);
	printf("\nEscribe el caracter que se busca: ");
	scanf("%c", &x);
	printf("\nCaracter leido: <%c>", x);

	//Llamada a la funcion recursiva
	resultado = contar(cadena, x);

	//Escritura del resultado
	printf("\nEl caractar <%c> aparece %i veces en la cadena <%s>\n", x, resultado, cadena);
	
	//Finalizamos
	return 0;
}