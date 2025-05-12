#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Realiza un programa que pida 15 números al usuario y al final imprima el menor//
int main(){
	int i, n=15, x, menor=INT_MAX;

	for(i=0; i<n; i++){
		cout << "Introduce un número: ";
		cin >> x;
		if(x<menor){
			menor=x;
		}
	}
	cout << "El numero menor es ";
	cout << menor<<endl;
	cin.ignore();
	cin.get();
}

