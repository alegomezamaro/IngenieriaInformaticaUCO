#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <random>

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

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <numero_de_hilos>" << std::endl;
        return 1;
    }

    int num_threads = std::atoi(argv[1]);
    omp_set_num_threads(num_threads); // Establecer el número de hilos

    const int TAMANO = 100000000;
    int* array = new int[TAMANO];
    int count_three = 0;
    std::vector<int> prime_numbers;
    std::vector<std::vector<int>> prime_numbers_private(num_threads);

    // Inicializamos el generador de números aleatorios
    std::srand(std::time(0));

    // Medimos el tiempo de inicio usando OpenMP
    double start_time = omp_get_wtime();

    // Generamos el array aleatorio y contamos los 3's y primos en paralelo
    #pragma omp parallel // Inicia una región paralela
    {
        int thread_id = omp_get_thread_num();
        std::vector<int>& local_prime_numbers = prime_numbers_private[thread_id];

        // Generador de números aleatorios local para cada hilo
        std::mt19937 rng(thread_id + std::time(0)); 
        std::uniform_int_distribution<int> dist(0, 100);

        // División del bucle entre los hilos y reducción para count_three
        #pragma omp for reduction(+:count_three)
        for (int i = 0; i < TAMANO; ++i) {
            array[i] = dist(rng);
            if (array[i] == 3) {
                count_three++;
            }
            if (esPrimo(array[i])) {
                local_prime_numbers.push_back(array[i]);
            }
        }
    }

    // Combinar resultados de números primos
    for (const auto& local_primes : prime_numbers_private) {
        prime_numbers.insert(prime_numbers.end(), local_primes.begin(), local_primes.end());
    }

    // Medimos el tiempo de finalización usando OpenMP
    double end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    // Mostramos los resultados
    std::cout << "Número de hilos: " << num_threads << std::endl;
    std::cout << "El número 3 aparece " << count_three << " veces en el array." << std::endl;
    std::cout << "Se han encontrado " << prime_numbers.size() << " números primos." << std::endl;
    std::cout << "Tiempo de ejecución: " << execution_time << " segundos." << std::endl;

    // Liberamos la memoria del array
    delete[] array;

    return 0;
}

