#include "ej12f.h"

int contar(char cadena[], char x){
	//Si se ha llegado al final de la cadena, termina el programa
	if(cadena[0] == '\0'){
		return 0;
	}

	//Si el caracter esta en la cadena
	else if(cadena[0] == x){
		return contar(cadena+1, x)+1;
	}

	//Si el caracter no esta en la cadena
	else{
		return contar(cadena+1, x);
	}
}