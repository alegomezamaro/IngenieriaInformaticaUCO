/*
Implemente un programa que obtenga e imprima informacion sobre usuarios del sistema
(todos los campos de la estructura passwd) e informacion sobre grupos del sistema (GID y
nombre del grupo mediante la estructura group), segun las opciones recibidas por la linea de
argumentos.

La opcion -u/--user se utilizara para indicar un usuario. Si le pasamos como argu-
mento un n  ́umero, lo interpretara como UID, en caso contrario como el nombre del
usuario. Se mostrara la informacion correspondiente a su estructura passwd.

La opcion -g/--group se utilizara para indicar un grupo. Si le pasamos como argu-
mento un numero, lo interpretara como GID, en caso contrario como el nombre del
grupo. Se mostrara la informacion correspondiente a su estructura group.

La opcion -a/--active sera equivalente a especificar--user con el usuario actual.

La opcion -m/--maingroup modifica a --user o --active y hace que imprima la
informacion de su grupo principal (mismo formato que --group).

Si se invoca al programa con la opcion -s o con --allgroups, se mostraran todos
los grupos del sistema, junto con su identificador. Para ello recorra el fichero corres-
pondiente (le permitira recordar como gestionar y buscar en cadenas) y luego vaya
extrayendo informacion como si se invocase la opcion --group. No muestre directamente 
el contenido del fichero, recorralo y muestre la informacion por cada grupo que haya.

Invocar al programa sin ninguna opcion sera equivalente a activar las opciones --active
y --maingroup, es decir, se mostrara la informacion del usuario actual (con el mismo
formato que que -u/--user) y del grupo al que pertenece (con el mismo formato que
que -g/--group).

Se creara una opcion de ayuda -h/--help para mostrar informacion sobre cada uno
de los usos del programa. Esa informaci  ́on tambi ́en se mostrara cuando el usuario
cometa cualquier error en la invocacion del programa.

Tenga tambien en cuenta el siguiente control de errores:
-Asegurar que se pasan nombres e identificadores de usuarios o grupos validos que
 existan en la maquina.
-Asegurar que no se puedan pasar por linea de comandos opciones que sean incompa-
 tibles. Las unicas combinaciones posibles son:
  • --help, junto con cualquiera (se ignoran las demas)
  • vacio (equivalente a --active --maingroup)
  • --user <uid o nombre de usuario>
  • --user <uid o nombre de usuario> --maingroup
  • --active
  • --active --maingroup
  • --group <gid o nombre de grupo>
  • --allgroups
*/

#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include <sys/types.h>


//Funcion que recibe un valor de tipo struct passwd la cual muestra la informacion del usuario
void Usuario(struct passwd *pw){

    printf("Usuario:\n");
    printf("Nombre: %s\n", (pw->pw_gecos)); // Nombre de usuario asociado a un login
    printf("Login: %s\n", pw->pw_name);//Login
    printf("Password: %s\n", pw->pw_passwd);//Contraseña
    printf("UID: %d\n", pw->pw_uid);//UID
    printf("Home: %s\n", pw->pw_dir);//Home
    printf("Shell: %s\n", pw->pw_shell);//Shell
    printf("Número de grupo principal: %d\n", pw->pw_gid); //Numero del grupo principal (GID)
}

//Funcion que recibe un valor de tipo struct group la cual muestra la informacion del grupo
void Grupo(struct group *gr){

    printf("Grupo:\n");
    printf("Nombre del grupo: %s\n", gr->gr_name);//Nombre del grupo principal
    printf("GID: %d\n",gr->gr_gid); //Numero del grupo principal (GID propio)
    printf("Miembros secundarios: %s\n", *gr->gr_mem);//Pueden ser más de uno (Por eso puntero)
    
}

//Imprime las principales opciones del programa
void Opciones(){

    printf("Uso del programa: ./ej1.c [opciones]:\n");
    printf("-h, --help Imprimir esta ayuda.\n");
    printf("-u, --user (<nombre>|<uid>) Información sobre el usuario.\n");
    printf("-a, --active Información sobre el usuario activo actual.\n");
    printf("-m, --maingroup Además de info de usuario, imprimir la info de su grupo,\n → principal.\n");
    printf("-g, --group (<nombre>|<gid>) Información sobre el grupo.\n");
    printf("-s, --allgroups Muestra info de todos los grupos del sistema.\n");   
}      


