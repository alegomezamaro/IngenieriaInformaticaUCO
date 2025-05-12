/**
 * @file graph_traversals_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <tuple>
#include <stack>
#include <queue>

#include "wgraph_traversals.hpp"

template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: set the visited flags to false.
    // Remember: to mark the start of the traversal, 'u' arriving
    // from 'u' must be indicated.

    //
}

template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g,
                      typename Graph<T, E>::VertexRef &v,
                      typename Graph<T, E>::VertexRef &u,
                      Processor &p)
{
    assert(!v->is_visited());
    // TODO
    // Remember: move vertex cursor to v to scan all the edges incident on it.

    //
}

template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: reset to false the visited flags.

    //
}

template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, typename Graph<T, E>::VertexRef &v,
                        typename Graph<T, E>::VertexRef &u,
                        Processor &p)
{
    assert(!v->is_visited());

    // TODO
    // Remember: we want to know from which vertex 'u' arriving from when processing
    // a vertex 'v' so we can enqueue a pair <v,u>.
    // Remember: to mark the first vertex we enqueue the pair <u,u>

    //
}

/**
 * @brief Helper function to do the topological sorting.
 *
 * @param g is the directed acyclic graph.
 * @param u is the vertex to continue the traversal.
 * @param sorting is the sorted vertices list.
 */
template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         typename Graph<T, E>::VertexRef &u,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(!u->is_visited());
    // TODO
    // Remember: move vertex cursor to u to scan all the edges incident on it.

    //
}

template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(g.is_directed());
    // TODO
    // Remember: set the visited flags to false.

    //
}