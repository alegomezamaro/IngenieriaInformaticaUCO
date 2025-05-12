#include "ej9f.h"

//Maximo comun divisor recursivo
int mcd(int x, int y){
	if(y==0){
		return x;
	}
	else{
		return mcd(y, x%y);
	}
}