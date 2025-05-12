#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Calcula el factorial de un numero dado por el teclado//
int main(){
	int i=1, n, suma=1;

	cout << "Introduce el numero al que quieres que se le realice el factorial: ";
	cin >> n;
	do{
		cout << " *" << i;
		suma=(suma*i);
		i++;
	}
	while(i<=n);
	cout << " =" << suma << endl;
	cin.ignore();
	cin.get();
}