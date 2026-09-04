#include <iostream>
#include <ctime>
#include <cstdlib>

#define MAX 2510

using namespace std;

double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int main(){

    srand(time(nullptr));

    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            A[i][j] = rand() % 10; 
            B[i][j] = rand() % 10; 
        }
    }

    double t0=clock();

    for(int i=0; i<45; i++){
        for(int k=0; k<45; k++){
            for(int j=0; j<45; j++){
                C[i][j]=+A[i][k]*B[k][j];
            }
        }
    }

    double t1=clock();
    double seconds=(double(t1-t0)/CLOCKS_PER_SEC);
    cout<<"Tiempo del bucle (i,k,j)= "<< seconds<<endl;

    return 0;
}

