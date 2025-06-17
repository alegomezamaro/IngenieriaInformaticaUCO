#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int esperfecto(int v){
	int i, cont=0;
	bool perf;
	for (i=1; i<=v/2; i++){
		if (v%i ==0){ 
			cont = cont+i;
		}
	}
	if (v == cont){
		perf = true;
	}
	else{
		perf = false;
	}
	return perf;
}

int main(){
	int x;
	bool perfecto;
	cout << "Introduce un numero: ";
	cin >> x;
	perfecto = esperfecto(x);
	if (perfecto == true){
		cout << "El numero " << x << " es perfecto" << endl;
	}
	else{
		cout << "El numero " << x << " no es perfecto" << endl;
	}
	cin.ignore();
	cin.get();
}