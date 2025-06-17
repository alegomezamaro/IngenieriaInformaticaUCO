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
#include <exception>
#include <memory>
#include <iostream>
#include <sstream>

#include "btree.hpp"

template <class T>
bool BTree<T>::is_empty() const
{
    bool ret_v = false;
    // TODO

    ret_v = (_root == nullptr); //Si el nodo raiz es nulo, el arbol esta vacio

    //
    return ret_v;
}

template <class T>
BTree<T>::BTree()
{
    // TODO

    _root = nullptr; //Creamos el arbol vacio

    //
    assert(is_empty());
}

template <class T>
BTree<T>::BTree(const T &it)
{
    // TODO

    _root = BTNode<T>::create(it); //Creamos el arbol con el item it
    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
BTree<T>::BTree(std::istream &in) noexcept(false)
    : BTree<T>()
{
    // TODO
    // Remember: throw std:runtime_error exception with text
    //"Wrong input format." when an input format error is found.

    std::string token; //Creamos el token
    in >> token; //Introducimos el primer valor en token

    if (token == "["){ //Si token es el corchete inicial

        T item; //Creamos una variable para almacenar item
        in >> item; //Leemos el valor en item

        create_root(item); //Creamos el root de item
        set_left(BTree<T>(in)); //Establecemos el hijo izquierdo
        set_right(BTree<T>(in)); //Establecemos el hijo derecho

        in >> token; //Leemos el valor de item

        if (token != "]"){ //Si token es el corchete final error

            throw std::runtime_error("Wrong input format.");
        }
    }

    else if (token != "[]"){ //Si token son los corchetes vacios error

        throw std::runtime_error("Wrong input format.");
    }
    //
}

template <class T>
T BTree<T>::item() const
{
    assert(!is_empty());
    T ret_v;
    // TODO

    ret_v = _root->item();

    //
    return ret_v;
}

template <class T>
BTree<T> BTree<T>::left() const
{
    assert(!is_empty());
    BTree<T> subtree;
    // TODO
    // Hint: use the private constructor given a root node.

    subtree.set_root(_root->left()); //Creamos un subarbol donde el root sea el hijo izquierdo

    //
    return subtree;
}

template <class T>
BTree<T> BTree<T>::right() const
{
    assert(!is_empty());
    BTree<T> subtree;
    // TODO
    // Hint: use the private constructor given a root node.

    subtree.set_root(_root->right()); //Creamos un subarbol donde el root sea el hijo derecho

    //
    return subtree;
}

template <class T>
std::ostream &BTree<T>::fold(std::ostream &out) const
{
    // TODO

    if (is_empty()){ //Si el arbol esta vacio lo representamos con []

        out << "[]";
    }
    
    else { //Si el arbol no esta vacio

        out << "[ " << item() << " "; //Añadimos el root
        left().fold(out); //Mostramos el subarbol izquierdo
        out << " "; //Espacio
        right().fold(out); //Mostramos el subarbol derecho
        out << " ]"; //Cerramos corchete
    }

    //
    return out;
}

template <class T>
void BTree<T>::create_root(const T &it)
{
    assert(is_empty());
    // TODO

    _root = BTNode<T>::create(it); //Creamos root con el item it

    //
    assert(!is_empty());
    assert(item() == it);
    assert(left().is_empty());
    assert(right().is_empty());
}

template <class T>
void BTree<T>::set_item(const T &new_it)
{
    assert(!is_empty());
    // TODO

    _root->item() = new_it; //Asignamos a item new_it

    //
    assert(item() == new_it);
}

template <class T>
void BTree<T>::set_left(const BTree<T> &new_left)
{
    assert(!is_empty());
    // TODO

    _root->set_left(new_left.root()); //Asignamos a left new_left

    //
    assert(left().root() == new_left.root());
}

template <class T>
void BTree<T>::set_right(const BTree<T> &new_right)
{
    assert(!is_empty());
    // TODO

    _root->set_right(new_right.root()); //Asignamos a right new_right

    //
    assert(right().root() == new_right.root());
}

template <class T>
BTree<T>::BTree(const typename BTNode<T>::Ref &n)
{
    // TODO

    _root = n; //Asignamos n a root

    //
    assert(root() == n);
}

template <class T>
typename BTNode<T>::Ref BTree<T>::root() const
{
    typename BTNode<T>::Ref node;
    // TODO

    node = _root; //Igualamos el valor de root a node

    //
    return node;
}

template <class T>
void BTree<T>::set_root(const typename BTNode<T>::Ref &new_root)
{
    // TODO

    _root = new_root; //Asignamos un nuevo valor a item del root

    //
    assert(root() == new_root);
}

template <class T>
BTree<T>::BTree(const BTree<T> &other)
{
    set_root(other.root());
}

template <class T>
BTree<T>::BTree(BTree<T> &&other)
{
    set_root(other.root());
}

template <class T>
BTree<T> &BTree<T>::operator=(const BTree<T> &other)
{
    set_root(other.root());
    return *this;
}

template <class T>
BTree<T> &BTree<T>::operator=(BTree<T> &&other)
{
    set_root(other.root());
    return *this;
}
