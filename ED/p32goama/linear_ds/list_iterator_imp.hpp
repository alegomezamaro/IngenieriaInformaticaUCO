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
#include <list_iterator.hpp>

template <class T>
ListIterator<T>::~ListIterator() {}

template <class T>
bool ListIterator<T>::is_valid() const
{
    bool ret_v = false;
    // TODO: recode with respect to your representation.
    // Hint: Do not invoke node() here because that provoques an infinite recursion.

    ret_v = (node_ != nullptr); //Si el nodo actual no es nulo verdadero
    return ret_v;

    //
}

template <class T>
ListIterator<T>::ListIterator()
{
    // TODO

    node_ = nullptr; //Inicializamos el nodo a nullptr

    //
    assert(!is_valid());
};

template <class T>
ListIterator<T>::ListIterator(typename DNode<T>::Ref const &n)
{
    // TODO

    node_ = n; //Asignamos el nodo

    //
    assert(n == nullptr || is_valid());
    assert(n != nullptr || !is_valid());
};

template <class T>
T const &ListIterator<T>::item() const
{
    assert(is_valid());
    // TODO: recode with respect to your representation.
    
    return (node_->item()); //Devolvemos el item del nodo actual

    //
}

template <class T>
ListIterator<T> ListIterator<T>::next(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO

    ret_v = *this; //Apuntamos al nodo actual
    ret_v.goto_next(dist); //Avanzamos dist nodos

    //
    return ret_v;
}

template <class T>
ListIterator<T> ListIterator<T>::prev(size_t dist) const
{
    assert(is_valid());
    ListIterator<T> ret_v;
    // TODO

    ret_v = *this; //Apuntamos al nodo actual
    ret_v.goto_prev(dist); //Retrocedemos dist nodos

    //
    return ret_v;
}

template <class T>
size_t ListIterator<T>::distance(ListIterator<T> const &other) const
{
    assert(is_valid());
    assert(other.is_valid());
    size_t ret_v = 0;
    // TODO

    auto it = *this; //Iterador actual

    while (it != other){ //Mientras no lleguemos al final
        ret_v++; //Aumentamos la distancia
        it.goto_next(1); //Pasamos al siguiente nodo
    }

    //
    return ret_v;
}

template <class T>
bool ListIterator<T>::operator==(ListIterator<T> const &o) const
{
    // TODO: recode with respect to your representation.
    // Remember: two iterators are equal if both point to the same node.

    return (node_ == o.node_); //Si los nodos son iguales verdadero

    //
}

template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> const &o) const
{
    bool ret_v = false;

    // TODO: recode with respect to your representation.
    // Remember: two iterators are equal if both point to the same node.
    
    ret_v = (node_ != o.node_); //Si los nodos son distintos true
    return ret_v;

    //
}

template <class T>
void ListIterator<T>::set_item(T const &it)
{
    assert(is_valid());
    // TODO

    node_->set_item(it); //Cambiamos el item del nodo actual

    //
}

template <class T>
void ListIterator<T>::goto_next(size_t dist)
{
    assert(is_valid());
    // TODO

    while (dist > 0 && node_->next() != nullptr) { //Mientras no lleguemos al final y no hayamos llegado a la distancia
        node_ = node_->next(); //Pasamos al siguiente nodo
        dist--; //Disminuimos la distancia
    }

    //
}

template <class T>
void ListIterator<T>::goto_prev(size_t dist)
{
    assert(is_valid());
    // TODO

    while (dist > 0 && node_->prev() != nullptr) { //Mientras no lleguemos al inicio y no hayamos llegado a la distancia
        node_ = node_->prev(); //Retrocedemos un nodo
        dist--; //Disminuimos la distancia
    }

    //
}

template <class T>
typename DNode<T>::Ref ListIterator<T>::node() const
{
    typename DNode<T>::Ref ret_v;
    // TODO: recode with respect to your representation.

    ret_v = node_; //Igualamos ret_v al nodo actual
    return ret_v;

    //
}

template <class T>
void ListIterator<T>::set_node(typename DNode<T>::Ref const &n)
{
    // TODO

    node_ = n; //Asignamos el nuevo nodo

    //
    assert(node() == n);
}