int main(int argc, char **argv){

    int gid; //Variable que almacena el GID
    int c; //Variable que ve las flags se han activado
    int uid; //Variable que almacena el UID
    char *nombre; //Variable que almacena el nombre del usuario (PUNTERO)
    char *gname; //Variable que almacenar el nombre del grupo (PUNTERO)
    struct passwd *pw; //Variable que almacena la informacion del usuario
    struct group *gr; //Variable que almacena la informacion del grupo

    //Estructura a utilizar por getoptlong
    static struct option long_options[] = {

        //{<nombre largo>, <recibe/no recibe argumento>, NULL, <nombre corto>}
        {"user", required_argument, NULL, 'u'},
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'},
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0} //Fin de la lista de opciones
    };

    //Estas variables que almacenar el resultado de procesar la línea de comandos 
    char *uvalue = NULL; //Almacena el valor de u (PUNTERO)
    char *gvalue = NULL; //Almacena el valor de g (PUNTERO)
    bool aflag = false; //Almacena el valor de a
    bool mflag = false; //Almacena el valor de m
    bool sflag = false; //Almacena el valor de s
    bool hflag = false; //Almacena el valor de h

    while((c = getopt_long(argc, argv, "u:g:amsh", long_options, NULL)) != -1){
    //Durante el while ponemos : para que se active la flag al tener un argumento
    printf("%d\n", c);

        switch(c) {
            case 'u':
                uvalue=optarg; //Espera argumentos
                break;
            
            case 'g':
                gvalue=optarg; //Espera argumentos
                break;
            
            case 'a':
                aflag=true;
                break;
            
            case 'm':
                mflag=true;
                break;
            
            case 's':
                sflag=true;
                break;
            
            case 'h':
                hflag=true;
                break;

            case '?': //Si no se encuentra la opción
                printf("Error: Opción no válida.\n");
                abort(); //Abortamos el programa

        }
    }
    
    if (argc == 1){ //Si no se pasan argumentos, se asume -a -m

        aflag = true;
        mflag = true;
    }

    //Entramos a este if si se activa el valor de h, da igual las demas flags
    if(hflag == true){

        Opciones(); 
        exit(0);
    }
   
    //Si se activa u y (o no) m
    if((uvalue != NULL)&&(gvalue == NULL)&&(hflag == false)&&(aflag == false)&&(sflag == false)){

        if(isdigit(*uvalue)!=0){ //Si u es el UID

            uid=atoi(uvalue); //Convertimos el UID a entero

            if((pw=getpwuid(uid))==NULL){ //Si no existe el UID

                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);
            }
            
            else{ //Si existe el UID, lo imprimimos

                Usuario(pw); //si existe el UID, imprimimos la info
            }
        }
        
        else{ //Si u es el login

            nombre=uvalue;//Guardamos el login en nombre

            if((pw=getpwnam(nombre))==NULL){ //Si no existe el login

                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);

            }
            
            else{
            
                Usuario(pw); //si existe el login, imprimimos la info
            }
        }

        if(mflag == true) { //Si se activa m, imprimimos la info del grupo principal
        
            if((gr=getgrgid(pw->pw_gid))==NULL){ //Si no existe el GID

                printf("Error al intentar acceder a la información de grupo.\n");
                exit(-1);
            }
            
            else { //Si existe el GID, lo imprimimos

                Grupo(gr);
                exit(0);
            }
        }

        exit(0);
    }

    //Si se activa a y (o no) m
    if((uvalue == NULL)&&(gvalue == NULL)&&(hflag == false)&&(aflag == true)&&(sflag == false)) {

        if((nombre=getenv("USER"))==NULL || (pw=getpwnam(nombre))==NULL){ //Si no existe el login

            printf("Error al intentar acceder a la información de usuario.\n");
            exit(-1);
        }

        else{ //Si existe el login, lo imprimimos

            Usuario(pw);
        }

        if(mflag==true) { //Si se activa m, imprimimos la info del grupo principal

            if((gr=getgrgid(pw->pw_gid))==NULL) { //Si no existe el GID

                printf("Error al intentar acceder a la información de grupo.\n");
                exit(-1);
            }
            
            else { //Si existe el gid, imprimimos la info
                Grupo(gr); 
                exit(0);
            }
        }

        exit(0);
    }


    //Si se activa el valor de s
    if((uvalue == NULL)&&(gvalue == NULL)&&(mflag == false)&&(hflag == false)&&(aflag == false)&&(sflag == true)){

        FILE *f; 
        f=fopen("/etc/group", "r"); //Abrimos la carpeta de grupos (Puede variar dependiendo del SO)

        if(f==NULL){ //Si no existe el fichero

            printf("Error al intentar acceder a la información de usuario.\n");
            exit(-1);
        }

        char buffer[256]; //Buffer que almacena la linea
        char *nombre;
        char *psw;
        char *gid;
        char *miembros;
        printf("Grupo:\n\n");

        while(fgets(buffer, 256, f) != NULL){ //Mientras no llegue al final del fichero

            nombre=strtok(buffer, ":"); //Separamos el nombre
            psw=strtok(NULL, ":"); //Separamos la contraseña           
            gid=strtok(NULL, ":"); //Separamos el GID
            miembros=strtok(NULL, ":"); //Separamos los miembros
            printf("Nombre del grupo principal: %s\n", nombre);
            printf("Contraseña: %s\n", psw);
            printf("GID: %s\n", gid);
            printf("Miembros secundarios: %s\n", miembros);
        }

        fclose(f); //Cerramos el fichero
        exit(0);
    }


  
    //Si se activa g
    if((uvalue == NULL)&&(gvalue != NULL)&&(mflag == false)&&(hflag == false)&&(aflag == false)&&(sflag == false)){

        if(isdigit(*gvalue)!=0) { //Si g es el GID

            gid=atoi(gvalue); //Convertimos el GID a entero

            if((gr=getgrgid(gid))==NULL){ //Si no existe el GID

                printf("Error al intentar acceder a la información de grupo.\n");
                exit(-1);
            }
            
            else{ //Si existe el GID, lo imprimimos

                Grupo(gr);
                exit(0);
            }
        }
        
        else{ //Si g es el nombre del grupo

            gname=gvalue;

            if((gr=getgrnam(gname))==NULL){ //Si no existe el grupo

                printf("Error al intentar acceder a la información de usuario.\n");
                exit(-1);
            }
            
            else{ //Si existe el grupo, lo imprimimos

                Grupo(gr);
                exit(0);
            }
        }
    }

    exit(0);
}