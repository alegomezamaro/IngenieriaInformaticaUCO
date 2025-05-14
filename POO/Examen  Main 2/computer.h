// 1. La clase Computer tiene dos campos de tipo string "nombre" y "modelo", y un campo de tipo entero "precio". Codifica el fichero computer.h y computer.cc de la clase Computer con
//    la siguiente funcionalidad:
//  - Constructor con 3 parámetros El nombre será el primer parámetro obligatorio, el modelo sera el segundo parámetro obligatorio. El precio como tercer parámetro y con valor por
//    defecto igual a 0. Si "nombre" o "modelo" reciben la cadena vacía, se asignará su respectivo valor "Ninguno". Si el precio pasado es menor a 0, se asignará al precio el valor 0.
//  - Modificador setNombre() que recibe como parámetro el nuevo nombre. Si el nuevo nombre es la cadena vacía, no se hará el cambio y se devolverá false. En caso contrario se
//    hará el cambio y se devolverá true.
//  - Modificador setModelo() que recibe como parámetro el nuevo modelo. Si el nuevo modelo es la cadena vacía, no se hará el cambio y se devolverá false. En caso contrario se
//    hará el cambio y se devolverá true.
//  - Modificador setPrecio() que recibe como parámetro el nuevo precio que debe ser mayor que cero, en cuyo caso se devuelve true. Si es menor o igual que cero no se asigna y
//    se devuelve false.
//  - Observadores getPrecio(), getModelo() y getNombre().
//  - Observador getNombreYModelo() que devuelve una cadena con el nombre seguido de una coma y un espacio, y a continuación el modelo.

#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>

class Computer{
    private:
    std::string nombre_;
    std::string modelo_;
    int precio_;

    public:
    Computer(std::string nombre, std::string modelo="Ninguno", int precio=0){
        nombre_=nombre;
        if(modelo.empty()){
            modelo_="Ninguno";
        }
        else{
            modelo_=modelo;
        }
        if(precio>0){
            precio_=precio;
        }
        else{
            precio_=0;
        }
    }

    //Observador y modificador nombre
    inline std::string getNombre(){
        return nombre_;
    }
    
    inline bool setNombre(std::string nombre){
        if(nombre.empty()){
            return false;
        }
        else{
            nombre_=nombre;
            return true;
        }
    }

    //Observador y modificador modelo
    inline std::string getModelo(){
        return modelo_;
    }
    
    inline bool setModelo(std::string modelo){
        if(modelo.empty()){
            return false;
        }
        else{
            modelo_=modelo;
            return true;
        }
    }

    //Observador y modificador precio
    inline int getPrecio(){
        return precio_;
    }
    
    inline bool setPrecio(int precio){
        if(precio<0){
            return false;
        }
        else{
            precio_=precio;
            return true;
        }
    }

    //Observador nombre y modelo
    std::string getNombreYModelo(){
        return std::string(getNombre()) + "; " + getModelo();
    }

};

#endif