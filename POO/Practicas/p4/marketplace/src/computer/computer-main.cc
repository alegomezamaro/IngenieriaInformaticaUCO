// computer-main.cc
// Ejemplo de uso de computer

#include "computer.h"

std::string TypeToString(ComputerType type) {
    switch (type) {
        case ComputerType::Desktop: return "Desktop";
        case ComputerType::Laptop: return "Laptop";
        case ComputerType::Server: return "Server";
        case ComputerType::Tablet: return "Tablet";
        case ComputerType::Gaming: return "Gaming";
        default: return "Unknown";
    }
}

int main(){

    Computer c1("123", ComputerType::Laptop, "Portatil 12 pulgadas", 1160, "Samsung", "MediaMark");
    Computer c2("456B", ComputerType::Gaming, "Portatil gaming", 3330, "LG", "MediaMark");
    std::cout << "ORDENADOR 1:" << "\nID: " << c1.GetId() << "\nTipo: " << TypeToString(c1.GetType())
        << "\nNombre: " << c1.GetName() << "\nPrecio: " << c1.GetPrice() << "\nFabricante: "
        << c1.GetMaker() << "\nVendedor: " << c1.GetSeller() << "\n\n";
    std::cout << "ORDENADOR 2:" << "\nID: " << c2.GetId() << "\nTipo: " << TypeToString(c2.GetType())
        << "\nNombre: " << c2.GetName() << "\nPrecio: " << c2.GetPrice() << "\nFabricante: "
        << c2.GetMaker() << "\nVendedor: " << c2.GetSeller() << "\n\n";
}