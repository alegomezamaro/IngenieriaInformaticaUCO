/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <algorithm>
#include <limits>

#include "kdtree.hpp"

bool operator==(const Pattern &a, const Pattern &b)
{
    return a.class_label() == b.class_label() &&
           a.dim() == b.dim() &&
           (a.values() == b.values()).min();
}

KDTree::~KDTree()
{
}

bool KDTree::is_empty() const
{
    bool empty = true;
    // TODO

    empty = tree_.is_empty(); //Devuelve si el arbol esta vacio

    //
    return empty;
}

Pattern KDTree::item() const
{
    assert(!is_empty());
    Pattern ret_v;
    // TODO

    ret_v = tree_.item(); //Devuelve la raiz del arbol

    //
    return ret_v;
}

KDTree KDTree::left() const
{
    assert(!is_empty());
    KDTree ret_v;
    // TODO

    ret_v = KDTree(tree_.left(), k_); //Construimos un KDTree con el subárbol izquierdo y la dimensión actual
    
    //
    return ret_v;
}

KDTree KDTree::right() const
{
    assert(!is_empty());
    KDTree ret_v;
    // TODO

    ret_v = KDTree(tree_.right(), k_); //Construimos un KDTree con el subárbol izquierdo y la dimensión actual

    //
    return ret_v;
}

size_t
KDTree::get_k() const
{
    size_t k = 0;
    // TODO

    k = k_; //Devuelve la dimension del espacio

    //
    return k;
}

KDTree::KDTree()
{
    // TODO

    k_ = 0; //Inicializa la dimension del espacio
    tree_ = BTree<Pattern>(); //Inicializa el arbol

    //
    assert(is_empty());
}

KDTree::KDTree(const BTree<Pattern> &tree, size_t k)
{
    // TODO

    k_ = k; //Inicializa la dimension del espacio
    tree_ = tree; //Inicializa el arbol

    //
}

BTree<Pattern> KDTree::btree() const
{
    BTree<Pattern> ret_v;
    // TODO

    ret_v = tree_; //Devuelve el arbol

    //
    return ret_v;
}

void KDTree::set_btree(const BTree<Pattern> &new_tree)
{
    // TODO

    tree_ = new_tree; //Asigna un nuevo arbol

    //
}

void KDTree::set_k(size_t k)
{
    // TODO

    k_ = k; //Asigna la dimension del espacio

    //
    assert(get_k() == k);
}

/**
 * @brief Create a level of the kdtree object.
 *
 * Create a binary tree in a recursive way splitting each dimension into two
 * parts using the median as pivot and calling recursively for each part.
 * The pivot will be the root of the binary tree.
 *
 * @param begin is the an iterator at the begin of patterns seq.
 * @param end is the an iterator at the end of patterns seq.
 * @param level is the current level of this subtree.
 * @param k is the number of dimensions of the pattern's space.
 * @return a ref to the binary tree created of this level.
 */
static BTree<Pattern>
create_kdtree(std::vector<Pattern>::iterator begin,
              std::vector<Pattern>::iterator end,
              size_t level, size_t k)
{
    BTree<Pattern> btree;
    const size_t size = std::distance(begin, end);

    if (size > 0)
    {
        // TODO

        // First: locate the median pattern.
        // Hint: use a lambda to implement the pattern comparison algorithm.

        // Second: create the root of the binary tree with the median pattern.

        // Third: Set the left and right subtrees (if needed) by recursion using
        // the begin and end iterators to set the range of the patterns for each subtree.
        // Remember: increment the level parameter.

        auto med = begin + size / 2; //Calculamos la mediana
        std::nth_element(begin, med, end, [level, k](const Pattern &a, const Pattern &b) { //Creamos una lambda que compara los patrones
            return a.values()[level % k] < b.values()[level % k]; //Comparamos los valores de los patrones
        });

        btree.create_root(*med); //Creamos la raiz con la mediana
        btree.set_left(create_kdtree(begin, med, level + 1, k)); //Creamos el subarbol izquierdo
        btree.set_right(create_kdtree(med + 1, end, level + 1, k)); //Creamos el subarbol derecho

        //
    }
    return btree;
}

void KDTree::fit(std::vector<Pattern> &dataset)
{
    assert(dataset.size() > 0);
    // TODO
    // Hint: use the create_kdtree function to create the binary tree.

    assert(std::all_of(dataset.begin(), dataset.end(), [&dataset](const Pattern &p) { //Todos los patrones deben tener las mismas dimensiones
        return p.dim() == dataset[0].dim(); 
    }));

    set_k(dataset[0].dim()); //Establecemos la dimensión del espacio
    set_btree(create_kdtree(dataset.begin(), dataset.end(), 0, get_k())); //Construimos el árbol binario usando "create_kdtree"

    //
    assert(get_k() == dataset[0].dim());
}

KDTree::KDTree(std::vector<Pattern> &dataset)
{
    assert(dataset.size() > 0);
    // TODO
    // Hint: use the fit method.

    assert(std::all_of(dataset.begin(), dataset.end(), [&dataset](const Pattern &p) { //Comprobamos que todos los patrones tengan las mismas dimensiones
        return p.dim() == dataset[0].dim();
    }));

    set_k(dataset[0].dim()); //Establecemos la dimensión del espacio
    set_btree(create_kdtree(dataset.begin(), dataset.end(), 0, get_k())); //Construimos el árbol binario usando "create_kdtree"

    //
    assert(dataset.size() == 0 || !is_empty());
}

