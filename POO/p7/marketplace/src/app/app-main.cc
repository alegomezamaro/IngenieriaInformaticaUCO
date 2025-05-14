// app-main.cc

#include <iostream>
#include <string>
#include "market.h"
#include "client.h"
#include "seller.h"
#include "product.h"

void ShowMenu() {
    std::cout << "================= Marketplace =================\n";
    std::cout << "1. Añadir cliente\n";
    std::cout << "2. Añadir vendedor\n";
    std::cout << "3. Añadir producto a la cesta de un cliente\n";
    std::cout << "4. Borrar producto de la cesta de un cliente\n";
    std::cout << "5. Volcar datos al fichero ventas.txt\n";
    std::cout << "6. Volcar datos a pantalla\n";
    std::cout << "7. Salir\n";
    std::cout << "==============================================\n";
    std::cout << "Elige una opción: ";
}

int main() {
    // Crear el marketplace con un eslogan
    Market marketplace("¡El mejor lugar para tus compras!");

    // Insertar 5 clientes
    marketplace.AddClient(Client("C1", "Alice", "Madrid", "Madrid", "Spain", 30, 4.5, 2015, 1));
    marketplace.AddClient(Client("C2", "Bob", "Barcelona", "Catalonia", "Spain", 25, 3.8, 2017, 0));
    marketplace.AddClient(Client("C3", "Charlie", "Valencia", "Valencia", "Spain", 35, 4.9, 2012, 1));
    marketplace.AddClient(Client("C4", "David", "Sevilla", "Andalucia", "Spain", 28, 4.2, 2018, 0));
    marketplace.AddClient(Client("C5", "Eva", "Bilbao", "Basque Country", "Spain", 22, 3.6, 2020, 1));

    // Insertar 5 vendedores con 5 productos cada uno
    Seller s1("S1", "Electronics Store", "Madrid", "Madrid", "Spain", 10, 4.8, 2010, "Electronics");
    s1.AddProduct(Product("P1", "Laptop", 1500.0, "Dell", "Electronics Store"));
    s1.AddProduct(Product("P2", "Smartphone", 800.0, "Samsung", "Electronics Store"));
    s1.AddProduct(Product("P3", "Tablet", 400.0, "Apple", "Electronics Store"));
    s1.AddProduct(Product("P4", "Monitor", 300.0, "LG", "Electronics Store"));
    s1.AddProduct(Product("P5", "Keyboard", 50.0, "Logitech", "Electronics Store"));
    marketplace.AddSeller(s1);

    Seller s2("S2", "Clothing Store", "Barcelona", "Catalonia", "Spain", 15, 4.5, 2015, "Clothing");
    s2.AddProduct(Product("P6", "T-shirt", 20.0, "Nike", "Clothing Store"));
    s2.AddProduct(Product("P7", "Jeans", 40.0, "Levis", "Clothing Store"));
    s2.AddProduct(Product("P8", "Jacket", 100.0, "Zara", "Clothing Store"));
    s2.AddProduct(Product("P9", "Shoes", 60.0, "Adidas", "Clothing Store"));
    s2.AddProduct(Product("P10", "Hat", 15.0, "H&M", "Clothing Store"));
    marketplace.AddSeller(s2);

    // Añadir más vendedores y productos según el mismo formato

    int option;
    do {
        ShowMenu();
        std::cin >> option;

        switch (option) {
            case 1: {
                std::string id, name, town, province, country;
                int age, entry_year, premium;
                double rank;

                std::cout << "Introduce el ID del cliente: ";
                std::cin >> id;
                std::cout << "Introduce el nombre del cliente: ";
                std::cin >> name;
                std::cout << "Introduce la ciudad: ";
                std::cin >> town;
                std::cout << "Introduce la provincia: ";
                std::cin >> province;
                std::cout << "Introduce el país: ";
                std::cin >> country;
                std::cout << "Introduce la edad: ";
                std::cin >> age;
                std::cout << "Introduce el ranking (0-5): ";
                std::cin >> rank;
                std::cout << "Introduce el año de registro: ";
                std::cin >> entry_year;
                std::cout << "¿Es premium? (1 para sí, 0 para no): ";
                std::cin >> premium;

                Client new_client(id, name, town, province, country, age, rank, entry_year, premium);
                if (marketplace.AddClient(new_client)) {
                    std::cout << "Cliente añadido correctamente.\n";
                } else {
                    std::cout << "El cliente ya existe.\n";
                }
                break;
            }
            case 2: {
                std::string id, name, town, province, country, sector;
                int age, entry_year;
                double rank;

                std::cout << "Introduce el ID del vendedor: ";
                std::cin >> id;
                std::cout << "Introduce el nombre del vendedor: ";
                std::cin >> name;
                std::cout << "Introduce la ciudad: ";
                std::cin >> town;
                std::cout << "Introduce la provincia: ";
                std::cin >> province;
                std::cout << "Introduce el país: ";
                std::cin >> country;
                std::cout << "Introduce el sector: ";
                std::cin >> sector;
                std::cout << "Introduce la edad: ";
                std::cin >> age;
                std::cout << "Introduce el ranking (0-5): ";
                std::cin >> rank;
                std::cout << "Introduce el año de registro: ";
                std::cin >> entry_year;

                Seller new_seller(id, name, town, province, country, age, rank, entry_year, sector);
                if (marketplace.AddSeller(new_seller)) {
                    std::cout << "Vendedor añadido correctamente.\n";
                } else {
                    std::cout << "El vendedor ya existe.\n";
                }
                break;
            }
            case 3: {
                std::string client_id, product_id;
                std::cout << "Introduce el ID del cliente: ";
                std::cin >> client_id;
                std::cout << "Introduce el ID del producto: ";
                std::cin >> product_id;

                if (marketplace.AddProductClient(Product(product_id, "unknown"), client_id)) {
                    std::cout << "Producto añadido a la cesta correctamente.\n";
                } else {
                    std::cout << "Error al añadir el producto a la cesta.\n";
                }
                break;
            }
            case 4: {
                std::string client_id, product_id;
                std::cout << "Introduce el ID del cliente: ";
                std::cin >> client_id;
                std::cout << "Introduce el ID del producto: ";
                std::cin >> product_id;

                if (marketplace.DeleteProductClient(Product(product_id, "unknown"), client_id)) {
                    std::cout << "Producto eliminado de la cesta correctamente.\n";
                } else {
                    std::cout << "Error al eliminar el producto de la cesta.\n";
                }
                break;
            }
            case 5: {
                if (marketplace.DumpMarket(1)) {
                    std::cout << "Datos volcados a ventas.txt correctamente.\n";
                } else {
                    std::cout << "Error al volcar los datos.\n";
                }
                break;
            }
            case 6: {
                if (marketplace.DumpMarket(0)) {
                    std::cout << "Datos volcados a pantalla correctamente.\n";
                } else {
                    std::cout << "Error al volcar los datos.\n";
                }
                break;
            }
            case 7:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción no válida. Inténtalo de nuevo.\n";
        }

    } while (option != 7);

    return 0;
}
