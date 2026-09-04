#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

#define MAX 4000

using namespace std;

double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int main(){
    srand(time(nullptr));
    int i,j,k;

    // Inicialización de matrices
    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++){
            A[i][j] = rand() % 10; 
            B[i][j] = rand() % 10; 
        }
    }

    double t0 = omp_get_wtime();

    // Paralelización del bucle más interno
    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++){
            for(k = 0; k < MAX; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    
    double t1 = omp_get_wtime();
    double seconds = t1 - t0;
    cout << "Tiempo del bucle secuencial (i,j,k): " << seconds << " segundos" << endl;

    return 0;
}
