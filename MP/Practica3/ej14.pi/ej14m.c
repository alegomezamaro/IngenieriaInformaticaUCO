#include "ej14f.h"
/*
Codifica una función recursiva que permita calcular el valor de π usando la serie de Leibniz.
Escribe un programa para probarla que pedirá al usuario que introduzca el número n de términos
a usar en la aproximación.
*/

int main(){
	//Definimos las variables
	int decimales;
	float resultado;

	//Leemos los datos
	printf("\nIntroduce la cantidad de terminos que se usaran en la aproximacion: ");
	scanf("%i", &decimales);

	//Llamamos a la funcion recursiva
	resultado = sumatorioPi(decimales);

	//Imprimimos resultado
	printf("\nEl numero pi con %i decimales es %f\n", decimales, resultado);

	//Finalizamos
	return 0;
}