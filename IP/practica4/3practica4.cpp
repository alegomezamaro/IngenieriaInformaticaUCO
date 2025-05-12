#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

long factorial(int v){
	int i=1;
	long fact=1;
	for (i=1; i<=v; i++){
		fact = fact*i;
	}
	return fact;
}

int main(){
	long resultado, x;
	cout << "Introduce un n: ";
	cin >> x;
	resultado = factorial(x);
	cout << "El factorial es " << resultado << endl;
	cin.ignore();
	cin.get();
}

