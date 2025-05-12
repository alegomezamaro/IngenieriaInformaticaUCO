#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void divisores(int v){
	int i, cont=0;
	for (i=1; i<=v/2; i++){
		if (v%i == 0){
			cout << i << " es divisor de " << v << endl;
		}
	}
}

int main(){
	int x;
	cout << "Introduce un numero: ";
	cin >> x;
	divisores(x);
	cin.ignore();
	cin.get();
}