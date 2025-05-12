/**
 * @file graph.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <memory>
#include <limits>
#include <list>
#include <vector>
#include <tuple>
#include <utility>

/**
 * @brief Class to model the Vertex of a Graph ADT.
 *
 * @tparam T is the vertex's data item type.
 *
 * It is assumed that T type defines a type T::key_t and
 * a method 'T::key_t T::key() const'
 *
 * @ingroup graph
 */
template <class T>
class Vertex
{
public:
  /** @brief alias type used as vertex's key type. */
  using key_t = typename T::key_t;

  /** @brief alias for a reference to a Vertex.*/
  using Ref = std::shared_ptr<Vertex<T>>;

  /** @name Makers*/
  /** @{*/

  /**
   * @brief Makes a new vertex.
   * @param label is the vertex label.
   * @param item is the vertex data item.
   * @post !is_visited()
   */
  Vertex(size_t label, T const &item);

  ~Vertex() {}
  /** @}*/

  /** @name Observers*/
  /**@{*/

  /**
   * @brief Get saved data item.
   * @return the saved data item.
   */
  const T &item() const;

  /**
   * @brief Get item's key.
   * @return a reference to the data saved in the vertex.
   */
  key_t key() const;

  /**
   * @brief get the label of the vertex.
   * @return the vertex's label.
   * @post no other vertex in the graph has this label.
   */
  size_t label() const;

  /**
   * @brief Has been the vertex visited?
   * @return true if the vertex was visited.
   */
  bool is_visited() const;

  /**@}*/

  /** @name Modifiers*/
  /** @{*/

  /**@brief Set data saved in the vertex.
   * @param[in] item is the data to save in.
   * @post item()==item
   */
  void set_item(T const &new_item);

  /**
   *  @brief Set the flag visited
   *  @param new_state is the state to set.
   *  @post new_state || !is_visited()
   *  @post !new_state || is_visited()
   */
  void set_visited(bool new_state);
  /** @} */

protected:
  size_t label_;    /**< the vertex label (unique in the graph)*/
  T item_;          /**< the data item associated to the vertex.*/
  bool is_visited_; /**< the visited flag.*/
};

/**
 * @brief Class to model the Edge of a Graph ADT.
 * An edge refers both a directed link u->v or an undirected link (u,v)
 *
 * @tparam T is the vertex's data type item.
 * @tparam E is the edge's data type item.
 *
 * @ingroup Graph
 */
template <class T, class E>
class Edge
{
public:
  /** @brief alias for a reference to a vertex.*/
  using VertexRef = typename Vertex<T>::Ref;

  /** @brief alias for a reference to an Edge.*/
  using Ref = std::shared_ptr<Edge<T, E>>;

  /** @name Lifecycle Makers*/
  /** @{*/

  /**
   * @brief Makes an edge.
   * @param[in] u,
   * @param[in] v are the edge's end (first, second if directed)
   * @param[in] item is the edge's data item.
   * @post first()==u
   * @post second()==v
   * @post has(u)
   * @post has(v)
   * @post other(u)==v
   * @post other(v)==u
   * @post item()==item
   * @post ! is_visited()
   */
  Edge(VertexRef u, VertexRef v, E const &item);

  ~Edge() {}

  /** @}*/

  /** @name Observers*/
  /** @{*/

  /**
   *  @brief Get edge's data item.
   */
  E const &item() const;

  /**
   * @brief Is the vertex visited?
   * @return true if the vertex is visited.
   */
  bool is_visited() const;

  /**
   *  @brief Is vertex u an end of this edge.
   * @param[in] u is the vertex to test.
   * @return true is @a u is one of the edge's ends.
   */
  bool has(VertexRef const &u) const;

  /**
   * @brief The other vertex end that is not u.
   * @param[in] u is one of the vertex ends.
   * @return the other vertex end that is not @a u.
   * @pre has(u)
   * @post has(retVal) and other(retVal)==u
   */
  VertexRef other(VertexRef const &u) const;

  /**
   * @brief the first vertex of the edge (u,v)
   * @return @a u.
   */
  const VertexRef &first() const;

