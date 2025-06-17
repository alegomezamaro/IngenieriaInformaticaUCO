#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;
//Cree un pograma que genere un numero secreto aleatorio entre 0 y 1000. El usuario tendra que acertar el numero secreto. Para cada numero introducido por el usuario, se le debera indicar si este es menor, mayor o igual al numero secreto. El problema finaliza cuando el usuario acierta el numero secreto//
int main(){
	float secreto, n, time;
	 srand(time(0));

	secreto= rand()%1001;
	cout << secreto<<endl;
	cout << "Adivina el número secreto: ";
	do{
		cin >> n;
		if(n>secreto){
			cout << "Introduce un numero mas chico: ";
		}
		else if(n<secreto){
			cout << "Introduce un numero mas grande: ";
		}
	}
	while(n!=secreto);
	cout << "Has acertado!!" << endl;
	cin.ignore();
	cin.get();
}