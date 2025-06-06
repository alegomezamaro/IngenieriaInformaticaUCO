/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <sstream>
#include <cassert>
#include <cdarray.hpp>

template <class T>
size_t
CDArray<T>::capacity() const
{
    // TODO: recode with respect to your representation.

    return capacity_; //Devuelve la capacidad

    //
}

template <class T>
size_t
CDArray<T>::size() const
{
    // TODO: recode with respect to your representation.

    return size_; //Devuelve el tamaño

    //
}

template <class T>
bool CDArray<T>::is_empty() const
{
    // TODO: recode with respect to your representation.

    if(size_==0){ //Si el tamaño es 0 esta vacio
        return true;
    }

    return false; //Si no falso

    //
}

template <class T>
bool CDArray<T>::is_full() const
{
    bool ret_v = false;
    // TODO

    if(size() == capacity()){ //Si su tamaño es igual que su capacidad esta lleno
        ret_v=true;
    }

    //
    assert(!ret_v || size() == capacity());
    return ret_v;
}

template <class T>
CDArray<T>::CDArray(size_t cap)
{
    assert(cap > 0);
    // TODO

    data_=std::shared_ptr<T[]>(new T[cap], std::default_delete<T[]>());  //Se asigna a data_ un puntero compartido de tamaño cap
    capacity_=cap; //Se asigna a capacity_ el valor de cap
    size_=0; //Se inicializa el tamaño a 0
    front_=0; //Se inicializa el primer elemento a 0
    back_=0; //Se inicializa el ultimo elemento a 0

    //
    assert(capacity() == cap);
    assert(is_empty());
    assert(size() == 0);
}

template <class T>
CDArray<T>::~CDArray()
{
    // TODO
    // Remember: depending on your representation, it is possible that nothing
    // must be done.

    //data_ no necesita ser liberado ya que se usa shared_ptr
    capacity_=0; //Asignamos 0 a la capacidad
    size_=0; //Asignamos 0 al tamaño
    front_=0; //Asignamos 0 al primer elemento
    back_=0; //Asignamos 0 al ultimo elemento

    //
}

template <class T>
CDArray<T>::CDArray(std::istream &in) noexcept(false) : CDArray(1)
{
    std::string token;
    in >> token;

    // TODO
    // Hint: use std::istringstream to convert from "string" to template
    //  parameter T type.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.

    if (token != "[") { //Si el inicio del formato es incorrecto
        throw std::runtime_error("Wrong input format.");
    }

    T value;

    while (in >> token && token != "]") { //Mientra haya tokens distintos al final del formato
        std::istringstream string(token); //Convierte token a string

        if (!(string >> value)) { //Si no se puede convertir a string
            throw std::runtime_error("Wrong input format.");
        }

        push_back(value); //Inserta el valor al final del array
    }

    if (token != "]") { //Si el final del formato es incorrecto
        throw std::runtime_error("Wrong input format.");
    }

    //
}

template <class T>
std::ostream &
CDArray<T>::fold(std::ostream &out) const
{
    // TODO

    //Dado: 1, 2, 3 obtenemos out = [ 1 2 3 ]
    
    out << "["; //Introduce el valor inicial del formato

    for (size_t i = 0; i < size_; ++i) { //For del tamaño del array
        out << " " << get(i); //Añade el elemento a la salida
    }

    out << " ]"; //Introduce el valor final del formato

    //
    return out;
}

template <class T>
T const &CDArray<T>::get(size_t pos) const
{
    // TODO: recode with respect to your representation.

    assert(pos >= 0 && pos < size_); //Comprueba que la posicion esta en el rango del array
    return data_[(front_ + pos) % capacity_]; //Se calcula la posicion del elemento y se devuelve

    //
}

template <class T>
void CDArray<T>::set(size_t pos, T const &new_v)
{
    // TODO

    assert(pos >= 0 && pos < size_); //Comprueba que la posicion esta en el rango del array
    data_[(front_ + pos) % capacity_] = new_v; //Se calcula la posicion del elemento y se asigna el nuevo valor

    //
    assert(new_v == get(pos));
}

size_t cInc(size_t v, size_t size)
{
    size_t ret_v;
    // TODO

    ret_v = (v + 1) % size; //Se calcula el siguiente elemento

    //
    return ret_v;
}

