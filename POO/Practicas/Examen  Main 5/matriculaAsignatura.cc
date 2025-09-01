#include "matriculaAsignatura.h"

bool MatriculaAsignatura::addAlumno(std::string estudiante){
    for(auto it = listaAlumnos_.begin(); it != listaAlumnos_.end(); ++it){
        if(it->getNombre() == estudiante || getN() == getMaxAlumnos()){
            return false;
        }
    }
    Estudiante a("Sin dni", estudiante);
    listaAlumnos_.push_back(a);
    return true;
}
