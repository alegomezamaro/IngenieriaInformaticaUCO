/**
 * @file edge_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <edge.hpp>

template <class T, class E>
Edge<T, E>::Edge(VertexRef const &u, VertexRef const &v, E const &data)
{
    // TODO

    u_ = u; //Asignamos u
    v_ = v; //Asignamos v
    item_ = data; //Asignamos el valor de data
    is_visited_ = false; //Asignamos el valor de is_visited_ a false
    //
    assert(has(u));
    assert(has(v));
    assert(other(u) == v);
    assert(other(v) == u);
    assert(first() == u);
    assert(second() == v);
    assert(item() == data);
    assert(!is_visited());
}

template <class T, class E>
typename Edge<T, E>::Ref Edge<T, E>::create(VertexRef const &u, VertexRef const &v, E const &data)
{
    return std::make_shared<Edge<T, E>>(u, v, data);
}

template <class T, class E>
Edge<T, E>::~Edge() {}

template <class T, class E>
bool Edge<T, E>::is_visited() const
{
    // TODO: fixme

    return is_visited_; //Retornamos el valor de is_visited_
    //
}

template <class T, class E>
E const &Edge<T, E>::item() const
{
    // TODO: fixme

    return item_; //Retornamos el valor de item
    //
}

template <class T, class E>
bool Edge<T, E>::has(VertexRef const &n) const
{
    // TODO: fixme

    return (n == u_) || (n == v_); //Retornamos true si n es igual a u o v
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::other(VertexRef const &n) const
{
    assert(has(n));
    // TODO: fixme

    if (n == u_){ //Si n es igual a u

        return v_;
    }

    else{ //Sino

        return u_;
    }
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::other(VertexRef const &n)
{
    assert(has(n));
    // TODO: fixme
    
    if (n == u_){ //Si n es igual a u

        return v_;
    }

    else{ //Sino

        return u_;
    }
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::first() const
{
    // TODO: fixme
    
    return u_; //Retornamos el valor de u
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::first()
{
    // TODO: fixme
    
    return u_; //Retornamos el valor de u
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::second() const
{
    // TODO: fixme
   
    return v_; //Retornamos el valor de v
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::second()
{
    // TODO: fixme
    
    return v_; //Retornamos el valor de v
    //
}

template <class T, class E>
void Edge<T, E>::set_visited(bool new_st)
{
    // TODO

    is_visited_ = new_st; //Ponemos el nuevo estado de visitado
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

template <class T, class E>
void Edge<T, E>::set_item(E const &v)
{
    // TODO

    item_ = v; //Ponemos el nuevo valor del item
    //
    assert(item() == v);
}
