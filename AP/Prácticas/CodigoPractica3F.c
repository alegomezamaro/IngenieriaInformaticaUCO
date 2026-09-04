#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define LENGTH 100000000

int *array;

int count3s_omp(int threads){

    int count=0;
    #pragma omp parallel for num_threads(threads) reduction(+:count)
    for (int i=0; i<LENGTH; i++) {
        if(array[i]==3){
            count++;
        }
    }

    return count;
}

int main(int argc, char *argv[]){

    int t=4;
    if(argc>1)
        t=atoi(argv[1]);
    array = (int*)malloc(LENGTH * sizeof(int));
    for (int i=0; i<LENGTH; i++)
        array[i]=rand()%101;

    double start_time = omp_get_wtime();
    int result = count3s_omp(t);
    double end_time = omp_get_wtime();
    printf("Pthreads (OpenMP) - Hilos: %d, Treses encontrados: %d\n", t, result);
    printf("Tiempo: %f milisegundos\n", (end_time - start_time)*1000);
    free(array);
    return 0;
}