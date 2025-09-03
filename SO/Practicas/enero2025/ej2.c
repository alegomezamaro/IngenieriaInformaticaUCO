#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

struct datos{
    pthread_mutex_t * mtx;
    int * suma;
};

void * hilo_pares(void *arg);
void * hilo_primos(void *arg);
int es_primo(int n);

int main(){

    int * suma;
    pthread_mutex_t * mtx;
    struct datos datos;
    pthread_t tids[2];

    if ((suma = (int*)malloc(sizeof(int))) == NULL){

        fprintf(stderr, "[MAIN] Error al reservar memoria para la suma.\n");
        exit(EXIT_FAILURE);
    }

    *suma = 0;
    if ((mtx = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t))) == NULL){

        fprintf(stderr, "[MAIN] Error al reservar memoria para el mutex.\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_mutex_init(mtx, NULL)){

        fprintf(stderr, "[MAIN] Error al inicializar el mutex.\n");
        exit(EXIT_FAILURE);
    }
    
    datos.mtx = mtx;
    datos.suma = suma;
    if (pthread_create(&tids[0], NULL, &hilo_pares, &datos)){

        fprintf(stderr, "[MAIN] Error al crear el hilo de los pares.\n");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&tids[1], NULL, &hilo_primos, &datos)){

        fprintf(stderr, "[MAIN] Error al crear el hilo de los primos.\n");
        exit(EXIT_FAILURE);
    }

    printf("[MAIN] Se han creado los hilos %lu y %lu.\n", tids[0], tids[1]);

    if (pthread_join(tids[0], NULL)){

        fprintf(stderr, "[MAIN] Error al recoger el hilo de los pares.\n");
        exit(EXIT_FAILURE);
    }

    printf("[MAIN] El HILO PARES con ID %lu ha finalizado.\n", tids[0]);

    if (pthread_join(tids[1], NULL)){

        fprintf(stderr, "[MAIN] Error al recoger el hilo de los primos.\n");
        exit(EXIT_FAILURE);
    }

    printf("[MAIN] El HILO PRIMOS con ID %lu ha finalizado.\n", tids[1]);
    printf("[MAIN] El valor de la suma tras ejecutar los hilos es %d.\n", *suma);

    if (pthread_mutex_destroy(mtx)){

        fprintf(stderr, "[MAIN] Error al destruir el mutex.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

void * hilo_pares(void *arg){

    struct datos * datos = (struct datos *) arg;
    int i = 2;
    int pares_encontrados = 0;

    printf("[HILO PARES] Mi ID es %lu.\n", pthread_self());

    while (pares_encontrados < 5){

        if (pthread_mutex_lock(datos->mtx)){

            fprintf(stderr, "[HILO PARES] Error al bloquear el mutex.\n");
            exit(EXIT_FAILURE);
        }

        *(datos->suma) += i;
        if (pthread_mutex_unlock(datos->mtx)){

            fprintf(stderr, "[HILO PARES] Error al desbloquear el mutex.\n");
            exit(EXIT_FAILURE);
        }

        printf("[HILO PARES] Encontrado el número par %d.\n", i);
        ++pares_encontrados;
        i += 2;
    }

    pthread_exit(NULL);
}

void * hilo_primos(void * arg){

    struct datos * datos = (struct datos *) arg;
    int i = 2;
    int primos_encontrados = 0;
    printf("[HILO PRIMOS] Mi ID es %lu.\n", pthread_self());

    while (primos_encontrados < 5){

        if (es_primo(i)){

            if (pthread_mutex_lock(datos->mtx)){

                fprintf(stderr, "[HILO PRIMOS] Error al bloquear el mutex.\n");
                exit(EXIT_FAILURE);
            }

            *(datos->suma) += i;

            if (pthread_mutex_unlock(datos->mtx)){

                fprintf(stderr, "[HILO PRIMOS] Error al desbloquear el mutex.\n");
                exit(EXIT_FAILURE);
            }

            printf("[HILO PRIMOS] Encontrado el número primo %d.\n", i);
            ++primos_encontrados;
        }
        ++i;
    }

    pthread_exit(NULL);
}

int es_primo(int n){

    for (int i = 2; i < n; ++i){
        if (n % i == 0){
            return 0;
        }
    }

    return 1;
}