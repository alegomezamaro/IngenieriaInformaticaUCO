// 5. Programa la clase Dato que posee un identificador de tipo int y un dato de tipo plantilla. Programe:
//  - Constructor: con parámetro obligatorio id correspondiente al identificador y valor correspondiente
//    al contenido de dato.
//  - Observador por referencia: getId, getDato
//  - Modificador: setId, setDato
//  - Operador:
//      Comparacion == : comparar dos objetos de tipo Dato por el dato plantilla.
//      Comparación != : comparar dos objetos de tipo Dato por el dato plantilla.

#ifndef DATO_H
#define DATO_H

#include <string>

template <class T>

class Dato {
private:
    int id_;
    T dato_;

public:
    //Constructor
    Dato(int id, T dato){
        id_=id;
        dato_=dato;
    }

    //Observador y modificador de id
    inline void getId(int& id) const {
        id = id_;
    }

    inline void setId(int id) {
        id_ = id;
    }

    //Observador y modificador de dato
    inline void getDato(T& dato) const {
        dato = dato_;
    }

    inline void setDato(T& dato) {
        dato_ = dato;
    }

    //Comparación ==
    bool operator==(Dato& d){
        return dato_ == d.dato_;
    }

    //Comparación !=
    bool operator!=(Dato& d){
        return !(*this == d);
    }
};

#endif