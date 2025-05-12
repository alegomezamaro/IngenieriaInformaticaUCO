#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;

//Imprimir por pantalla los divisores de un numero en orden ascendente//
int main(){
	int i=1, n;

	cout << "Introduce el número del que quieres ver los divisores: ";
	cin >> n;
	while(i<=n/2){
		if(n%i==0){
			cout<< "Tu número es divisible entre " << i <<endl;
		}
		i++;
	}
   cin.ignore();
	cin.get();
}

