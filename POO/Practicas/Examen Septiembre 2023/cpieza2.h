// 5. Copie los ficheros del ejercicio anterior con el nombre cpieza2.cc y cpieza2.h.
//  - Operador[]. Este recibe un entero y retorna la pieza que se encuentra en la posición
//    de la lista que dice el entero.
//  - Operador=. Efectúa la asignación de un objeto CPieza en otro.

#ifndef CPIEZA2_H
#define CPIEZA2_H

#include "pieza.h"
#include <list>

//Clase cpieza2
class Cpieza2 : public Pieza{
    private:
    std::list<Pieza> piezalist_;

    public:
    //Constructor vacio
    Cpieza2(){
        std::list<Pieza> piezalist;
        if(piezalist_.empty()){
            piezalist_ = piezalist;
        }
        else{
            piezalist.clear();
        }
    }

    //Codigo copia
    Cpieza2(const Cpieza2&) = default;

    //Observador cpieza
    inline std::list<Pieza> get(){
        return piezalist_;
    }

    //Tamaño lista
    inline  int size(){
        return piezalist_.size();
    }

    //Añadir pieza
    bool addPieza(Pieza p);

    //Eliminar pieza
    bool deletePieza(Pieza p);

    //Operador[]
    Pieza operator[](int n);

    //Operador=
    Cpieza2 operator=(const Cpieza2& p){
        piezalist_ = p.piezalist_;
        return *this;
    }
};

#endif