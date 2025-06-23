#include"funciones.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void aniadeMonomio(monomio **cabeza,int *nmonomios)
{
	monomio temp;
	printf("Introduzca el valor del coeficiente\n");
	scanf("%i",&temp.coef);
	
	printf("Introduzca el valor del exponente\n");
	scanf("%i",&temp.exp);
	
	

	if(contiene(*cabeza,temp)==1)
	{
		if(*cabeza==NULL)
		{
			monomio *nuevo=(monomio*)malloc(sizeof(monomio));
		
			nuevo->coef=temp.coef;
			nuevo->exp=temp.exp;

			nuevo->siguiente=*cabeza;
			*cabeza=nuevo;
		}
		else
		{
			printf("Ya existe un monomio con este grado");
			(*nmonomios)++;
		}
	}
	else
	{
		monomio *nuevo=(monomio*)malloc(sizeof(monomio));
		
		nuevo->coef=temp.coef;
		nuevo->exp=temp.exp;

		nuevo->siguiente=*cabeza;
		*cabeza=nuevo;
	}
	 
}

int contiene(monomio *cabeza,monomio temp)
{
	while (cabeza!=NULL)
	{
		if(cabeza->exp==temp.exp)
		{
			return 1;
		}
		cabeza=cabeza->siguiente;
	}
	return 0;
}

void evaluaPolinomio(monomio *cabeza,int x)
{
	float sum;
	while(cabeza!=NULL)
	{
		sum+=(cabeza->coef)*pow(x,(cabeza->exp));
		cabeza=cabeza->siguiente;
	}
	
	printf("El resultado del polinomio es %.2f\n",sum);
}

void eliminarMonomio(monomio *cabeza)
{
	monomio aux;
	int cont=0;
	monomio *anterior;
	printf("Introduzca el valor del coeficiente del monomio a borrar\n");
	scanf("%i",&aux.coef);
	printf("Introduzca el valor del exponente del monomio a borrar\n");
	scanf("%i",&aux.exp);
	
	while(cabeza!=NULL)
	{
		if((aux.coef==cabeza->coef)&&(aux.exp==cabeza->exp))
		{
			anterior->siguiente=cabeza->siguiente;
			printf("Elemento encontrado y eliminado con exito\n");
			
		}
		anterior=cabeza;
		cabeza=cabeza->siguiente;
	}
}

void imprimeMonomio(monomio *cabeza)
{
	while(cabeza!=NULL)
	{
		printf("Coeficiente =%i\tExponente=%i\n",cabeza->coef,cabeza->exp);
		cabeza=cabeza->siguiente;
	}
}
