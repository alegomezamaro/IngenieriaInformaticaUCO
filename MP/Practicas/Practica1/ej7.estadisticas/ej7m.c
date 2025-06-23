#include "ej7f.h"

/*
Codifica una función denominada estadisticasVector que reciba un vector de enteros y calcule,
devolviendo mediante paso de parámetros por referencia, la media, la varianza y la desviación
típica de los datos del vector. Implementa un programa que mediante funciones lea un vector de
enteros, lo imprima por pantalla, calcule las estadísticas y finalmente muestre los resultados.
*/

int main(){
	int v[TAM_vector]={3,4,5,6};
	estadisticasVector(v);
	return 0;
}
