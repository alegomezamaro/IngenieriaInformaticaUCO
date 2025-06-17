#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
	int i=1, num;
	cout << "Introduce el numero al que quieres que se le busquen los divisores" << endl;
	cin >> num;
	while(i <= num/2){
		if(num % i ==0){
			cout << "El numero " <<  i << " es divisor de " << num << endl;
		}
	i++;
	}

	cin.get();
	cin.ignore();
}

