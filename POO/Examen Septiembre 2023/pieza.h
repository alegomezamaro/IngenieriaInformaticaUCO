// 1. Implementar la clase Pieza en los ficheros pieza.cc y pieza.h. Una pieza tiene una cadena
//    nombre, un entero código, entero cantidad y double precio.
//  - Constructor vacío con los valores por defecto nombre("Sin Nombre") y el resto a cero.
//  - Constructor parametrizado cuyos únicos parámetros obligatorios son el codigo y el nombre
//    (en ese orden) el resto son opcionales tomando como valores por defecto cero.
//  - Constructor de copia.
//  - Observadores y modificadores.
//    NOTA: el observador de la variable nombre se debe implementar por referencia.
//  - Método getPieza. Dicho método retorna una cadena, por ejemplo:
//    "Hay X unidades de la pieza Y." Siendo X la cantidad e Y el nombre de la pieza.

#ifndef PIEZA_H
#define PIEZA_H

#include <iostream>
#include <string>

//Clase pieza
class Pieza{
    private:
    std::string nombre_;
    int codigo_;
    int cantidad_;
    double precio_;

    public:
    //Constructor vacio
    Pieza(){
        nombre_= "Sin Nombre";
        codigo_=0;
        cantidad_=0;
        precio_=0.0;
    }

    //Constructor con codigo y nombre
    Pieza(std::string nombre, int codigo){
        nombre_=nombre;
        codigo_=codigo;
        int cantidad_=0;
        double precio_=0.0;
    }

    //Constructor copia
    Pieza(const Pieza&) = default;

    //Observador y modificador nombre
    inline std::string GetNombre(){
        return nombre_;
    }

    inline void SetNombre(std::string nombre){
        nombre_=nombre;
    }

    //Observador y modificador codigo
    inline int GetCodigo(){
        return codigo_;
    }

    inline void SetCodigo(int codigo){
        codigo_=codigo;
    }

    //Observador y modificador cantidad
    inline int GetCantidad(){
        return cantidad_;
    }

    inline void SetCantidad(int cantidad){
        cantidad_=cantidad;
    }

    //Observador y modificador precio
    inline int GetPrecio(){
        return precio_;
    }

    inline void SetPrecio(double precio){
        precio_=precio;
    }

    //String con "Hay CANTIDAD unidades de la pieza NOMBRE."
    inline std::string GetPieza(){
        std::string pieza = ("Hay ") + std::to_string(this->cantidad_) + (" unidades de la pieza ")
            + nombre_; 
        return pieza;
    }
};

#endif