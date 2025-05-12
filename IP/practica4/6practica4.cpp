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
	long resultado, n, k;
	cout << "Introduce un n: ";
	cin >> n;
	cout << "Introduce un k: ";
	cin >> k;
	resultado = (factorial(n) / factorial(k) * factorial(n-k));
	cout << "El combinatorio es " << resultado << endl;
	cin.ignore();
	cin.get();
}

