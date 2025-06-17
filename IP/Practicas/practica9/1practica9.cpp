#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(int argc, char **argv	){
	float num, raiz;
	if (argc != 2){
			cout << "Los datos introducidos son incorrectos" << endl;
			return -1;
	}
	num = stof(argv[1]);
	if (num<0){
	cout << "Debes introducir un valor positivo" << endl;
	return -1;
	}
	raiz = sqrt(num);
	cout << "La raiz de " << num << " es " << raiz << endl;
}

