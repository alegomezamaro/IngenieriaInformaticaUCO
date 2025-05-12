/**
 * @file test_graph.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>

#include "graph.hpp"
#include "item.hpp"
#include "city.hpp"

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file(argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }

        std::shared_ptr<Graph<Char, float>> graph = nullptr;
        std::vector<Vertex<Char>::Ref> vertices(10);
        std::vector<Edge<Char, float>::Ref> edges(10);
        size_t e_label = 0;

        std::cout << std::unitbuf;

        std::string buffer;
        std::istringstream input;
        while (std::getline(input_file, buffer))
        {
            input.str(buffer);
            input.clear();
            std::string command;

            input >> command;
            if (!input || command == "" || command[0] == '#')
                continue;

            if (command == "VERTEX_CREATE")
            {
                size_t label;
                Char data;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Creating a vertex with label " << label << " ... ";
                vertices[label] = std::make_shared<Vertex<Char>>(label, data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "VERTEX_PRINT")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Vertex with label "
                          << vertices[label]->label()
                          << " visited flag: " << (vertices[label]->is_visited() ? "T" : "F")
                          << " data: '" << vertices[label]->item()
                          << "' data key: '" << vertices[label]->key() << "'."
                          << std::endl;
            }
            else if (command == "VERTEX_SET_VISITED")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                bool is_visited;
                if (!(input >> is_visited))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting visited flag of vertex with label "
                          << label << " to " << (is_visited ? "T" : "F")
                          << " ...";
                vertices[label]->set_visited(is_visited);
                std::cout << "ok." << std::endl;
            }
            else if (command == "VERTEX_SET_ITEM")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                Char data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting item of vertex with label "
                          << label << " to '" << data
                          << "' ...";
                vertices[label]->set_item(data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "EDGE_CREATE")
            {
                size_t e_label, u_label, v_label;
                if (!(input >> e_label >> u_label >> v_label))
                    throw std::runtime_error("Wrong command");
                float data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Creating edge " << e_label << " connecting "
                          << " vertices (" << u_label << "," << v_label
                          << ") with data " << data << " ...";
                edges[e_label] = std::make_shared<Edge<Char, float>>(vertices[u_label], vertices[v_label], data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "EDGE_PRINT")
            {
                size_t e_label;
                if (!(input >> e_label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Edge " << e_label << " connecting vertices ("
                          << edges[e_label]->first()->label() << ","
                          << edges[e_label]->second()->label() << ")"
                          << ", visited flag: " << (edges[e_label]->is_visited() ? "T" : "F")
                          << ", data: " << edges[e_label]->item() << std::endl;
            }
            else if (command == "EDGE_SET_VISITED")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                bool is_visited;
                if (!(input >> is_visited))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting visited flag of edge with label "
                          << label << " to " << (is_visited ? "T" : "F")
                          << " ...";
                edges[label]->set_visited(is_visited);
                std::cout << "ok." << std::endl;
            }
            else if (command == "EDGE_SET_ITEM")
            {
                size_t label;
                if (!(input >> label))
                    throw std::runtime_error("Wrong command");
                float data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Setting item of edge with label "
                          << label << " to '" << data << "' ...";
                edges[label]->set_item(data);
                std::cout << "ok." << std::endl;
            }
            else if (command == "GRAPH_CREATE")
            {
                bool directed;
                if (!(input >> directed))
                    throw std::runtime_error("Wrong command");
                std::cout << "Creating "
                          << (directed ? "a directed" : "an undirected")
                          << " graph ... ";
                graph = std::make_shared<Graph<Char, float>>(directed);
                std::cout << " ok." << std::endl;
            }
            else if (command == "IS_DIRECTED")
            {
                std::cout << "Is a directed graph? "
                          << (graph->is_directed() ? "Y" : "N") << std::endl;
            }
            else if (command == "IS_EMPTY")
            {
                std::cout << "Is the graph empty? "
                          << (graph->is_empty() ? "Y" : "N") << std::endl;
            }
            else if (command == "NUM_VERTICES")
            {
                std::cout << "Number of vertices: "
                          << graph->num_vertices() << std::endl;
            }
            else if (command == "NUM_EDGES")
            {
                std::cout << "Number of edges: "
                          << graph->num_edges() << std::endl;
            }
            else if (command == "ADD_VERTEX")
            {
                Char data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Adding vertex with data item: '" << data
                          << "' ... ";
                auto vertex = graph->add_vertex(data);
                vertices[vertex->label()] = vertex;
                std::cout << "ok." << std::endl;
            }
            else if (command == "PRINT_CURRENT_VERTEX")
            {
                if (graph->has_current_vertex())
                {
                    auto vertex = graph->current_vertex();
                    std::cout << "Current vertex with label "
                              << vertex->label()
                              << " visited flag: " << (vertex->is_visited() ? "T" : "F")
                              << " data: '" << vertex->item()
                              << "' data key: '" << vertex->key() << "'."
                              << std::endl;
                }
                else
                    std::cout << "Current vertex doesn't exist." << std::endl;
            }
            else if (command == "ADD_EDGE")
            {
                size_t u_label, v_label;
                if (!(input >> u_label >> v_label))
                    throw std::runtime_error("Wrong command");
                float data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                std::cout << "Adding edge " << e_label << " for vertices ('"
                          << vertices[u_label]->item() << "','"
                          << vertices[v_label]->item() << "') with data item: '" << data
                          << "' ... ";
                auto edge = graph->add_edge(vertices[u_label], vertices[v_label], data);
                edges[e_label++] = edge;
                std::cout << "ok." << std::endl;
            }
            else if (command == "PRINT_CURRENT_EDGE")
            {
                if (graph->has_current_edge())
                {
                    auto edge = graph->current_edge();
                    std::cout << "Current edge ('"
                              << edge->first()->item() << "','"
                              << edge->second()->item()
                              << "'), visited flag: " << (edge->is_visited() ? "T" : "F")
                              << ", data: " << edge->item()
                              << std::endl;
                }
                else
                    std::cout << "Current edge doesn't exist." << std::endl;
            }
            else if (command == "GOTO_VERTEX")
            {
                size_t u_label;
                if (!(input >> u_label))
                    throw std::runtime_error("Wrong command 'GOTO_VERTEX'");
                std::cout << "Moving cursor to vertex '"
                          << vertices[u_label]->item() << "' ...";
                graph->goto_vertex(vertices[u_label]);
                std::cout << " ok." << std::endl;
            }
            else if (command == "GOTO_EDGE")
            {
                size_t u_label, v_label;
                if (!(input >> u_label >> v_label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Moving cursor to edge ('"
                          << vertices[u_label]->item() << "','"
                          << vertices[v_label]->item() << "') ...";
                graph->goto_edge(vertices[u_label], vertices[v_label]);
                std::cout << " ok." << std::endl;
            }
            else if (command == "GOTO_EDGE2")
            {
                size_t edge_label;
                if (!(input >> edge_label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Moving cursor to edge "
                          << edge_label << ": ";
                graph->goto_edge(edges[edge_label]);
                std::cout << " u: " << graph->current_vertex()->item()
                          << " v: " << graph->current_edge()->second()->item()
                          << std::endl;
            }
            else if (command == "PRINT_VERTICES")
            {
                std::cout << "Vertices: ";
                graph->goto_first_vertex();
                while (graph->has_current_vertex())
                {
                    std::cout << " '" << graph->current_vertex()->item()
                              << "'";
                    graph->goto_next_vertex();
                }
                std::cout << std::endl;
            }
            else if (command == "PRINT_INCIDENT_EDGES")
            {
                std::cout << "Edges incident in current vertex: ";
                graph->goto_first_edge();
                while (graph->has_current_edge())
                {
                    std::cout << " ('"
                              << graph->current_edge()->first()->item()
                              << "','"
                              << graph->current_edge()->second()->item()
                              << "')";
                    graph->goto_next_edge();
                }
                std::cout << std::endl;
            }
            else if (command == "IS_ADJACENT")
            {
                size_t u_label, v_label;
                if (!(input >> u_label >> v_label))
                    throw std::runtime_error("Wrong command");
                std::cout << "Is adjacent the vertex '"
                          << vertices[u_label]->item()
                          << "' to vertex '"
                          << vertices[v_label]->item()
                          << "' ?: "
                          << (graph->is_adjacent(vertices[u_label], vertices[v_label]) ? "Y" : "N")
                          << std::endl;
            }
            else if (command == "GOTO_FIRST_VERTEX")
            {
                std::cout << "Moving cursor to first vertex ...";
                graph->goto_first_vertex();
                std::cout << " ok." << std::endl;
            }
            else if (command == "GOTO_NEXT_VERTEX")
            {
                std::cout << "Moving cursor to next vertex ...";
                graph->goto_next_vertex();
                std::cout << " ok." << std::endl;
            }
            else if (command == "FIND_VERTEX")
            {
                char key;
                if (!(input >> key))
                    throw std::runtime_error("Wrong command");
                std::cout << "Finding vertex with key '" << key << "' ... ";
                auto vertex = graph->find_vertex(key);
                std::cout << (vertex ? " found." : " didn't found.") << std::endl;
            }
            else if (command == "FIND_NEXT_VERTEX")
            {
                char key;
                if (!(input >> key))
                    throw std::runtime_error("Wrong command");
                std::cout << "Finding next vertex with key '" << key << "' ... ";
                auto vertex = graph->find_next_vertex(key);
                std::cout << (vertex ? " found." : " didn't found.") << std::endl;
            }
            else if (command == "RESET")
            {
                bool state;
                if (!(input >> state))
                    throw std::runtime_error("Wrong command");
                std::cout << "Reseting visited flags to " << (state ? "T" : "F")
                          << " ... ";
                graph->reset(state);
                std::cout << " ok." << std::endl;
            }
            else if (command == "CHECK_VISITED")
            {
                std::cout << "Checking visited flags:" << std::endl;
                graph->goto_first_vertex();
                while (graph->has_current_vertex())
                {
                    std::cout << "\tVertex '" << graph->current_vertex()->key() << "':"
                              << (graph->current_vertex()->is_visited() ? "T" : "F")
                              << " incident edges:";
                    while (graph->has_current_edge())
                    {
                        auto e = graph->current_edge();
                        std::cout << " (" << e->first()->key() << ','
                                  << e->second()->key() << "):"
                                  << (e->is_visited() ? "T" : "F");
                        graph->goto_next_edge();
                    }
                    std::cout << std::endl;
                    graph->goto_next_vertex();
                }
            }
            else if (command == "FOLD")
            {
                std::cout << "Folding graph ... " << std::endl;
                graph->fold(std::cout);
                std::cout << std::endl;
            }
            else if (command == "UNFOLD")
            {
                std::cout << "unfolding graph ... ";
                try
                {
                    graph = std::make_shared<Graph<Char, float>>(input_file);
                    std::cout << " ok." << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "STRING")
            {
                std::cout << "unfolding a graph<String, float> ... ";
                try
                {
                    Graph<String, float> g(input_file);
                    std::cout << " ok." << std::endl;
                    g.fold(std::cout);
                    std::cout << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "INTEGER")
            {
                std::cout << "unfolding a graph<Int, float> ... ";
                try
                {
                    Graph<Int, float> g(input_file);
                    std::cout << " ok." << std::endl;
                    g.fold(std::cout);
                    std::cout << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "CITY")
            {
                std::cout << "unfolding a graph<City, float> ... ";
                try
                {
                    Graph<City, float> g(input_file);
                    std::cout << " ok." << std::endl;
                    g.fold(std::cout);
                    std::cout << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    std::cout << "runtime error: '" << e.what() << "'." << std::endl;
                }
            }
            else if (command == "VERTICES_VECTOR")
            {
                auto vertices = graph->vertices();
                std::cout << "Vertices:";
                for (auto &v : vertices)
                    std::cout << ' ' << v->key();
                std::cout << std::endl;
            }
            else if (command == "EDGES_VECTOR")
            {
                auto edges = graph->edges();
                std::cout << "Edges:";
                for (auto &e : edges)
                    std::cout << ' ' << e->first()->key() << ':' << e->second()->key();
                std::cout << std::endl;
            }
            else if (command == "REMOVE_CURRENT_VERTEX")
            {
                std::cout << "Removing current vertex '" << graph->current_vertex()->key()
                          << "' ...";
                graph->remove_vertex();
                std::cout << " ok." << std::endl;
            }
            else if (command == "REMOVE_CURRENT_EDGE")
            {
                std::cout << "Removing current edge '"
                          << graph->current_edge()->first()->key() << "':'"
                          << graph->current_edge()->second()->key()
                          << "' ...";
                graph->remove_edge();
                std::cout << " ok." << std::endl;
            }
            else
            {
                std::cerr << "Error: command unknown '" << command << "'." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch (...)
    {
        std::cerr << "Caught unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
