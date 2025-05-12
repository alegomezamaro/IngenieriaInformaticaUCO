cmake_minimum_required(VERSION 3.10)
project(vector2d VERSION 1.1 LANGUAGES CXX)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_INIT "/W4")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "/Od /Zi /Zl /EHsc /DEBUG")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_INIT "-Wall")
    set(CMAKE_CXX_FLAGS_DEBUG_INIT "-O0 -ggdb3")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
enable_testing()
find_package(Python 3 COMPONENTS Interpreter)

add_executable(test_vector2d test_vector2d.cpp vector2d.hpp vector2d_imp.hpp)

add_test(NAME TestVector2D COMMAND ${Python_EXECUTABLE} run_tests.py ${CMAKE_CURRENT_BINARY_DIR}/$<$<BOOL:${WIN32}>:$<CONFIG>>/test_vector2d tests_vector2d WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
