#include "examen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

int comprobar1(struct dato *Vector, int nElementos, struct lista *LS);

int main()
{
    struct dato alumnos[] = {
        {"Juan", 123456789, 7.5, 8.0, 6.5},   // Aprobado
        {"María", 987654321, 8.5, 9.0, 7.0},  // Aprobado
        {"Pedro", 555444333, 6.0, 7.5, 8.0},  // Aprobado
        {"Laura", 111222333, 5.0, 4.5, 5.5},  // Suspenso
        {"Ana", 444555666, 6.7, 6.8, 6.9},    // Aprobado
        {"Carlos", 777888999, 4.5, 5.0, 4.0}, // Suspenso
        {"Sofía", 666777888, 6.5, 7.5, 6.0},  // Aprobado
        {"Javier", 999888777, 1.5, 5.0, 2.0}, // Suspenso
        {"Elena", 222333444, 7.5, 7.0, 8.5},  // Aprobado
        {"Miguel", 333222111, 4.0, 3.5, 4.5}  // Suspenso
    };

    struct dato aprobados[] = {
        {"Juan", 123456789, 7.5, 8.0, 6.5},  // Aprobado
        {"María", 987654321, 8.5, 9.0, 7.0}, // Aprobado
        {"Pedro", 555444333, 6.0, 7.5, 8.0}, // Aprobado
        {"Ana", 444555666, 6.7, 6.8, 6.9},   // Aprobado
        {"Sofía", 666777888, 6.5, 7.5, 6.0}, // Aprobado
        {"Elena", 222333444, 7.5, 7.0, 8.5}  // Aprobado
    };

    struct lista *LS = NULL;
    int size = 0;
    apartado1(alumnos, 10, &LS, &size);

    if (size == 6 && comprobar1(aprobados, 6, LS))
    {
        printf(ANSI_COLOR_GREEN "Apartado 1) CORRECTO\n" ANSI_COLOR_RESET);

        int result = apartado2(LS, "salida.txt");

        if(result!=6)
        {
            printf(ANSI_COLOR_RED "Apartado 2) INCORRECTO (no estás retornando el valor correcto)\n" ANSI_COLOR_RESET);
            return 0;
        }

        printf("\nLos datos que debe contener tu fichero son estos:\n");
        for (int i = 0; i < 6; i++)
        {
            printf("%s;%ld;%f\n", aprobados[i].nombre, aprobados[i].dni, (aprobados[i].nota1 + aprobados[i].nota2 + aprobados[i].nota3) / 3);
        }

        printf("\nLos datos que contiene el fichero después de ejecutar tu código es el siguiente:\n");
        FILE *fich = fopen("salida.txt", "r");
        if (fich == NULL)
        {
            printf(ANSI_COLOR_RED "Apartado 2) INCORRECTO\n" ANSI_COLOR_RESET);
            return 0;
        }
        char linea[500];
        while (fgets(linea, 500, fich))
        {
            if (linea[strlen(linea) - 1] == '\n')
                linea[strlen(linea) - 1] = '\0';
            printf("%s\n", linea);
        }
        fclose(fich);

        printf("\n\t¿El contenido del fichero es correcto? (s/n): ");
        char opcion;
        scanf("%c", &opcion);

        if (opcion == 's' || opcion == 'S')
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
        printf(ANSI_COLOR_RED "Apartado 2) INCORRECTO (debes tener correcto el primer apartado)\n" ANSI_COLOR_RESET);
    }

    return 0;
}

int comprobar1(struct dato *Vector, int nElementos, struct lista *LS)
{
    struct lista *actual = LS;

    for (int i = 0; i < nElementos; i++)
    {
        float mediaVector = (Vector[i].nota1 + Vector[i].nota2 + Vector[i].nota3) / 3;
        if (actual == NULL || strcmp(Vector[i].nombre, actual->nombre) != 0 || Vector[i].dni != actual->dni || mediaVector != actual->notaMedia)
        {
            return 0;
        }
        actual = actual->siguiente;
    }

    if (actual == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}