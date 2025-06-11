#include "examen.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v[] = {2,5,7,8,23,1,-4};
    float media;
    int cont;

    apartado1(v,7,&cont);

    if(cont!=6)
    {
        printf("\nAPARTADO 1 --> MAL\n");
    }
    else
    {
        printf("\nAPARTADO 1 --> BIEN\n");
    }

    apartado2(v,7);
    if(v[0]!=-4 || v[1]!=1 || v[2]!=23 || v[3]!=8 || v[4]!=7 || v[5]!=5 || v[6]!=2)
    {
        printf("\nAPARTADO 2 --> MAL\n");
    }
    else
    {
        printf("\nAPARTADO 2 --> BIEN\n");
    }

    printf("\n");
    return 0;
}