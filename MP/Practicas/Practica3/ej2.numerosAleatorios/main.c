#include "funciones.h"

/*
Codifica un programa en C que, utilizando funciones, cree un fichero texto con números enteros
generados aleatoriamente en un intervalo especificado por el usuario. El programa le preguntará
al usuario el nombre del fichero a crear, el número de elementos que contendrá el fichero y los
extremos superior e inferior del intervalo.
*/

int main(){

	//Definir variables
	FILE* f;
	char nombre[TAM];
	int min, max, n;

	//Introducimos el nombre del fichero y lo abrimos en modo escritura
	printf("Introduce el nombre del fichero: ");
	scanf("%s", nombre);
	f = fopen(nombre, "w");

	//Introducimos los datos
	printf("Introduzca la cantidad de números que tendrá el fichero: ");
	scanf("%d", &n);
	printf("Introduzca el valor mínimo para los números aleatorios: ");
	scanf("%d", &min);
	printf("Introduzca el valor máximo para los números aleatorios: ");
	scanf("%d", &max);

	//Llamamos a la función
	numerosAleatorios(f, n, min, max);

	//Ceramos el fichero y retornamos 0
	fclose(f);
	return 0;
}