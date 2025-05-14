// 2. La clase Cart representa una cesta de la compra de una tienda online y tiene un campo de tipo entero “id” y una lista de objetos de la clase Computer del ejercicio anterior
//    (para la lista usar el tipo list de la STL de C++). Codifica los ficheros cart.h y cart.cc para la clase Cart con la siguiente funcionalidad:
// a) Constructor que recibe como parámetro obligatorio el id de la compra.
// b) Observador getld().
// c) El método addComputer() de tipo void que recibe un objeto de tipo Computer y lo añade a la lista.
// d) El método getN() que devuelve un entero con el tamaño de la lista.
// e) El método print(), de tipo void, que muestra en pantalla un Computer por línea con la posición numérica, su nombre y su modelo:
//      1,nombre,modelo
//      2,nombre,modelo
//      3,nombre,modelo
//      ...
//    Durante la ejecución del test2 deberá mostrarse en pantalla (bajo el test Cart, print):
//      1,PC1,PV1
//      2,PC2,PV2
//      3,PC3,PV3
// f) El método write(), de tipo void, que escriba lo mismo pero en un fichero texto que se llamará "salida.txt". Despues de la ejecución del test2 el contenido del fichero
//    "salida.txt" será:
//      1,PC1,PVX
//      2,PC2,PVX
//      3,PC3,PVX
//    OJO: comprueba que este fichero se crea y no escribas ningún espacio en blanco en él“sal ida.txt”

#ifndef CART_H
#define CART_H

#include "computer.h"
#include <list>
#include <fstream>

class Cart : public Computer{
    private:
    int id_;
    std::list<Computer> objetos_;

    public:
    Cart(int id){
        id_=id;
    }

    //Observador id
    inline int getId(){
        return id_;
    }

    //Añadir ordenadores a la lista
    inline void addComputer(Computer c){
        objetos_.push_back(c);
    }

    //Tamaño de la lista
    inline int getN(){
        return objetos_.size();
    }

    //Muestra en pantalla un Computer por línea con la posición numérica, su nombre y su modelo (1,PC1,PV1)
    void print(){
        std::list<Computer>::iterator it=objetos_.begin();
        int i=1;
        while(it!=objetos_.end()){
            std::cout << i << "," << it->getNombre() << "," << it->getModelo() << "\n";
            ++it;
            i++;
        }
    }

    //Print escrito en un fichero de testo "salida.txt"
    void write(){
        std::ofstream f("salida.txt");
        if(f.is_open()){
            std::list<Computer>::iterator it=objetos_.begin();
            int i=1;
            while(it!=objetos_.end()){
                f << i << "," << it->getNombre() << "," << it->getModelo() << "\n";
                ++it;
                i++;
            }
            f.close();
        }
    }

};

#endif