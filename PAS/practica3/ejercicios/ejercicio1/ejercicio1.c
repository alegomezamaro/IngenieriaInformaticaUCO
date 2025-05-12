/*
Implemente un programa que obtenga e imprima informacion sobre usuarios del sistema
(todos los campos de la estructura passwd) e informacion sobre grupos del sistema (GID y
nombre del grupo mediante la estructura group), segun las opciones recibidas por la linea de
argumentos.
    - La opcion -u/--user se utilizara para indicar un usuario. Si le pasamos como argumento
      un numero, lo interpretar a como UID, en caso contrario como el nombre del
      usuario. Se mostrara la informaci on correspondiente a su estructura passwd.
    - La opcion -g/--group se utilizara para indicar un grupo. Si le pasamos como argumento
      un numero, lo interpretar a como GID, en caso contrario como el nombre del
      grupo. Se mostrara la informacion correspondiente a su estructura group.
    - La opcion -a/--active sera equivalente a especificar --user con el usuario actual
    - La opcion -m/--maingroup modifica a --user o --active y hace que imprima la
      informacion de su grupo principal (mismo formato que --group).
    - Si se invoca al programa con la opcion -s o con --allgroups, se mostraran todos
      los grupos del sistema, junto con su identificador. Para ello recorra el fichero correspondiente
      (le permitira recordar como gestionar y buscar en cadenas) y luego vaya
      extrayendo informacion como si se invocase la opcion --group. No muestre directamente
      el contenido del fichero, recorralo y muestre la informacion por cada grupo que haya.
    - Invocar al programa sin ninguna opcion sera equivalente a activar las opciones --active
      y --maingroup, es decir, se mostrara la informacion del usuario actual (con el mismo
      formato que que -u/--user) y del grupo al que pertenece (con el mismo formato que -g/--group).
    - Se creara una opcion de ayuda -h/--help para mostrar informacion sobre cada uno
      de los usos del programa. Esa informacion tambien se mostrara cuando el usuario
      cometa cualquier error en la invocacion del programa.
Tenga tambien en cuenta el siguiente control de errores:
    - Asegurar que se pasan nombres e identificadores de usuarios o grupos validos que existan en la maquina.
    - Asegurar que no se puedan pasar por linea de comandos opciones que sean incompatibles. Las unicas combinaciones posibles son:
        • --help, junto con cualquiera (se ignoran las demas)
        • vacio (equivalente a --active --maingroup)
        • --user <uid o nombre de usuario>
        • --user <uid o nombre de usuario> --maingroup
        • --active
        • --active --maingroup
        • --group <gid o nombre de grupo>
        • --allgroups
*/

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>    // getpwnam, getpwuid
#include <grp.h>    // getgrnam, getgrgid
#include <unistd.h> // getuid
#include <string.h> // strtok, etc.

void ayuda(){ //Función que muestra la ayuda del programa

    printf("Uso del programa:\n");
    printf("  -h, --help               Muestra este mensaje de ayuda\n");
    printf("  -u, --user <uid|user>    Muestra información de un usuario (struct passwd)\n");
    printf("  -g, --group <gid|group>  Muestra información de un grupo (struct group)\n");
    printf("  -a, --active             Equivale a --user con el UID actual\n");
    printf("  -m, --maingroup          Muestra también el grupo principal del usuario\n");
    printf("  -s, --allgroups          Muestra todos los grupos del sistema\n\n");
    printf("Si no se pasa ninguna opción, equivale a --active --maingroup\n");
    printf("Combinaciones permitidas:\n"
           "  --help [en cualquier momento]\n"
           "  (sin opciones) = --active --maingroup\n"
           "  --user <uid|nombre> [--maingroup]\n"
           "  --active [--maingroup]\n"
           "  --group <gid|nombre>\n"
           "  --allgroups\n");
}

bool esNumero(const char *str){ //Función que comprueba si un string es un número

    for (int i = 0; str[i] != '\0'; i++){ //Recorremos el string

        if (str[i]<'0' || str[i]>'9'){ //Si encontramos un caracter que no es un número

            return false;
        }
    }

    return true;
}

void mostrarUsuario(struct passwd *pw){ //Función que muestra la información del usuario

    if(!pw){ //Si no se encuentra el usuario

        printf("Usuario no encontrado.\n");
        return;
    }

    printf("\nInformación del usuario:\n");
    printf("  Nombre (gecos): %s\n", pw->pw_gecos);
    printf("  Login: %s\n", pw->pw_name);
    printf("  UID: %u\n", pw->pw_uid);
    printf("  GID principal: %u\n", pw->pw_gid);
    printf("  Home: %s\n", pw->pw_dir);
    printf("  Shell: %s\n", pw->pw_shell);
}

void mostrarGrupo(struct group *gr){ //Función que muestra la información del grupo

    if(!gr){ //Si no se encuentra el grupo

        printf("Grupo no encontrado.\n");
        return;
    }

    printf("\nInformación del grupo:\n");
    printf("  Nombre del grupo: %s\n", gr->gr_name);
    printf("  GID: %u\n", gr->gr_gid);

    if(gr->gr_mem){ //Si el grupo tiene miembros

        printf("  Miembros: ");
        char **miembro = gr->gr_mem;

        while(*miembro){ //Recorremos la lista de miembros

            printf("%s ", *miembro);
            miembro++;
        }

        printf("\n");
    }
}