size_t cDec(size_t v, size_t size)
{
#ifndef NDEBUG
    size_t old_v = v;
#endif
    size_t ret_v;
    // TODO
    // Remember: v is a unsigned value, so you must cast to signed before decrementing

    ret_v = (v - 1) % size; //Se calcula el elemento anterior

    //
    assert(old_v == cInc(ret_v, size));
    return ret_v;
}

template <class T>
void CDArray<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_front = is_empty() ? T() : get(0);
#endif
    // REPASO

    

    //
    assert(size() == old_size + 1);
    assert(get(0) == new_it);
    assert(old_is_empty || (get(1) == old_front));
}

template <class T>
void CDArray<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
    bool old_is_empty = is_empty();
    T old_back = is_empty() ? T() : get(size() - 1);
#endif
    // TODO

    if (is_full()) { //Si esta lleno crece 1
        grow();
    }

    if (is_empty()) { //Si esta vacio se añade el elemento en la primera posicion
        data_[0] = new_it;
        front_ = 0;
        back_ = 0;
    }
    
    else { //Se añade el elemento en la ultima posicion
        back_ = (back_ + 1) % capacity_; //Se calcula la nueva posicion del ultimo elemento
        data_[back_] = new_it;
    }

    size_++; //Se incrementa el tamaño

    //
    assert(size() == old_size + 1);
    assert(get(size() - 1) == new_it);
    assert(old_is_empty || (get(size() - 2) == old_back));
}

template <class T>
void CDArray<T>::pop_front()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_front = size() > 1 ? get(1) : T();
#endif
    // TODO

    front_ = cInc(front_, capacity_); //Se calcula la nueva posicion del primer elemento
    size_--; //Se decrementa el tamaño

    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(0) == old_next_front);
}

template <class T>
void CDArray<T>::pop_back()
{
#ifndef NDEBUG
    size_t old_size = size();
    T old_prev_back = size() > 1 ? get(size() - 2) : T();
#endif
    // TODO

    back_ = cInc(back_, capacity_); //Se calcula la nueva posicion del ultimo elemento
    size_--; //Se decrementa el tamaño

    //
    assert(size() == old_size - 1);
    assert(is_empty() || get(size() - 1) == old_prev_back);
}

template <class T>
void CDArray<T>::insert(size_t pos, T const &v)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_back = get(size() - 1);
    T old_pos_v = get(pos);
#endif
    // TODO
    // Hint: if pos==0, delegate in push_front.
    // Remember: back_ needs to be updated too.

    if (is_full()) { //Si esta lleno crece 1
        grow();
    }

    for (size_t i = size_; i > pos; i--) { //Se desplazan los elementos de detras de pos
        data_[(front_ + i) % capacity_] = data_[(front_ + i - 1) % capacity_];
    }

   
    data_[(front_ + pos) % capacity_] = v;  // Insertar el nuevo elemento en la posición especificada.
    size_++; // Incrementar el tamaño del array.

    //
    assert(size() == old_size + 1);
    assert(get(pos) == v);
    assert(get(pos + 1) == old_pos_v);
    assert(get(size() - 1) == old_back);
}

template <class T>
void CDArray<T>::remove(size_t pos)
{
    assert(pos >= 0 && pos < size());
#ifndef NDEBUG
    size_t old_size = size();
    T old_next_pos_v = (pos <= (size() - 2)) ? get(pos + 1) : T();
#endif
    // TODO
    // Remember: back_ needs to be updated.

    for (size_t i = pos; i < size_ - 1; ++i) { //Se desplazan los elementos de detras de pos
        data_[(front_ + i) % capacity_] = data_[(front_ + i + 1) % capacity_];
    }

    size_--; //Se decrementa el tamaño

    //
    assert(size() == old_size - 1);
    assert(pos == size() || get(pos) == old_next_pos_v);
}

template <class T>
void CDArray<T>::grow()
{
#ifndef NDEBUG
    size_t old_capacity = capacity();
    T old_front = get(0);
    T old_back = get(size() - 1);
#endif
    // REPASO

    

    //
    assert(capacity() == 2 * old_capacity);
    assert(get(0) == old_front);
    assert(get(size() - 1) == old_back);
}