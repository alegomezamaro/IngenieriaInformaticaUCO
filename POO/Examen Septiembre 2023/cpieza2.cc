#include "cpieza2.h"

bool Cpieza2::addPieza(Pieza p){
    std::string nombre = p.GetNombre();
    for(auto it = piezalist_.begin(); it != piezalist_.end(); ++it){
        if(it->GetNombre() == nombre){
            return false;
        }
    }
    piezalist_.push_back(p);
    return true;
}

bool Cpieza2::deletePieza(Pieza p){
    std::string nombre = p.GetNombre();
    for(auto it = piezalist_.begin(); it != piezalist_.end(); ++it){
        if(it->GetNombre() == nombre){
            piezalist_.erase(it);
            return true;
        }
    }
    return false;
}

Pieza Cpieza2::operator[](int n){
    if(n < this->size()){
        auto it = piezalist_.begin();
        std::advance(it, n);
        return *it;
    }
    exit(EXIT_FAILURE);
}