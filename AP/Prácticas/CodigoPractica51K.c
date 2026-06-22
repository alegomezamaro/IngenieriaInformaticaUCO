#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 4000

// Variables globales para evitar Stack Overflow
double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

void inicializar() {
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            A[i][j] = 1.0; B[i][j] = 1.0; C[i][j] = 0.0;
        }
    }
}

int main(){
    double t0, t1;

    // Requiere 'reduction' porque todos los hilos suman a la misma variable C[i][j]
    inicializar();
    
    t0 = omp_get_wtime();
    for(int i=0; i<MAX; i++){
        for(int j=0; j<MAX; j++){
            double temp = C[i][j];
            #pragma omp parallel for reduction(+:temp)
            for(int k=0; k<MAX; k++){
                temp = temp + A[i][k] + B[k][j];
            }
            C[i][j] = temp;
        }
    }
    t1 = omp_get_wtime();
    printf("Tiempo Bucle Interno (k): %f segundos\n", t1 - t0);

    return 0;
}