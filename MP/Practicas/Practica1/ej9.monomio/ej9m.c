#include "ej9f.h"

/*
Un monomio (5x3) puede codificarse en C mediante una estructura con dos campos enteros
coeficiente y grado (ej. coeficiente=5, grado=3). Por su parte, un polinomio es una sucesión de
monomios de diferente grado (5x3 + 7x2 + 4x5).
	a) Implementa una función denominada leerMonomio, que reciba una estructura pasada por
	referencia y permita leer los datos de un monomio.
	b) Implementa una función denominada imprimirMonomio, que reciba una estructura por
	valor y muestre el coeficiente y el grado del monomio
	c) Utilizando las funciones anteriores, en el programa principal lee y escribe un polinomio
	(vector de monomios). Por simplicidad, no introducir monomios con el mismo exponente.
	d) Crea una función que, usando paso de parámetros por referencia, devuelva el monomio de
	mayor grado y el de menor grado. Utilízala en tu programa.
	e) Crea un función que evalúe un polinomio en un punto X. Utilízala en tu programa.
*/

int main(){

	struct Monomio m;

    leerMonomio(&m);
    printf("\n");
    imprimirMonomio(m);
    printf("\n");

    struct Monomio p[TAM];

    leerPolinomio(p);
    imprimirPolinomio(p);

    struct Monomio menor;
    struct Monomio mayor;

    mayorMenor(p, &menor, &mayor);
    printf("\nMayor: ");
    imprimirMonomio(mayor);
    printf("\nMenor: ");
    imprimirMonomio(menor);
    printf("\n");

    evaluarPolinomio(p);
	
	return 0;
}
