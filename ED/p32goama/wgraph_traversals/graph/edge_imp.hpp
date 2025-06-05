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
    return false;
    //
}

template <class T, class E>
E const &Edge<T, E>::item() const
{
    // TODO: fixme
    return E();
    //
}

template <class T, class E>
bool Edge<T, E>::has(VertexRef const &n) const
{
    // TODO: fixme
    return false;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::other(VertexRef const &n) const
{
    assert(has(n));
    // TODO: fixme
    VertexRef retv;
    return retv;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::other(VertexRef const &n)
{
    assert(has(n));
    // TODO: fixme
    VertexRef retv;
    return retv;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::first() const
{
    // TODO: fixme
    VertexRef retv;
    return retv;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::first()
{
    // TODO: fixme
    VertexRef retv;
    return retv;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef const &Edge<T, E>::second() const
{
    // TODO: fixme
    VertexRef retv;
    return retv;
    //
}

template <class T, class E>
typename Edge<T, E>::VertexRef &Edge<T, E>::second()
{
    // TODO: fixme
    VertexRef retv;
    return retv;
    //
}

template <class T, class E>
void Edge<T, E>::set_visited(bool new_st)
{
    // TODO

    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

template <class T, class E>
void Edge<T, E>::set_item(E const &v)
{
    // TODO

    //
    assert(item() == v);
}
