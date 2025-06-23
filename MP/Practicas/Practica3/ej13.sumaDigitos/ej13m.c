#include "ej13f.h"
/*
Codifica una función recursiva que permita sumar los dígitos de un número entero positivo.
Implementa un programa para probarla.
	Ejemplo: Entrada: 124 Resultado: 7.
*/

int main(){
	//Definimos las variables
	int n;
	int suma;

	//Lectura de datos
	printf("\nIntroduce el numero: ");
	scanf("%i", &n);

	//Llamamos a la funcion recursiva
	suma=sumaDigitos(n);

	//Imprimimos el resultado
	printf("\nEl suma de los digitos de %i es %i\n", n, suma);

	//Finalizamos
	return 0;
}