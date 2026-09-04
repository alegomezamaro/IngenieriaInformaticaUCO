#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

int main(){
    int* array;
    int length = 400000000, count = 0; 
    
    array = (int*)malloc(length * sizeof(int));
    if(array == NULL) {
        printf("Error: No se pudo asignar memoria para el array.\n");
        return 1;
    }
    
    srand(time(NULL));
    
    for(int i = 0; i < length; i++){
        array[i] = rand() % 50 + 1;
    }
    
    double start_time = omp_get_wtime();
    
    for(int i = 0; i < length; i++){
        if(array[i] == 3){
            count++;
        }
    }
  
    double end_time = omp_get_wtime();
    
    double execution_time = end_time - start_time;
    
    printf("El número 3 aparece %d veces en el array.\n", count);
    printf("Tiempo de ejecución: %.4f segundos\n", execution_time);
    
    free(array);
    
    return 0;
}

