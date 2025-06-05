/**
 * @file prim_algorithm_imp.hpp
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

#include "prim_algorithm.hpp"

template <class T>
float prim_algorithm(Graph<T, float> &g,
                     VertexIterator<T, float> &start_vertex,
                     std::vector<typename Graph<T, float>::EdgeRef> &mst) noexcept(false)
{
    assert(!g.is_directed());

    float total_distance = 0.0;
    mst.resize(0);

    // Create and initialize auxiliary vectors.
    auto U = get_vertices(g);
    std::vector<size_t> V(g.num_vertices());
    for (size_t i = 0; i < V.size(); ++i)
        V[i] = i;
    std::vector<bool> A(g.num_vertices(), false);
    std::vector<float> C(g.num_vertices(), std::numeric_limits<float>::infinity());

    // Find the index 'u' of the start vertex in vector U.
    size_t u = 0;
    while (U[u] != *start_vertex)
        ++u;

    // Add the start vertex to the Minimum Spanning Tree with cost 0.
    A[u] = true;
    C[u] = 0.0;

    // TODO
    // Remember: Use auxiliary vectors U, V, A and C.
    // Remember: U vector has the graph's nodes.
    // Remember: We need to find the N-1 edges.
    for (size_t i = 1; i < U.size(); ++i)
    {
        // Update distances to MST for not visited vertex using as predecessor
        // the vertex 'u'.

        //

        float least_cost = std::numeric_limits<float>::infinity();
        // Select the next vertex 'u' to add to the MST (with the least cost).

        //

        assert(!A[u]); // u does not belong to the MST yet.

        if (least_cost == std::numeric_limits<float>::infinity())
            throw std::runtime_error("It is an unconnected graph.");

        // Add the found vertex to the MST.
        total_distance += least_cost;
        A[u] = true;
        mst.push_back(g.edge(U[V[u]], U[u]));
    }
    //

    return total_distance;
}