  /** @brief the second vertex when af the edge (u,v).
   * @return @a v.
   */
  const VertexRef &second() const;

  /**@}*/

  /** @name Modifiers*/
  /** @{*/

  /**
   * @brief Set data saved in the vertex.
   * @param[in] v is the data to save in.
   * @post item()==v
   */
  void set_item(E const &v);

  /**
   *  @brief Set the flag visited
   *  @param new_state is the state to set.
   *  @post new_state || !is_visited()
   *  @post !new_state || is_visited()
   */
  void set_visited(bool new_state);

  /** @} */

protected:
  VertexRef u_;     /**< the first end.*/
  VertexRef v_;     /**< the second end.*/
  E item_;          /**< the data item associated to this edge.*/
  bool is_visited_; /**< the visited flag.*/
};

/**
 * @brief Models the Graph ADT.
 * @ingroup graph

 * @tparam T is the vertex's data type item.
 * It is assumed that T type defines a type T::key_t and
 * a method 'T::key_t T::key() const' return the key.
 * @tparam E is the edge's data type item.
 *
 * @invariant !is_empty() || size()==0
 * @invariant !is_full() || size()>=capacity()
 *
 */
template <class T, class E>
class Graph
{
public:
  /** @brief alias type for a reference to a graph's vertex. */
  using VertexRef = std::shared_ptr<Vertex<T>>;

  /** @brief alias type for a reference to a graph's edge. */
  using EdgeRef = std::shared_ptr<Edge<T, E>>;

  /** @name Makers*/
  /** @{*/

  /**
   * @brief Makes a Graph.
   * @post is_empty()
   * @post !is_directed || is_directed()
   * @post is_directed || !is_directed()
   */
  Graph(bool is_directed);

  /**
   * @brief Makes a Weighted graph from an input stream.
   *
   * FORMAT:
   *
   * 'DIRECTED'|'UNDIRECTED'
   * <NUM. NODES>
   * <NODE_0_ITEM>
   * ...
   * <NODE_N-1_ITEM>
   * <NUM_EDGES>
   * <U_KEY_0> <V_KEY_0> <WEIGHT_0>
   * ...
   * <U_KEY_num_edges-1> <V_KEY_num_edges-1> <WEIGHT_num_edges-1>
   *
   * @warning if the input graph is undirected, the edge (u,v) will be
   *          duplicated to make the edge (v, u).
   * @param in is the input stream.
   * @return a reference to the Graph.
   * @throw std::runtime_error("Wrong graph")
   */
  Graph(std::istream &input) noexcept(false);

  ~Graph() {}

  /** @}*/

  /** @name Observers*/
  /**@{*/

  /**
   * @brief is the graph empty?
   * @return true if there is not any vertex.
   * @pos !is_empty() or size()==0
   */
  bool is_empty() const;

  /**
   * @brief Is a directed graph?
   *
   * @return true if is a directed graph.
   */
  bool is_directed() const;

  /**
   * @brief Get current number of vertices.
   */
  size_t num_vertices() const;

  /**
   * @brief Get current number of edges.
   */
  size_t num_edges() const;

  /** @brief is u a vertex of this graph?
   * @pre u is not nullptr.
   * @return if its true.
   */
  bool has(VertexRef const &u) const;

  /**
   * @brief Is vertex u adjacent to vertex v?
   * A vertex u is adjacent to v if there is a directed edge u->v.
   * @param[in] u ,
   * @param[in] v are vertices.
   * @return true if there is a directed edge u->v.
   * @pre u and v are vertices of the graph.
   */
  bool is_adjacent(VertexRef const &u, VertexRef const &v) const;

  /**
   * @brief Get a vertex given its label.
   *
   * @param label is the vertex's label.
   * @return the vertex if a vertex with this label was found.
   * @post !ret_v || has(ret_v)
   */
  VertexRef vertex(size_t label) const;

  /**
   * @brief Is the vertex cursor valid?
   * @return true if the vertex cursor references to a valid vertex.
   */
  bool has_current_vertex() const;

  /**
   * @brief Get the current vertex.
   * @return a reference to the current vertex.
   * @pre has_current_vertex()
   */
  VertexRef current_vertex() const;

