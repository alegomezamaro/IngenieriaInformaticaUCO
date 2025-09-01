//g++ main.cc product.h product.cc cart.h cart.cc computer.h computer.cc -o main

#include "product.h"
#include "product.cc"
#include "cart.h"
#include "cart.cc"
#include "computer.h"
#include "computer.cc"

int main(){
    //1.
    Product p("Id", "Nombre", 1.0);
    Product p2("", "Nombre", 2.0);

    std::cout << "Product p:" 
        << "\nId: " << p.getId()
        << "\nNombre: " << p.getName()
        << "\nPrecio: "<< p.getPrice() << "\n\n"
        << p.getIdName() << "\n\n"
        << p.getStatus() << "\n\n" //error
        << p2.getStatus() << "\n\n"; //ok

        p.writeData();

    //2.
    Cart c(1);

    std::cout << "Product p:" 
        << "\nId: " << c.getId() << "\n\n"
        << c.getN() << "\n\n";//0

    c.addProduct(p);
    c.addProduct(p2);
    c.addProduct(p);

    std::cout << c.getN() << "\n\n";//2

    c.deleteProduct(p);

    std::cout << c.getN() << "\n\n";//1

    c.addProduct(p);

    std::cout << c.getTotal() << "\n\n";//3.0

    c.print();

    std::cout << "\n\n";

    //3.
    Computer c1(0, "Id", "Nombre", 1.0);
    Computer c2(2, "", "Nombre", 2.0);

    std::cout << "Computer c1:" 
        << "\nId: " << c1.getId()
        << "\nNombre: " << c1.getName()
        << "\nPrecio: "<< c1.getPrice()
        << "\nRam: "<< c1.getRam() << "\n\n"
        << c2.getRam() << "\n\n";

    c2.setRam(4);

    std::cout << c2.getRam() << "\n\n";
    std::cout << c1.getIdNameRam() << "\n\n";

    
}