#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define MAX 4000
#define HILOS 64

double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

void inicializar() {
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            A[i][j] = 1.0; B[i][j] = 1.0; C[i][j] = 0.0;
        }
    }
}

int main(){
    double t0, t1, dif;

    printf("Vector (i, j, k) con %02d hilos - Bucle interno\n", HILOS);

    omp_set_num_threads(HILOS);
    inicializar();

    t0 = omp_get_wtime();

    #pragma omp parallel for
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            for(int k = 0; k < MAX; k++){
                C[i][j] = C[i][j] + A[i][k] + B[k][j];
            }
        }
    }

    t1 = omp_get_wtime();
    dif = t1 - t0;
    printf("  -> C[20][20] = %.2f\n", C[20][20]);
    printf("  -> La diferencia es de %f segundos\n", dif);
    return 0;
}