#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
//Imprimir por pantalla los n primeros términos la sucesion de Fibonacci//
int main(){
	int a=0, b=1, c=0, n, i=3;

	cout << "Introduce la cantidad de numeros de la sucesion de Fibonacci que quieres que aparezcan: ";
	cin >> n;
	if(n>=1){
		cout<< a << " . ";
	}
	if(n>=2){
		cout<< b << " . ";
	}
	while(n>=3 && i<=n){
			c=a+b;
			cout<< c << " . ";
			a=b;
			b=c;
			i++;
	}
    cin.ignore();
		cin.get();
}