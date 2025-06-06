/**
 * @file dijkstra_algorithm_imp.hpp
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
#include <tuple>
#include <functional>
#include <limits>

#include <dijkstra_algorithm.hpp>
#include <priority_queue.hpp>

template <class T>
void dijkstra_algorithm(Graph<T, float> &g,
                        typename Graph<T, float>::VertexRef const &source,
                        std::vector<size_t> &predecessors,
                        std::vector<float> &distances)
{
    assert(g.has(source));

    /** @brief the Dijkstra tuple.
     * We use the tuple (dist,u's label,v's label) format to represent an edge.
     * Remember: tuples use lexicographic comparisons.
     */
    using Tuple = std::tuple<float, size_t, size_t>;

    // Reset visited flags.
    g.reset(false);

    // TODO: initialize the predecessors and distances vectors.
    // Remember: each vertex is predecessor of itself with distance infinite.

    predecessors.resize(g.num_vertices()); //Inicializa el vector de predecesores
    distances.resize(g.num_vertices()); //Inicializa el vector de distancias

    for (size_t i = 0; i < g.num_vertices(); ++i){ //Recorre todos los vértices del grafo
        
        predecessors[i] = i; //Cada vértice es su propio predecesor
        distances[i] = std::numeric_limits<float>::infinity(); //Inicializa la distancia de cada vértice a infinito
    }

    //

    // TODO: implement the Dijkstra algorithm.
    // Note: you can use std::priority_queue if you have not implemented
    // the ADT PriorityQueue.

    std::vector<Tuple> queue_buffer; //Crear vector para la cola de prioridad
    PriorityQueue<Tuple> pq(queue_buffer, std::less<Tuple>()); //Crear cola de prioridad con comparador less (heap mínimo)
    pq.enqueue(std::make_tuple(0.0f, source->label(), source->label())); //Insertar el vértice fuente con distancia 0

    
    while (!pq.is_empty()){ //Mientras la cola de prioridad no esté vacía

        Tuple current = pq.front(); //Obtener el primer elemento de la cola de prioridad
        pq.dequeue(); //Eliminar el primer elemento de la cola de prioridad
        float dist = std::get<0>(current); //Obtener la distancia del vértice actual
        size_t u_label = std::get<1>(current); //Obtener la etiqueta del vértice actual
        size_t pred_label = std::get<2>(current); //Obtener la etiqueta del predecesor del vértice actual
        auto u = g.vertex(u_label); //Obtener el vértice actual

        if (u->is_visited()){ //Si ya fue visitado, continuar

            continue;
        }
        
        u->set_visited(true); //Marcar el vértice actual como visitado
        predecessors[u_label] = pred_label; //Actualizar el predecesor del vértice actual
        distances[u_label] = dist; //Actualizar la distancia del vértice actual
        auto u_iter = g.get_iterator(u); //Obtener el iterador del vértice actual

        for (auto e_iter = g.edges_begin(u_iter); e_iter != g.edges_end(u_iter); ++e_iter){ //Recorrer los bordes incidentes en el vértice actual

            auto edge = *e_iter; //Obtener el borde actual
            auto v = edge->other(u); //Obtener el vértice destino del borde actual
            
            if (!v->is_visited()){ //Si el vértice destino no fue visitado

                float new_dist = distances[u_label] + edge->item(); //Calcular la nueva distancia al vértice destino
                pq.enqueue(std::make_tuple(new_dist, v->label(), u_label)); //Insertar el vértice destino en la cola de prioridad con la nueva distancia y el predecesor actual
            }
        }
    }

    //
}

inline std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t> const &predecessors)
{
    assert(src < predecessors.size());
    assert(dst < predecessors.size());
    assert(predecessors[src] == src);
    std::list<size_t> path;
    // TODO
    // Remember: if the destination is unreachable, return an empty list.

    if (dst != src && predecessors[dst] == dst){ //Si el destino no es el origen y su predecesor es él mismo, significa que no hay camino
        
        return path; // Retorna lista vacía
    }
    
    size_t current = dst; //Comenzar desde el destino

    while (current != src){ //Mientras no se llegue al origen

        path.push_front(current); //Agregar el vértice actual al principio de la lista
        current = predecessors[current]; //Actualizar el vértice actual al predecesor del vértice actual
        
        if (current == predecessors[current] && current != src){ //Si el predecesor del vértice actual es él mismo y no es el origen, significa que no hay camino
            
            path.clear(); //Limpiar la lista de camino
            return path; //Retorna lista vacía
        }
    }
    
    path.push_front(src); //Agregar el origen al principio de la lista de camino

    //
    return path;
}
