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

#include <wgraph_traversals.hpp>

/**
 * @brief Depth first scanning of a graph from a given vertex.
 *
 * The traversal starts/continue from the vertex @a v arriving from @a u.
 * Only the connected component including this vertices will be traversed.
 *
 * @param g is the graph.
 * @param v is the vertex used to continue the traversal.
 * @param u is the predecessor vertex of v.
 * @param p is a functional to process a spanning tree edge.
 *
 * @warning p must accept the interface
 * 'void (typename Graph<T,E>::VertexRef & v, typename Graph<T,E>::VertexRef & u)'
 * meaning process 'v' arriving from 'u'
 */
template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g,
                      VertexIterator<T, E> &v,
                      VertexIterator<T, E> &u,
                      Processor &p)
{
    assert(!(*v)->is_visited());
    // TODO
    // Remember: we apply a prefix processing of nodes.
    // Hint: use and edge iterator to scan the edges incident on the vertex 'v'.

    //
}

template <class T, class E, class Processor>
void depth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: reset the visited flags to false.
    // Remember: to mark the start of the traversal, 'u' arriving
    // from 'u' must be indicated.

    //
}

/**
 * @brief Breadth first scanning of a graph.
 *
 * The traversal starts from the given vertex. Only the connected
 * component including this vertex will be traversed.
 *
 * @param g is the graph.
 * @param start_v is the scanning start vertex.
 * @param u is the predecessor vertex of v.
 * @param p is a functional to process a spanning tree edge.
 *
 * @warning p must accept the interface
 * 'void (typename Graph<T,E>::VertexRef & v, typename Graph<T,E>::VertexRef & u)'
 * meaning process 'v' arriving from 'u'
 */
template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, VertexIterator<T, E> &start_v,
                        Processor &p)
{
    assert(!(*start_v)->is_visited());

    // TODO
    // Remember: we need to use a std::queue to process the vertices.
    // Hint: enqueue a pair <v,u> to mark the vertex 'v' arriving from
    // vertex 'u'.
    // Hint: to enqueue the start vertex u with the pair <u,u>

    //
}

template <class T, class E, class Processor>
void breadth_first_scan(Graph<T, E> &g, Processor &p)
{
    // TODO
    // Remember: reset to false the visited flags.

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
                         VertexIterator<T, E> &u,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(!(*u)->is_visited());
    // TODO
    // Remember: use edge iterator to traverse the edges incident in u.
    // Remember: we apply a postfix processing of nodes.

    //
}

template <class T, class E>
void topological_sorting(Graph<T, E> &g,
                         std::list<typename Graph<T, E>::VertexRef> &sorting)
{
    assert(g.is_directed());
    // TODO
    // Remember: reset the visited flags to false.

    //
}