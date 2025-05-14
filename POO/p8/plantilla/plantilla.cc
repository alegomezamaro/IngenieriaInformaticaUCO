#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

template <class T>
void print_vector(const std::vector<T>& v) {
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << "Posicion de memoria " << i << ": " << v[i] << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Introduce ./plantilla <Tipo de vector: int (I), float (F) o char (C)> <Tamaño del vector>\n";
        return 0;
    }
    std::string tipo = argv[1];
    int tam = std::atoi(argv[2]);
    if (tipo == "I") {
        std::vector<int> v(tam);
        std::cout << "\nVector de enteros:" << std::endl;
        for (int j = 0; j < tam; j++) {
            std::cout << "Pos[ " << j << "]: ";
            std::cin >> v[j];
        }
        print_vector(v);
    }
    else if (tipo == "F") {
        std::vector<float> v(tam);
        std::cout << "\nVector de floats:" << std::endl;
        for (int j = 0; j < tam; j++) {
            std::cout << "Pos[ " << j << "]: ";
            std::cin >> v[j];
        }
        print_vector(v);
    }
    else if (tipo == "C") {
        std::vector<char> v(tam);
        std::cout << "\nVector de char:" << std::endl;
        for (int j = 0; j < tam; j++) {
            std::cout << "Pos[ " << j << "]: ";
            std::cin >> v[j];
        }
        print_vector(v);
    }
    else {
        std::cout << "Orden no válido. Introduce 'I', 'F' o 'C'.\n";
    }
    return 0;
}