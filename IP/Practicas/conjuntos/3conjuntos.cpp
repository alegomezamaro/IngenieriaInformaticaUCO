#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ctime>
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

int difsimetrica(int A[], int na, int B[], int nb, int C[]){
	int nc = 0;
	for ( int i=0; i<na; i++){
		bool estaAB = find(A[i], B, nb);
		bool estaAC = find(A[i], C, nc);
		if ((estaAB == false) && (estaAC == false)){
			C[nc] = A[i];
			nc++;
		}
	}
		for ( int j=0; j<nb; j++){
		bool estaBA = find(B[j], A, na);
		bool estaBC = find(B[j], C, nc);
		if ((estaBA == false) && (estaBC == false)){
			C[nc] = B[j];
			nc++;
		}
	}
return nc;
}

int main(){
	srand(time(0));
	int v1[10], v2[10], u1[10], u2[10], D[10];
	for(int i=0; i<10; i++){
		v1[i] = rand() % 21;
		v2[i] = rand() % 21;
	}
	imprime(v1, 10);
	imprime(v2, 10);
	int nu1 = unico(v1, u1, 30);
	imprime(u1, nu1);
	int nu2 = unico(v2, u2, 30);
	imprime(u2, nu2);
	int nd = difsimetrica(u1, nu1, u2, nu2, D);
	imprime(D, nd);
}