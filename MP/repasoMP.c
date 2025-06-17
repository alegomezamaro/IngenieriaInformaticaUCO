//LIBRERIAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Strlen, strcpy, strcmp...
#include <ctype.h> //Toupper, tolower, isalpha...
#include <math.h> //Compilar con -lm. Sqrt y pow
#include <stdbool.h> //buleano
#include <time.h> //Srand

//CADENAS DE CARACTERES

int strlen(char *cad) //Obtiene la longitud de cad
    char *cad //Puntero a cadena


char *strcpy(char *dest, char *orig); //Copia un char
    char *dest //Puntero a cadena destino
    char *orig //Puntero a cadena origen

int strcmp(char *cad1, char *cad2); //Compara dos char
    char *cad1 //Puntero a cadena 1
    char *cad2 //Puntero a cadena 2
//Devuelve
    //0 son idénticas
    //<0 cad1 precede alfabéticamente a cad2
    //>0 cad2 precede alfabéticamente a cad1

char *strcat(char *cad1, char *cad2); //Concatena las cadenas en cad1 (cad1+cad2)
    char *cad1 //Puntero a cadena 1
    char *cad2 //Puntero a cadena 2

char *strstr(char *cad1, char *cad2); //Buscar una subcadena cad2 en cad1
    char *cad1 //Puntero a cadena 1
    char *cad2 //Puntero a cadena 2
//Devuelve NULL si no la encuentra

char *strchr(char *cad, int c); //Busca la primera aparicion de c en cad
    char *cad //Puntero a cadena
    int c //Caracter a encontrar
//Devuelve
    //Posicion de c si lo encuentra
    //NULL si no lo encuentra

char *strrchr(char *cad, int c); //Busca la ultima aparicion de c en cad
    char *cad //Puntero a cadena
    int c //Caracter a encontrar
//Devuelve
    //Posicion de c si lo encuentra
    //NULL si no lo encuentra

int sprintf(char *cadena, const char *formato, ...); //Almacena en un char un printf
    char *cadena //Puntero al array donde se guardaran los datos
    const char *formato //Texto y conversiones -> "Hola Alejandro, tienes %d años", edad

int sscanf(const char *cadena, const char *formato, ...); //Lee los datos de un char
    const char *cadena //Puntero a la cadena de donde extraer datos
    const char *formato //Texto y conversiones -> "%s %d", nombre, &edad

int atoi(const char *numPtr); //De argumento a int
    const char *numPtr //Argumento

int atol(const char *numPtr); //De argumento a long
    const char *numPtr //Argumento

int atof(const char *numPtr); //De argumento a float
    const char *numPtr //Argumento

int getchar (void); //Almacena en una cadena la tecla pulsada



//GESTIÓN DINÁMICA

void *calloc(size_t nelem, size_t size); //Reserva nelem elementos de tamaño size inicializados a 0
    size_t nelem //Numero de elementos
    size_t size //Tamaño
//Devuelve NULL si hay un error

void *malloc(size_t size); //Reserva memoria de tamaño size
    size_t size //Tamaño
//Devuelve NULL si hay un error

void *realloc(void *ptr, size_t size); //Cambia el tamaño de un calloc o malloc
    void *ptr //Puntero a la memoria reservada
    size_t size //Nuevo tamaño
//Devuelve NULL si hay un error

void free(void *ptr); //Libera memoria
    void *ptr //Puntero a la memoria reservada



//BIBLIOTECAS

ar -rsv libreria.a operaciones.o //Creamos la libreria
gcc -o main1.exe main.o libreria.a //Compilamos con la libreria



//DOXYGEN

    doxygen -g ficheroConfiguracion //Generamos el fichero de configuración

        PROJECT_NAME = Nombre del Proyecto
        OUTPUT_LANGUAGE = Spanish //o English
        OPTIMIZE_OUTPUT_FOR_C = YES //Estructuras en lugar de clases
        SOURCE_BROWSER = YES //Muestra el código de los ficheros .c
        GENERATE_HTML = YES


    doxygen -g ficheroConfiguracion //Generamos el documentación

    /** Comentario de varias líneas en Doxygen */
    /*! Igual */

    /// Comentario de una linea en Doxygen
    //! Igual

    //Si va despues de un bloque de cógido ///< o /**<

    //Estructura
        @brief //Descripción breve
        @fn //Función
        @struct //Estructura
        @var //Variable global
        @param //Parámetros
        @def //Define
        @typedef //Typedef
        @return //Devolución
        @pre //Precondición
        @post //Postcondición

    //Cabecera del fichero
        @file //Fichero
        @author //Autor
        @date //Fecha
        @version //Version



//FICHEROS (AMBOS)

FILE* fopen (const char* nombre, const char* modo); //Abrir ficheros
    const char* nombre //Char puntero con el nombre del ficher
    const char* modo //Modo en el que se va a abrir el fichero
        r   rb //Leer desde, NO escribir (Si no existe error)
        w   wb //Sobreescribir, el archivo que uses se borra, NO leer
        a   ab //Escribir al final del archivo
        r+  r+b //Leer y escribir (Si no existe error)
        w+  w+b //Leer y sobreescribir
        a+  a+b //Leer y escribir al final del archivo, NO sobreescribir
        //Si le añades una b (r -> rb o a+ -> a+b) sirven para ficheros binarios
//Devuelve NULL si hay algún problema durante su apertura

int fclose (FILE* f); //Cerrar ficheros
    FILE* f //Variable a la que asignamos un archivo en fopen
