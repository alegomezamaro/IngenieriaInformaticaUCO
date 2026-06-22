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

    // B) PARALELIZANDO EL BUCLE INTERMEDIO (k)
    //Condición de carrera, varios hilos intentan sumar a la vez en la misma C[i][j].
    inicializar();
    t0 = omp_get_wtime();
    for(int i=0; i<MAX; i++){
        #pragma omp parallel for
        for(int k=0; k<MAX; k++){
            for(int j=0; j<MAX; j++){
                #pragma omp atomic
                C[i][j] += A[i][k] + B[k][j];
            }
        }
    }
    t1 = omp_get_wtime();
    printf("Tiempo Intermedio (k): %f segundos\n", t1 - t0);

    return 0;
}