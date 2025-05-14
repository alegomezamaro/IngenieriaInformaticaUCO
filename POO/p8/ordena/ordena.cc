#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
//compilar con g++ o incluir -lstdc++ en gcc

int main(int argc, char *argv[]){
    if(argc != 2){
        std::cout << "Introduce ./ordena <Tamaño del vector>\n";
        return 0;
    }
    int tam = atoi(argv[1]);
    std::vector<int> v(tam);
    for(int i = 0; i < tam; i++){
        std::cout << "\nPosicion de memoria " << i << ": ";
        std::cin >> v[i];
    }
    std::cout << "\nReordenación del vector:\n";
    std::sort(v.begin(), v.end());
    for(int i = 0; i < tam; i++){
        std::cout << "\nPosicion de memoria " << i << ": " << v[i] << std::endl;
    }
    return 0;
}