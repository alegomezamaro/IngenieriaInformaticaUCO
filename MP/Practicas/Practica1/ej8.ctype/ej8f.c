#include "ej8f.h"

void estadisticasCadena(char cadena[TAM_char]){	//Te proporciona un contador y lo imprime
	int digitos=0, mayusculas=0, minusculas=0, espacios=0;
	
	
	for(int i=0; i<TAM_char; i++){
		if(isdigit(cadena[i]) != 0){	//Dígitos
			digitos++;
		}
		if(isupper(cadena[i]) != 0){	//Mayúsculas
			mayusculas++;
		}
		if(islower(cadena[i]) != 0){	//Minúscula
			minusculas++;
		}
		if(isspace(cadena[i]) != 0){	//Espacios
			espacios++;
		}
	}
	printf("\nLa cadena es <%s>", cadena);
	printf("\nEn la cadena hay %i digitos", digitos);
	printf("\nEn la cadena hay %i mayusculas", mayusculas);
	printf("\nEn la cadena hay %i minusculas", minusculas);
	printf("\nEn la cadena hay %i espacios\n", espacios);
}
