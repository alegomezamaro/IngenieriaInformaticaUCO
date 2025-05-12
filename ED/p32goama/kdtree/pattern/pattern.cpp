/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#include <cassert>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <pattern.hpp>

Pattern::Pattern()
{
    // TODO

    _values = std::make_shared<std::valarray<float>>(0); //Values inicializado a 0
    _class_label = -1; //Etiqueta inicial

    //
    assert(dim() == 0);
    assert(class_label() == -1);
}

Pattern::Pattern(float *values, const size_t size, const int cl)
{
    assert(size > 0);
    // TODO

    _values = std::make_shared<std::valarray<float>>(values, size); //Values inicializado con values y size
    _class_label = cl; //Etiqueta inicial

    //
    assert(dim() == size);
    assert(class_label() == cl);
}

Pattern::~Pattern()
{
    // TODO

    //Values es un make_shared, por lo que no es necesario liberar memoria
    _class_label = -1; //Etiqueta a -1

    //
}

size_t Pattern::dim() const
{
    size_t d = 0;
    // TODO

    d =  _values->size(); //Igualamos d a values.size()

    //
    return d;
}

int Pattern::class_label() const
{
    int cl = -1;
    // TODO

    cl = _class_label; //Igualamos cl a _class_label

    //
    return cl;
}

const std::valarray<float> &
Pattern::values() const
{
    // TODO

    return *_values; //Devolvemos _values

    //
}

void Pattern::set_class_label(const int new_label)
{
    // TODO

    _class_label = new_label; //Igualamos _class_label a new

    //
    assert(class_label() == new_label);
}

std::valarray<float> &
Pattern::values()
{
    // TODO
    
    return *_values; //Devolvemos _values

    //
}

void Pattern::reset(float *values, const size_t size, const int cl)
{
    assert(size >= 0);
    // TODO

    _values = std::make_shared<std::valarray<float>>(values, size); //Values inicializado con values y size
    _class_label = cl; //Etiqueta cl

    //
    assert(dim() == size);
    assert(class_label() == cl);
}
 
std::ostream &operator<<(std::ostream &output, const Pattern &p)
{
    // TODO
    // Remember: format "[ class_label [ v0 v1 ... vn-1 ] ]"

    output << "[ " << p.class_label() << " [ "; //Escribimos la etiqueta y el primer corchete

    for (size_t i = 0; i < p.dim(); ++i){  //Recorremos los valores de p
        output << p.values()[i] << " "; //Escribimos el valor
    }

    output << "] ]"; //Escribimos el final de formato

    //
    return output;
}

std::istream &operator>>(std::istream &in, Pattern &p) noexcept(false)
{
    // TODO
    // Remember: input format is "[ class_label [ v_0 v_1 ... v_size-1 ] ]"

    std::string ch; //Variable para leer los corchetes
    in >> ch; //Leemos el primer corchete

    if (ch != "["){ //Si no es un corchete, error

        throw std::runtime_error("wrong input format");
    }
    int cl; //Variable para la etiqueta
    in >> cl; //Leemos la etiqueta
    p.set_class_label(cl); //Asignamos la etiqueta a p
    in >> ch; //Leemos el siguiente corchete
    
    if (ch != "["){ //Si no es un corchete, error

        throw std::runtime_error("wrong input format");
    }
    std::vector<float> values; //Vector para los valores
    float value; //Variable para los valores

    while (in >> ch && ch != "]"){ //Mientras no sea un corchete

        std::istringstream iss(ch); //Creamos un stream para c

        if (iss >> value){ //Si se puede leer un valor

            values.push_back(value); //Lo añadimos al vector
        
        }
        else{ //Si no se puede leer un valor, error

            throw std::runtime_error("wrong input format");
        }
    }

    if (ch != "]"){ //Si no es un corchete, error

        throw std::runtime_error("wrong input format");
    }

    if (!(in >> ch) || ch != "]"){ //Si no es un corchete, error

        throw std::runtime_error("wrong input format");
    }

    float *v = new float[values.size()]; //Creamos un array de floats

    for (size_t i = 0; i < values.size(); i++){ //Recorremos los valores
        
        v[i] = values[i]; //Asignamos los valores al array
    }
    p.reset(v, values.size(),cl); //Reseteamos p con los valores
    
    //
    return in;
}

float distance_L2(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    // TODO

    for (size_t i = 0; i < a.dim(); ++i){ //Recorremos los valores de a y b
        float diff = a.values()[i] - b.values()[i]; //Calculamos la diferencia
        dist += diff * diff; //Sumamos la diferencia al cuadrado
    }

    dist = std::sqrt(dist); //Calculamos la raiz cuadrada

    //
    assert(dist >= 0.0);
    return dist;
}

float distance_L1(const Pattern &a, const Pattern &b)
{
    assert(a.dim() == b.dim());
    float dist = 0.0;
    // TODO

    for (size_t i = 0; i < a.dim(); ++i){ //Recorremos los valores de a y b
        dist += std::abs(a.values()[i] - b.values()[i]); //Sumamos el valor absoluto de la diferencia
    }

    //
    assert(dist >= 0.0);
    return dist;
}

std::istream &
load_dataset(std::istream &input,
             std::vector<Pattern> &dts) noexcept(false)
{
    // TODO
    // Remember: input format is
    // "<size_t num_patterns> <size_t pattern_dimensions>
    // <p_0>
    // <p_1>
    // ...
    // <p_num_patterns-1>
    // "

    size_t num_patterns, pattern_dimensions;
    input >> num_patterns >> pattern_dimensions;

    dts.clear();
    dts.reserve(num_patterns);

    for (size_t i = 0; i < num_patterns; ++i) {
        Pattern p;
        input >> p;
        if (p.dim() != pattern_dimensions) {
            throw std::runtime_error("wrong format");
        }
        dts.push_back(p);
    }

    return input;

    //
    return input;
}
