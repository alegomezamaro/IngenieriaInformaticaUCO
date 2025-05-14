//g++ pieza.h refpieza.h cpieza.h cpieza.cc  cpieza2.h cpieza2.cc  main-pieza.cc -o ej
#include "pieza.h"
#include "refpieza.h"
#include "cpieza.h"
#include "cpieza2.h"

int main(){

    //pieza.h
    Pieza p1;
    Pieza p2("Tornillo", 123);

    std::cout << "\n\nPIEZA 1:\nNombre: " << p1.GetNombre() << "\nCodigo: " << p1.GetCodigo() << "\nCantidad: "
        << p1.GetCantidad() << "\nPrecio: " << p1.GetPrecio();
    std::cout << "\n\nPIEZA 2:\nNombre: " << p2.GetNombre() << "\nCodigo: " << p2.GetCodigo() << "\nCantidad: "
        << p2.GetCantidad() << "\nPrecio: " << p2.GetPrecio();
    
    p1.SetNombre("Llave Inglesa");
    p1.SetCodigo(234);
    p1.SetCantidad(3);
    p1.SetPrecio(3.99);

    std::cout << "\n\nPIEZA 1 MODIFICADA:\nNombre: " << p1.GetNombre() << "\nCodigo: " << p1.GetCodigo()
        << "\nCantidad: " << p1.GetCantidad() << "\nPrecio: " << p1.GetPrecio();
    
    std::cout << "\n\n" << p1.GetPieza();
    std::cout << "\n\n" << p2.GetPieza();

    //refpieza.h
    Refpieza r1("123A", "Tornillo", 123);

    std::cout << "\n\nREFPIEZA 1:\nReferencia: " << r1.GetCodigoref() << "\nNombre: " << r1.GetNombre()
        << "\nCodigo: " << r1.GetCodigo();
    
    r1.SetCodigoref("123B");

    std::cout << "\n\nREFPIEZA 1 MODIFICADO:\nReferencia: " << r1.GetCodigoref() << "\nNombre: " << r1.GetNombre()
        << "\nCodigo: " << r1.GetCodigo();

    //cpieza2.h
    Cpieza2 cp1;
    std::cout << "\n" << cp1.addPieza(p1);
    std::cout << "\n\nHay " << cp1.size() << " pieza";
    std::cout << "\n" << cp1.addPieza(p2);
    std::cout << "\n\nHay " << cp1.size() << " piezas al añadir p2";
    std::cout << "\n" << cp1.deletePieza(p2);
    std::cout << "\n\nHay " << cp1.size() << " pieza al eliminar p2";

    std::cout << "\n\nLISTA PIEZAS 1 POSICION 0:\nNombre: " << cp1[0].GetNombre() << "\nCodigo: "
    << cp1[0].GetCodigo() << "\nCantidad: " << cp1[0].GetCantidad() << "\nPrecio: " << cp1[0].GetPrecio();

    Cpieza2 cp2 = cp1;
    std::cout << "\n\nLISTA PIEZAS 2 POSICION 0:\nNombre: " << cp2[0].GetNombre() << "\nCodigo: "
    << cp2[0].GetCodigo() << "\nCantidad: " << cp2[0].GetCantidad() << "\nPrecio: " << cp2[0].GetPrecio();

    return 0;
}