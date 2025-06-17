/**
 * @file kruskal_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <exception>
#include <limits>
#include <memory>
#include <algorithm>

#include "disjointsets.hpp"
#include "kruskal_algorithm.hpp"

template <class T>
float kruskal_algorithm(Graph<T, float> &g,
                        std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false)
{
    float total_distance = 0.0;

    DisjointSets sets(g.num_vertices());

    // Generate a set for each node.
    for (size_t i = 0; i < g.num_vertices(); ++i)
        sets.make_set(i);

    auto edges = get_edges(g);

    // Sort the edges using the comparison function.
    auto compare = [](const typename Graph<T, float>::EdgeRef &a,
                      const typename Graph<T, float>::EdgeRef &b) -> bool
    {
        bool ret_v = false;
        // TODO: implement the comparison function.
        // Remember: the edge is seen as a tuple (weight,first_key,second_key).
        // Remember: compare(a,b) must return true if edge a must be before
        // edge b using lexicographic order.

        //
        return ret_v;
    };
    std::sort(std::begin(edges), std::end(edges), compare);

    // TODO: implement the Kruskal algorithm.
    // Remember: use 'DisjointSets::find(u_label)' method to find the "color"
    // of vertex u and DisjointSets::joint(u_label, v_label) to join the subset
    // with vertex u->label() with the subset with vertex v.

    //

    // TODO: check if the graph is connected and throw
    // std::runtime_error("It is an unconnected graph.") exception if it is not.
    // Remember: In a connected graph th MST will have N-1 edges (N is the number of vertices).

    //

    assert(mst.size() == g.num_vertices() - 1);
    return total_distance;
}
