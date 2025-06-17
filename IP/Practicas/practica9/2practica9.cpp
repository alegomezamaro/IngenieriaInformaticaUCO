#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char **argv	){
	float num, suma=0, media;
	if (argc<2){
			cout << "Los datos introducidos son incorrectos" << endl;
			return -1;
	}
	for (int i=1; i<argc; i++){
		num = stof(argv[i]);
		suma += num;
	}
	media = suma / (argc-1);
	cout << "La media de todos los numeros es " << media << endl;
}