#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

long esprimo(int v){
	int i, cont=0;
	bool primo;
	for (i=2; i<=v/2; i++){
		if (v%i ==0){
			cont++;
		}
	}
	if (cont == 0){
		primo = true;
	}
	else{
		primo = false;
	}
	return primo;
}


void primos(int v){
	int cont=0, contp=1;
	while (cont<v){
		if (esprimo(contp)){
			cout << contp << " es primo" << endl;
			cont++;
		}
		contp++;
	}
}

int main(){
	int x;
	cout << "Introduce un numero: ";
	cin >> x;
	primos(x);
	cin.ignore();
	cin.get();
}