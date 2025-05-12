#include "ej12f.h"

int main(){
	struct Fraccion division1, division2;
	struct Fraccion resultado = multiplicar(&division1,&division2);
	printf("\nEl resultado es %i/%i", resultado.numerador, resultado.denominador);
	return 0;
}
