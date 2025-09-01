// 3. Implementar la clase CPieza que dispone de una lista de objetos de tipo Pieza.
//  - Constructor vacío. Debe asegurarse que la lista esta vacía.
//  - Constructor de copia.
//  - Observador get() que retorna la lista.
//  - Método size() de la clase CPieza, que retorna el numero de piezas de la lista.
//  - Método addPieza. Recibe un objeto Pieza y lo inserta en la lista si este no existe ya.
//    Para buscar la pieza se utiliza el campo código. Retorna true si la pieza se ha insertado
//    correctamente y false en caso contrario.
//  - Método deletePieza. Recibe un objeto Pieza y lo elimina de la lista. Si se ha eliminado el
//    método retorna true y false en caso contrario. Para buscar la pieza se utiliza el campo
//    código, como en el apartado anterior.

#ifndef CPIEZA_H
#define CPIEZA_H

#include "pieza.h"
#include <list>

//Clase cpieza
class Cpieza : public Pieza{
    private:
    std::list<Pieza> piezalist_;

    public:
    //Constructor vacio
    Cpieza(){
        std::list<Pieza> piezalist;
        if(piezalist.empty()){
            piezalist_ = piezalist;
        }
        else{
            piezalist.clear();
            piezalist_ = piezalist;
        }
    }

    //Codigo copia
    Cpieza(const Cpieza&) = default;

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
};

#endif