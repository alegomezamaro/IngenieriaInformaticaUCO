#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
using namespace std; 

//cree aqui su funcion
 float trace(float m[4][4]){
	int suma=0;
	for(int i=0; i<4; i++){
		suma = suma + m[i][i];
	}
	return suma;
}

//// 
int test();//indica que la funcion test esta mas abajo
int main(){ 
		test();
		cout<<"Correcto"<<endl;
		system("pause");
		return 0;
}
//funcion de test
int test(){
	
	float m[4][4]={ {1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4}};
	assert( trace(m)== 10 );
	return 0;
}	


