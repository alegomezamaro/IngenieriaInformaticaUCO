#include "funciones.h"

// Función para calcular la media de los números pares en un array
double calcularMediaPares(char* nombreFichero) {

    //Declaramos las variables
    FILE* fichero = fopen(nombreFichero, "r");
    int nums[100]; // Suponemos un máximo de 100 números en el fichero
    int indice = 0;
    int num;
    int suma = 0;
    int num_pares = 0;

    //Si el fichero no se abre correctamente error
    if (fichero == NULL) {
        printf("Error1, no se pudo abrir el fichero <%s>\n", nombreFichero);
        exit(-1);
    }

    // Leer números del fichero y almacenarlos en un array
    while (fscanf(fichero, "%d,", &num) == 1){
        nums[indice] = num;
        indice++;
    }

    //Si el fichero esta vacío error
    if (indice == 0){
        printf("Error2, el fichero está vacío.\n");
        exit(-1);
    }

    //Sumamos los numeros pares
    for (int i = 0; i < indice; i++){
        if (nums[i] % 2 == 0) {
            suma += nums[i];
            num_pares++;
        }
    }

    //Si no existen numeros pares return 0
    if (num_pares == 0){
        return 0;
    }

    //Devolvemos el resultado y cerramos el fichero
    return (double)suma / num_pares;
    fclose(fichero);
}
