#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <mqueue.h>
#include <errno.h>
#include <time.h>


void ayuda(){ //Función que muestra la ayuda del programa

    printf("Uso del programa:\n");
    printf("  -h, --help               Muestra este mensaje de ayuda\n");
    printf("  -m, --maingroup          Muestra también el grupo principal del usuario\n");
    printf("Si no se pasa ninguna opción, equivale a --help\n");
    printf("Combinaciones permitidas:\n"
           "  --help [en cualquier momento]\n");
}


int main(int argc, char **argv){

    //PARÁMETROS

    bool hvalue= false;
    char *mvalue= NULL;
    int c; //Comprobar errores
    struct passwd *pwd= NULL;
    int uid; //Para pedirle el uid (número entero) al usuario
    pid_t pid,ppid;
    int status;    
    mqd_t cola; //DESCRIPTOR DE LA COLA
    char buffer[1024]; //BUFFER Lectura/Escritura
    char name[100]; //Nombre de la cola
    struct mq_attr attr; //Estructura atributos de la cola
    attr.mq_maxmsg= 10; //Número máximo de mensajes en la cola
    attr.mq_msgsize= 1024; //Tamaño máximo del mensaje en la cola
    int resultado; //Para comprobar las operaciones sobre la cola
    sprintf(name,"%s-%s","/COLA_ALEX",getenv("USER"));

    static struct option long_options[]={

        {"help",no_argument,NULL,'h'},
        {"maingroup",required_argument,NULL,'m'},
        {0, 0, 0, 0}
    };

    while((c=getopt_long(argc,argv,"hm:",long_options,NULL))!=-1){

        switch(c){

            case 'h':

                hvalue=true;
                break;

            case 'm':

                mvalue= optarg;
                break;

            case '?':

                break;

            default:

                abort();

        }


    }

    if(hvalue==true){

        ayuda();
        return 0;

    }

    pid=fork();
    
    switch(pid){

        case -1:

            printf("Fallo al obtener información de usuario.\n");
            printf("Valor del errno: %d\n",errno);
            exit(EXIT_FAILURE);

        case 0:

            printf("[HIJO]: mi ID es %d y el de mi padre es %d\n",getpid(),getppid());
            printf("[HIJO]: El nombre de la cola es %s\n",name);
            cola= mq_open(name, O_CREAT | O_WRONLY, 0644, &attr);

            if(cola == (mqd_t)-1){

                printf("Error al abrir la cola\n");
                printf("Valor del errno: %d\n",errno);
                exit(EXIT_FAILURE);
            }

            printf("[HIJO]: El descriptor de la cola es: %d\n", (int)cola);
            printf("Dame un id para pasarselo a mi padre y muestra la información de dicho usuario\n");
            scanf("%d",&uid);
            sprintf(buffer,"%d",uid);
            printf("[HIJO]: MANDANDOLE EL UID A MI PADRE...\n");
            resultado= mq_send(cola,buffer,1024,0);

            if(resultado == -1){

                printf("Error al enviar el mensaje\n");
                printf("Valor del errno: %d\n",errno);
                exit(EXIT_FAILURE);
            }

            if(mq_close(cola) == (mqd_t)-1){
            
                printf("Error al cerrar la cola\n");
                printf("Valor del errno: %d\n",errno);
                exit(EXIT_FAILURE);
            }

            exit(EXIT_SUCCESS);
        
        default:

            printf("[PADRE]: Mi PID es %d y el de mi hijo es %d \n", getpid(),pid);
            printf("[PADRE]: El nombre de la cola es %s\n",name);
            cola= mq_open(name, O_CREAT | O_RDONLY, 0644, &attr);

            if(cola == (mqd_t)-1){

                printf("Error al abrir la cola\n");
                printf("Valor del errno: %d\n",errno);
                exit(EXIT_FAILURE);
            }

            printf("[PADRE]: El descriptor de la cola es: %d\n", (int)cola);
            printf("[PADRE]: RECIBIENDO MENSAJE DE MI HIJO (llamada bloqueante)...\n");
            ssize_t mensaje= mq_receive(cola,buffer,1024,NULL);

            if(mensaje == -1){

                printf("Error al recibir el mensaje\n");
                printf("Valor del errno: %d\n",errno);
                exit(EXIT_FAILURE);
            }

            int uid_original=(int)atoi(buffer); //Transformo de cadena a entero
            pwd= getpwuid(uid_original);

            if(pwd){

                printf("[PADRE]: RECIBIDO\nNombre: %s\nLogin: %s\nPassword: %s\nUID: %d\nHome: %s\nShell: %s\nNumero de grupo principal(GID): %d\n",pwd->pw_gecos,pwd->pw_name,pwd->pw_passwd,pwd->pw_uid,pwd->pw_dir,pwd->pw_shell,pwd->pw_gid);
            }

            else{

                printf("No se ha encontrado nigún usuario con ese id en el sistema\n");
            }

            if(mq_close(cola) == (mqd_t)-1){
            
                printf("Error al cerrar la cola\n");
                printf("Valor del errno: %d\n",errno);
                exit(EXIT_FAILURE);
            }

            if(mq_unlink(name) == (mqd_t)-1){
                    
                printf("Error al eliminar la cola\n");
                printf("Valor del errno: %d\n",errno);
                exit(EXIT_FAILURE);
            }

            break;


    }

    while((ppid=waitpid(-1,&status,WUNTRACED | WCONTINUED))>0){

        if(WIFEXITED(status)){

            printf("Proceso padre %d, hijo con PID %ld ha finalizado,status= %d\n",getpid(),(long int)ppid,WEXITSTATUS(status));
        }

        else if(WIFSIGNALED(status)){

            printf("Proceso padre %d, hijo con PID %ld ha finalizado al recibir la señal %d\n",getpid(),(long int)ppid,WTERMSIG(status));
        }

        else if(WIFSTOPPED(status)){

            printf("Proceso padre %d, hijo con PID %ld ha parado al recibir la señal %d\n",getpid(),(long int)ppid,WSTOPSIG(status));
        }

        else if(WIFCONTINUED(status)){

            printf("Proceso padre %d, hijo con PID %ld ha reanudado\n",getpid(),(long int)ppid);
        }

    }

    if(ppid == (pid_t)-1 && errno == ECHILD){

        printf("Proceso Padre %d, no hay mas hijos que esperar.Valor del errno %d, definido como %s\n",getpid(),errno,strerror(errno));
    }

    else{

        printf("Error en la invocacion del wait o waitpid.Valor del errno %d, definido como %s\n",errno,strerror(errno));

        
    }

    if(mvalue!=NULL){

        int aux=(int)atoi(mvalue);
        struct passwd *gidUsuario= NULL;
        int aux2=(int)atoi(buffer);
        gidUsuario= getpwuid(aux2);

        if(aux > (gidUsuario->pw_gid)){

            struct passwd *nuevo=NULL;
            nuevo= getpwuid(aux);

            if(nuevo){
            
                printf("Nombre: %s\nLogin: %s\nPassword: %s\nUID: %d\nHome: %s\nShell: %s\nNumero de grupo principal(GID): %d\n",nuevo->pw_gecos,nuevo->pw_name,nuevo->pw_passwd,nuevo->pw_uid,nuevo->pw_dir,nuevo->pw_shell,nuevo->pw_gid);
            }

            else{

                printf("No se ha encontrado nigún usuario con ese id en el sistema\n");
            }

        }

        else{

            printf("El valor entero insertado es menor que el gid del usuario que te he solicitado antes\n");
        }

    }

    return 0;
}