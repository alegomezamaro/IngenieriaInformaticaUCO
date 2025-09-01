// basket-main.cc
// Ejemplo de uso de basket

#include "basket.h"

int main() {
    Basket basket;

    Product p1("001", "Laptop", 999.99, "TechCorp", "BestBuy");
    Product p2("002", "Smartphone", 499.99, "MobileInc", "Amazon");
    Product p3("003", "Headphones", 199.99, "AudioTech", "Walmart");

    // Añadir productos a la cesta
    basket.AddProduct(p1);
    basket.AddProduct(p2);
    basket.AddProduct(p3);
    basket.AddProduct(p2); // Añadir el mismo producto otra vez para probar cantidad

    // Mostrar el contenido de la cesta
    std::cout << "Contenido inicial de la cesta:\n";
    std::vector<std::string> ids = basket.GetIds();
    std::vector<int> quantities = basket.GetQs();
    for (size_t i = 0; i < ids.size(); ++i) {
        std::cout << "ID: " << ids[i] << ", Cantidad: " << quantities[i] << "\n";
    }
    std::cout << "Total de la cesta: $" << basket.GetTotal() << "\n";

    // Eliminar un producto
    basket.DeleteProduct("002"); // Eliminar uno de los smartphones
    std::cout << "\nContenido de la cesta después de eliminar un smartphone:\n";
    ids = basket.GetIds();
    quantities = basket.GetQs();
    for (size_t i = 0; i < ids.size(); ++i) {
        std::cout << "ID: " << ids[i] << ", Cantidad: " << quantities[i] << "\n";
    }
    std::cout << "Total de la cesta: $" << basket.GetTotal() << "\n";

    // Vaciar la cesta
    basket.DeleteBasket();
    std::cout << "\nCesta vaciada.\n";
    std::cout << "Tamaño de la cesta: " << basket.GetSize() << " productos.\n";
    std::cout << "Total de la cesta: $" << basket.GetTotal() << "\n";

    return 0;
}