//Devuelve
    //0 si todo va bien
    //EOF (-1) si hay algún problema

int remove (const char* nombre); //Borrar un archivo
    const char* nombre //Nombre del archivo
//Devuelve un valor distinto de 0 en caso de error
        
int rename (const char* viejo, const char* nuevo); //Renombrar un archivo
    const char* viejo //Nombre del archivo
    const char* nuevo //Nuevo nombre del archivo
//Devuelve un valor distinto de 0 en caso de error
        
int fflush (FILE* f); //Se asegura del guardado del archivo
    FILE* f //Fichero a verifica
//Devuelve
    //0 si funciona bien
    //EOF si hay algún error de escritura



//FICHEROS DE TEXTO

int fprintf (FILE* f, const char* formato,...); //Escribir en ficheros
    FILE* f //Fichero a escribir
    const char* formato //Texto y conversiones -> "Nombre: %s, Edad: %d\n", "Alejandro", 29
//Devuelve 
    //El número de caracteres escritos si va bien
    //Un valor negativo si se produce un error

int fscanf (FILE *f, const char *formato, ...); //Leer en ficheros
    FILE* f //Fichero a leer
    const char* formato //Texto y conversiones -> "%s %d", nombre, &edad
//Devuelve
    //Devuelve el número de objetos asignados si va bien (En este caso 2)
    //EOF si se alcanza el fin del fichero o se produce un error

char* fgets (char* s, int n, FILE* f); //Lee lineas de los ficheros
    char* s //Puntero a la cadena donde se guardaran los datos
    int n //Número máximo de caracteres (Contar \0 al final)
    FILE* f //Fichero a leer
//Devuelve NULL si encuentra EOF o hay error

int fputs (const char* s, FILE* f); //Lee lineas de los ficheros
    const char* s //Puntero a la cadena que se quiere escribir
    FILE* f //Fichero a leer
//Devuelve
    //Un valor no negativo si tiene éxito
    //EOF si ocurre un error de escritura

int fgetc (FILE *f); int getc (FILE *f); //Leen un caracter del fichero
    FILE* f //Fichero a leer
//Devuelven el siguiente carácter del fichero f

int fputc (int c, FILE *f); int putc (int c, FILE *f); //Escriben un carácter
    int c //Caracter a escribir
    FILE* f //Fichero a escribir
//Devuelven EOF si hay error



//FICHEROS BINARIOS

size_t fread(void* ptr, size_t tam, size_t num, FILE* f); //Leer datos binarios de un archivo
    void* ptr //Puntero al buffer de destino donde se guardarán los datos
    size_t tam //Tamaño de elementos (bytes)
    size_t num //Cantidad de elementos
    FILE* f //Fichero a leer
//Devuelve
    //=num correcto
    //<num error o se alcanza el fin del fichero

size_t fwrite(const void* ptr,size_t tam,size_t num, FILE* f); //
    void* ptr //Puntero al buffer de origen de donde se obtendrán los datos
    size_t tam //Tamaño de elementos (bytes)
    size_t num //Cantidad de elementos
    FILE* f //Fichero a escribir
//Devuelve
    //=num correcto
    //<num error o se alcanza el fin del fichero

long ftell (FILE* f); //Obtiene la posición actual del cursor en un archivo
    FILE* f //Fichero
//Devuelve –1L si hay error

int fseek (FILE* f, long desp, int origen); //Mover el cursor del archivo a una posición concreta
    FILE* f //Fichero
    long desp //Numero de bytes a desplazar
    int origen //Origen del desplazamiento
        SEEK_SET    0 //Inicio del archivo
        SEEK_CUR    1 //Posición actual
        SEEK_END    2 //Final del archivo
//Devuelve distinto de 0 si se produce algún error



//MAKEFILE

    make //Creamos el makefile
        make -f nombre //Con un nombre personalizado
        make -h //Ayuda

    //Fichero makefile
    #Este es el makefile de compilacion

    all:saludo ejercicio.exe clean

    saludo: 
        @echo Compilando el programa...
        
    ejercicio.exe:main.o funciones.o
        @gcc main.o funciones.o -lm -o ejercicio.exe 

    main.o:main.c funciones.h
        @gcc main.c -lm -c main.o
        
    funciones.o:funciones.c  funciones.h
        @gcc funciones.c -lm -c funciones.o

    .PHONY: clean

    clean:
        @echo Archivos .o borrados con exito
        @rm *.o



//COMPROBACIONES MICRO 2

if((f = fopen(nombre, "r")) == NULL){ //Comprobamos que el fichero se abra correctamente
    printf("\nError, el fichero binario no se ha abierto correctamente\n");
    exit(-1);
}

while(fread(&p, sizeof(struct producto), 1, ficheroBinario) == 1){ //Mientras se pueda leer el fichero binario
    fprintf(ficheroTexto, "%s\n%d\n%f\n%i\n", p.nombre, p.cod, p.precio, p.unidades); //Lo pasamos a un fichero de texto
}



//LISTAS, PILAS Y COLAS

struct lista{

    int dato; //Dato de la lista
    struct lista *sig; //Puntero al siguiente elemento de la lista
};

struct pila{

    char nombre[20];
    struct pila *sig;
};

struct punto{
    
    float x;
    float y;
};

struct cola{

    struct punto p;
    struct cola *sig;
};



//QSORT

int compararEnteros(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void qsort(void *vector, size_t tamaño, size_t sizeof, int (*comparar)(const void *, const void *));
//Ordenar arrays usando quicksort


