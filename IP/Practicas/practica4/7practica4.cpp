#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void ndivisores(int v){
	int i;
	for (i=1; i<=v/2; i++){
		if (v%i ==0){
			cout << i << " es divisor de " << v << endl;
		}
		i++;
	}
}

int main(){
	int x;
	cout << "Introduce un numero: ";
 	cin>> x;
	ndivisores(x);
	cin.ignore();
	cin.get();
}
