// 1. Codificar la clase Persona en los ficheros persona.h y persona.cc con las siguientes características.
//    Atributos: nombre_ (string), direccion_ (string), DNI_ (string)
//    Constructor
//      - Versión 1: recibe como parámetros el nombre (obligatorio), la dirección (opcional) y el DNI (opcional). Los argumentos deberán tener un valor por defecto "XX".
//      - Versión 2: constructor de copia.
//    Observadores: getNombre, getDireccion, getDNI.
//    Modificadores: setNombre, setDireccion, setDNI. Todos ellos serán booleanos, comprobando que no se recibe una cadena vacía. En caso de recibirla, no se modificará la
//      variable y retornarán false. En caso contrario, se modificará y retornará true.
//    Método getDatos(): Dicho método retornará por referencia la concatenación del nombre, dirección y dni de la siguiente forma:
//      "XXX con DNI YYY vive en CCC" donde XXX corresponde al nombre, YYY al DNI y CCC a la dirección.


#ifndef PERSONA_H
#define PERSONA_H

#include <iostream>
#include <string>

class Persona{
    private:
    std::string nombre_;
    std::string direccion_;
    std::string DNI_;

    public:
    //Constructor parametrado
    Persona(std::string nombre, std::string direccion="XX", std::string DNI="XX"){
        nombre_=nombre;
        direccion_=direccion;
        DNI_=DNI;
    }

    //Constructor copia
    Persona(const Persona&) = default;

    //Observador y constructor nombre
    inline std::string getNombre() const {
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
    
    //Observador y constructor direccion
    inline std::string getDireccion() const {
        return direccion_;
    }

    inline bool setDireccion(std::string direccion){
        if(direccion.empty()){
            return false;
        }
        else{
            direccion_=direccion;
            return true;
        }
    }

    //Observador y constructor DNI
    inline std::string getDNI() const {
        return DNI_;
    }

    inline bool setDNI(std::string DNI){
        if(DNI.empty()){
            return false;
        }
        else{
            DNI_=DNI;
            return true;
        }
    }

    std::string getDatos(std::string datos){
        datos = nombre_ + " con DNI " + DNI_ + " vive en " + direccion_;
        std::cout << "Datos generados: " << datos << std::endl;
        return datos;
    }
};

#endif