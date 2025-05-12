#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;

bool numero(string cad){
	for (int i=0; i<cad.size(); i++){
		if (isdigit(cad[i]) == false){
			return false;
		}
	}
	return true;
}

int main(int argc, char **argv){
	if (argc==1){
		cout << "Ingresa unos valores optimos" << endl;
		return EXIT_FAILURE;
	}
	float suma=stof(argv[1]);
	for(int i=2; i<argc; i++){
		string op=argv[i];
		if(op == "-sum"){
			if((i+1 >= argc) or (numero(argv[i+1]) == false)){
				cout << "Ingresa unos valores optimos" << endl;
				return EXIT_FAILURE;
			}
			else{
				float aux= stof(argv[i+1]);
				suma += aux;
				i++;
			}
		}
		else if(op == "-mult"){
			if((i+1 >= argc) or (numero(argv[i+1]) == false)){
				cout << "Ingresa unos valores optimos" << endl;
				return EXIT_FAILURE;
			}
			else{
				float aux= stof(argv[i+1]);
				suma = suma*aux;
				i++;
			}
		}
		else if(op == "-div"){
			if((i+1 >= argc) or (numero(argv[i+1]) == false)){
				cout << "Ingresa unos valores optimos" << endl;
				return EXIT_FAILURE;
			}
			else{
				float aux= stof(argv[i+1]);
				suma /= aux;
				i++;
			}
		}
		else if(op == "-sqrt"){
			suma = sqrt(suma);
		}
	}
	cout << "La cuenta da como resultado " << suma << endl;
}