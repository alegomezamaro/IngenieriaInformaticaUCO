// client-main.cc
// Ejemplo de uso de client

#include "client.h"

int main(){

    Client c1("123", "Juan", "Cordoba", "Cordoba", "Spain", 18, 4.568, 2006, 1);
    Client c2("456", "Ana", "Guadalcazar", "Cordoba", "Spain", 25, 7.371, 1999, 2);
    std::cout << c1.GetDataStr() << "Premium: " << c1.GetPremium() << "\n";
    std::cout << "\n\n" << c2.GetDataStr()<< "Premium: " << c2.GetPremium() << "\n";

    return 0;
}