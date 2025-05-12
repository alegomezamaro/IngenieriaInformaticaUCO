#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Imprimir por pantalla los divisores de un número en orden descendente//
int main(){
	int i, n;

	cout << "Introduce el numero del que quieres ver los divisores: ";
	cin >> n;
	i=(n/2);
	while(i!=0){
		if(n%i==0){
			cout<< "Tu numero es divisible entre " << i <<endl;
		}
		i=(i-1);
	}
   cin.ignore();
	cin.get();
}
