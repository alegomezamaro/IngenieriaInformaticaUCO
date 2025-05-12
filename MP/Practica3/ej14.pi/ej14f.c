#include "ej14f.h"

float terminoLeibniz(int n){
	return 4.0*(pow(-1.0, n)/((2.0*n)+1.0));
}

float sumatorioPi(int n){
	if(n==0){
		return terminoLeibniz(0);
	}
	else{
		return terminoLeibniz(n)+sumatorioPi(n-1);
	}
}