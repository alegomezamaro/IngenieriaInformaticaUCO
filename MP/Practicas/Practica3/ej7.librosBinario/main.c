#include "funciones.h"

/*
Construye un programa que gestione, mediante ficheros binarios, el stock de libros de una
librería. Cada libro se almacenará en una estructura struct libro, descrita en el ejercicio 4.
El programa contará con un menú que permitirá realizar las siguientes operaciones:
- Comprobar la existencia de un determinado libro buscando por su título.
- Introducir un nuevo libro en el stock.
- Contar el número de libros (títulos) diferentes que hay en el stock. Considera que no puede
haber títulos de libros repetidos en el fichero.
- Listar los libros en el stock almacenándolos previamente en un vector dinámico
- Vender n unidades de un libro buscándolo por su título. Si hay menos de n unidades en el
stock, se venderán solo las unidades disponibles.
- Borrar (borrado físico) aquellos registros con 0 unidades disponibles.
- Salir.
El nombre del fichero se pasará como argumento en la línea de órdenes.
*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nombre_del_fichero>\n", argv[0]);
        return 1;
    }

    char *nombre_fichero = argv[1];

    FILE *fichero = fopen(nombre_fichero, "rb+");
    if (!fichero) {
        printf("El fichero no existe. Creando uno nuevo...\n");
        fichero = fopen(nombre_fichero, "wb+");
        if (!fichero) {
            printf("Error al crear el fichero.\n");
            return 1;
        }
    }

    int opcion;
    do {
        printf("\nMenú:\n");
        printf("1. Comprobar existencia de un libro por título.\n");
        printf("2. Introducir un nuevo libro en el stock.\n");
        printf("3. Contar el número de libros diferentes en el stock.\n");
        printf("4. Listar los libros en el stock.\n");
        printf("5. Vender n unidades de un libro.\n");
        printf("6. Borrar libros con 0 unidades disponibles.\n");
        printf("7. Salir.\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                comprobar_existencia_libro(fichero);
                break;
            case 2:
                introducir_nuevo_libro(fichero);
                break;
            case 3:
                contar_libros_diferentes(fichero);
                break;
            case 4:
                listar_libros(fichero);
                break;
            case 5:
                vender_libro(fichero);
                break;
            case 6:
                borrar_libros_sin_stock(fichero);
                break;
            case 7:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Por favor, seleccione una opción del menú.\n");
        }
    } while (opcion != 7);

    fclose(fichero);

    return 0;
}
