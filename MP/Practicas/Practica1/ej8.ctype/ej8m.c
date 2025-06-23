#include "ej8f.h"

/*
Una cadena de caracteres en C es un vector de caracteres terminado en un carácter especial ('\0').
Este carácter marca la terminación de la cadena y es utilizado por las funciones de cadenas.
Teniendo esto en cuenta, codifica una función denominada estadisticasCadena que reciba una
cadena de caracteres y calcule, devolviendo mediante paso de parámetros por referencia, el
número de dígitos, mayúsculas, minúsculas y espacios que hay en la cadena. Implementa un
programa para probar la función anterior. Utiliza funciones de la librería <ctype.h> para
determinar si un carácter es dígito, mayúscula, etc.
*/

int main(){
	char cadena[TAM_char];
	gets(cadena);
	estadisticasCadena(cadena);
	return 0;	
}