void mostrarTodosLosGrupos(){ //Función que muestra todos los grupos del sistema

    FILE *f = fopen("/etc/group", "r"); //Abrimos el fichero /etc/group

    if(!f){ //Si no se puede abrir el fichero

        perror("Error al abrir /etc/group");
        return;
    }

    char linea[1024]; //Buffer para almacenar cada línea del fichero

    while(fgets(linea, sizeof(linea), f)){ //Leemos cada línea del fichero
        //Formato: nombre:password:gid:lista_miembros

        char *nombre = strtok(linea, ":"); //Nombre del grupo
        strtok(NULL, ":"); //Ignoramos el password
        char *gidStr = strtok(NULL, ":"); //GID
        
        if (gidStr){ //Si se encuentra el GID

            gid_t gidNum = (gid_t)atoi(gidStr); //Convertimos el string a un número
            struct group *gr = getgrgid(gidNum); //Obtenemos el grupo a partir del GID
            mostrarGrupo(gr); //Mostramos la información del grupo
        }
    }

    fclose(f); //Cerramos el fichero
}

int main(int argc, char **argv){

    int c; //Variable para almacenar el resultado de getopt_long

    static struct option long_options[]={ //Estructura a utilizar por getopt_long

        {"user", required_argument, NULL, 'u'}, //Recibe un argumento
        {"group", required_argument, NULL, 'g'},
        {"active", no_argument, NULL, 'a'}, //No recibe argumento,
        {"maingroup", no_argument, NULL, 'm'},
        {"allgroups", no_argument, NULL, 's'},
        {"help", no_argument, NULL, 'h'},
        {0, 0, 0, 0} //Final de las opciones
    };

    char *uvalue=NULL; //Variable para almacenar el valor de la opción User
    char *gvalue=NULL;
    bool aflag=false; //Variable para almacenar el valor de la opción Active
    bool mflag=false;
    bool sflag=false;
    bool hflag=false;

    while((c=getopt_long(argc, argv, "u:g:amsh", long_options, NULL))!=-1){ //Procesamos la línea de comandos u y g esperan un argumento

        switch(c){ 

            case 'u':
                uvalue=optarg;
                break;

            case 'g':
                gvalue=optarg;
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

            case '?':
                break;

            default:
                abort();
        }
    }

    if(hflag==true){ //Help e ignora el resto

        ayuda();
        return 0;
    }

    if (argc == 1){ //Si no se pasan argumentos, se asume --active --maingroup

        aflag = true;
        mflag = true;
    }

    struct passwd *pwd = NULL; //Estructura para almacenar la información del usuario
    struct group  *grp = NULL; //Estructura para almacenar la información del grupo

    if(uvalue!=NULL){ //User

        if(esNumero(uvalue)){ //Si es un número, lo interpretamos como UID

            uid_t uid=(uid_t)atoi(uvalue); //Convertimos el string a un número
            pwd = getpwuid(uid); //Obtenemos el usuario a partir del UID
        }
        
        else{ //Sino

            pwd = getpwnam(uvalue); //Obtenemos el usuario a partir del nombre
        }

        if (!pwd){ //Si no se encuentra el usuario

            printf("Error: usuario '%s' no encontrado\n", uvalue);
            return 1;
        }

        mostrarUsuario(pwd); //Mostramos la información del usuario
    }

    if(gvalue!=NULL){

        if (esNumero(gvalue)){ //Si es un número, lo interpretamos como GID

            gid_t gid = (gid_t)atoi(gvalue); //Convertimos el string a un número
            grp = getgrgid(gid); //Obtenemos el grupo a partir del GID
        }
        
        else{

            grp = getgrnam(gvalue); //Obtenemos el grupo a partir del nombre
        }
    
        if (!grp){ //Si no se encuentra el grupo

            printf("Error: grupo '%s' no encontrado\n", gvalue);
            return 1;
        }

        mostrarGrupo(grp); //Mostramos la información del grupo
    }

    if(aflag==true){ //Si se ha pasado la opción --active

        if(pwd){ //Si se ha pasado la opción --user

            fprintf(stderr, "Error: no se puede usar --user y --active a la vez.\n");
            return 1;
        }

        uid_t uidActual = getuid(); //Obtenemos el UID del usuario actual
        pwd = getpwuid(uidActual); //Obtenemos el usuario a partir del UID

        if (!pwd) { //Si no se encuentra el usuario

            fprintf(stderr, "Error: no se pudo obtener usuario actual (UID %d)\n", uidActual); 
            return 1;
        }

        mostrarUsuario(pwd); //Mostramos la información del usuario
    }

    if(mflag && pwd){ //Si se ha pasado la opción --maingroup y se ha pasado un usuario

        gid_t gidPrincipal = pwd->pw_gid; //Obtenemos el GID del grupo principal del usuario
        struct group *gPrinc = getgrgid(gidPrincipal); //Obtenemos el grupo a partir del GID
        mostrarGrupo(gPrinc); //Mostramos la información del grupo
    }

    if(sflag==true){ //Si se ha pasado la opción --allgroups

        if(uvalue || gvalue || aflag || mflag){ //Si se pasan opciones incompatibles

            fprintf(stderr, "Error: --allgroups no puede combinarse con --user/--group/--active/--maingroup.\n");
            return 1;
        }

        mostrarTodosLosGrupos(); //Función que muestra todos los grupos del sistema
        return 0;
    }


    exit(0);
}
