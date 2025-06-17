#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int i=2, num, cont=0;
	cout << "Introduce el numero que quieras comprobar" << endl;
	cin >> num;
	while(i <= num){
		if (num%i ==0){
			cont++;
		}
		i++;
	}
	if(cont=1){
	cout << "El numero " << num << " es primo" << endl;
	}
	else{
	cout << "El numero " << num << " no es primo" << endl;
	}

	cin.get();
	cin.ignore();
}