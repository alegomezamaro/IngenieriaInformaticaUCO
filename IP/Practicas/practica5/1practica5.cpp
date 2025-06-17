#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
using namespace std;

void lee(float v1[], int n){
	int i;
	for (i=0; i<n; i++){
		cout << "Introduce v[" << i << "]: ";
		cin >> v1[i];
	}
	cout << endl;
}

void imprime(float v1[], int n){
	int i;
	for (i=0; i<n; i++){
		cout << "v[" << i << "] es " << v1[i] << endl;
	}
	cout << endl;
}

int main(){
	float v[10];
	lee(v,10);
	imprime(v,10);
	cin.ignore();
	cin.get();
}