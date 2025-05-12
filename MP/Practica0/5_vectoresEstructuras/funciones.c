#include <stdio.h>
#include "funciones.h" 
#include <string.h>

struct datos rellenarAlumno()
{
   struct datos alumno;
   
   printf("Indique nombre y apellidos: ");
  
   //opcion A
   //fgets(alumno.nombre, MAX_LINEA, stdin);
   //if(alumno.nombre[strlen(alumno.nombre)-1]=='\n')
   //  alumno.nombre[strlen(alumno.nombre)-1]='\0';

   //opcion B - 250 es el valor de MAX_LINEA
   scanf("%250[^\n]", alumno.nombre);

   printf("\tIndique la edad: ");
   scanf("%d", &alumno.edad);

   printf("\tIndique la nota media: ");
   scanf("%f", &alumno.nota);
   getchar(); //quita el \n

   /*Cuando mezclamos lectura de cadenas con lectura de números,
    si después del numero se va a leer una cadena, usaremos un getchar() 
    para quitar el \n que ha quedado en el buffer*/ 
   
   return alumno;

}

void imprimirAlumno(struct datos alumno)
{
   printf("\nNombre: <%s>\n\tedad: %d\n\tnota media: %f", alumno.nombre, alumno.edad, alumno.nota);
}

void rellenarVector(struct datos Alumnos[], int nEle)
{
   int i;
   for(i=0; i<nEle; i++)
     Alumnos[i]=rellenarAlumno();
}

void imprimirVector(struct datos Alumnos[], int nEle)
{
   int i;
   for(i=0; i<nEle; i++)
     imprimirAlumno(Alumnos[i]);

}

int primerNombre(struct datos Alumnos[], int nEle)
{
   float suma=0;
   int i, primero=0;
   
   for(i=0; i<nEle; i++)
     if(strcmp(Alumnos[i].nombre, Alumnos[primero].nombre)<0) 
        primero=i;
   return primero;
}

float calcularEdadMedia(struct datos Alumnos[], int nEle)
{
   int suma=0;
   int i;
   
   for(i=0; i<nEle; i++)
    suma += Alumnos[i].edad; //suma = suma+Alumnos[i].edad
 
   return (suma*1.0)/nEle; //para tener decimales
}
