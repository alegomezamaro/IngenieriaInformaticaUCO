// ======================================================
// clienteP2.c
// Compilación: gcc -Wall -O2 -o clienteP2 clienteP2.c
// Ejecución: ./clienteP2 <IP_servidor>
//            ./clienteP2 127.0.0.1 
// ======================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>

#define SERVER_PORT 1865              // Puerto indicado en el enunciado
#define MAX_MSG     200               // Longitud máxima de un comando

// Elimina saltos de línea al final de un mensaje
static void trim_newline(char *s){
    if(!s) return;
    size_t n=strlen(s);
    while(n>0 && (s[n-1]=='\n'||s[n-1]=='\r')) s[--n]='\0';
}

int main(int argc, char **argv){

    if(argc!=2){
        fprintf(stderr, "Uso: %s <IP_servidor>\n", argv[0]); return 1;
    }

    // Creamos socket TCP
    int s=socket(AF_INET,SOCK_STREAM,0); if(s<0){
        perror("socket");
        return 1;
    }

    struct sockaddr_in srv;
    memset(&srv,0,sizeof(srv));
    srv.sin_family=AF_INET;
    srv.sin_port=htons(SERVER_PORT);

    // Convertimos la IP que nos pasan por argumento
    if(inet_pton(AF_INET, argv[1], &srv.sin_addr)<=0){
        perror("inet_pton");
        return 1;
    }

    // Nos conectamos al servidor
    if(connect(s,(struct sockaddr*)&srv,sizeof(srv))<0){
        perror("connect");
        return 1;
    }

    // Mensaje de ayuda
    printf("Conectado. Escriba comandos (máx 200 chars). Ejemplos: \n");
    printf("  REGISTRO -u user -p pass\n  USUARIO user\n  PASSWORD pass\n  INICIAR-PARTIDA\n  TIRAR-DADOS 1|2\n  NO-TIRAR-DADOS\n  PLANTARME\n  SALIR\n\n");
    char rbuf[512];
    int n=recv(s,rbuf,sizeof(rbuf)-1,0);

    if(n>0){
        rbuf[n]='\0'; printf("%s", rbuf);
    }

    // Leemos el teclado y socket usando select()
    fd_set rset;
    int maxfd = (s>STDIN_FILENO? s:STDIN_FILENO);

    for(;;){
        FD_ZERO(&rset);
        FD_SET(STDIN_FILENO,&rset);
        FD_SET(s,&rset);

        // Esperamos a que haya datos en cualquiera de los dos
        if(select(maxfd+1,&rset,NULL,NULL,NULL)<0){
            perror("select");
            break;
        }

        // Datos que llegan del servidor
        if(FD_ISSET(s,&rset)){
            char buf[512]; int n=recv(s,buf,sizeof(buf)-1,0);

            if(n<=0){
                printf("\n[Servidor cerrado]\n");
                break;
            }

            buf[n]='\0';
            printf("%s", buf);
            fflush(stdout);
        }

        // Datos que teclea el usuario
        if(FD_ISSET(STDIN_FILENO,&rset)){
            char line[MAX_MSG+4];
            if(!fgets(line,sizeof(line),stdin)) break;
            trim_newline(line);
            if(strlen(line)==0) continue;
            size_t len=strlen(line);

            if(line[len-1]!='\n'){
                line[len]='\n'; line[len+1]='\0'; len++;
            }

            if(send(s,line,len,0)<0){
                perror("send"); break;
            }
        }
    }

    close(s);
    return 0;
}
