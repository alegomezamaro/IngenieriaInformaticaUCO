#include"funciones.h"
#include <stdio.h>
#include <math.h>

#define e 2.71

float funcionf(float valor)
{
	return (3*pow(e,valor) -2*valor);
}
float funciong(float valor)
{
	return -valor*sin(valor)+1.5;
}
float funcionz(float valor)
{
	return pow(valor,3)-2*valor +1;
}



void limpiarbuffer()
{
	int c;
	while(c=getchar()!='\n' && c!=EOF){}
}
