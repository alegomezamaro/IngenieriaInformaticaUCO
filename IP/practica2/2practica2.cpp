#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Dada la serie 1+2+3+4+...+n, cree un programa que calcule el termino n introducido por el usuario//
int main(){
	int i=1, n, suma=0;

	cout << "Introduce el numero al que quieres que se le realice la serie: ";
	cin >> n;
	do{
		cout << " +" << i;
		suma=suma+i;
		i++;
	}
	while(i<=n);
	cout << " =" << suma << endl;
	cin.ignore();
	cin.get();
}