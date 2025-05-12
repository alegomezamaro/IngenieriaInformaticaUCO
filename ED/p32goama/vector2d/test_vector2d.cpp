/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "vector2d.hpp"

int main(int argc, const char *argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        std::cout.setf(std::ios::unitbuf); // unbuffering output.

        if (argc != 2)
        {
            std::cerr << "Usage: test_slist test_case" << std::endl;
            return EXIT_FAILURE;
        }
        std::string filename = argv[1];

        std::ifstream input(argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open input filename '" << argv[1]
                      << "'." << std::endl;
            return EXIT_FAILURE;
        }
        std::vector<Vector2D<float>> vectors(5);

        while (input)
        {
            std::string operation;
            input >> operation;
            if (input)
            {
                if (operation == "CREATE_ZERO_VECTOR")
                {
                    int idx;
                    input >> idx;
                    std::cout << "Creating zero vector " << idx << " ... ";
                    vectors[idx] = Vector2D<float>();
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "CREATE_VECTOR")
                {
                    int idx;
                    input >> idx;
                    float x, y;
                    input >> x >> y;
                    std::cout << "Creating vector " << idx << " ... ";
                    vectors[idx] = Vector2D<float>(x, y);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "SET_X")
                {
                    int idx;
                    input >> idx;
                    float x;
                    input >> x;
                    std::cout << "Setting " << x << " as x ordinate to vector "
                              << idx << " ... ";
                    vectors[idx].set_x(x);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "SET_Y")
                {
                    int idx;
                    input >> idx;
                    float y;
                    input >> y;
                    std::cout << "Setting " << y << " as y ordinate to vector "
                              << idx << " ... ";
                    vectors[idx].set_y(y);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "ADD")
                {
                    int idx1, idx2;
                    input >> idx1 >> idx2;
                    std::cout << "Adding vector " << idx1 << " to vector "
                              << idx2 << " ... ";
                    vectors[idx2].add(vectors[idx1]);
                    std::cout << "ok." << std::endl;
                }
                else if (operation == "PRINT")
                {
                    int idx;
                    input >> idx;
                    std::cout << "Vector " << idx << " [" << vectors[idx].x()
                              << ',' << vectors[idx].y() << "]" << std::endl;
                }
                else
                {
                    std::cerr << "Error: operation not found '"
                              << operation << "'." << std::endl;
                    return EXIT_FAILURE;
                }
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
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}
