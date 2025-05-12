#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Realice un programa que calcule la suma de los números divisibles entre 2 o 3 hasta el número n indicado por el usuario//
int main(){
	int i=2, n, suma=0;

	cout << "Introduce un numero y se sacara la suma de todos los numeros que lo forman divisibles entre 2 o 3: ";
	cin >> n;
	while(i<=n){
		if((n%2==0) or (n%3==0)){
			if((i%2==0) or (i%3==0)){
				suma=suma+i;
				cout << " +" << i;
			}
		}
		i++;
	}
	cout << " =" << suma <<endl; 
	cin.ignore();
	cin.get();
}