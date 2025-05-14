// 3. Implemente, en los ficheros matriculaAsignatura.cc y matriculaAsignatura.h, la clase MatriculaAsignatura.
//    Esta clase define todos los alumnos que han sido matriculados en una determinada asignatura. La
//    clase está definida por una cadena que representa el nombre de la asignatura, un número máximo de
//    alumnos que se pueden matricular en ella y una lista de la STL formada por los estudiantes
//    matriculados en dicha clase.
//    Codificar el constructor parametrizado, el cuál reciba como únicos parámetros obligatorios el nombre
//    de la asignatura y el número máximo de alumnos que se pueden matricular en dicha asignatura.
//    Observador getAsignatura() que retorna el nombre de la asignatura y getMaxAlumnos() que retorna el
//    número máximo de alumnos.
//    Método addAlumno(), que recibe un alumno y lo añade a la lista siempre y cuando este no se encuentre
//    ya en ella. Si se añade el método retornará true, en caso contrario false.
//    Método getN(), que retorna el número de alumnos matriculados en la asignatura.

#ifndef MATRICULAASIGNATURA_H
#define MATRICULAASIGNATURA_H

#include "estudiante.h"
#include <list>

class MatriculaAsignatura{
    private: 
    std::string asignatura_;
    int maxAlumnos_;
    std::list<Estudiante> listaAlumnos_;

    public:
    //Constructor parametrizado
    MatriculaAsignatura(std::string asignatura, int maxAlumnos, std::list<Estudiante> listaAlumnos={}){
        asignatura_=asignatura;
        maxAlumnos_=maxAlumnos;
        listaAlumnos_=listaAlumnos;
    }

        //Observador asignatura
    inline std::string getAsignatura(){
        return asignatura_;
    }

    //Observador maxAlumnos
    inline int getMaxAlumnos(){
        return maxAlumnos_;
    }

    //Añadir alumno
    bool addAlumno(std::string estudiante);

    //Tamaño de la lista
    inline int getN(){
        int n=listaAlumnos_.size();
        return n;
    }
};

#endif