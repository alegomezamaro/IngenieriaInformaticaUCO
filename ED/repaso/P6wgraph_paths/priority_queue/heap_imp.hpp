/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <exception>
#include <cassert>
#include <algorithm>
#include <heap.hpp>

/**
 * @brief Compute the parent's index of a given child.
 *
 * @param i is the index of the child in the heap.
 * @return size_t
 */
inline size_t parent(size_t i)
{
    assert(i > 0);
    //  TODO: fixme

    return (i - 1) / 2; //Devolvemos el padre
    //
}

/**
 * @brief Compute the left child's index of a given parent.
 *
 * @param i is the index of the parent in the heap.
 * @return the index of the left child.
 */
inline size_t left(size_t i)
{
    // TODO: fixme

    return (2 * i + 1); //Devolvemos el hijo izquierdo
    //
}

/**
 * @brief Compute the right child's index of a given parent.
 *
 * @param i is the index of the parent in the heap.
 * @return the index of the right child.
 */
inline size_t right(size_t i)
{
    // TODO: fixme

    return (2 * i + 2); //Devolvemos el hijo derecho
    //
}

template <class T>
void Heap<T>::shift_up(size_t i)
{
    // TODO

    if(i > 0 && comp_((*values_)[i], (*values_)[parent(i)])){ //Mientras el padre es mayor que el hijo

        std::swap((*values_)[i], (*values_)[parent(i)]); //Cambiamos el padre por el hijo
        shift_up(parent(i)); //Llamamos recursivamente a la función para seguir subiendo el hijo
    }
    //
}

template <class T>
void Heap<T>::shift_down(size_t i)
{
    // TODO

    size_t n = i; //Indice del padre
    size_t lC = left(i);  //Indice del hijo izquierdo
    size_t rC = right(i); //Indice del hijo derecho

    if (lC < last_item_ && comp_((*values_)[lC], (*values_)[n])){ //Si el hijo izquierdo es menor que el padre

        n = lC; //Actualizamos el índice del padre
    }

    if (rC < last_item_ && comp_((*values_)[rC], (*values_)[n])){ //Si el hijo derecho es menor que el padre

        n = rC; //Actualizamos el índice del padre
    }

    if (i != n){ //Si el padre no es el menor

        std::swap((*values_)[i], (*values_)[n]); //Cambiamos el padre por el hijo
        shift_down(n); //Llamamos recursivamente a la función para seguir bajando el padre
    }
    //
}

template <class T>
bool Heap<T>::is_a_heap(size_t root) const
{
    bool ret_val = true;
    // TODO
    // Remember: the tree is a heap if both children are heaps and the root is
    // comp(parent, child) if true for both children.
    // Remember: a leaf is a heap.

    size_t lC = left(root);  //Indice del hijo izquierdo
    size_t rC = right(root); //Indice del hijo derecho

    if (lC < last_item_){ //Si el indice del hijo izquierdo es menor que el último elemento del montículo
    
        if (!comp_((*values_)[root], (*values_)[lC]) || !is_a_heap(lC)){ // Si el elemento actual no es menor que el hijo izquierdo y el hijo izquierdo no es un heap
    
            ret_val=false; 
        }
    }

    else if(rC < last_item_){ //Si el índice del hijo derecho es menor que el último elemento del montículo
    
        if (!comp_((*values_)[root], (*values_)[rC]) || !is_a_heap(rC)){ //Si el elemento actual no es menor que el hijo derecho y el hijo derecho no es un heap
    
            ret_val=false;
        }
    }
    //
    return ret_val;
}

template <class T>
void Heap<T>::heapify()
{
    // TODO
    // Remember: we want O(N) here.

    if (size() > 0){ //Si el tamaño del array es mayor que 0

        for (size_t i = (size() / 2) - 1; i < size(); --i){ //Recorremos el array desde la mitad hasta el principio

            shift_down(i); //Llamamos a la función shift_down para bajar el padre
        }
    }
    //
    assert(is_a_heap());
}

template <class T>
Heap<T>::Heap(std::vector<T> &values, Comp const &comp) : values_(&values), comp_(comp)
{
    // TODO
    // Hint: use the heapify function

    last_item_ = values.size(); //Guardamos el tamaño del array
    heapify(); //Construimos el heap
    //
    assert(is_a_heap());
    assert(size() == values.size());
}

template <class T>
Heap<T>::~Heap()
{
}

template <class T>
bool Heap<T>::is_empty() const
{
    // TODO: fixme

    return (last_item_ == 0); //Si el tamaño del array es 0, el heap está vacío
    //
}

template <class T>
size_t Heap<T>::size() const
{
    // TODO: fixme

    return last_item_; //Devolvemos el tamaño del array
    //
}

template <class T>
T const &Heap<T>::item() const
{
    assert(!is_empty());
    // TODO: fixme

    return (*values_)[0]; //Devolvemos el primer elemento del array
    //
}

template <class T>
void Heap<T>::insert(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    // Remember: we are using a dynamic array, so we need to check if the array
    // is full to push_back the new value if it is needed.

    if (last_item_ == values_->size()){ //Si el tamaño del array es igual al tamaño del heap

        values_->push_back(new_it); //Añadimos el nuevo elemento al final del array
    }
    
    else{ //Sino

        (*values_)[last_item_] = new_it; //Añadimos el nuevo elemento al final del heap
    }

    last_item_++; //Aumentamos el tamaño del array
    shift_up(last_item_ - 1); //Llamamos a la función shift_up para subir el nuevo elemento

    //
    assert(is_a_heap());
    assert(size() == old_size + 1);
}

template <class T>
void Heap<T>::remove()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(!is_empty());
    // TODO

    last_item_--; //Disminuimos el tamaño del array

    if (last_item_ > 0){ //Si el tamaño del array es mayor que 0

        std::swap((*values_)[0], (*values_)[last_item_]); //Intercambiamos el primer elemento del array con el último
        shift_down(0); //Llamamos a la función shift_down para bajar el primer elemento
    }
    //
    assert(is_a_heap());
    assert(size() == old_size - 1);
}

template <class T>
void heapsort(std::vector<T> &values, std::function<bool(T const &a, T const &b)> const &comp)
{
    // TODO
    // Remember: we want O(N log N) here.

    Heap<T> heap(values, comp); //Creamos un heap con el array

    for (size_t i = values.size(); i > 0; i--){ //Recorremos el array desde el final hasta el principio

        heap.remove(); //Llamamos a la función remove para eliminar el primer elemento del heap
    }
    //
#ifndef NDEBUG
    for (size_t i = 1; i < values.size(); ++i)
        assert(comp(values[i], values[i - 1]));
#endif
}