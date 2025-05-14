// 1. Implementar la clase Estudiante la cual está compuesta por un campo de tipo cadena
//    que representa el nombre, un campo de tipo entero que representa la edad y un campo
//    de tipo cadena que representa su dni.
//    Se debe codificar el constructor vacío, donde el nombre tomará el valor por defecto
//    “Sin nombre”, la edad cero y el dni “Sin dni”.
//  - Constructor parametrizado cuyo único parámetro obligatorio será el dni, siendo el resto opcional
//    y tomando como valores por defecto los indicados anteriormente. Se debe controlar que, si alguna
//    cadena recibida está vacía, se asignará el valor por defecto y no cadena vacía, mientras que, si
//    la edad recibida es menor que cero se asignará cero, es decir, el valor por defecto.
//    Implementar además los observadores y modificadores:
//  - getNombre(), getEdad() y getDNI()
//  - setNombre(), setEdad() y setDNI()
//    Nota: los modificadores deben ser booleanos y retornar true o false dependiendo de si han
//    modificado la variable privada o no. Si las cadenas son vacías o si la variable entera es
//    menor que cero, la variable privada no se modificará y se retornará false. En caso contrario,
//    se modificará y se devolverá true.
//    Por último, implementar un método getInfo() que retorne una cadena de caracteres con el siguiente
//    formato:
//    “El alumno con nombre XXX tiene YYY años y su DNI es ZZZ.”
//    Donde XXX corresponde al nombre, YYY a la edad y ZZZ a su dni.

#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <iostream>
#include <string>

class Estudiante{
    private:
    std::string dni_;
    std::string nombre_;
    int edad_;
    
    public:
    //Constructor vacio
    Estudiante(){
        dni_="Sin dni";
        nombre_="Sin nombre";
        edad_=0;
    }

    //Constructor parametrizado
    Estudiante(std::string dni, std::string nombre="Sin nombre", int edad=0){
        if(dni.empty()){
            dni_="Sin dni";
        }
        else{
            dni_=dni;
        }
        nombre_=nombre;
        if(edad < 0){
            edad_ = 0;
        }
        else{
            edad_=edad;
        }
    }

    //Observador y modificador dni
    inline std::string getDNI(){
        return dni_;
    }

    inline bool setDNI(std::string dni){
        if(dni.empty()){
            return false;
        }
        else{
            dni_=dni;
            return true;
        }
    }

    //Observador y modificador nombre
    inline std::string getNombre(){
        return nombre_;
    }

    inline bool setNombre(std::string nombre){
        if(nombre.empty()){
            return false;
        }
        else{
            nombre_=nombre;
            return true;
        }
    }

    //Observador y modificador codigo
    inline int getEdad(){
        return edad_;
    }

    inline bool setEdad(int edad){
        if(edad < 0){
            return false;
        }
        else{
            edad_=edad;
            return true;
        }
    }

    //El alumno con nombre NOMBRE tiene AÑOS años y su DNI es DNI.
    inline std::string getInfo(){
        std::string info = ("El alumno con nombre ") + getNombre() + (" tiene ") + std::to_string(getEdad())
            + (" años y su DNI es ") + getDNI();
        return info;
    }
};

#endif