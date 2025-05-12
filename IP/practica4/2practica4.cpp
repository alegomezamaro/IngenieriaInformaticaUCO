#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

long esprimo(int v){
	int i, cont=0;
	bool primo;
	for(i=2; i<=v/2; i++){
		if(v%i ==0){
			cont++;
		}
	}
	if (cont == 0){
		primo = true;
	}
	else{
		primo = false;
	}
	return primo;
}

int main(){
	int x;
	bool resultado = esprimo(x);
	cout << "Introduce un numero: ";
	cin >> x;
	if (esprimo(x) == true){
		cout << "El numero " << x << " es primo";
	}
	else{
		cout << "El numero " << x << " no es primo";
	}
	cin.ignore();
	cin.get();
}
