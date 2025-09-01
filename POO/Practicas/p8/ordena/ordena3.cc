#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
//compilar con g++ o incluir -lstdc++ en gcc

bool desc(float a, float b){
    return a > b;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        std::cout << "Introduce ./ordena3 <Tamaño del vector>\n";
        return 0;
    }
    int tam = atoi(argv[1]);
    std::vector<float> v(tam);
    for(int i = 0; i < tam; i++){
        std::cout << "\nPosicion de memoria " << i << ": ";
        std::cin >> v[i];
    }
    std::string orden;
    std::cout << "\n¿En qué orden quieres ordenar el vector? Ascendente (A) o descendente (D)): ";
    std::cin >> orden;
    if (orden == "A") {
        std::sort(v.begin(), v.end());
    } else if (orden == "D") {
        std::sort(v.begin(), v.end(), desc);
    } else {
        std::cout << "Orden no válido. Introduce 'A' o 'D'.\n";
        return 0;
    }
    for(int i = 0; i < tam; i++){
        std::cout << "\nPosicion de memoria " << i << ": " << v[i] << std::endl;
    }
    return 0;
}