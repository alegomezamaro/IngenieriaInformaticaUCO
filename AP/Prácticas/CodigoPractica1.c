#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#define MAX 2048

double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

int main(){

   int t0, t1, dif;
   t0=clock();
   for(int i=0; i<MAX; i++){
       for(int j=0; j<MAX; j++){
           for(int k=0; k<MAX; k++){
            
               C[i][j]= C[i][j] + A[i][k] + B[k][j];
           }
       }
   }

   t1=clock();
   printf("C[20][20]= %d\n",C[20][20]);
   dif=(t1 - t0)/CLOCKS_PER_SEC;
   printf("La diferencia es de %i segundos\n", dif);
}
