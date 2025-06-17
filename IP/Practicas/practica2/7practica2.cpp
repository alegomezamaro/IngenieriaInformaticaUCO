#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;
//Dado un número natural N, indicar si es primo o no//
int main(){
	int i=2, n, cont=0;

	cout << "Introduce el numero al que quieres verificar si es primo: ";
	cin >> n;
	while(i<n/2 && cont==0){
		if(n%i==0){
			cont++;
		}
		i++;
	}
	if(cont!=0){
		cout<< "Tu numero no es primo" <<endl;
	} 
	else{
		cout<< "Tu numero es primo" <<endl;
	} 
	cin.ignore();
	cin.get();
}