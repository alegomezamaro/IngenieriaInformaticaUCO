#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

bool matricesiguales(int m1[3][3], int m2[3][3]){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(m1[i][j] != m2[i][j]){
				return false;
			}
		}
	}
	return true;
}

int main(){
	int m1[3][3] = {{1,2,3},{4,5,6},{7,8,9}}, m2[3][3] = {{1,2,3},{4,5,6},{7,8,9}}, m3[3][3] = {{1,2,3},{4,0,6},{7,8,9}};
	if (matricesiguales(m1, m2) == true){
		cout << "Correcto" << endl;
	}
	else if (matricesiguales(m1, m2) == false){
		cout << "Falso" << endl;
	}	
		if (matricesiguales(m1, m3) == true){
		cout << "Correcto" << endl;
	}
	else if (matricesiguales(m1, m3) == false){
		cout << "Falso" << endl;
	}	

	cin.get();
	cin.ignore();
}