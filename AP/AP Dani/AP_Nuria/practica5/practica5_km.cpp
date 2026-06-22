#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>

#define MAX 4000

using namespace std;

double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int main() {
    srand(time(nullptr));
    int i,j,k;

    // Inicialización de matrices
    for(i = 0; i < MAX; i++) {
        for(j = 0; j < MAX; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    }

    int thread_counts[] = {2, 4, 8, 16, 32, 64};
    for (int t = 0; t < 6; ++t) {
        int num_threads = thread_counts[t];
        omp_set_num_threads(num_threads);

        // Reinicializar la matriz C a 0
        for(i = 0; i < MAX; i++) {
            for(j = 0; j < MAX; j++) {
                C[i][j] = 0;
            }
        }

        double t0 = omp_get_wtime();

        // Paralelización del bucle más externo
        #pragma omp parallel for schedule(static) private(i,k,j) shared(A,B,C)
        for(i = 0; i < MAX; i++) {
            for(k = 0;  k< MAX; k++) {
                for(j = 0; j < MAX; j++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }

        double t1 = omp_get_wtime();
        double seconds = t1 - t0;
        cout << "Tiempo con " << num_threads << " hilos: " << seconds << " segundos" << endl;
    }

    return 0;
}
