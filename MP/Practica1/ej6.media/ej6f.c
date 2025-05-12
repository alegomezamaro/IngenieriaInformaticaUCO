#include "ej6f.h"

float media(int num1, int num2){	//Hace la media entre dos numeros
	return (num1 + num2)/ 2;
}

void media_referencia(int num1, int num2, float*resultado){	//Hace la media (pasando por referencia)
	*resultado = (num1 + num2)/ 2.0f;
}
