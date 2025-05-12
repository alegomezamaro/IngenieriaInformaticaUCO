#include "ej12f.h"

void leerFraccion(struct Fraccion *division){ //Lee la funciom
	printf("\nNumerador:");
	scanf("%i", &division->numerador);
	printf("\nDenominador:");
	scanf("%i", &division->denominador);
}

void imprimirFraccion(struct Fraccion *division){	//Imprime la funcion
	printf("%i/%i", division->numerador, division->denominador);
}

struct Fraccion multiplicar(struct Fraccion *division1, struct Fraccion *division2){	//Multiplica ambas fracciones
	leerFraccion(division1);
	imprimirFraccion(division1);
	leerFraccion(division2);
	imprimirFraccion(division2);
	struct Fraccion resultado, multiplicacion1=*division1, multiplicacion2=*division2;
	resultado.numerador= multiplicacion1.numerador * multiplicacion2.numerador;
	resultado.denominador= multiplicacion1.denominador * multiplicacion2.denominador;
	return resultado;
}
