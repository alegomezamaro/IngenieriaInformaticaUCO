#include <iostream>
#include <ctime>
#include <cstdlib>

#define MAX 2048

using namespace std;

double A[MAX][2056], B[MAX][2056], C[MAX][2056];

int main(){

    srand(time(nullptr));

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            A[i][j] = rand() % 10; 
            B[i][j] = rand() % 10; 
        }
    }

    double t0=clock();

    for(int i=0; i<MAX; i++){
        for(int k=0; k<MAX; k++){
            for(int j=0; j<MAX; j++){
                C[i][j]=+A[i][k]*B[k][j];
            }
        }
    }
    
    double t1=clock();
    double seconds=(double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"Tiempo del bucle (i,k,j)= "<< seconds<<endl;

    return 0;
}

