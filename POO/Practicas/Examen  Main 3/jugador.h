// 2. Codificar la clase Jugador en los ficheros jugador.h y jugador.cc con las siguientes características.
//  - La clase Jugador hereda de forma pública de la clase Persona y además dispone del siguiente atributo:
//      puesto_ (string). Puede tomar los valores de "base", "escolta", "alero", "ala-pivot" y "pivot".
//  - Constructor:
//      Versión 1: recibe como parámetros el nombre (obligatorio), la dirección (opcional), el DNI (opcional) y el puesto (obligatorio). Todos los argumentos deberán tener
//      un valor por defecto.
//      Versión 2: constructor de copia.
//  - Observadores: getPuesto.
//  - Modificadores: setPuesto. Deberá comprobar que el valor es uno de los permitidos. En dicho caso, lo modificará y retornará true. En caso contrario, no lo modifica y retorna
//    false.
//  - Sobrecarga de los operadores: El operador =. El operador << escribirá en pantalla los valores de todos los atributos. Al ejercutar el test2 deberá salir por pantalla:
//    Nombre 1;Dir 1;DNI 1;alero

#ifndef JUGADOR_H
#define JUGADOR_H

#include "persona.h"
#include <iostream>

class Jugador : public Persona {
private:
    std::string puesto_;

public:
    // Constructor parametrizado
    Jugador(std::string nombre, std::string puesto, std::string direccion = "XX", std::string DNI = "XX") : Persona(nombre, direccion, DNI) {
        if (puesto == "base" || puesto == "escolta" || puesto == "alero" || puesto == "ala-pivot" || puesto == "pivot") {
            puesto_ = puesto;
        } else {
            puesto_ = "Ninguno";
        }
    }

    // Constructor por copia
    Jugador(const Jugador&) = default;

    // Operador de asignación
    Jugador& operator=(const Jugador& j){
        if (this != &j) {
            Persona::operator=(j);
            puesto_ = j.puesto_;
        }
        return *this;
    }

    // Observador y modificador de puesto
    inline std::string getPuesto() const {
        return puesto_;
    }

    inline bool setPuesto(std::string puesto){
        if(puesto == "base" || puesto == "escolta" || puesto == "alero" || puesto == "ala-pivot" || puesto == "pivot") {
            puesto_ = puesto;
            return true;
        }
        return false;
    }

    //Operador<< Nombre 1;Dir 1;DNI 1;alero
    friend std::ostream& operator<<(std::ostream& o, const Jugador& j){
        o << "Nombre " << j.getNombre() << "; Dir " << j.getDireccion() << "; DNI = " << j.getDNI() << "; " << j.getPuesto();
        return o;
    }
};

#endif