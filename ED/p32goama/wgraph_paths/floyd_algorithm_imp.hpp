/**
 * @file floyd_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <utility>
#include <limits>
#include <stack>
#include <floyd_algorithm.hpp>

#ifdef __VERBOSE__
extern int Verbose_level;
#endif

inline std::ostream &
print_floyd_I(std::ostream &out,
              IMatrix const &I)
{
    std::string blanks = "          ";
    std::string unders = "__________";
    size_t field_width = 4;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < I.cols(); ++i)
        out << std::setw(field_width) << i;
    out << std::endl;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < I.cols(); ++i)
        out << std::setw(field_width) << unders.substr(0, field_width);
    out << std::endl;
    for (size_t r = 0; r < I.rows(); ++r)
    {
        out << std::setw(field_width) << r << '|';
        for (size_t c = 0; c < I.cols(); ++c)
        {
            if (I[r][c] == -1)
                out << std::setw(field_width) << '-';
            else
                out << std::setw(field_width) << I[r][c];
        }
        out << std::endl;
    }
    return out;
}

inline std::ostream &
print_floyd_D(std::ostream &out,
              FMatrix const &D)
{
    std::string blanks = "          ";
    std::string unders = "__________";
    size_t field_width = 4;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < D.cols(); ++i)
        out << std::setw(field_width) << i;
    out << std::endl;
    out << blanks.substr(0, field_width + 1);
    for (size_t i = 0; i < D.cols(); ++i)
        out << std::setw(field_width) << unders.substr(0, field_width);
    out << std::endl;
    for (size_t r = 0; r < D.rows(); ++r)
    {
        out << std::setw(field_width) << r << '|';
        for (size_t c = 0; c < D.cols(); ++c)
        {
            if (D[r][c] == std::numeric_limits<float>::infinity())
                out << std::setw(field_width) << '-';
            else
                out << std::setw(field_width) << D[r][c];
        }
        out << std::endl;
    }
    return out;
}

/**
 * @brief Compute the weight matrix.
 *
 * Also compute two maps to convert between the vertex key and the index of the matrix.
 *
 * @tparam T Vertex item data type.
 * @param[in] g is the graph.
 * @param[out] D is the distances matrix.
 */
template <class T>
void compute_weight_matrix(Graph<T, float> const &g,
                           FMatrix &D)
{
    D.resize(g.num_vertices(), g.num_vertices(),
             std::numeric_limits<float>::infinity());

    // TODO: Initialize the distances matrix traversing the graph by vertex and edges.

    for(auto v_iter = g.vertices_begin(); v_iter != g.vertices_end(); ++v_iter){ //Recorrer los vértices del grafo

        auto vertex = *v_iter; //Obtener el vértice actual
        size_t u_label = vertex->label(); //Obtener la etiqueta del vértice actual
        
        for(auto e_iter = g.edges_begin(v_iter); e_iter != g.edges_end(v_iter); ++e_iter){ //Recorrer los bordes incidentes en el vértice actual

            auto edge = *e_iter; //Obtener el borde actual
            auto other_vertex = edge->other(vertex); //Obtener el otro vértice del borde actual
            size_t v_label = other_vertex->label(); //Obtener la etiqueta del otro vértice
            D[u_label][v_label] = edge->item(); //Asignar el peso del borde a la matriz de distancias
        }
    }

    //
}

template <class T>
void floyd_algorithm(Graph<T, float> const &g,
                     FMatrix &D,
                     IMatrix &I)
{
    compute_weight_matrix(g, D);
    I.resize(g.num_vertices(), g.num_vertices(), -1);

    // TODO: Codify the Floyd algorithm.

    size_t n = g.num_vertices(); //Número de vértices en el grafo

    for(size_t k = 0; k < n; ++k){ //Iterar sobre cada vértice como intermedio

        for(size_t i = 0; i < n; ++i){ //Iterar sobre cada vértice de origen

            for(size_t j = 0; j < n; ++j){ //Iterar sobre cada vértice de destino

                if(D[i][k] != std::numeric_limits<float>::infinity() &&
                    D[k][j] != std::numeric_limits<float>::infinity() &&
                    D[i][k] + D[k][j] < D[i][j]){ //Si la distancia a través del vértice intermedio es menor que la distancia actual

                    D[i][j] = D[i][k] + D[k][j]; //Actualizar la distancia
                    I[i][j] = static_cast<int>(k); //Actualizar el índice del vértice intermedio
                }
            }
        }
    }

    //
}

std::list<size_t>
floyd_path(size_t src, size_t dst, IMatrix const &I)
{
    // Prec: distance (u,v) < inf
    std::list<size_t> path;

    // TODO: Find the path.
    // Hint: Think first. Is it necessary to build a binary tree? or it
    // is enough to do an first-depth search using an iterative approach with
    // a stack of pairs (u,v).

    std::stack<std::pair<size_t, size_t>> stack; //Pila para almacenar los pares (u,v)
    stack.push(std::make_pair(src, dst)); //Agregar el par (src, dst) a la pila
    std::vector<size_t> path_vector; //Vector para almacenar los vértices intermedios del camino
    
    while(!stack.empty()){ //Mientras la pila no esté vacía

        auto current = stack.top(); //Obtener el par (u,v) del tope de la pila
        stack.pop(); //Eliminar el par del tope de la pila
        size_t u = current.first; //Vértice origen
        size_t v = current.second; //Vértice destino
        
        if(I[u][v] == -1){ //Si no hay vértice intermedio
 
            if(u != v){ //Si u y v son diferentes, agregar v al camino

                path_vector.push_back(v);
            }
        }
        
        else{ //Si hay un vértice intermedio
    
            size_t k = I[u][v]; //Obtener el vértice intermedio
            stack.push(std::make_pair(k, v)); //Agregar el par (k,v) a la pila
            stack.push(std::make_pair(u, k)); //Agregar el par (u,k) a la pila
        }
    }

    path.push_back(src); //Agregar el vértice origen al camino
    
    for(size_t vertex : path_vector){ //Recorrer los vértices intermedios del camino

        path.push_back(vertex); //Agregar el vértice intermedio al camino
    }

    //
    return path;
}
