/*
PRACTICA 3 EJERCICIO 1
Una tienda que vende camisetas guarda en una base de datos (buffer) las cantidades de camisetas
que tiene según el modelo. Por ejemplo, un buffer de camisetas[5] indica que existen 5 modelos de
camisetas y cada elemento de este buffer guarda las cantidades iniciales de cada una de ellas.
Implementar un programa que genere N clientes (pedido por linea de argumentos) y M proveedores
(la misma cantidad de proveedores que modelos de camiseta, también pedido por linea de
argumentos).
Para simular una compra, cada hilo Cliente debe generar un valor aleatorio para el modelo de
camiseta que quiere comprar y otro para la cantidad a comprar. Esta cantidad debe decrementar el
stock de la camiseta en cuestión.
Para simular un suministro, cada Proveedor debe hacer lo mismo que el Cliente pero en este caso,
incrementando el stock de la camiseta en cuestión.
Utilice semáforos binarios para resolver este problema de concurrencia imprimiendo el buffer antes
de generar los hilos y al final del programa para comprobar que se ha ejecutado correctamente.
En cuanto al numero de camisetas a comprar o suministrar, por ejemplo pueden ser valores
aleatorios entre [1-10]. Para rellenar el vector inicial de stock de camisetas podría generar números
aleatorios entre [1-100]. Si se diera el caso de que algún cliente quiere comprar más camisetas de
las disponibles solo se le proporcionarán las que queden.
El ejercicio se puede implementar de diversas maneras. La salida que se muestra a continuación
como ejemplo ha hecho uso en la zona de variables globales de un puntero a un vector de enteros
(para el vector de camisetas) y de la creación e inicialización de un mutex.
*/

#include <stdio.h>  //Funciones de entrada/salida, como printf o perror
#include <stdlib.h> //exit, malloc o atoi
#include <string.h> //strerror
#include <errno.h> //Errores en la variable errno
#include <pthread.h> //Hilos y mutex
#include <time.h> //Numeros aleatorios

//Definimos las variables globales
pthread_mutex_t protect=PTHREAD_MUTEX_INITIALIZER;
int *stock;
int proveedores;

//Hilo proveedor
void *proveedor(void *arg){

    //Introducimos la cantidad de camisetas
    pthread_mutex_lock(&protect);
    int pos=(rand()%proveedores);
    int cant=(rand()%11);
    stock[pos] += cant;
    pthread_mutex_unlock(&protect);

    //Imprimimos los valores del hilo
    printf("\nSTOCK: El proveedor %ld, ha añadido %d unidades a la camiseta %d = %d\n", pthread_self(), cant, pos, stock[pos]);

    //Retornamos el hilo
    pthread_exit(NULL);
}

//Hilo cliente
void *cliente(void *arg){

    //Eliminamos la cantidad de camisetas
    pthread_mutex_lock(&protect);
    int pos=(rand()%proveedores);
    int cant=(rand()%11);
    stock[pos] -= cant;
    pthread_mutex_unlock(&protect);

    //Imprimimos los valores del hilo
    printf("\nSTOCK: El cliente %ld, ha recogido %d unidades a la camiseta %d = %d\n", pthread_self(), cant, pos, stock[pos]);

    //Retornamos el hilo
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){

    //Llamada incorrecta
    if(argc != 3){
        fprintf(stderr, "\nNumero de argumentos invalido ./ej1 <numero de clientes> <numero de proveedores>\n");
        exit(EXIT_FAILURE);
    }

    //Definimos variables
    srand(time(NULL));
    int clientes=atoi(argv[1]);
    proveedores=atoi(argv[2]);
    pthread_t hilosP[proveedores];
    pthread_t hilosC[clientes];

    //Reservamos memoria
    stock=(int*)malloc(sizeof(int)*proveedores);

    //Error al reservar memoria
    if(stock==NULL){
        fprintf(stderr, "\nError reservar memoria (malloc)\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<proveedores;i++){
        stock[i]=(rand()%101);
        printf("\nSTOCK INICIAL: Camiseta %d, %d unidades\n", i, stock[i]);
    }

    //Creamos los hilos proveedor
    for(int i=0; i<proveedores; i++){
        if(pthread_create(&hilosP[i], NULL, proveedor, (void*)stock) != 0){
            fprintf(stderr, "\nError al crear el hilo %d (pthread_create)\n", (i+1));
            exit(EXIT_FAILURE);
        }
    }

    //Creamos los hilos cliente
    for(int i=0; i<clientes; i++){
        if(pthread_create(&hilosC[i], NULL, cliente, (void*)stock) != 0){
            fprintf(stderr, "\nError al crear el hilo %d (pthread_create)\n", (i+1));
            exit(EXIT_FAILURE);
        }
    }

    //Recogemos los hilos proveedor
    for(int i=0; i < proveedores; i++){
        if(pthread_join(hilosP[i], NULL) != 0){
            fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n", (i+1));
            exit(EXIT_FAILURE);
        }
    }

    //Recogemos los hilos cliente
    for(int i=0; i < clientes; i++){
        if(pthread_join(hilosC[i], NULL) != 0){
            fprintf(stderr, "\nError al recoger el hilo %d (pthread_join)\n", (i+1));
            exit(EXIT_FAILURE);
        }
    }

    //Imprimimos el stock final
    for(int i=0; i<proveedores;i++){
        printf("\nSTOCK FINAL: Camiseta %d, %d unidades\n", i, stock[i]);
    }

    //Liberamos memoria
    pthread_mutex_destroy(&protect);
    free(stock);
}