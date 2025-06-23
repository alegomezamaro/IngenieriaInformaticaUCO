#include "examen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comprobar1(struct lista *queue, struct dato2 *resultado, int tamResultado);
int comprobar2(struct dato2 * v, struct dato2 *resultado2);

int main()
{
    struct dato v[] = {
        {"111A", 10, 8.0, 4.0},
        {"222B", 20, 4.0, 8.0},
        {"333C", 30, 60.0, 30.0},
        {"444D", 40, 12.0, 24.0},
        {"555D", 50, 10.0, 5.0},
    };

    struct dato2 resultado[] = {
        {"111A", 10, 0.5},
        {"222B", 20, 2.0},
        {"333C", 30, 0.5},
        {"444D", 40, 2.0},
        {"555D", 50, 0.5},
    };

    struct dato2 resultado2[] = {
        {"222B", 20, 2.0},
        {"444D", 40, 2.0},
    };

    struct lista *queue = NULL;

    ejercicio1(v, 5, &queue);

    int ejercicio1 = comprobar1(queue, resultado, 5);

    if (ejercicio1 == 1)
    {
        printf("Ejercicio 1 CORRECTO\n");
        int tam;
        struct dato2 *v = NULL;
        v = ejercicio2(queue, &tam);
        if (tam != 2 || v == NULL)
        {
            printf("Ejercicio 22 INCORRECTO\n");
            exit(-1);
        }
        int ejercicio2 = comprobar2(v, resultado2);
        if (ejercicio2 == 0)
        {
            printf("Ejercicio 2 INCORRECTO\n");
            exit(-1);
        }
        printf("Ejercicio 3 CORRECTO\n");
    }
    else
    {
        printf("Ejercicio 1 INCORRECTO\n");
        printf("No probamos el 2 hasta que te salga el 1\n");
    }

    return 0;
}

int comprobar1(struct lista *queue, struct dato2 *resultado, int tamResultado)
{
    int i = 0;
    struct lista *aux = queue;
    while (aux != NULL)
    {
        if (strcmp(aux->codigo, resultado[i].codigo) != 0 || aux->unidades != resultado[i].unidades || aux->ratio_ganancia != resultado[i].ratio_ganancia)
        {
            return 0;
        }
        i++;
        aux = aux->siguiente;
    }
    if (i != tamResultado)
    {
        return 0;
    }
    return 1;
}

int comprobar2(struct dato2 * v, struct dato2 *resultado2)
{
    for (int i = 0; i < 2; i++)
    {
        if(strcmp(v[i].codigo,resultado2[i].codigo)!=0 || v[i].unidades!=resultado2[i].unidades || v[i].ratio_ganancia!=resultado2->ratio_ganancia)
        {
            return 0;
        }
    }
    return 1;    
}