KDTree::KDTree(std::istream &in) noexcept(false)
    : KDTree()
{
    // TODO

    std::string k_str; //Variable para almacenar la dimension del espacio
    char c; //Variable para almacenar los caracteres leidos
    while (in.get(c) && c != ' ') { // Leer carácter por carácter hasta encontrar un espacio
        k_str += c;
    }

    if (k_str.empty() || !in) { // Validar si la lectura fue exitosa
        throw std::runtime_error("wrong input format");
    }

    size_t k; //Variable para almacenar la dimension del espacio 
    k = std::stoul(k_str); //Convertimos la dimension del espacio a entero
    BTree<Pattern> tree(in); //Creamos un arbol binario a partir de in

    if (!in) { //Si no se ha podido leer el arbol binario

        throw std::runtime_error("wrong input format");
    }

    set_k(k); // Establecer la dimensión del espacio
    set_btree(tree); // Establecer el árbol binario

    //
}

std::ostream &KDTree::fold(std::ostream &out) const
{
    // TODO

    std::string k_str = std::to_string(k_) + " "; //Convertimos la dimension del espacio a string
    out.write(k_str.c_str(), k_str.size()); //Escribimos la dimension del espacio
    tree_.fold(out); //Escribimos el arbol binario

    //
    return out;
}

std::tuple<float, Pattern>
KDTree::find_nn(Pattern const &p, const KDTree::distance_function_t &dist,
                size_t level) const
{
    // Which dimension is splitted here.
    size_t axis = level % p.dim();

    Pattern curr = item();
    float curr_dist = dist(p, curr);

    auto curr2 = curr;
    auto curr2_dist = curr_dist;

    // TODO: step 1: find candidate in the corresponding subtree.
    // Hint: use std::tie to set the return values to curr2 and curr2_dist.

    if (p.values()[axis] < curr.values()[axis]) { //Si el valor de p en el eje es menor que el valor de curr en el eje

        if (!left().is_empty()) { //Si el subarbol izquierdo no esta vacio

            std::tie(curr2_dist, curr2) = left().find_nn(p, dist, level + 1); //Buscamos el vecino más cercano en el subarbol izquierdo
        }
    }

    else { //Si no

        if (!right().is_empty()) { //Si el subarbol derecho no esta vacio

            std::tie(curr2_dist, curr2) = right().find_nn(p, dist, level + 1); //Buscamos el vecino más cercano en el subarbol derecho
        }
    }

    //

    // TODO: step 2: update the current candidate if needed.

    if (curr2_dist < curr_dist) { //Si la distancia del vecino más cercano del subarbol es menor que la distancia del vecino más cercano actual
        
        curr = curr2; //Actualizamos el vecino más cercano
        curr_dist = curr2_dist; //Actualizamos la distancia del vecino más cercano
    }

    //

    // TODO: step 3: find candidate in the other subtree or cut the search.

    float split_dist = std::abs(p.values()[axis] - item().values()[axis]); //Calculamos la distancia entre el valor de p en el eje y el valor de curr en el eje
    
    if (split_dist < curr_dist) { //Si la distancia entre p y curr es menor que la distancia del vecino más cercano actual

        if (p.values()[axis] < curr.values()[axis]) { //Si el valor de p en el eje es menor que el valor de curr en el eje

            if (!right().is_empty()) { //Si el subarbol derecho no esta vacio

                auto result = right().find_nn(p, dist, level + 1); //Buscamos el vecino más cercano en el subarbol derecho
                float other_dist = std::get<0>(result); //Obtenemos la distancia del vecino más cercano
                Pattern other = std::get<1>(result); //Obtenemos el vecino más cercano
                
                if (other_dist < curr_dist) { //Si la distancia del vecino más cercano del subarbol derecho es menor que la distancia del vecino más cercano actual
                    
                    curr = other; //Actualizamos el vecino más cercano
                    curr_dist = other_dist; //Actualizamos la distancia del vecino más cercano
                }
            }
        } 
        
        else { //Si no
            
            if (!left().is_empty()) { //Si el subarbol izquierdo no esta vacio

                float other_dist; //Variable para almacenar la distancia del vecino más cercano
                Pattern other; //Variable para almacenar el vecino más cercano
                std::tie(other_dist, other) = left().find_nn(p, dist, level + 1); //Buscamos el vecino más cercano en el subarbol izquierdo
                
                if (other_dist < curr_dist) { //Si la distancia del vecino más cercano del subarbol izquierdo es menor que la distancia del vecino más cercano actual
                    
                    curr = other; //Actualizamos el vecino más cercano
                    curr_dist = other_dist; //Actualizamos la distancia del vecino más cercano
                }
            }
        }
    }

    //

    // TODO: step 4: update the current candidate if needed.

    //

    return std::make_tuple(curr_dist, curr);
}

std::tuple<float, Pattern>
KDTree::find_nn(Pattern const &p, const KDTree::distance_function_t &dist) const
{
    assert(!is_empty());
    assert(p.dim() == get_k());
    return find_nn(p, dist, 0);
}
