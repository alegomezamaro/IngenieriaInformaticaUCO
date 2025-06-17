#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int mincolumna(int m[3][3]){
	int min[3];
	for(int i=0; i<3; i++){
		min[i] = m[0][i];
		for(int j=0; j<3; j++){
			if(min[i] > m[j][i]){
			min[i] = m[j][i];
			}
		}
	}
	return min;
}

int main(){
	int m[3][3] = {{3, 8, 5}, {4, 6, 1}, {6, 3, 7}}, min[3]={0, 0, 0};
	min = mincolumna(m);
	cout << "Los minimos de cada columna son " << min[0] << ", " << min[1] << ", " << min[2] <<endl;
	cin.get();
	cin.ignore();
}

