#include "funciones.h"

void crearNegativoPGM(const char *nombreArchivoOriginal, const char *nombreArchivoResultado) {
    FILE *archivoOriginal = fopen(nombreArchivoOriginal, "rb");
    if (archivoOriginal == NULL) {
        perror("Error1 al abrir el archivo original");
        exit(EXIT_FAILURE);
    }

    FILE *archivoResultado = fopen(nombreArchivoResultado, "wb");
    if (archivoResultado == NULL) {
        perror("Error2 al abrir el archivo de resultado");
        exit(EXIT_FAILURE);
    }

    // Leer y escribir la cabecera del archivo
    char tipo[3];
    fscanf(archivoOriginal, "%2s\n", tipo);
    fprintf(archivoResultado, "%2s\n", tipo);

    // Ignorar comentarios
    char c;
    while ((c = fgetc(archivoOriginal)) == '#') {
        while ((c = fgetc(archivoOriginal)) != '\n');
        fprintf(archivoResultado, "#\n");
    }

    ungetc(c, archivoOriginal); // Devolver el caracter leído que no era un comentario

    // Leer dimensiones y nivel máximo de gris
    int columnas, filas, maxNivelGris;
    fscanf(archivoOriginal, "%d %d\n%d\n", &columnas, &filas, &maxNivelGris);
    fprintf(archivoResultado, "%d %d\n%d\n", columnas, filas, maxNivelGris);

    // Calcular negativo y escribirlo en el archivo de resultado
    unsigned char pixel;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            fread(&pixel, sizeof(unsigned char), 1, archivoOriginal);
            pixel = 255 - pixel;
            fwrite(&pixel, sizeof(unsigned char), 1, archivoResultado);
        }
    }

    fclose(archivoOriginal);
    fclose(archivoResultado);
}