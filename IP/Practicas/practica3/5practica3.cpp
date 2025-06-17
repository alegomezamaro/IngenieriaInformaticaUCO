#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Realice un programa que vaya pidiendo numeros al usuario y continue mientras la media del mismo sea menos que 30//
int main(){
	int n=0, x=0, suma=0;
	float media;

	do{
		n++;
		cout << "Introduce un número, la aplicación se detendra cuando la media sea superior a 30: ";
		cin >> x;
		suma += x;
		media = 1.0*suma/n;
		cout << "La media vale " << media << endl;
	} 
	while(media<30);
	cin.ignore();
	cin.get();
}