#include"funciones.h"
#include <stdio.h>

/*
Polinomio codificado mediante una lista simple
	- Un polinomio es una expresión algebraica de la forma:
		a⭣n *x^n + a⭣n-1 *x^n−1 + a⭣n−2 *x^n-2 ++ a⭣1 *x + a⭣0
	- A cada a⭣i *x^i se le denomina monomio, siendo a⭣i el coeficiente del monomio e i
	el exponente del monomio.
	- Se denomina polinomio a la suma algebraica de varios monomios.
	- Algunos ejemplos de polinomios son (1). (2) y (3).
	1 2x3
	2 x^37x^23x9
	3 2x^8x^36x
Un polinomio se puede representar como una lista enlazada.
	- El primer nodo de la lista representa el primer monomio del polinomio, el
	segundo nodo el segundo monomio del polinomio, y así sucesivamente.
	- Cada nodo representa un monomio del polinomio y tiene como campo dato el
	coeficiente del monomio (a) y el exponente (e).

Objetivo: Escribe un programa que, secuencialmente, permita:
	- Crear un polinomio. El programa preguntará cuántos monomios tendrá el
	polinomio y se creará un polinomio preguntando al usuario el coeficiente y el
	exponente de cada monomio.
	- Obtener una tabla de valores de un polinomio para valores de x = 0.0, 0.5, 1.0, 1.5, ..., 5.0
		Ejemplo: Para el polinomio (1) tendríamos la siguiente salida:
			(x=0.0, 3), (x=0.5, 4), (x=1.0, 5), (x=1.5, 6), ..., (x=5.0, 13)
	- Eliminar del polinomio el término con exponente e que se pedirá por pantalla
	Implementa para ello, al menos, las siguientes funciones:
	- contiene. Comprueba si ya hay en la lista un monomio con un determinado
	exponente.
	- anyadeMonomio. Inserta un nuevo monomio en el polinomio. No se permitirá
	más de un monomio con un determinado exponente, para lo cual se utilizará la
	función contiene antes de realizar la inserción. Implementad una inserción por
	delante. Como trabajo práctico más avanzado, podéis implementar una inserción
	ordenada (esto último es opcional).
	- evaluaPolinomio. Evalúa el polinomio para un valor concreto de x.
	- eliminaMonomio. Elimina, si existe, el monomio de exponente e (parámetro de la
	función).
	- muestraPolinomio. Muestra por pantalla el polinomio.
*/

int main()
{
	int nmonomios,i,x,seleccion;
	monomio *cabeza=NULL;
	
	
	printf("Cuantos monomios tendra el polinomio\n");
	scanf("%i",&nmonomios);
	
	for(i=0;i<nmonomios;i++)
	{
		aniadeMonomio(&cabeza,&nmonomios);
	}
	
	printf("Hasta aqui llega\n");
	getchar();
	
	imprimeMonomio(cabeza);

	printf("Introduzca un valor x para la funcion\n");
	scanf("%i",&x);
	
	evaluaPolinomio(cabeza,x);
	
	eliminarMonomio(cabeza);
	
	printf("Desea recalcular la funcion?\n yes-1 no-2\n");
	scanf("%i",&seleccion);
	
	if(seleccion==1)
	{
		evaluaPolinomio(cabeza,x);
		imprimeMonomio(cabeza);
	}
	
	
	return 0;
}
