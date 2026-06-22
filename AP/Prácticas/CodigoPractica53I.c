#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 4000

double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

void inicializar() {
    #pragma omp parallel for
    for(int i=0; i<MAX; i++) {
        for(int j=0; j<MAX; j++) {
            A[i][j] = 1.0; B[i][j] = 1.0; C[i][j] = 0.0;
        }
    }
}

int main(){
    double t0, t1;

    // A) PARALELIZANDO EL BUCLE EXTERNO (i)
    // Cada hilo coge una fila distinta. No hay colisiones.
    inicializar();
    t0 = omp_get_wtime();
    #pragma omp parallel for
    for(int i=0; i<MAX; i++){
        for(int k=0; k<MAX; k++){
            for(int j=0; j<MAX; j++){
                C[i][j] += A[i][k] + B[k][j];
            }
        }
    }
    t1 = omp_get_wtime();
    printf("Tiempo Externo (i): %f segundos\n", t1 - t0);

    return 0;
}