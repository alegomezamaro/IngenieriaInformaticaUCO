#include "examen.h"

#include <stdio.h>
#include <string.h>
#include <stdio.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

int comprobar1(struct alumno *Vector, int nElementos);
int comprobar2(struct alumno *Vector, int nElementos);
float calcular_media(struct alumno alumno);
int comprobar3(struct alumno *Vector, int nElementos);

int main()
{
    struct alumno alumnos[10] = {
        {"Carlos", 123456789, 7.5, 8.0, 6.5},
        {"Ana", 987654321, 8.5, 9.0, 7.0},
        {"Juan", 555444333, 6.0, 7.5, 8.0},
        {"María", 111222333, 9.0, 8.5, 9.5},
        {"Pedro", 444555666, 7.0, 7.0, 7.0},
        {"Laura", 777888999, 8.0, 8.0, 8.0},
        {"Sofía", 666777888, 6.5, 7.5, 6.0},
        {"Javier", 999888777, 7.5, 8.0, 7.0},
        {"Elena", 222333444, 9.0, 9.0, 7.5},
        {"Miguel", 333222111, 8.5, 8.5, 9.0}};

    apartado1(alumnos, 10, 1);
    if (comprobar1(alumnos, 10))
    {
        apartado1(alumnos, 10, 2);
        if (comprobar2(alumnos, 10))
        {
            printf(ANSI_COLOR_GREEN "Apartado 1) CORRECTO\n" ANSI_COLOR_RESET);
        }
        else
        {
            printf(ANSI_COLOR_RED "Apartado 1) INCORRECTO\n" ANSI_COLOR_RESET);
        }
    }
    else
    {
        printf(ANSI_COLOR_RED "Apartado 1) INCORRECTO\n" ANSI_COLOR_RESET);
    }

    apartado2(alumnos, 10);
    if (comprobar3(alumnos, 10))
    {
        printf(ANSI_COLOR_GREEN "Apartado 2) CORRECTO\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "Apartado 2) INCORRECTO\n" ANSI_COLOR_RESET);
    }

    int result1, result2;
    apartado3(24, 3, &result1);
    apartado3(38, 4, &result2);
    if (result1 == 8 && result2 == 9)
    {
        printf(ANSI_COLOR_GREEN "Apartado 3) CORRECTO\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "Apartado 3) INCORRECTO\n" ANSI_COLOR_RESET);
    }

    char cadena[] = "Academia Main()";
    if (apartado4(cadena, 'e') == 1 && apartado4(cadena, 'a') == 3 && apartado4(cadena, 'w') == 0)
    {
        printf(ANSI_COLOR_GREEN "Apartado 4) CORRECTO\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "Apartado 4) INCORRECTO\n" ANSI_COLOR_RESET);
    }

    return 0;
}

int comprobar1(struct alumno *Vector, int nElementos)
{
    for (int i = 0; i < nElementos - 1; i++)
    {
        if (strcmp(Vector[i].nombre, Vector[i + 1].nombre) > 0)
        {
            return 0;
        }
    }
    return 1;
}

int comprobar2(struct alumno *Vector, int nElementos)
{
    for (int i = 0; i < nElementos - 1; i++)
    {
        if (Vector[i].dni < Vector[i + 1].dni)
        {
            return 0;
        }
    }
    return 1;
}

float calcular_media(struct alumno alumno)
{
    return (alumno.nota1 + alumno.nota2 + alumno.nota3) / 3.0;
}

int comprobar3(struct alumno *Vector, int nElementos)
{
    for (int i = 0; i < nElementos - 1; i++)
    {
        if (calcular_media(Vector[i]) > calcular_media(Vector[i + 1]))
        {
            return 0;
        }
    }
    return 1;
}