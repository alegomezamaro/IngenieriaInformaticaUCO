/**
 * @file graph_imp.hpp
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
#include <graph.hpp>

template <class T, class E>
Graph<T, E>::Graph(bool directed)
{
    next_label_ = 0;

    // TODO

    is_directed_ = directed; // Inicializa el atributo is_directed_ según el parámetro recibido
    //

    assert(is_empty());
    assert(!directed || is_directed());
    assert(directed || !is_directed());
}

template <class T, class E>
bool Graph<T, E>::is_empty() const
{
    // TODO: fixme
    // Remember: the graph is empty if there are not vertices.

    return vertices_.empty(); //Comprueba si la lista de vértices está vacía
    //
}

template <class T, class E>
bool Graph<T, E>::is_directed() const
{
    // TODO: fixme

    return is_directed_; // Comprueba si el grafo es dirigido
    //
}

template <class T, class E>
size_t Graph<T, E>::num_vertices() const
{
    // TODO: fixme

    return vertices_.size(); // Devuelve el número de vértices en la lista de vértices
    //
}

template <class T, class E>
size_t Graph<T, E>::num_edges() const
{
    size_t ret_v = 0;
    // TODO
    // Remember: is the graph is undirected the edge (u:v) was duplicated in
    // the incident list of u an v.

    for(auto it = vertices_.begin(); it != vertices_.end(); ++it){ // Recorre los vértices desde el principio hasta el final
    
        ret_v += it->second.size(); // Suma el número de bordes incidentes en el vértice actual a ret_v
    }
    
    if(!is_directed()){ // Si el grafo es no dirigido, cada borde se cuenta dos veces (una vez en cada extremo)

        ret_v /= 2; // Divide el número total de bordes por 2 para obtener el número real de bordes en un grafo no dirigido
    }
    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::has(VertexRef const &u) const
{
    assert(u != nullptr);
    // TODO: fixme
    // Hint: use vertex() to find the vertex with u's label.

    return vertex(u->label()) != nullptr; // Comprueba si existe un vértice con la etiqueta de u
    //
}

template <class T, class E>
bool Graph<T, E>::has(EdgeRef const &e) const
{
    assert(e != nullptr);
    assert(has(e->first()));
    assert(has(e->second()));
    bool ret_v = false;
    // TODO
    // Hint: use get_iterator() to get an iterator points to the first vertex.

    auto iter = get_iterator(e->first()); // Obtiene el iterador al vértice que es el primer extremo del borde e
    
    for (auto edge = edges_begin(iter); edge != edges_end(iter); ++edge){ // Recorre los bordes incidentes en el vértice desde el principio hasta el final

        if (*edge == e){ // Si el borde actual es igual a e
    
            ret_v = true; // Marca ret_v como verdadero si se encuentra el borde e
            break;
        }

    }
    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::is_adjacent(VertexRef const &u, VertexRef const &v) const
{
    assert(has(u));
    assert(has(v));

    // TODO: fixme
    // Remember: a vertex u is adjacent to v if there is a edge (u,v) or
    // if the graph is undirected, there is a edge (v,u).
    // Hint: use the method edge(x, y).

    return edge(u, v) != nullptr; // Comprueba si existe un borde entre u y v
    //
}

template <class T, class E>
typename Graph<T, E>::EdgeRef Graph<T, E>::edge(VertexRef const &u,
                                                VertexRef const &v) const
{
    assert(has(u));
    assert(has(v));
    EdgeRef ret_v = nullptr;

    // TODO
    // Remember: if the graph is undirected, the edge (u,v) is the same as (v,u).
    // Hint: use vertex and edge iterators.

    auto iter = vertices_begin(); // Obtiene el iterador al principio de la lista de vértices
    
    while(iter != vertices_end() && (*iter) != u){ // Recorre los vértices desde el principio hasta el final

        iter++; // Avanza al siguiente vértice
    }

    if(iter != vertices_end()){ // Si se encontró el vértice u en la lista de vértices

        auto edge_iter = edges_begin(iter); // Obtiene el iterador al principio de la lista de bordes incidentes en u
        
        while(edge_iter != edges_end(iter)){ // Recorre los bordes incidentes en u desde el principio hasta el final

            if((*edge_iter)->other(u) == v){ // Si el borde actual tiene v como otro extremo

                ret_v = *edge_iter; // Asigna el borde actual a ret_v
                break;
            }

            edge_iter++; // Avanza al siguiente borde
        }
    }

    //

    assert(!ret_v || (!is_directed() || ret_v->first() == u));
    assert(!ret_v || (!is_directed() || ret_v->second() == v));
    assert(!ret_v || (is_directed() || ret_v->has(u)));
    assert(!ret_v || (is_directed() || ret_v->other(u) == v));
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::reset(bool state)
{
    // TODO
    // Remember: Both vertices and edges has a visited flag to be reset.

    for (auto& vertex_pair : vertices_){ // Recorre los pares de vértices y sus listas de bordes

        vertex_pair.first->set_visited(state); // Establece el estado de visitado del vértice actual
        
        for(auto& edge : vertex_pair.second){ // Recorre los bordes incidentes en el vértice actual
    
            edge->set_visited(state); // Establece el estado de visitado del borde actual   
        }
    }

    //
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::find_vertex(typename T::key_t const &value) const
{
    VertexRef ret_v = nullptr;
    // TODO

    for (auto iter = vertices_begin(); iter != vertices_end(); ++iter){ // Recorre los vértices desde el principio hasta el final
        
        if ((*iter)->item().key() == value){ // Si el vértice actual tiene la clave igual al valor dado
        
            ret_v = *iter; // Asigna el vértice actual a ret_v
            break;
        }
    }

    //
    assert(ret_v == nullptr || ret_v->item().key() == value);
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::vertex(size_t value) const
{
    VertexRef ret_v = nullptr;
    // TODO

    for(auto iter = vertices_begin(); iter != vertices_end(); ++iter){ // Recorre los vértices desde el principio hasta el final
    
        if ((*iter)->label() == value){ // Si el vértice actual tiene la etiqueta igual al valor dado
            
            ret_v = *iter; // Asigna el vértice actual a ret_v
            break;
        }
    }

    //
    assert(ret_v == nullptr || ret_v->label() == value);
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::add_vertex(T const &v)
{
#ifndef NDEBUG
    size_t old_next_label = next_label_;
#endif

    VertexRef ret_v = nullptr;
    // TODO
    // Remember: use push_back to add the vertex to the list of vertices.
    // Remember: updated the next label attribute to next integer.

    ret_v= Vertex<T>::create(next_label_, v); // Crea un nuevo vértice con la etiqueta actual y el ítem dado
    next_label_++;
    vertices_.push_back(std::make_pair(ret_v, edges_list_t())); // Añade el nuevo vértice a la lista de vértices

    //
    assert(next_label_ == (old_next_label + 1));
    assert(ret_v->label() == (old_next_label));
    assert(has(ret_v));
    assert(ret_v->item() == v);
    assert(!ret_v->is_visited());
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::remove_vertex(const VertexRef &v)
{
    assert(has(v));
#ifndef NDEBUG
    auto old_num_vertices = num_vertices();
#endif
    // TODO
    // Remember: you must also remove all edges incident in this vertex.
    // Remember: if the graph is undirected, the edge (u,v) was duplicated in
    // the incident list of u and v.

    auto iter = vertices_.begin(); // Obtiene el iterador al principio de la lista de vértices

    while(iter != vertices_.end() && iter->first != v){ // Recorre los vértices desde el principio hasta el final

        iter++;
    }

    if(iter != vertices_.end()){ // Si se encontró el vértice v en la lista de vértices

        for(auto& vertex_pair : vertices_){ // Recorre todos los pares de vértices y sus listas de bordes

            if(vertex_pair.first != v){ // Si el vértice actual no es v

                auto edge_iter = vertex_pair.second.begin(); // Obtiene el iterador al principio de la lista de bordes incidentes en el vértice actual
                
                while(edge_iter != vertex_pair.second.end()){ // Recorre los bordes incidentes en el vértice actual desde el principio hasta el final

                    if((*edge_iter)->has(v)){ // Si el borde actual tiene v como uno de sus extremos

                        edge_iter = vertex_pair.second.erase(edge_iter); // Elimina el borde de la lista de bordes incidentes en el vértice actual                    
                    }
                    
                    else{ // Sino, avanza al siguiente borde

                        edge_iter++;
                    }
                }
            }
        }
        
        vertices_.erase(iter); // Elimina el vértice v de la lista de vértices
    }

    //
    assert(!has(v));
    assert(num_vertices() == (old_num_vertices - 1));
}

template <class T, class E>
typename Graph<T, E>::EdgeRef Graph<T, E>::add_edge(VertexRef const &u, VertexRef const &v, E const &item)
{
    assert(has(u));
    assert(has(v));

#ifndef NDEBUG
    auto old_num_edges = num_edges();
#endif

    EdgeRef ret_v = nullptr;

    // TODO
    // Remember: if the graph is directed, the edge only is incident on
    // the u end but if it is not directed, the edge is incident on both u and v ends.
    // Hint: use get_iterator() to get the iterator to
    //   the adjacent list of vertices u and v.
    // Remember: We add the new edge to the end of adjacent lists.

    ret_v = Edge<T, E>::create(u, v, item); // Crea un nuevo borde entre u y v con el ítem dado
    auto u_iter = get_iterator(u); // Obtiene el iterador al vértice u
    u_iter.it_->second.push_back(ret_v); // Añade el borde a la lista de bordes incidentes en u
    
    if(!is_directed()){ // Si el grafo es no dirigido, también debemos añadir el borde a la lista de bordes incidentes en v

        auto v_iter = get_iterator(v); // Obtiene el iterador al vértice v
        v_iter.it_->second.push_back(ret_v); // Añade el borde a la lista de bordes incidentes en v
    }

    //
    assert(num_edges() == (old_num_edges + 1));
    assert(!ret_v->is_visited());
    assert(ret_v->first() == u);
    assert(ret_v->second() == v);
    assert(ret_v->item() == item);
    assert(ret_v->has(u));
    assert(ret_v->has(v));
    assert(ret_v->other(u) == v);
    assert(ret_v->other(v) == u);
    assert(is_adjacent(u, v));
    assert(is_directed() || is_adjacent(v, u));
    return ret_v;
}

template <class T, class E>
void Graph<T, E>::remove_edge(VertexRef const &u, VertexRef const &v)
{
    assert(has(u));
    assert(has(v));
#ifndef NDEBUG
    auto old_num_edges = num_edges();
#endif
    // TODO
    // Remember: if the graph is undirected, the edge u-v was duplicated as
    // incident in the u and v adjacent lists.

    auto u_iter = get_iterator(u); // Obtiene el iterador al vértice u
    auto edge_iter = edges_begin(u_iter); // Obtiene el iterador al principio de la lista de bordes incidentes en u

    while(edge_iter != edges_end(u_iter)){ // Recorre los bordes incidentes en u desde el principio hasta el final
    
        if((*edge_iter)->other(u) == v){ // Si el borde actual tiene v como otro extremo

            edge_iter.it_ = u_iter.it_->second.erase(edge_iter.it_); // Elimina el borde de la lista de bordes incidentes en u
            break;
        }
        
        else{

            edge_iter++; // Avanza al siguiente borde
        }
    }
    
    if(!is_directed()){ // Si el grafo es no dirigido, también debemos eliminar el borde de la lista de bordes incidentes en v

        auto v_iter = get_iterator(v); // Obtiene el iterador al vértice v
        edge_iter = edges_begin(v_iter); // Obtiene el iterador al principio de la lista de bordes incidentes en v
        
        while(edge_iter != edges_end(v_iter)){ // Recorre los bordes incidentes en v desde el principio hasta el final

            if((*edge_iter)->other(v) == u){ // Si el borde actual tiene u como otro extremo
                
                edge_iter.it_ = v_iter.it_->second.erase(edge_iter.it_); // Elimina el borde de la lista de bordes incidentes en v
                break;
            }
            
            else{ // Sino, avanza al siguiente borde 

                edge_iter++; 
            }
        }
    }

    //
    assert(!is_adjacent(u, v));
    assert(num_edges() == (old_num_edges - 1));
}

template <class T, class E>
std::ostream &
Graph<T, E>::fold(std::ostream &out) const
{
    // TODO
    // Remember: to fold and edge we use item().key() to fold the edge's ends.

    if (is_directed()){ // Si el grafo es dirigido
    
        out << "DIRECTED" << std::endl;
    }

    else{ // Si el grafo es no dirigido
    
        out << "UNDIRECTED" << std::endl;
    }
    
    out << num_vertices() << std::endl; // Mostramos el número de vértices
    
    for (auto iter = vertices_begin(); iter != vertices_end(); ++iter){ // Recorre los vértices desde el principio hasta el final

        out << (*iter)->item() << std::endl; // Mostramos el ítem del vértice actual
    }
    
    out << num_edges() << std::endl;
    
    for (auto iter = vertices_begin(); iter != vertices_end(); ++iter){ // Recorre los vértices desde el principio hasta el final

        for (auto edge_iter = edges_begin(iter); edge_iter != edges_end(iter); ++edge_iter){ // Recorre los bordes desde el principio hasta el final

            if (is_directed() || (*edge_iter)->first() == *iter){ // Si el grafo es dirigido o el borde comienza en el vértice actual
                
                out << (*iter)->item().key() << " " << (*edge_iter)->other(*iter)->item().key() << " " << (*edge_iter)->item() << std::endl;
            }
        }
    }

    //
    return out;
}

template <class T, class E>
Graph<T, E>::Graph(std::istream &in) noexcept(false)
{
    // TODO
    // Remember: Throw std::runtime_error("Wrong graph") when detecting a wrong
    //           input format.
    // Remember: key_t type is used to unfold the edge's ends.

    // TODO
    // Reset the next label attribute to 0.
    next_label_ = 0;
    //

    // TODO
    // First: is it directed or undirected?

    std::string graph_type; // Tipo de grafo (DIRECTED o UNDIRECTED)

    if (!(in >> graph_type)){ //Si no se puede leer el tipo de grafo
    
        throw std::runtime_error("Wrong graph");
    }
    
    if (graph_type == "DIRECTED"){ //Si es directo

        is_directed_ = true;
    
    }

    else if (graph_type == "UNDIRECTED"){ //Sino, si es indirecto
    
        is_directed_ = false;
    }

    else{ //Sino es ninguno de los dos
    
        throw std::runtime_error("Wrong graph");
    }

    //

    size_t size = 0;
    // TODO
    // Second: get the number of vertices and create a Graph with this capacity.

    if (!(in >> size)){ //Si no se puede leer el número de vértices

        throw std::runtime_error("Wrong graph");
    }

    //

    // TODO
    // Third: load the N data items and add a vertex for each one.

    for (size_t i = 0; i < size; ++i){ //Recorre los vértices desde el principio hasta el final
    
        T item; // Ítem del vértice

        if (!(in >> item)){ //Si no se puede leer el ítem del vértice
        
            throw std::runtime_error("Wrong graph");   
        }

        add_vertex(item); // Añade el vértice con el ítem leído
    }

    //

    size_t n_edges = 0;

    // TODO
    // Fourth: load the number of edges.

    if (!(in >> n_edges)){ //Si no se puede leer el número de bordes
    
        throw std::runtime_error("Wrong graph");
    }

    //

    // TODO
    // Fifth: load the N edges.
    // Remember: Use T::key_t type to unfold the edge's end keys.
    // Hint: use find_vertex(T::key_t) to get a reference to the vertex with that key.

    for (size_t i = 0; i < n_edges; ++i){ //Recorre los bordes desde el principio hasta el final
    
        typename T::key_t u_key, v_key; // Claves de los vértices que forman el borde
        E item;
    
        if (!(in >> u_key >> v_key >> item)){ //Si no se pueden leer las claves de los vértices y el ítem del borde

            throw std::runtime_error("Wrong graph");
        }
        
        VertexRef u = find_vertex(u_key);
        VertexRef v = find_vertex(v_key);
        
        if (!u || !v){ // Si no se encuentran los vértices con las claves dadas

            throw std::runtime_error("Wrong graph");
        }
        
        add_edge(u, v, item); // Añade el borde entre los vértices u y v con el ítem dado
    }

    //
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::vertices_begin() const
{
    return VertexIterator<T, E>(const_cast<Graph *>(this)->vertices_.begin());
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::vertices_end() const
{
    return VertexIterator<T, E>(const_cast<Graph *>(this)->vertices_.end());
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::find_first(typename T::key_t const &value) const
{
    auto iter = vertices_begin();
    // TODO

    while(iter != vertices_end() && (*iter)->item().key() != value){ //Recorre los vértices desde el principio hasta el final
    
        iter++; //Avanza al siguiente vértice
    }

    //
    assert(iter == vertices_end() || (*iter)->item().key() == value);
    return iter;
}

template <class T, class E>
VertexIterator<T, E> Graph<T, E>::get_iterator(const VertexRef &v) const
{
    assert(has(v));
    auto iter = vertices_begin();
    // TODO

    while(iter != vertices_end() && (*iter) != v){ //Recorre los vértices desde el principio hasta el final
    
        iter++; //Avanza al siguiente vértice
    }
    
    //
    assert((*iter) == v);
    return iter;
}

template <class T, class E>
void Graph<T, E>::remove_vertex(const VertexIterator<T, E> &iter)
{
    assert(has(*iter));
#ifndef NDEBUG
    auto old_num_vertices = num_vertices();
#endif
    // TODO
    // Hint: use remove_vertex(const VertexRef &v) method.

    remove_vertex(*iter); //Elimina el vértice actual del iterador

    //
    assert(!has(*iter));
    assert(num_vertices() == (num_vertices() - 1));
}

template <class T, class E>
EdgeIterator<T, E> Graph<T, E>::edges_begin(const VertexIterator<T, E> &v) const
{
    return EdgeIterator<T, E>(v.it_->second.begin());
}

template <class T, class E>
EdgeIterator<T, E> Graph<T, E>::edges_end(const VertexIterator<T, E> &v) const
{
    return EdgeIterator<T, E>(v.it_->second.end());
}

template <class T, class E>
EdgeIterator<T, E> Graph<T, E>::find_first(VertexIterator<T, E> u_iter, typename T::key_t const &value) const
{
    auto edge_iter = edges_begin(u_iter);
    // TODO

    while(edge_iter != edges_end(u_iter) && (*edge_iter)->other(*u_iter)->item().key() != value){ //Recorre los bordes desde el principio hasta el final
    
        edge_iter++; //Avanza al siguiente borde
    }

    //
    assert(edge_iter == edges_end(u_iter) || (*edge_iter)->has(*u_iter));
    assert(edge_iter == edges_end(u_iter) || (*edge_iter)->other(*u_iter)->item().key() == value);
    return edge_iter;
}

template <class T, class E>
std::vector<typename Graph<T, E>::VertexRef>
get_vertices(const Graph<T, E> &g)
{
    std::vector<typename Graph<T, E>::VertexRef> vs;
    // TODO
    // Hint: use a VertexIterator to traverse the graph's vertices.

    for (auto iter = g.vertices_begin(); iter != g.vertices_end(); ++iter){ //Recorre los vértices desde el principio hasta el final
    
        vs.push_back(*iter); //Añade el vértice actual al vector de vértices
    }

    //
    return vs;
}

template <class T, class E>
std::vector<typename Graph<T, E>::EdgeRef>
get_edges(const Graph<T, E> &g)
{
    std::vector<typename Graph<T, E>::EdgeRef> es;
    // TODO
    // Hint: use VertexIterator and EdgeIterator iterators to traverse the graph.
    // Remember: if the graph is undirected, the edge (u,v) was duplicated as (v, u) into
    // the incident list of u and v but we only want one copy in the returned vector.

    for(auto v_iter = g.vertices_begin(); v_iter != g.vertices_end(); ++v_iter){ //Recorre los vértices desde el principio hasta el final

        for(auto e_iter = g.edges_begin(v_iter); e_iter != g.edges_end(v_iter); ++e_iter){ //Recorre los bordes desde el principio hasta el final

            if (g.is_directed() || (*e_iter)->first() == *v_iter){ //Si el grafo es dirigido o el borde comienza en el vértice actual

                es.push_back(*e_iter); //Añade el borde al vector de bordes       
            }
        }
    }

    //
    return es;
}
