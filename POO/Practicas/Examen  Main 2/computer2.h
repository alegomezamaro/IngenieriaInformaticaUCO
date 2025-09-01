// 5. Haz una copia del fichero computer, h que se llame computer2.h, y otra de computer, cc que se llame computer2.cc (Recuerda cambiar include "computer2.h" en computer2.cc).
//    Añade la siguiente funcionalidad:
// a) Un extractor para la clase Computer (operador >>) que saque en pantalla el nombre y el modelo del Computer de la siguiente forma. Por ejemplo, si el nombre fuese Computer]
//    y el modelo PIV, el resultado será el siguiente (es el que saldrá en el test Computer2.Extractor):
//      Nombre: Computer1
//      Modelo: PIV
// b) Un insertador para la clase Computer (operador <<) que pida por teclado el nombre y el modelo del Computer de la siguiente forma:
//    Introduce nombre: (el usuario lo introduce desde el teclado)
//    Introduce modelo: (el usuario lo introduce desde el teclado)

#ifndef COMPUTER2_H
#define COMPUTER2_H

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

    //Extractor operador>>
    //  Nombre: Computer1
    //  Modelo: PIV
    friend std::istream &operator>>(std::istream &i, Computer &c){
        std::cout << "Introduce el nombre: ";
        i >> c.nombre_;
        std::cout << "Introduce el modelo: ";
        i >> c.modelo_;
        return i;
    }
   
    //Operador<<
    //  Introduce nombre: (el usuario lo introduce desde el teclado)
    //  Introduce modelo: (el usuario lo introduce desde el teclado)
    friend std::ostream& operator<<(std::ostream &o, Computer &c){
        o << "Nombre: " << c.nombre_ << "\n";
        o << "Modelo: " << c.modelo_ << "\n";
        return o;
    }

};

#endif