#include "funciones.h"

/*
Codifica un programa en C que, utilizando funciones, lea números enteros desde un fichero
binario generado en el ejercicio anterior, almacene sus valores en un vector dinámico y calcule la
media de los números pares. El nombre del fichero se le preguntará al usuario.
*/

int main() {
    char nombre_fichero[100];
    printf("Introduce el nombre del fichero binario: ");
    scanf("%s", nombre_fichero);

    FILE *fichero = fopen(nombre_fichero, "rb");
    if (!fichero) {
        printf("Error al abrir el fichero para lectura.\n");
        return 1;
    }

    int *numeros;
    int num_elementos = leer_numeros_desde_fichero(fichero, &numeros);
    fclose(fichero);

    if (num_elementos == -1) {
        printf("Error al leer los números desde el fichero.\n");
        return 1;
    }

    float media = calcular_media_pares(numeros, num_elementos);
    printf("La media de los números pares es: %.2f\n", media);

    free(numeros);

    return 0;
}