// seller-main.cc
// Ejemplo de uso de seller

#include "seller.h"

int main(){

    Seller s1("123", "Juan", "Cordoba", "Cordoba", "Spain", 18, 4.568, 2006, "Carniceria");
    Seller s2("456", "Ana", "Guadalcazar", "Cordoba", "Spain", 25, 7.371, 1999, "Tecnologia");
    std::cout << s1.GetDataStr() << "Sector: " << s1.GetSector() << "\n";
    std::cout << "\n\n" << s2.GetDataStr()<< "Sector: " << s2.GetSector() << "\n";

    return 0;
}