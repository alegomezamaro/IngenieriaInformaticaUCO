// product-main.cc
// Ejemplo de uso de product

#include "product.h"

int main(){

    Product p1("123", "Cepillo de dientes", 30.5, "Oral B", "Mercadona");
    Product p2("456B", "TV 75 pulgadas", 3330, "LG", "MediaMark");
    std::cout << "PRODUCTO 1:" << "\nID: " << p1.GetId() << "\nNombre: " << p1.GetName() << "\nPrecio: "
        << p1.GetPrice() << "\nFabricante: " << p1.GetMaker() << "\nVendedor: " << p1.GetSeller() << "\n\n";
    std::cout << "PRODUCTO 2:" << "\nID: " << p2.GetId() << "\nNombre: " << p2.GetName() << "\nPrecio: "
        << p2.GetPrice() << "\nFabricante: " << p2.GetMaker() << "\nVendedor: " << p2.GetSeller() << "\n\n";
}