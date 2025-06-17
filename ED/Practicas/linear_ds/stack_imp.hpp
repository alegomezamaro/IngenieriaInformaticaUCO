/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <cassert>
#include <stack.hpp>

template <class T>
Stack<T>::Stack()
{
    // TODO

    l_ = List<T>(); //Crea una lista vacía

    //
    assert(is_empty());
}

template <class T>
bool Stack<T>::is_empty() const
{
    // TODO: reocde with respect to your representation.
    
    return l_.is_empty(); //Devuelve si la lista esta vacía

    //
}

template <class T>
size_t Stack<T>::size() const
{
    // TODO: recode with respect to your representation.
    
    return l_.size(); //Devuelve el tamaño de la lista

    //
}

template <class T>
T const &Stack<T>::top() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
   
    return l_.front(); //Devuelve el último elemento de la lista

    //
}

template <class T>
void Stack<T>::push(const T &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO

    l_.push_front(new_it); //Inserta el nuevo elemento al principio de la lista

    //
    assert(top() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void Stack<T>::pop()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(!is_empty());
    // TODO

    l_.pop_front(); //Elimina el primer elemento de la lista

    //
    assert(size() == (old_size - 1));
}
