/**
 * @file avltree_iterator_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <avltree_iterator.hpp>

template <class T>
const typename AVLTNode<T>::Ref &AVLTreeIterator<T>::node() const
{
    // TODO: recode using your representation.

    return node_;
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTreeIterator<T>::node()
{
    // TODO: recode using your representation.
    
    return node_;
    //
}

template <class T>
AVLTreeIterator<T>::AVLTreeIterator()
{
    // TODO

    node_=nullptr;
    //
    assert(node() == nullptr);
}

template <class T>
AVLTreeIterator<T>::AVLTreeIterator(typename AVLTNode<T>::Ref const &node)
{
    // TODO

    node_=node;
    //
    assert(this->node() == node);
}

template <class T>
bool AVLTreeIterator<T>::operator==(AVLTreeIterator<T> const &other) const
{
    bool equal = false;
    // TODO

    equal = (node_ == other.node_);
    //
    return equal;
}

template <class T>
bool AVLTreeIterator<T>::operator!=(AVLTreeIterator<T> const &other) const
{
    bool different = false;
    // TODO

    different = (node_ != other.node_);
    //
    return different;
}

template <class T>
T const &AVLTreeIterator<T>::operator*() const
{
    assert(node());
    return node()->item();
}

template <class T>
const T *AVLTreeIterator<T>::operator->() const
{
    assert(node());
    return &node()->item();
}

template <class T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator++()
{
    assert(node());
    // TODO

    if (node_->right()){

        node_ = node_->right();
        
        while (node_->left()){

            node_ = node_->left();
        }
    }

    else{
        
        // Otherwise, move up the tree until we find a node that is the left child of its parent.
        auto parent = node_->parent();

        while (parent && node_ == parent->right()){
            node_ = parent;
            parent = parent->parent();
        }

        node_ = parent; // Move to the parent.
    }
    //
    return *this;
}

template <class T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator++(int)
{
    AVLTreeIterator<T> old = *this;
    ++(*this);
    return old;
}

template <class T>
AVLTreeIterator<T> &AVLTreeIterator<T>::operator--()
{
    assert(node());
    // TODO

    if (node_->left()){
        
        node_ = node_->left();

        while (node_->right()){

            node_ = node_->right();
        }
    }

    else{

        auto parent = node_->parent();

        while (parent && node_ == parent->left()){

            node_ = parent;
            parent = parent->parent();
        }

        node_ = parent; // Move to the parent.
    }
    //
    return *this;
}

template <class T>
AVLTreeIterator<T> AVLTreeIterator<T>::operator--(int)
{
    AVLTreeIterator<T> old = *this;
    --(*this);
    return old;
}
