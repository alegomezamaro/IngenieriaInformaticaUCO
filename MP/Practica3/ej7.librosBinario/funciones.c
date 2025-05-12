#include "funciones.h"

void comprobar_existencia_libro(FILE *fichero) {
    fseek(fichero, 0, SEEK_SET);
    char titulo_buscar[100];
    printf("Introduce el título del libro a buscar: ");
    scanf(" %[^\n]", titulo_buscar);

    struct libro temp;
    while (fread(&temp, sizeof(struct libro), 1, fichero) == 1) {
        if (strcmp(temp.titulo, titulo_buscar) == 0) {
            printf("El libro '%s' existe en el stock.\n", titulo_buscar);
            return;
        }
    }

    printf("El libro '%s' no existe en el stock.\n", titulo_buscar);
}

void introducir_nuevo_libro(FILE *fichero) {
    fseek(fichero, 0, SEEK_END);

    struct libro nuevo_libro;
    printf("Introduce el título del nuevo libro: ");
    scanf(" %[^\n]", nuevo_libro.titulo);
    printf("Introduce el autor del nuevo libro: ");
    scanf(" %[^\n]", nuevo_libro.autor);
    printf("Introduce el número de unidades del nuevo libro: ");
    scanf("%d", &nuevo_libro.unidades);

    fwrite(&nuevo_libro, sizeof(struct libro), 1, fichero);

    printf("Libro agregado correctamente al stock.\n");
}

void contar_libros_diferentes(FILE *fichero) {
    fseek(fichero, 0, SEEK_SET);

    struct libro temp;
    int contador = 0;
    char titulos[1000][100];
    while (fread(&temp, sizeof(struct libro), 1, fichero) == 1) {
        int encontrado = 0;
        for (int i = 0; i < contador; i++) {
            if (strcmp(temp.titulo, titulos[i]) == 0) {
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            strcpy(titulos[contador], temp.titulo);
            contador++;
        }
    }

    printf("Número de libros diferentes en el stock: %d\n", contador);
}

void listar_libros(FILE *fichero) {
    fseek(fichero, 0, SEEK_SET);

    struct libro temp;
    printf("Libros en el stock:\n");
    while (fread(&temp, sizeof(struct libro), 1, fichero) == 1) {
        printf("Título: %s, Autor: %s, Unidades: %d\n", temp.titulo, temp.autor, temp.unidades);
    }
}

void vender_libro(FILE *fichero) {
    fseek(fichero, 0, SEEK_SET);
    char titulo_vender[100];
    printf("Introduce el título del libro a vender: ");
    scanf(" %[^\n]", titulo_vender);

    struct libro temp;
    int encontrados = 0;
    long pos_inicio = ftell(fichero);
    while (fread(&temp, sizeof(struct libro), 1, fichero) == 1) {
        if (strcmp(temp.titulo, titulo_vender) == 0) {
            encontrados = 1;
            int unidades_vender;
            printf("Introduce el número de unidades a vender: ");
            scanf("%d", &unidades_vender);

            if (temp.unidades >= unidades_vender) {
                temp.unidades -= unidades_vender;
                fseek(fichero, -sizeof(struct libro), SEEK_CUR);
                fwrite(&temp, sizeof(struct libro), 1, fichero);
                printf("Venta realizada con éxito.\n");
                break;
            } else {
                printf("No hay suficientes unidades disponibles para la venta.\n");
                break;
            }
        }
    }

    if (!encontrados) {
        printf("El libro '%s' no está en el stock.\n", titulo_vender);
    }
}

void borrar_libros_sin_stock(FILE *fichero) {
    FILE *temporal = tmpfile();
    fseek(fichero, 0, SEEK_SET);

    struct libro temp;
    while (fread(&temp, sizeof(struct libro), 1, fichero) == 1) {
        if (temp.unidades > 0) {
            fwrite(&temp, sizeof(struct libro), 1, temporal);
        }
    }

    fclose(fichero);
    fseek(temporal, 0, SEEK_SET);
    fichero = fopen("temporal.bin", "wb+");
    if (!fichero) {
        printf("Error al crear el fichero temporal.\n");
        fclose(temporal);
        return;
    }

    while (fread(&temp, sizeof(struct libro), 1, temporal) == 1) {
        fwrite(&temp, sizeof(struct libro), 1, fichero);
    }

    fclose(temporal);
    remove("temporal.bin");
    printf("Libros sin stock borrados correctamente.\n");
}
