#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>





#define MAX 2048

int main()
{
    float matriz1[MAX][MAX];
    float matriz2[MAX][MAX];
    float matrizre[MAX][MAX];
    int t0,t1;
    int dif;


    t0=clock();

    for(int i=0;i<=MAX;i++)
    {
        for(int j=0;j<=MAX;j++)`
        {
            for(int k=0; k<=MAX;k++)
            {
                matrizre[i][j]= matrizre[i][j] + matriz1[i][k] + matriz2[k][j]
            }
        }
    }

    t1=clock();

    printf("%d\n" ,matrizre[20][20]);

    dif=t1-t0;

    printf("La diferencia es: %i\n");

}