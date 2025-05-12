#include "examen.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

int comprobarVectores(struct dato *v1, struct dato *v2, int size);

int main()
{
    struct dato *v = NULL;
    int tam = 0;
    v = apartado1("libros.bin", &tam);

    if (tam == 10 && v != NULL)
    {
        printf(ANSI_COLOR_GREEN "Apartado 1) CORRECTO\n" ANSI_COLOR_RESET);

        struct dato result[6] = {
            {"El Quijote", "Miguel de Cervantes", 19.99, 5},
            {"Cien años de soledad", "Gabriel Garcia Marquez", 14.50, 3},
            {"La sombra del viento", "Carlos Ruiz Zafon", 24.99, 10},
            {"La casa de los espíritus", "Isabel Allende", 17.00, 12},
            {"Rayuela", "Julio Cortazar", 20.00, 30},
            {"Ficciones", "Jorge Luis Borges", 13.99, 21}};

        int return_value = apartado2("libros.bin", v);

        if (return_value == 6 && comprobarVectores(result, v, 6))
        {
            printf(ANSI_COLOR_GREEN "Apartado 2) CORRECTO\n" ANSI_COLOR_RESET);
        }
        else
        {
            printf(ANSI_COLOR_RED "Apartado 2) INCORRECTO\n" ANSI_COLOR_RESET);
        }
    }
    else
    {
        printf(ANSI_COLOR_RED "Apartado 1) INCORRECTO\n" ANSI_COLOR_RESET);
        printf(ANSI_COLOR_RED "Apartado 2) INCORRECTO (debe funcionar el primer apartado)\n" ANSI_COLOR_RESET);
    }

    free(v);
}

int comprobarVectores(struct dato *v1, struct dato *v2, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(v1[i].titulo, v2[i].titulo) != 0 ||
            strcmp(v1[i].autor, v2[i].autor) != 0 ||
            v1[i].precio != v2[i].precio ||
            v1[i].unidades != v2[i].unidades)
        {
            return 0;
        }
    }
    return 1;
}