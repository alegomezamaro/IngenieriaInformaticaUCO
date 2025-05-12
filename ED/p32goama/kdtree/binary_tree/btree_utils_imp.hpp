/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include <btree_utils.hpp>

template <class T>
int compute_height(const BTree<T> &t)
{
    int height = 0;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    if(t.is_empty()){ //Si el arbol esta vacio retornamos -1

        height = -1;
    }
    
    else { //Si el arbol no esta vacio

        height = 1 + std::max(compute_height(t.left()), compute_height(t.right())); //Calculamos la altura del arbol desarrollando por hijos
    }

    //
    return height;
}

template <class T>
size_t compute_size(const BTree<T> &t)
{
    size_t ret_val = 0;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    if(t.is_empty()){ //Si el arbol esta vacio retornamos -1

        ret_val = 0;
    }
    
    else { //Si el arbol no esta vacio

        ret_val = 1 + compute_size(t.left()) + compute_size(t.right()); //Calculamos la altura del arbol desarrollando por hijos
    }

    //
    return ret_val;
}

template <class T, typename Processor>
bool prefix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    if(!tree.is_empty()){ //Si el arbol no esta vacio

        retVal = p(tree.item()); //Procesamos el item
        retVal = retVal && prefix_process(tree.left(), p); //Procesamos el hijo izquierdo
        retVal = retVal && prefix_process(tree.right(), p); //Procesamos el hijo derecho
    }

    //
    return retVal;
}

template <class T, class Processor>
bool infix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    if(!tree.is_empty()){ //Si el arbol no esta vacio

        retVal = infix_process(tree.left(), p); //Procesamos el hijo izquierdo
        retVal = retVal && p(tree.item()); //Procesamos el item
        retVal = retVal && infix_process(tree.right(), p); //Procesamos el hijo derecho
    }

    //
    return retVal;
}

template <class T, class Processor>
bool postfix_process(const BTree<T> &tree, Processor &p)
{
    bool retVal = true;
    // TODO
    // Hint: when you call a template into other template maybe you need
    //  to specialize the call.

    if(!tree.is_empty()){ //Si el arbol no esta vacio

        retVal = postfix_process(tree.left(), p); //Procesamos el hijo izquierdo
        retVal = retVal && postfix_process(tree.right(), p); //Procesamos el item
        retVal = retVal && p(tree.item()); //Procesamos el hijo derecho
    }

    //
    return retVal;
}

template <class T, class Processor>
bool breadth_first_process(const BTree<T> &tree, Processor &p)
{
    bool go_on = true;
    // TODO
    // Hint: think about which data structure can help you to do this kind
    //   of traversal.

    std::queue<BTree<T>> q; //Creamos una cola de arboles
    q.push(tree); //Añadimos el arbol a la cola

    while (!q.empty() && go_on){ //Mientras la cola no este vacia y go_on sea true

        BTree<T> subtree = q.front(); //Obtenemos el primer elemento de la cola
        q.pop(); //Eliminamos el primer elemento de la cola

        if (!subtree.is_empty()){ //Si el arbol no esta vacio

            go_on = p(subtree.item());  //Procesamos el item
            q.push(subtree.left()); //Añadimos el hijo izquierdo
            q.push(subtree.right()); //Añadimos el hijo derecho
        }
    }

    //
    return go_on;
}

template <class T>
std::ostream &
print_prefix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a prefix_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    auto p = [&out] (T item) {out << item << " "; return true;}; //Creamos una lambda que imprime el item y retorna true
    prefix_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return out;
}

template <class T>
std::ostream &
print_infix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use an infix_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    auto p = [&out] (T item) {out << item << " "; return true;}; //Creamos una lambda que imprime el item y retorna true
    infix_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return out;
}

template <class T>
std::ostream &
print_postfix(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a postfix_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    auto p = [&out] (T item) {out << item << " "; return true;}; //Creamos una lambda que imprime el item y retorna true
    postfix_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return out;
}

template <class T>
std::ostream &
print_breadth_first(std::ostream &out, const BTree<T> &tree)
{
    // TODO
    // You must create a lambda function with a parameter to be printed and
    //   use a breadth_first_process to process the tree with this lambda.
    // Remember: the lambda must return true.

    auto p = [&out] (T item) {out << item << " "; return true;}; //Creamos una lambda que imprime el item y retorna true
    breadth_first_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return out;
}

