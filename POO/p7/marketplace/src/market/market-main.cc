// market-main.cc
// Ejemplo de uso de market

#include "market.h"

int main(){
    Market m1("Hola mundo");
    std::cout << "SLOGAN: " << m1.GetSlogan() << "\n";
}