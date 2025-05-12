#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Realiza la media de un conjunto de datos pedidos por el teclado. Se pediran datos hasta que el dato introducido sea menor o igual que 0//
int main(){
	int i=0, n=1, suma=0, x;

	cout << "Introduce numeros para realizar su media, cuando acabes pon 0: " << endl;
	while(n!=0){
		cin >> n;
		if(n!=0){
			suma=suma+n;
			i++;
		}
	}
	x = suma/i;
	cout << "La media de tus numeros es: " << x;
	cin.ignore();
	cin.get();
}