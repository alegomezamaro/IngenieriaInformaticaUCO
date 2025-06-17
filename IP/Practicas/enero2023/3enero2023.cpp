#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int sumaprimo(int n){
	int suma = 0;
	for(int i=1; i < n/2; i++){
		if(n % i == 0){
			suma += i;
		}
	}
}

int main(){
	int n=9;
	cout << "Suma de los primos de " << n << " es " << sumaprimo(n);

	cin.get();
	cin.ignore();
}