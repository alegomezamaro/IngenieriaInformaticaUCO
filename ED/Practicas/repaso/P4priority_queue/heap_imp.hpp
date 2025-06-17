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
    return 0;
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
    return 0;
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
    return 0;
    //
}

template <class T>
void Heap<T>::shift_up(size_t i)
{
    // TODO

    //
}

template <class T>
void Heap<T>::shift_down(size_t i)
{
    // TODO

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

    //
    return ret_val;
}

template <class T>
void Heap<T>::heapify()
{
    // TODO
    // Remember: we want O(N) here.

    //
    assert(is_a_heap());
}

template <class T>
Heap<T>::Heap(std::vector<T> &values, Comp const &comp) : values_(&values), comp_(comp)
{
    // TODO
    // Hint: use the heapify function

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
    return true;
    //
}

template <class T>
size_t Heap<T>::size() const
{
    // TODO: fixme
    return 0;
    //
}

template <class T>
T const &Heap<T>::item() const
{
    assert(!is_empty());
    // TODO: fixme
    return T{};
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

    //
    assert(is_a_heap());
    assert(size() == old_size - 1);
}

template <class T>
void heapsort(std::vector<T> &values, std::function<bool(T const &a, T const &b)> const &comp)
{
    // TODO
    // Remember: we want O(N log N) here.

    //
#ifndef NDEBUG
    for (size_t i = 1; i < values.size(); ++i)
        assert(comp(values[i], values[i - 1]));
#endif
}