#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>

// Función para verificar si un número es primo
bool esPrimo(int num) {
    int div = 0;
    for (int i = num; i > 0; i--) {
        if (num % i == 0) {
            div++;
        }
    }
    return div == 2;
}

int main() {
    const int TAMANO = 100000000;
    int* array = new int[TAMANO];
    int count_three = 0;
    std::vector<int> prime_numbers;

    // Inicializamos el generador de números aleatorios
    std::srand(std::time(0));

    // Medimos el tiempo de inicio usando OpenMP
    double start_time = omp_get_wtime();

    // Generamos el array aleatorio y contamos los 3's y primos
    for (int i = 0; i < TAMANO; ++i) {
        array[i] = std::rand() % 101;
        if (array[i] == 3) {
            count_three++;
        }
        if (esPrimo(array[i])) {
            prime_numbers.push_back(array[i]);
        }
    }

    // Medimos el tiempo de finalización usando OpenMP
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    // Mostramos los resultados
    std::cout << "El número 3 aparece " << count_three << " veces en el array." << std::endl;
    std::cout << "Se han encontrado " << prime_numbers.size() << " números primos." << std::endl;
    std::cout << "Tiempo de ejecución: " << execution_time << " segundos." << std::endl;

    // Liberamos la memoria del array
    delete[] array;

    return 0;
}