  /**
   * @brief Is the edge cursor valid?.
   * @return true if the edge cursor references a valid edge.
   * @post !ret_v || has_current_vertex()
   */
  bool has_current_edge() const;

  /**
   * @brief Get the weight of current edge.
   * @return a reference to the current edge.
   * @pre has_current_edge()
   * @post is_directed() && ret_v->first()==current_vertex()
   * @post !is_directed() && ret_v->has(current_vertex())
   */
  EdgeRef current_edge() const;

  /**
   * @brief Get the edge (u,v).
   * @param u,
   * @param v are the ends of the edge (first, second if the graph is directed).
   * @return a reference to the edge or nullptr if it doesn't exist.
   * @pre has(u)
   * @pre has(v)
   * @post ret_v->first()==u
   * @post ret_v->second()==v
   * @post ret_val->weight()==weight(u, v)
   */
  EdgeRef edge(VertexRef const &u, VertexRef const &v) const;

  /**
   * @brief Get the graph's vertices.
   *
   * @return a vector with the graph's vertices.
   */
  std::vector<VertexRef> vertices() const;

  /**
   * @brief Get the graph's edges.
   *
   * @return a vector with the graph's edges.
   */
  std::vector<EdgeRef> edges() const;

  /**
   * @brief Fold a weighted graph to an output stream.
   * When folding, the graph is always "DIRECTED".
   * @see constructor to get the grammar.
   * @param out is the output stream.
   * @return the output stream.
   */
  std::ostream &fold(std::ostream &out) const;

  /** @}*/

  /** @name Modifiers*/
  /** @{*/

  /** @name Graph editing */
  /** @{ */

  /**
   * @brief set the visited state for all the vertices and edges.
   */
  void reset(bool state);

  /**
   * @brief Add a new vertex.
   * @param[in] v is the data item to be save in the new vertex.
   * @post has_current_vertex()
   * @post ret_v == current_vertex()
   * @post ret_v->item()==v
   * @post !ret_v->is_visited()
   */
  VertexRef add_vertex(T const &v);

  /**
   * @brief Remove current vertex.
   * All the edges incident on current vertex will be removed also.
   * @pre has_current_vertex()
   * @post !has(old current_vertex())
   * @post num_vertices()==(old.num_vertices()-1)
   * @post !has_current_vertex()
   */
  void remove_vertex();

  /**
   * @brief Add a new edge.
   *
   * If the graph is directed, the edge will be the directed edge u->v and it means that u is adjacent to v.
   * If the graph is not directed, the edge (u,v) means both u is adjacent to v and v is adjacent to u.
   *
   * @param[in] u is the first end.
   * @param[in] v is the second end.
   * @param[in] weight is the edge's weight.
   * @return a reference to the added edge.
   * @pre !is_adjacent(u, v)
   * @post !is_directed() || is_adjacent( @a u, @a v)
   * @post is_directed() || (is_adjacent( @a u, @a v) && is_adjacent( @a v, @a u))
   * @post current_vertex() == u
   * @post current_edge()->second() == v
   * @post current_edge()->item() == item
   */
  EdgeRef add_edge(VertexRef const &u, VertexRef const &v, E const &item);

  /**
   * @brief Remove current edge.
   * @pre has_current_edge()
   * @post !has_current_edge()
   * @post !is_adjacent(old current_edge()->first(), old current_edge()->second())
   * @post is_directed() || !is_adjacent(old current_edge()->second(), old current_edge()->first())
   * @post num_edges()==(old num_edges()-1)
   */
  void remove_edge();

  /** @} */

  /** @name Cursor Management*/
  /** @{*/

  /**
   * @brief Goto to the first vertex.
   * @pre !is_empty().
   * @post !has_current_edge() || current_edge()->first() == current_vertex()
   */
  void goto_first_vertex();

  /**
   * @brief Goto to the first edge.
   * @pre has_current_vertex()
   * @post !has_current_edge() || current_edge()->first() == current_vertex()
   */
  void goto_first_edge();

