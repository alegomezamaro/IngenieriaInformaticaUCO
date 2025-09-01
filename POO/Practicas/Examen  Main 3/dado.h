//  3. La clase Dado gestiona el lanzamiento de 1 Dado. Codifica la clase Dado en C++ con los siguientes métodos:
//  - Constructor: recibe 1 parámetro opcional con el valor inicial para el dado. Si no se recibe parámetro el valor inicial se asignará 1. Control de errores: Si el valor
//    inicial no es correcto, el valor asignado será 1.
//  - Observadores: get(). Devuelve el valor del dado (función inline).
//  - Modificadores: set(). Recibe un parámetro con el valor entero a asignar al dato.
//    Control de errores: Si se produce algún error en el valor asignado (debe estar entre 1 y 6), set() devuelve false y no modificado el dado, en caso contrario, set() modifica
//    el dado y devuelve true.
//  - Sobrecarga de los operadores: Sobrecarga del operador + para que se sume el valor de dos dados y devuelve un entero con el resultado.

#ifndef DADO_H
#define DADO_H

#include <iostream>

class Dado{
    private:
    int valor_;

    public:
    //Constructor
    Dado(int valor=1){
        if(valor > 1 && valor <= 6){
            valor_=valor;
        }
        else{
            valor_=1;
        }
    }

    //Observador y modificador valor
    inline int get(){
        return valor_;
    }

    inline bool set(int valor){
        if(valor >= 1 && valor <= 6){
            valor_=valor;
            std::cout << "\nFalso\n";
            return true;
        }
        return false;
    }

    //Operador+
    friend int operator+(Dado &d1, Dado &d2){
        int suma = d1.get() + d2.get();
        return suma;
    }
};

#endif