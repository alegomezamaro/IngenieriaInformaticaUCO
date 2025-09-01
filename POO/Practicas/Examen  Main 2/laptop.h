// 4. La clase Laptop deriva de la clase Computer del ejercicio anterior y además gestiona una variable de tipo int denominada “pulgadas”. Escribe el código de la clase Laptop
//    en los ficheros laptop,h y laptop,cc con la siguiente funcionalidad:
//  - Constructor que recibe como parámetro obligatorio el valor para “pulgadas”, el segundo parámetro obligatorio será el modelo del Laptop, y el tercer parámetro obligatorio
//    será el precio del Laptop. Si las pulgadas recibidas es menor o igual a cero se asignará el valor 1. El constructor además asignará al campo “nombre” de la clase Computer
//    el valor “Laptop” y el campo "modelo" y "precio" de la clase Computer a los valorres recibidos como parámetro.
//  - Observador getPulgadas().
//  - Modificador setPulgadas() que no permita valores menores o iguales que cero. Si el parámetro es menor o igual a O debe devolver false y no asignarlo. Si por el contrario es
//    positivo debe asignarlo y devolver true.
//  - Observador getInfo() que devuelve una cadena formada por la concatenación de la información del Laptop. Por ejemplo si el Laptop es de 18 pulgadas modelo PV3 y el precio son
//    300, esta función debe devolver la cadena: “Laptop de 18 pulgadas modelo PV3 precio 300” (NOTA: usa la función std::to_string() para pasar convertir las pulgadas a string).

#ifndef LAPTOP_H
#define LAPTOP_H

#include "computer.h"

class Laptop : public Computer{
    private:
    int pulgadas_;

    public:
    Laptop(int pulgadas, std::string modelo, int precio, std::string nombre="Laptop") : Computer(nombre, modelo, precio){
        if(pulgadas>0){
            pulgadas_=pulgadas;
        }
        else{
            pulgadas_=1;
        }
    }

    //Observador y mopdificador pulgadas
    inline int getPulgadas(){
        return pulgadas_;
    }

    inline bool setPulgadas(int pulgadas){
        if(pulgadas<=0){
            return false;
        }
        else{
            pulgadas_=pulgadas;
            return true;
        }
    }

    //Devuelve “Laptop de PULGADAS pulgadas modelo MODELO precio PRECIO"
    inline std::string getInfo(){
        return std::string("Laptop de ") + std::to_string(getPulgadas()) + " pulgadas modelo " + getModelo() + " precio " + std::to_string(getPrecio());
    }

};

#endif