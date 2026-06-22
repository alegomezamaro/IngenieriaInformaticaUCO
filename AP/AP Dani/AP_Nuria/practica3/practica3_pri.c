#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <omp.h>
#include <stdint.h>

#define MaxThreads 32

int *array, length, count;
int t; // número de threads
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // mutex

// Estructura para el contador privado de cada hilo
struct padded_int {
    int value;
    char padding[60];
} private_count[MaxThreads];

// Prototipo de funciones
void *count3s_thread(void *arg);

int count3s() {
    int i;
    count = 0;
    pthread_t *threads = (pthread_t *)malloc(t * sizeof(pthread_t));

    // Crear t threads
    for (i = 0; i < t; i++) {
        pthread_create(&threads[i], NULL, count3s_thread, (void *)(intptr_t)i);
    }

    // Esperar a que todos los hilos terminen
    for (i = 0; i < t; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
    return count;
}

void *count3s_thread(void *arg) {
    int id = (intptr_t)arg;
    int i;
    int start = id * (length / t);
    int end = start + (length / t);

    // Contar ocurrencias del número 3 en la sección asignada al hilo
    for (i = start; i < end; i++) {
        if (array[i] == 3) {
            private_count[id].value++;
        }
    }

    // Sumar los contadores locales al contador global de manera segura
    pthread_mutex_lock(&m);
    count += private_count[id].value;
    pthread_mutex_unlock(&m);

    pthread_exit(NULL);
}

int main() {
    length = 400000000; // Tamaño del array
    array = (int *)malloc(length * sizeof(int));
    if (array == NULL) {
        printf("Error: No se pudo asignar memoria para el array.\n");
        return 1;
    }

    // Semilla para la generación de números aleatorios
    srand((unsigned int)time(NULL));

    // Llenar el array con números aleatorios en el rango de 1 a 50
    for (int i = 0; i < length; i++) {
        array[i] = rand() % 50 + 1;
    }

    t = MaxThreads; // número de hilos

    // Medir el tiempo de inicio
    double start_time = omp_get_wtime();

    // Llamar a la función para contar los 3s
    int result = count3s();

    // Medir el tiempo de finalización
    double end_time = omp_get_wtime();

    // Calcular el tiempo transcurrido
    double execution_time = end_time - start_time;

    printf("El número 3 aparece %d veces en el array.\n", result);
    printf("Tiempo de ejecución con %d hilos: %.4f segundos\n",t, execution_time);

    // Liberar la memoria asignada para el array
    free(array);

    return 0;
}
