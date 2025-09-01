// 4. Programa la clase Equipo la cual debe disponer de un vector de objetos Jugador, en los ficheros
//    equipo.h y equipo.cc con los siguientes métodos:
//  - Constructo vacío.
//  - Constructor de copia.
//  - Método size(), que retorna el tamaño del vector de jugadores de la clase.
//  - Método addJugador(): el cual insertar un jugador en el vector de jugadores siempre y cuando no se
//    encuentre insertado el DNI de dicho jugador ya.
//  - Operador []: el cual recibe una posición del vector y retorna el jugador que se encuentre en dicha
//    posición.
//  - Método ordenar(): que ordena alfabéticamente el vector de jugadores según su nombre

#ifndef EQUIPO_H
#define EQUIPO_H

#include "jugador.h"
#include <vector>
#include <algorithm>

class Equipo{
private:
    std::vector<Jugador> plantilla_;

public:
    //Constructor vacío
    Equipo() = default;

    //Constructor de copia
    Equipo(const Equipo&) = default;

    //Tam
    inline int size() const {
        return plantilla_.size();
    }

    //Añade jugador a la lista
    inline bool addJugador(const Jugador& j) {
        for (const auto& jugador : plantilla_) {
            if (jugador.getDNI() == j.getDNI()) {
                return false;
            }
        }
        plantilla_.push_back(j);
        return true;
    }

    //Operador[]
    Jugador& operator[](int n) {
        return plantilla_.at(n); //at(pos) evita errores
    }

    //Ordena albafeticamente
    static bool alfab(const Jugador& a, const Jugador& b) {
        return a.getNombre() < b.getNombre();
    }

    //Ordena
    inline void ordenar() {
        std::sort(plantilla_.begin(), plantilla_.end(), alfab);
    }
};

#endif