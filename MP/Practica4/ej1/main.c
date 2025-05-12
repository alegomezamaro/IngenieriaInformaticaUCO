#include"funciones.h"
#include <stdio.h>

/*
Dada una función, se desea conocer su valor medio en un intervalo [0, N(. Para ello,
se calculará el valor de la función en todos los valores de x en el intervalo [0, N(
con incremento de 0.2 y se obtendrá el valor medio.
Realiza un programa que:
	a) Solicite al usuario el valor de N.
	b) Solicite una función a evaluar: f (x), g(x) ó z(x).
		- f(x) = 3*e^x – 2x
		- g(x) = -x * sin(x) +1.5
		- z(x) = x^3 -2x +1
c) Muestre el valor medio de la función elegida en el intervalo indicado. Utiliza un puntero a
función para hacer la llamada a la función en el programa principal.
*/

int main()
{
	float valor;
	int funcion;
	printf("Introduzca el valor\n");
	scanf("%f",&valor);
	
	limpiarbuffer();
	printf("seleccione la funcion,1,2,3\n");
	scanf("%i",&funcion);
	
	limpiarbuffer();
	float (*funcionF)(float);

	switch(funcion)
	{
		case 1:
		{
			funcionF = funcionf;
		}break;
		case 2:
		{
			funcionF=funciong;
		}break;
		case 3:
		{
			funcionF=funcionz;
		}break;
	}
	
	if(funcionF!=NULL)
	{
		float i;
		float cont=0;
		float suma=0;
		for(i=0;i<valor;i+=0.2)
		{
			suma+=funcionF(i);
			cont++;
		}
		printf("La media es %f",(suma/cont));
	}
	
	return 0;
}
