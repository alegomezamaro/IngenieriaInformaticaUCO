/*
Servidor que lee de una cola abierta para lectura una cadena de caracteres y la
imprime por pantalla.
*/

#include "ej3_common.h"

void funcionLog(char *mensaje); //Función para almacenar mensajes y errores

FILE *fLog = NULL; //Apuntador al fichero de log

int main(int argc, char **argv) {

    mqd_t mq_server; //Cola del servidor
    mqd_t mq_client; //Cola del cliente
    struct mq_attr attr; //Atributos de la cola
    char readbuffer[MAX_SIZE]; //Buffer para recibir mensajes
    char writebuffer[MAX_SIZE]; //Buffer para enviar mensajes
    int must_stop = 0; //Flag que indica 1 (STOP) cuando recibe 'exit'
    attr.mq_maxmsg = 10; //Maximo número de mensajes
    attr.mq_msgsize = MAX_SIZE; //Maximo tamaño de un mensaje
    char serverCola[100]; //Nombre de la cola del servidor
    char clienteCola[100]; //Nombre de la cola del cliente

    sprintf(serverCola, "%s-%s", SERVER_QUEUE, getenv("USER")); //Nombre para la cola del servidor
    printf("[Servidor]: El nombre de la cola es: %s\n", serverCola);
    mq_server = mq_open(serverCola, O_CREAT | O_RDONLY, 0644, &attr); //Crear la cola del servidor y abrirla para lectura
    //0644 son permisos de lectura y escritura para el propietario y de sólo lectura para el grupo y para otros
 
    if (mq_server == (mqd_t)-1){ //Comprobamos que se haya abierto correctamente

        perror("Error al abrir la cola del servidor");
        funcionLog("Error al abrir la cola del servidor"); //Escribimos el error en el log
        exit(-1);
    }

    printf("[Servidor]: El descriptor de la cola del servidor es: %d\n", (int)mq_server); //Imprimimos el descriptor de la cola del servidor
    sprintf(clienteCola, "%s-%s", CLIENT_QUEUE, getenv("USER")); //Nombre de la cola del cliente
    printf("[Servidor]: El nombre de la cola del cliente es: %s\n", clienteCola);
    mq_client = mq_open(clienteCola, O_CREAT | O_WRONLY, 0644, &attr); //Crear la cola del cliente y abrirla para escritura

    if (mq_client == (mqd_t)-1){ //Si no se ha abierto correctamente

        perror("Error al abrir la cola del cliente"); 
        funcionLog("Error al abrir la cola del cliente"); //Escribimos el error en el log
        exit(-1);
    }
    
    printf("[Servidor]: El descriptor de la cola del cliente es: %d\n\n", (int)mq_client); //Imprimimos el descriptor de la cola del cliente

    do{ //Bucle para recibir mensajes del cliente (do while)

        ssize_t bytes_read; //Número de bytes leidos
        bytes_read = mq_receive(mq_server, readbuffer, MAX_SIZE, NULL); //Recibimos el mensaje del cliente

        if (bytes_read < 0){ //Comprobamos que la recepción es correcta (bytes leidos no son negativos)

            perror("Error al recibir el mensaje");
            funcionLog("Error al recibir el mensaje"); //Escribimos el error en el log
            exit(-1);
        }
        
        if(strncmp(readbuffer, MSG_STOP, strlen(MSG_STOP)) == 0){ //Comprobamos si el mensaje es "exit"

            must_stop = 1;
        }

        else{ //Sino

            printf("Recibido el mensaje: %s\n", readbuffer); //Imprimimos el mensaje recibido del cliente
            sprintf(writebuffer,"Número de caracteres leídos: %ld",(strlen(readbuffer)-1)); //Escribimos el número de caracteres leídos (sin'\0')
            funcionLog(writebuffer);
        }

        if(mq_send(mq_client, writebuffer, MAX_SIZE, 0) != 0){ //Enviamos el mensaje al cliente

            perror("Error al enviar el mensaje");
            funcionLog("Error al enviar el mensaje"); //Escribimos el error en el log
            exit(-1);
        }
    } while (!must_stop); //Iterar hasta que llegue reciba 'exit'

    funcionLog("exit"); //Escribimos el mensaje de salida en el log

    if (mq_close(mq_server) == (mqd_t)-1){ //Cerrar la cola del servidor

        perror("Error al cerrar la cola del servidor");
        funcionLog("Error al cerrar la cola del servidor"); //Escribimos el error en el log
        exit(-1);
    }

    if(mq_close(mq_client)==(mqd_t)-1 ){ //Cerrar la cola del cliente
        
        perror("Error al cerrar la cola del cliente");
        funcionLog("Error al cerrar la cola del cliente"); //Escribimos el error en el log
        exit(-1);
    }

    if (mq_unlink(serverCola) == (mqd_t)-1){ //Eliminar la cola del servidor

        perror("Error al eliminar la cola del servidor");
        funcionLog("Error al eliminar la cola del servidor"); //Escribimos el error en el log
        exit(-1);
    }

    if(mq_unlink(clienteCola) == (mqd_t)-1){ //Eliminar la cola del cliente

        perror("Error al eliminar la cola del cliente");
        funcionLog("Error al eliminar la cola del cliente"); //Escribimos el error en el log
        exit(-1);
    }

    return 0;
} 

void funcionLog(char *mensaje){ //Función que almacena los mensajes y errores
    
    int resultado; //Variable que almacena el resultado de la escritura
    char nombreFichero[100]; //Nombre del fichero de log
    char fecha[100]; //Fecha y hora
    char mensajeAEscribir[300]; //Mensaje a escribir en el log
    time_t t; //Variable para almacenar la hora actual
    sprintf(nombreFichero, "log-servidor.txt"); //Nombre del fichero de log

    if (fLog == NULL){ //Si el puntero al fichero es nulo, lo abrimos

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