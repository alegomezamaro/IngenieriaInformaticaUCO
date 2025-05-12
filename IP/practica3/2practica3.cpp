#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int n, mayor=0, i=0;
	while(n!=0){
		cout << "Introduce un número, cuando acabe introduzca 0 y se imprimira por pantalla"<< endl;
		cin >> n;
		if(mayor<n){
			mayor = n;
		}
	i++;
	}
	cout << "El numero mayor es " << mayor << endl;
	cin.get();
	cin.ignore();
}

