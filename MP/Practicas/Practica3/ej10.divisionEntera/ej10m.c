#include "ej10f.h"
/*
Construye una función recursiva que calcule la división entera de dos números mediante el
métodos de restas sucesivas. Implementa un pequeño programa para probarla.
	Por ejemplo, si 28 es el dividendo y 9 el divisor, el programa irá restando el divisor al
	dividendo de forma sucesiva, mientras el dividendo sea mayor o igual que 0. el número de
	veces que se haga esta resta será la división entera.
	28 – 9 = 19 > 0 (1 vez)
	19 -9 = 10 > 0 (2 veces)
	10 -9 = 1 > 0 (3 veces)
	1 -9 = -8 < 0 (esta no cuenta).
	Por tanto, la división entera es 3, ya que se han realizado 3 iteraciones.
*/

int main(){
	//Definimos las variables
	int divisor;
	int dividendo;
	int division;

	//Leemos los datos
	printf("\nIntroduce el dividendo de la division: ");
	scanf("%i", &dividendo);
	printf("\nIntroduce el divisor de la division: ");
	scanf("%i", &divisor);

	//Llamamos a la funcion recursiva
	division = divisionEntera(dividendo, divisor);

	//Imprimimos el resultado
	printf("\nLa division entera de %i : %i = %i\n", dividendo, divisor, division);
	//Finalizamos
	return 0;
}