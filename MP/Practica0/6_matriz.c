//Ejemplo basico de matrices en C
//PARA COMPILAR: gcc matriz.c -o matriz.exe -Wall
//opción -Wall: muestra avisos con posibles fallos (recomendable usar)

#include<stdio.h>
#define MAX 100


/*No hace falta indicar la dimensión máxima de las filas porque
  los elementos de una matriz estática se almacenan consecutivos
  por filas y para calcular al direccion de [i,j] se utiliza:
  direccion[i, j] = M[0]+NCOL*i+j
*/  

void rellenarMatriz(int M[][MAX], int nFil, int nCol);
void imprimirMatriz(int M[][MAX], int nFil, int nCol);
float mediaMatriz(int M[][MAX], int nFil, int nCol);

int main()
{
   int M[MAX][MAX];
   int nFil, nCol;
   float media;
   
   printf("\nIndique numero de filas (maximo %d): ", MAX);
   scanf("%d", &nFil);
   
   printf("\nIndique numero de columnas (maximo %d): ", MAX);   
   scanf("%d", &nCol);
   
   printf("\nIntroducir valores a la matriz: \n");
   rellenarMatriz(M, nFil, nCol);
   
   printf("\nLa matriz rellena es la siguiente: ");
   imprimirMatriz(M, nFil, nCol);
      
   media = mediaMatriz(M, nFil, nCol);
   printf("\nEl valor medio de la matriz es: %f", media);   
   
   return 0;
}	


void rellenarMatriz(int M[][MAX], int nFil, int nCol)
{
	int i, j;
	for(i=0; i<nFil; i++)
	{	
	  for(j=0; j<nCol; j++)
	  {
	  	 printf("M[%d][%d]: ", i, j);
	  	 scanf("%d", &M[i][j]);
	  }
    }
}

void imprimirMatriz(int M[][MAX], int nFil, int nCol)
{
	int i, j;
	for(i=0; i<nFil; i++)
	{	
	  for(j=0; j<nCol; j++)
	  {
	  	 printf("\nM[%d][%d]: %d", i, j, M[i][j]);	  	 
	  }	  
    }

}

float mediaMatriz(int M[][MAX], int nFil, int nCol)
{
	int i, j;
	int suma=0;
	
	for(i=0; i<nFil; i++)
	{	
	  for(j=0; j<nCol; j++)
	  {
	    suma+=M[i][j];
	  }	  
    }
    
    return (suma*1.0)/(nFil*nCol);
}
