#include "ej6f.h"

/*
Se desea mostrar la equivalencia entre funciones que devuelven un resultado y funciones que
utilizan parámetros por referencia.
	a) Primera versión: función denominada media
		1. Recibe dos números num1 y num2 de tipo int pasados por valor.
		2. Devuelve como resultado la media aritmética de los números num1 y num2 pasados como
		parámetros.
	b) Segunda versión: función denominada media_referencia
		1. Recibe dos números num1 y num2 de tipo int pasados por valor.
		2. Recibe otro parámetro denominado resultado de tipo float pero pasado por referencia.
		3. La función debe asignar a resultado la media aritmética de num1 y num2.
	c) Codifica un programa que permita comprobar el funcionamiento de las dos funciones
	anteriores
*/

int main(){
	int num1, num2; 
	float resultado;
	scanf("%i", &num1);
	scanf("%i", &num2);
	float media1 = media(num1, num2);
	media_referencia(num1, num2, &resultado);
	printf("La media es %0.2f y pasada por referencia es %0.2f", media1, resultado);
	return 0;
}
