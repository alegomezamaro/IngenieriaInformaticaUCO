#include "ej10f.h"

int divisionEntera (int dividendo, int divisor){
		//Comprobamos que dividendo < 0. Si lo es retornamos resultado
		if(dividendo - divisor < 0){ 
			return 0;
		}
		else{
			//Si no, llamamos a la funcion recursiva
			return 1 + divisionEntera (dividendo - divisor, divisor);
		}
}