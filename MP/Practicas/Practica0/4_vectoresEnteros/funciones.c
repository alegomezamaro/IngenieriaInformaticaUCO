#include <stdio.h>
#include "funciones.h" 

void rellenarVector(int Vector[], int nEle)
{
   int i;
   for(i=0; i<nEle; i++)
   {
   	  printf("Vector[%d]: ", i);
   	  scanf("%d", &Vector[i]); 
      //tambien es valido scanf("%d", Vector+i);   	  
   }
}

void imprimirVector(int Vector[], int nEle)
{
   for(int i=0; i<nEle; i++)   
   	  printf("\nVector[%d]: %d", i, Vector[i]);   	 
}

float calcularMedia(int Vector[], int nEle)
{
   int suma=0;
   int i;
   
   for(i=0; i<nEle; i++)
    suma += Vector[i]; // suma = suma+Vector[i]
 
   return (suma*1.0)/nEle; 
   // suma y nEle son de tipo entero. Para tener decimales el dividendo
   // o el divisor deben ser float. Podemos hacer la conversión:
   // a) multiplicando por por 1.0 => (suma*1.0)/nEle
   // b) haciendo un casting a float => ((float)suma)/nEle
}