template <class T>
bool search_prefix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the prefix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    auto p = [&count, &it] (T item) {count++; return it != item;}; //Creamos una lambda que compara el item con it y actualiza count
    found = !prefix_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return found;
}

template <class T>
bool search_infix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the infix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    auto p = [&count, &it] (T item) {count++; return it != item;}; //Creamos una lambda que compara el item con it y actualiza count
    found = !infix_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return found;
}

template <class T>
bool search_postfix(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the postfix_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    auto p = [&count, &it] (T item) {count++; return it != item;}; //Creamos una lambda que compara el item con it y actualiza count
    found = !postfix_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return found;
}

template <class T>
bool search_breadth_first(const BTree<T> &tree, const T &it, size_t &count)
{
    bool found = false;
    count = 0;
    // TODO
    // You must create a lambda function with a parameter to compare it to the
    //  value of the element to be searched for.
    //  Use the lambda with the breadth_first_process.
    // Remember: Also, the lambda must update the count variable and
    // must return True/False.

    auto p = [&count, &it] (T item) {count++; return it != item;}; //Creamos una lambda que compara el item con it y actualiza count
    found = !breadth_first_process<T>(tree, p); //Procesamos el arbol con la lambda

    //
    return found;
}

template <class T>
bool check_btree_in_order(const BTree<T> &tree)
{
    bool ret_val = true;
    // TODO
    // Hint: You can create a lambda function with a parameter to compare it with
    //  the last the value seen.
    //  Use the lambda with the infix_process.

    if (tree.is_empty()) { // Si el árbol está vacío

        ret_val = true; // Retornamos true a través de ret_val

    }
    else { // Si el árbol no está vacío

        T* item = nullptr; // Creamos un puntero a T
        auto p = [&item, &ret_val](T it) { // Lambda que compara el item con it y actualiza item

            if (item == nullptr){ // Si item es nulo

                item = new T(it); // Item será el nuevo item
            }

            else { //Si no es nulo

                if (*item < it){ //Si item es menor que it

                    *item = it; //Item = it
                } 
                
                else { //Si no cumple la condición, actualizamos ret_val

                    ret_val = false; 
                }
            }
            
            return ret_val; //Retornamos el estado actual de ret_val
        };

        ret_val = infix_process<T>(tree, p); //Procesamos el árbol con la lambda
    }

    //
    return ret_val;
}

template <class T>
bool has_in_order(const BTree<T> &tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    bool ret_val = false;
    // TODO

    if(!tree.is_empty()){ //Si no esta vacio

        if(v < tree.item()){ //Si v es menor que el item

            ret_val = has_in_order<T>(tree.left(), v); //Hacer el orden del hijo izquierdo
        }
        
        else if(v > tree.item()){ //Si v es mayor que el item

            ret_val = has_in_order<T>(tree.right(), v); //Hacer el orden del hijo derecho
        }
        
        else{ //Si no se cumple ninguna de las condiciones anteriores

            ret_val = true; //Retornamos true
        }
    }

    //
    return ret_val;
}

template <class T>
void insert_in_order(BTree<T> &&tree, T const &v)
{
    assert(check_btree_in_order<T>(tree));
    // TODO

    if (tree.is_empty()){ //Si el arbol esta vacio

        tree.create_root(v); //Creamos la raiz con el valor v
    }

    else if (v < tree.item()){ //Si v es menor que el item

        if (tree.left().is_empty()){ //Si el hijo izquierdo esta vacio

            tree.set_left(BTree<T> (v)); //Creamos el hijo izquierdo con el valor v
        }

        else{

            insert_in_order(tree.left(), v); //Insertamos el orden del hijo izquierdo
        }
    }

    else if (v > tree.item()){ //Si v es mayor que el item

        if (tree.right().is_empty()){ //Si el hijo derecho esta vacio

            tree.set_right(BTree<T> (v)); //Creamos el hijo derecho con el valor v
        }

        else{

            insert_in_order(tree.right(), v); //Insertamos el orden del hijo derecho
        }
    }

    //
    assert(has_in_order<T>(tree, v));
}

template <class T>
void insert_in_order(BTree<T> &tree, T const &v)
{
    insert_in_order(std::move(tree), v);
}