  /**
   * @brief Move the cursor to the next vertex if there is.
   * The edge cursor is also affected.
   * @pre has_current_vertex().
   * @post !has_current_edge()||current_edge()->first() == current_vertex()
   */
  void goto_next_vertex();

  /**
   * @brief Move the cursor to the next edge with weight < inf.
   * @pre has_current_edge().
   * @post !has_current_edge()||current_edge()->first() == current_vertex()
   * @post !has_current_edge()||current_weight()<inf
   */
  void goto_next_edge();

  /**
   * @brief Move the cursor to a vertex.
   * @param[in] u is a vertex.
   * @pre has(u)
   * @post current_vertex()==u.
   * @post !has_current_edge() || current_edge()->first()==u
   */
  void goto_vertex(VertexRef const &u);

  /**
   * @brief Move the edge cursor.
   *
   * @param[in] v is the second end.
   *
   * @pre has_current_vertex()
   * @pre has(v)
   * @post !has_current_edge() || (!is_directed() || current_edge()->first() == current_vertex() )
   * @post !has_current_edge() || (!is_directed() || current_edge()->second() == @a v )
   * @post !has_current_edge() || (is_directed() || current_edge()->has( current_vertex() ))
   * @post !has_current_edge() || (is_directed() || current_edge()->has( @a v ))
   */
  void goto_edge(VertexRef const &v);

  /**
   * @brief Move the vertex and graph cursors.
   *
   * @param[in] u,
   * @param[in] v are vertices.
   *
   * @pre has(u)
   * @pre has(v)
   * @post !has_current_edge() || (!is_directed() || current_edge()->first() == @a u )
   * @post !has_current_edge() || (!is_directed() || current_edge()->second() == @a v )
   * @post !has_current_edge() || (is_directed() || current_edge()->has( @a u ))
   * @post !has_current_edge() || (is_directed() || current_edge()->has( @a v ))
   */
  void goto_edge(VertexRef const &u, VertexRef const &v);

  /**
   * @brief Move the vertex and graph cursors.
   * @param[in] e is the edge where moving cursors.
   * @pre has(e->fist())
   * @pre has(e->second())
   * @post current_vertex() == e->first()
   * @post !has_current_edge() || current_edge()->first() == e->first()
   * @post !has_current_edge() || current_edge()->second() == e->second()
   */
  void goto_edge(EdgeRef const &e);

  /**
   * @brief Move cursor to the first vertex with data item equal to key.
   * @param key is the data item to be found.
   * @return a reference to the vertex or nullptr if it doesn't exist.
   * @pre !is_empty()
   * @post ret_v==nullptr || has_current_vertex() && current_vertex()==ret_v
   * @post !has_current_vertex() || current_vertex()->item()==key
   * @post !has_current_edge() || current_edge()->first()==current_vertex()
   */
  VertexRef find_vertex(typename T::key_t const &key);

  /**
   * @brief Move cursor to the next vertex with data item equal to key.
   * @param key is the data item to be found.
   * @return a reference to the vertex or nullptr if it doesn't exist.
   * @pre !is_empty()
   * @post ret_v==nullptr || has_current_vertex() && current_vertex()==ret_v
   * @post !has_current_vertex() || current_vertex()->item()==key
   * @post !has_current_edge() || current_edge()->first()==current_vertex()
   */
  VertexRef find_next_vertex(typename T::key_t const &key);

  /** @} */

  /** @} */

protected:
  size_t next_label_;                                                    /**< you need a next label attribute to give unique labels to the new vertices.*/
  bool is_directed_;                                                     /**< is it a directed graph?*/
  using edges_list_t = std::list<EdgeRef>;                               /**< alias to define list of edges.*/
  using vertices_list_t = std::list<std::pair<VertexRef, edges_list_t>>; /**< alias to define pair of vertex and its incident edge list.*/
  vertices_list_t vertices_;                                             /**< the list of vertex and their incident edge lists.*/
  typename vertices_list_t::iterator curr_vertex_;                       /**< the vertex cursor.*/
  typename edges_list_t::iterator curr_edge_;                            /**< the edge cursor.*/
};

#include "graph_imp.hpp"
