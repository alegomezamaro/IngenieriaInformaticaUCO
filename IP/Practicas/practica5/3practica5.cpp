#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <ctime>
using namespace std;

void fijaValorAleatorio(int v[], int n, int max){
	int secs=time(0);
	srand(secs);
	for(int i=0; i<n; i++){
		int x=rand() % (max+1);
		v[i] = x;
	}
}

void imprime(int v[], int n){
	for (int i=0; i<n; i++){
		cout << "v[" << i << "] es " << v[i] << endl;
	}
	cout << endl;
}

int main(){
	int n=10, max=10, v[n];
	fijaValorAleatorio(v, n, max);
	imprime(v, n);
	cin.ignore();
	cin.get();
}