// 2. Codificar la clase Refpieza, en los ficheros, refpieza.h y refpieza.cc, que deriva de
//    la clase Pieza. Esta clase tiene además un codigo de referencia de tipo string.
//  - Constructor parametrizado cuyos únicos parámetros, todos obligatorios, son el codigo
//    de referencia, el codigo de pieza, y el nombre de pieza, en dicho orden.
//  - Constructor de copia.
//  - Observadores y modificadores.

#ifndef REFPIEZA_H
#define REFPIEZA_H

#include "pieza.h"

//Clase refpieza
class Refpieza : public Pieza{
    private:
    std::string codigoref_;

    public:
    //Constructor con codigoref, nombre y codigo
    Refpieza(std::string codigoref, std::string nombre, int codigo) : Pieza(nombre, codigo){
        codigoref_=codigoref;
    }

    //Codigo copia
    Refpieza(const Refpieza&) = default;

    //Observador y modificador codigoref
    inline std::string GetCodigoref(){
        return codigoref_;
    }

    inline void SetCodigoref(std::string codigoref){
        codigoref_=codigoref;
    }
};

#endif