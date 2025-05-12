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

    auto edges = g.edges();

    // TODO
    // Remember: use 'DisjointSets::find(u)' method to find the "color" of vertex
    // with u->label().
    // and DisjointSets::joint(u,v) to join the subset of vertex' u->label()  with
    // subset with vertex v->label().
    // Hint: use std::sort and a proper compare function for edges to sort the edges vector.
    // Remember: the edge sort order is (weight:u.key():v.key()) and lexicographical sorting.

    //

    return total_distance;
}
