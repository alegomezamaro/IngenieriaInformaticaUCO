// tv-main.cc
// Ejemplo de uso de tv

#include "tv.h"

int main(){

    Tv t1("123", "Televisión curva", 2560, "Samsung", "MediaMark", 60.4);
    Tv t2("456B", "Televisión plana", 3330, "LG", "MediaMark", 75.1);
    std::cout << "TV 1:" << "\nID: " << t1.GetId() << "\nNombre: " << t1.GetName() << "\nPrecio: "
        << t1.GetPrice() << "\nFabricante: " << t1.GetMaker() << "\nVendedor: " << t1.GetSeller()
        << "\nPulgadas: " << t1.GetInch() << "\n\n";
    std::cout << "TV 2:" << "\nID: " << t2.GetId() << "\nNombre: " << t2.GetName() << "\nPrecio: "
        << t2.GetPrice() << "\nFabricante: " << t2.GetMaker() << "\nVendedor: " << t2.GetSeller()
        << "\nPulgadas: " << t2.GetInch() << "\n\n";
}