#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define LENGTH 100000000

int *array;
int count;

int count3s(){
    int i;
    count=0;
    for(i=0; i<LENGTH; i++){
        if(array[i]==3)
            count++;
    }
    return count;
}

int main(){

    array = (int*)malloc(LENGTH * sizeof(int));
    for(int i = 0; i < LENGTH; i++){
        array[i] = rand() % 101; 
    }

    double start_time = omp_get_wtime();
    int result = count3s();
    double end_time = omp_get_wtime();
    printf("Secuencial - Treses encontrados: %d\n", result);
    printf("Tiempo secuencial: %f milisegundos\n", (end_time - start_time)*1000);
    free(array);
    return 0;
}