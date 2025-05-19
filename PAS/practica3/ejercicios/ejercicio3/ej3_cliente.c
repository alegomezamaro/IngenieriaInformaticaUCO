/*
Cliente que envia por una cola abierta para escritura una cadena de caracteres
recogida por teclado, mientras el valor de esa cadena sea distinto a la palabra exit
*/

#include "ej3_common.h"

void funcionLog(char *mensaje); //Función para almacenar errores

FILE *fLog = NULL; //Apuntador al fichero de log
mqd_t mq_server; //Cola del servidor
mqd_t mq_client; //Cola del cliente
char readbuffer[MAX_SIZE]; //Buffer para recibir mensajes
char writebuffer[MAX_SIZE]; //Buffer para enviar mensajes
char serverCola[100]; //Nombre de la cola del servidor
char clienteCola[100]; //Nombre de la cola del cliente

int main(int argc, char **argv) {

    sprintf(serverCola, "%s-%s", SERVER_QUEUE, getenv("USER")); //Nombre para la cola del servidor
    printf("[Cliente]: El nombre de la cola del servidor es: %s\n", serverCola); 
    mq_server = mq_open(serverCola, O_WRONLY); //Abrir la cola del servidor solo para escritura

    if (mq_server == (mqd_t)-1){ //Comprobamos que se haya abierto correctamente

        perror("Error al abrir la cola del servidor");
        funcionLog("Error al abrir la cola del servidor"); //Escribimos el error en el log
        exit(-1);
    }

    printf("[Cliente]: El descriptor de la cola del servidor es: %d\n", (int)mq_server); //Imprimimos el descriptor de la cola del servidor
    sprintf(clienteCola, "%s-%s", CLIENT_QUEUE, getenv("USER")); //Nombre de la cola del cliente
    printf("[Cliente]: El nombre de la cola del cliente es: %s\n", clienteCola);
    mq_client = mq_open(clienteCola, O_RDONLY); //Abrir la cola del cliente solo para lectura

    if (mq_client == (mqd_t)-1){ //Comprobamos que se haya abierto correctamente

        perror("Error al abrir la cola del cliente");
        funcionLog("Error al abrir la cola del cliente"); //Escribimos el error en el log
        exit(-1);
    }

    printf("[Cliente]: El descriptor de la cola del cliente es: %d\n", (int)mq_client); //Imprimimos el descriptor de la cola del cliente
    printf("Mandando mensajes al servidor (escribir \"%s\" para parar):\n", MSG_STOP);

    do{ //Bucle para enviar mensajes al servidor (do while)

        printf("> "); //Imprimimos el prompt para que el usuario escriba el mensaje
        ssize_t bytes_read; //Número de bytes leidos

        fgets(writebuffer, MAX_SIZE, stdin); //Leemos el mensaje que queremos enviar e inserta automaticamente '\0'

        if(mq_send(mq_server, writebuffer, MAX_SIZE, 0) != 0){ //Enviamos el mensaje al servidor

            perror("Error al enviar el mensaje");
            funcionLog("Error al enviar el mensaje"); //Escribimos el error en el log
            exit(-1);
        }

        bytes_read=mq_receive(mq_client, readbuffer, MAX_SIZE, NULL); //Recibimos el mensaje del servidor

        if (bytes_read < 0){ //Comprobamos que la recepción es correcta (bytes leidos no son negativos)

            perror("Error al recibir el mensaje"); 
            funcionLog("Error al recibir el mensaje"); //Escribimos el error en el log
            exit(-1);
        }

        printf("Recibido: %s\n", readbuffer); //Imprimimos el mensaje recibido del servidor
    } while(strncmp(writebuffer, MSG_STOP, strlen(MSG_STOP))); //Iterar hasta escribir el código de salida

    if (mq_close(mq_server) == (mqd_t)-1){ //Cerrar la cola del servidor

        perror("Error al cerrar la cola del servidor");
        funcionLog("Error al cerrar la cola del servidor"); //Escribimos el error en el log
        exit(-1);
    }

    if (mq_close(mq_client) == (mqd_t)-1){ //Cerrar la cola del cliente

        perror("Error al cerrar la cola del cliente");
        funcionLog("Error al cerrar la cola del cliente"); //Escribimos el error en el log
        exit(-1);
    }

    return 0;
}

void funcionLog(char *mensaje){ //Función que almacena los errores

    int resultado; //Variable que almacena el resultado de la escritura
    char nombreFichero[100]; //Nombre del fichero de log
    char fecha[100]; //Fecha y hora
    char mensajeAEscribir[300]; //Mensaje a escribir en el log
    time_t t; //Variable para almacenar la hora actual
    sprintf(nombreFichero, "log-cliente.txt"); //Nombre del fichero de log

    if (fLog == NULL){ //Si el al fichero no esta abierto

        fLog = fopen(nombreFichero, "at"); //Abrimos el fichero en modo append

        if (fLog == NULL){ //Si no se ha abierto correctamente

            perror("Error abriendo el fichero de log"); 
            exit(1);
        }
    }

    t = time(NULL); //Obtenemos la hora actual
    struct tm *p = localtime(&t); //Convertimos la hora a formato local
    strftime(fecha, 1000, "[%Y-%m-%d, %H:%M:%S]", p); //Formateamos la fecha y hora
    sprintf(mensajeAEscribir, "%s ==> %s\n", fecha, mensaje); //Formateamos el mensaje a escribir en el log
    resultado = fputs(mensajeAEscribir, fLog); //Escribimos el mensaje en el log

    if (resultado < 0){ //Si no se ha escrito correctamente

        perror("Error escribiendo en el fichero de log");
    }

    fclose(fLog); //Cerramos el fichero de log
    fLog = NULL; //Ponemos el puntero a NULL para que se vuelva a abrir la proxima vez
}