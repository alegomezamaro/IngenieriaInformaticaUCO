#include "ej7f.h"

float media(int v[]){	//Hace la media
	float suma = 0;
	for(int i=0; i<TAM_vector; i++){
		suma += v[i];
	}
	return suma/TAM_vector;
}

float varianza(float media, int v[]){	//Hace la varianza
	float suma = 0;
	for(int i=0; i<TAM_vector; i++){
		suma += v[i]*v[i];
	}
	return suma/TAM_vector - (media*media);
}

void estadisticasVector(int v[]){	//Imprime media, varianza y desviacion tipica
	float med=media(v), var=varianza(med, v), desviacion_tipica=sqrt(var);
	printf("\nEl vector tiene los valores %i, %i, %i, %i", v[0], v[1], v[2], v[3]);
	printf("\nLa media es %0.2f", med);
	printf("\nLa varianza es %0.2f", var);
	printf("\nLa desviacion tipica es %0.2f\n", desviacion_tipica);
}


