#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int espar(int v){
	bool par;
	if (v%2 ==0){
		par = true;
	}
	else{
		par = false;
	}
	return par;
}

int main(){
	int n;
	bool resultado = espar(n);
	cout << "Introduce un numero: ";
	cin >> n;
	if (resultado == true){
		cout << "El numero " << n << " es par" << endl;
	}
	else if (resultado == false){
		cout << "El numero " << n << " es impar" << endl;
	}
	cin.ignore();
	cin.get();
}