#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Realice un programa que calcule la suma  de los numeros impares hasta el numero n indicado por el usurio//
int main(){
	int i=1, n, suma=0;
	
	cout << "Introduce un numero impar, se hara la suma de todos los numeros impares hasta llegar a el: ";
	cin >> n;
	while(i<=n){
		if(n%2!=0){
			cout << " +" << i << endl;
 			suma=suma+i;
			i=i+2;
		}
		else{
			cout << "El numero es par" ;
			i=99999999;
		}
	}
	cout << "La suma da como resultado" << suma << endl;
	cin.ignore();
	cin.get();
}