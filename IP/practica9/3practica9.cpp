#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int main(int argc, char **argv	){
	string an;
	if (argc != 2){
			cout << "Los datos introducidos son incorrectos, deben ser dd/mm/aaaa " << endl;
			return -1;
	}
	string fecha = argv[1];
	if (fecha.size()!=10){
			cout << "Los datos introducidos son incorrectos, deben ser dd/mm/aaaa " << endl;
			return -1;
	}
	for(int i=6; i<10; i++){
		an += fecha[i];
	}
	int AN = stoi(an);
	if ((AN%4== 0) && (AN%100!=0 or AN%400==0)){
		cout << AN << " es un año bisiesto" << endl;
	}
	else{
		cout << AN << " no es un año bisiesto" << endl;
		return 0;
	}
}