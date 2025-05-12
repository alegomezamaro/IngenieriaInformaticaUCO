#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

void imprime(int v[], int n){
	for(int i=0; i<n; i++){
		cout << v[i] << "  ";
	}
	cout << "FIN" << endl;
}

bool find(int val, int x[], int n){
	for(int i=0; i<n; i++){
		if (val == x[i]){
			return true;
		}
	}
	return false;
}

int unico(int A[], int B[], int n){
	int nb=0;
	for (int i=0; i<n; i++){
		bool esta = find(A[i], B, n);
		if (!esta){
			B[nb] = A[i];
			nb++;
		}
	}
	return nb;
}

int main(){
	int v[30], u[30];
	for (int i=0; i<30; i++){
		v[i]=rand() % 21;
	}
	imprime(v, 30);
	int nu = unico(v,u,30);
	imprime(u, nu);
}