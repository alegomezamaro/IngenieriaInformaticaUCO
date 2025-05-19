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
    return false;
    //
}

template <class T, class E>
bool Graph<T, E>::is_directed() const
{
    // TODO: fixme
    return false;
    //
}

template <class T, class E>
size_t Graph<T, E>::num_vertices() const
{
    // TODO: fixme
    return 0;
    //
}

template <class T, class E>
size_t Graph<T, E>::num_edges() const
{
    size_t ret_v = 0;
    // TODO
    // Remember: is the graph is undirected the edge (u:v) was duplicated in
    // the incident list of u an v.

    //
    return ret_v;
}

template <class T, class E>
bool Graph<T, E>::has(VertexRef const &u) const
{
    assert(u != nullptr);
    // TODO: fixme
    // Hint: use vertex() to find the vertex with u's label.
    return false;
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
    return false;
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

    //
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::find_vertex(typename T::key_t const &value) const
{
    VertexRef ret_v = nullptr;
    // TODO

    //
    assert(ret_v == nullptr || ret_v->item().key() == value);
    return ret_v;
}

template <class T, class E>
typename Graph<T, E>::VertexRef Graph<T, E>::vertex(size_t value) const
{
    VertexRef ret_v = nullptr;
    // TODO

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

    //

    size_t size = 0;
    // TODO
    // Second: get the number of vertices and create a Graph with this capacity.

    //

    // TODO
    // Third: load the N data items and add a vertex for each one.

    //

    size_t n_edges = 0;

    // TODO
    // Fourth: load the number of edges.

    //

    // TODO
    // Fifth: load the N edges.
    // Remember: Use T::key_t type to unfold the edge's end keys.
    // Hint: use find_vertex(T::key_t) to get a reference to the vertex with that key.

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

    //
    return es;
}
