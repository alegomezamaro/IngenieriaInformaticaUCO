cmake_minimum_required (VERSION 3.5)
project (graph-al VERSION 1.1 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb3")
include_directories(".")

add_library(graph STATIC city.hpp city.cpp)
link_libraries(graph)

add_executable(test_graph test_graph.cpp graph.hpp graph_imp.hpp item.hpp city.hpp city.cpp)
target_compile_definitions(test_graph PRIVATE -D__DEBUG__=1)



