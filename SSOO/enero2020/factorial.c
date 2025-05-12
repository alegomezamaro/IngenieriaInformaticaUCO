#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    
    if(argc!=2){
        fprintf(stderr, "\nNumero de argumentos incorrecto: ./factorial <Numero a calcular>\n");
        exit(EXIT_FAILURE);
    }
    int num=atoi(argv[1]);
    int fact=1;
    for(int i=1; i<=num; i++){
        fact=fact*i;
    }
    printf("\nSoy el hijo %d , mi padre %d el factorial de %d es %d\n", getpid(), getppid(), num, fact);

    exit(EXIT_SUCCESS);
}