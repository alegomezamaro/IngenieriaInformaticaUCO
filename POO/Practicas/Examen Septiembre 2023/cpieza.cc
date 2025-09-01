#include "cpieza.h"

bool Cpieza::addPieza(Pieza p){
    std::string nombre = p.GetNombre();
    for(auto it = piezalist_.begin(); it != piezalist_.end(); ++it){
        if(it->GetNombre() == nombre){
            return false;
        }
    }
    piezalist_.push_back(p);
    return true;
}

bool Cpieza::deletePieza(Pieza p){
    std::string nombre = p.GetNombre();
    for(auto it = piezalist_.begin(); it != piezalist_.end(); ++it){
        if(it->GetNombre() == nombre){
            piezalist_.erase(it);
            return true;
        }
    }
    return false;
}