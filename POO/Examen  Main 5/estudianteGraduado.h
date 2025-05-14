// 2. Implementar la clase EstudianteGraduado que deriva de la clase Estudiante. Esta clase dispondrá
//    además de un campo de tipo cadena que representa la especialidad y un campo de tipo entero que
//    representa el año de finalización o graduación.
//    Debe implementar un constructor vacío, el cuál establecerá la especialidad por defecto a
//    “Sin indicar” y el año 2011.
//    Constructor parametrizado que recibirá como parámetros obligatorios el
//    dni del estudiante, la especialidad y el año de graduación. El resto de los valores se tomarán por
//    defecto los indicados anteriormente.
//    Observador getEspecialidad() y getAnioGraduacion(), ambos por referencia.
//    Modificadores setEspecialidad() y setAnioGraduacion(). Ambos serán de tipo booleano y controlará
//    que el año sea superior al 2011 y que la especialidad sea “Mención en Computación”, “Mención en
//    Computadores” o “Mención en Software”. En caso de recibir un valor permitido, este se asignará a
//    la variable privada y se retornará true, en caso contrario, no se asignará y se retornará false.
//    Nota: en el constructor parametrizado, si no se recibe como valores de especialidad o año de
//    graduación los permitidos e indicados en los modificadores, estos tomarán por defecto los valores
//    indicados en el constructor vacío.

#ifndef ESTUDIANTEGRADUADO_H
#define ESTUDIANTEGRADUADO_H

#include "estudiante.h"

class EstudianteGraduado : public Estudiante{
    private:
    std::string especialidad_;
    int anioGraduacion_;

    public:
    //Constructor vacio
    EstudianteGraduado(){
        especialidad_="Sin indicar";
        anioGraduacion_=2011;
    }

    //Constructor parametrizado
    EstudianteGraduado(std::string dni, std::string especialidad="Sin indicar", int anioGraduacion=2011, std::string nombre="Sin nombre", int edad=0) : Estudiante(dni, nombre, edad){
        especialidad_=especialidad;
        anioGraduacion_=anioGraduacion;
    }

    //Observador y modificador especialidad
    inline std::string getEspecialidad(){
        return especialidad_;
    }

    inline bool setEspecialidad(std::string especialidad){
        if(especialidad=="Mención en Computación" || especialidad=="Mención en Computadores"
            || especialidad=="Mención en Software"){
            especialidad_ = especialidad;
            return true;
        }
        else{
            return false;
        }
    }

    //Observador y modificador anioGraduacion
    inline int getAnioGraduacion(){
        return anioGraduacion_;
    }

    inline bool setAnioGraduacion(int anioGraduacion){
        if(anioGraduacion < 2011){
            return false;
        }
        else{
            anioGraduacion_=anioGraduacion;
            return true;
        }
    }
};

#endif