/**
 * @file a_star_algorithm_imp.hpp
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
#include <limits>
#include <functional>

#include <a_star_algorithm.hpp>
#include <priority_queue.hpp>

template <class T, class Heuristic>
size_t
a_star_algorithm(Graph<T, float> &g,
                 typename Graph<T, float>::VertexRef &start,
                 typename Graph<T, float>::VertexRef &end,
                 Heuristic &H,
                 std::vector<size_t> &predecessors,
                 std::vector<float> &distances)
{
    assert(g.has(start));
    assert(g.has(end));

    /** @brief the Dijkstra tuple.
     * We use the tuple (dist,u's label,v's label) format to represent an edge.
     * Remember: tuples use lexicographic comparisons.
     */
    using Tuple = std::tuple<float, float, size_t, size_t>;

    size_t iterations = 0;
    g.reset(false);

    // TODO: initialize the predecessors and distances vectors.
    // Remember: each vertex is predecessor of itself with distance infinite.

    //

    // TODO: implement the A* algorithm.
    // Note: you can use std::priority_queue if you have not implemented
    // the ADT PriorityQueue.

    //
    return iterations;
}

inline std::list<size_t>
a_star_path(size_t src, size_t dst,
            std::vector<size_t> const &predecessors)
{
    assert(src < predecessors.size());
    assert(dst < predecessors.size());
    assert(predecessors[src] == src);
    std::list<size_t> path;
    // TODO

    //
    return path;
}
