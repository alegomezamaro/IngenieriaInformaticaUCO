#include <time.h>
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

double A[4000][4000], B[4000][4000], C[4000][4000];

void inicializar_matrices()
{
    for (int i = 0; i < 4000; i++)
    {
        for (int j = 0; j < 4000; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
            C[i][j] = 0;
        }
    }
}

void multiplicacion(int num_threads)
{
    omp_set_num_threads(num_threads);
    int i, j, k;

    for (i = 0; i < 4000; i++)
    {
        for (j = 0; j < 4000; j++)
        {
            #pragma omp parallel for schedule(static) private(i) shared(A,B,C)
            for (k = 0; k < 4000; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    double start_time, end_time;

    srand(time(NULL));

    int threads[] = {2, 4, 8, 16, 32, 64};
    for (int t = 0; t < sizeof(threads) / sizeof(threads[0]); t++)
    {
        int num_threads = threads[t];
        inicializar_matrices();

        start_time = omp_get_wtime();

        multiplicacion(num_threads);

        end_time = omp_get_wtime();
        double tiempo = end_time - start_time;

        printf("Número de hilos: %d\n", num_threads);
        printf("Tiempo de multiplicación paralela: %f segundos\n", tiempo);

        printf("Resultado en C[20][20]: %f\n", C[20][20]);
    }
}
