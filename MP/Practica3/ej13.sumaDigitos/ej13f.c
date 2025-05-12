#include "ej13f.h"

int sumaDigitos(int n){
	if(n<10){
		return n;
	}
	else{
		return(n%10+sumaDigitos(n/10));
	}
}