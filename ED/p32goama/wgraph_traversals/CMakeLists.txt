cmake_minimum_required (VERSION 3.5)
project (graph_traversals VERSION 1.3 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
include_directories(".")

add_subdirectory(graph)
include_directories("graph")

add_executable(test_traversals test_traversals.cpp wgraph_traversals.hpp wgraph_traversals_imp.hpp
    prim_algorithm.hpp prim_algorithm_imp.hpp
    kruskal_algorithm.hpp kruskal_algorithm_imp.hpp disjointsets.hpp)
target_link_libraries(test_traversals graph)
target_compile_definitions(test_traversals PRIVATE -D__VERBOSE__=1)

