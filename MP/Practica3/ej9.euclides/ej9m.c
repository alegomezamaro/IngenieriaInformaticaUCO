#include "ej9f.h"
/*
Escribe una solución recursiva que calcule el algoritmo de Euclides, usado para calcular el
máximo común divisor de dos enteros. El algoritmo de Euclides se describe del siguiente modo:
	mcd(x, y) = x, si y = 0 
	mcd(x, y) = mcd(y, mod(x,y)) si y > 0
	Antes de llamar a la función, comprobar que x >= y
*/

int main(){
	//Definimos las variables
	int x, y, resultado; 

	//Introducimos los numeros a los que buscamos hacer el calculo
	printf("\nIntroduce los valores (float) a los que hay que hacer el algoritmo de Euclides: ");
	printf("\nx: ");
	scanf("%i", &x);
	printf("\ny: ");
	scanf("%i", &y);

	//Comprobamos que x >= y para hacer el mcd de x e y. Si no, hacemos el mcd de y y x
	if(x >= y){
		resultado = mcd(x, y);
	}
	else{
		resultado = mcd(y, x);	
	}
	//Imprimimos el resultado y finalizamos
	printf("\nEl maximo comun divisor de %i y %i es %i\n", x, y, resultado);
	return 0;
}