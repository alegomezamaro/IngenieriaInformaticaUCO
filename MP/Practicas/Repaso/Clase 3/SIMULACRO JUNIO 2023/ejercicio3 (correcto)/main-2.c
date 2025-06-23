#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int imprimirVector(int nEle, struct datos * Vector);
int comprobarLista(struct lista* cabeza, struct datos* Correctos, int nEle);
int indice(struct datos* V, int nEle, int codigo);

int main()
{
   int nEle1 = 5, nEle2=6, presentados=8, respuesta, comprobacion;
   float acumulada = 0;
   float pesoExamen=0.3;
   float puntosListas=3;   

   struct datos C1[]={{3, "Jose Luis Perez"},{1, "Sofia Sanchez"},{7, "Maria Luisa Avila"},{9, "Mariano Lopez"},{2, "Alfonso Gomez"}};
   struct datos C2[]={{7, "Maria Luisa Avila"}, {4, "Lucia Olmo"}, {9, "Mariano Lopez"}, {6, "Umberto Gutierrez"}, {5, "Alicia Vilches"}, {2, "Alfonso Gomez"}};
   struct lista* LP=NULL;
  
   printf("\n\n-----------------------------");
   printf("\nEJERCICIO 3: LISTAS");
   printf("\n\tTOTAL EJERCICIO (sobre 10): %.3f puntos", puntosListas);
   printf("\n\tTOTAL NOTA FINAL(sobre 3) : %.3f puntos", pesoExamen*puntosListas);   
   printf("\n-----------------------------");
   
   printf("\nEl ejercicio se esta evaluando...");    
   printf("\n\nAlumnos de la primera convocatoria: ");
   imprimirVector(nEle1, C1);
   printf("\n\nAlumnos de la segunda convocatoria: ");
   imprimirVector(nEle2, C2);   
   
   struct datos Correctos[]={{1, "Sofia Sanchez"},{2, "Alfonso Gomez"},{3, "Jose Luis Perez"},{4, "Lucia Olmo"}, {5, "Alicia Vilches"}, {6, "Umberto Gutierrez"}, {7, "Maria Luisa Avila"},{9, "Mariano Lopez"}, {9, "Mariano Lopez"} };
   
   printf("\n\nComprobando lista resultado...\n\n");
   respuesta = ejercicio3(nEle1, nEle2, C1, C2, &LP);     
   if((respuesta != presentados))
   {
       printf("\n\tINCORRECTO: La funcion no devuelve el numero correcto de elementos de la lista. Devuelve %d en lugar de %d. Puntuacion obtenida en listas: %.3f puntos", respuesta, presentados, 0.0);                
   }
   else
   { 
       printf("\n\tNumero de elementos: %d\n\n", respuesta);
       comprobacion = comprobarLista(LP, Correctos, presentados);
       if(comprobacion == 1)
       {
          acumulada+=puntosListas;
          printf("\n\tCORRECTO: Puntuacion obtenida en listas: %.3f puntos", puntosListas);                           
       }
       else
       { 
           if(comprobacion == -1)           
              printf("\n\tINCORRECTO: La lista no contiene los elementos correctos. Puntuacion obtenida en listas: %.3f puntos", 0.0); 
           else        
              printf("\n\tINCORRECTO: El ultimo elemento de la lista no apunta a NULL. Puntuacion obtenida en listas: %.3f puntos", 0.0); 
       }       
   }                     

   printf("\n\n-----------------------------");
   printf("\nEJERCICIO 3: RESUMEN");
   printf("\n\tEVALUACION EJERCICIO (sobre 10): %.3f puntos", acumulada);
   printf("\n\tTOTAL NOTA FINAL(sobre 3) : %.3f puntos", pesoExamen*acumulada);   
   printf("\n\tLa calificacion es PROVISIONAL y deber ser validada por la profesora");   
   printf("\n-----------------------------");   
   
   return 0;    
}


int imprimirVector(int nEle, struct datos * Vector)
{
  
  int i;
  printf("\n\n\t");
  for(i=0; i<nEle-1; i++)
  {
   printf("[%d, <%s>], ",  Vector[i].codigo, Vector[i].nombre);  
  }  
  printf("[%d, <%s>]", Vector[i].codigo, Vector[i].nombre);
  return 1;   
}

int comprobarLista(struct lista* cabeza, struct datos* Correctos, int nEle)
{

   int* check = (int*) calloc (nEle, sizeof(int));
   
   struct lista * aux=cabeza;
   int i=0;
 
   printf("\n\t(%d, <%s>)->", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;  
   i++;
   aux=aux->sig;

   printf("\n\t(%d, <%s>)->", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;     
   i++;
   aux=aux->sig;
   
   printf("\n\t(%d, <%s>)->", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;      
   i++;
   aux=aux->sig;
 
   printf("\n\t(%d, <%s>)->", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;    
   i++;
   aux=aux->sig;
   
   printf("\n\t(%d, <%s>)->", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;      
   i++;
   aux=aux->sig;
   
   printf("\n\t(%d, <%s>)->", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;      
   i++;
   aux=aux->sig;
   
   printf("\n\t(%d, <%s>)->", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;     
   i++;
   aux=aux->sig;
   
   printf("\n\t(%d, <%s>)", aux->codigo, aux->nombre);     
   check[indice(Correctos, nEle, aux->codigo)]=1;      
   i++;
   aux=aux->sig;  
   
   
   for(int i=0; i<nEle; i++)
   {
     if(check[i]!=1)
       return -1;
   }
   
   if(aux!=NULL)
     return -2;
   else
     printf("->NULL\n"); 
   
   return 1;      
}

int indice(struct datos* V, int nEle, int codigo)
{
   int i;
   for(i=0; i<nEle; i++)
     if( V[i].codigo == codigo)
        return i;    
   return -1;
}
