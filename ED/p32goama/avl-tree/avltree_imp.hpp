/**
 * @file avltree_imp.hpp
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
#include <numeric>
#include <functional>
#include <limits>
#include <vector>
#include <algorithm>
#include <avltree.hpp>

template <class T>
AVLTree<T>::AVLTree()
{
    // TODO

    root_=nullptr; 
    current_=nullptr;
    parent_.reset();
    size_=0;
    height_=-1;

    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(is_empty());
    assert(!current_exists());
#ifndef __ONLY_BSTREE__
    assert(height() == -1);
#endif
}

template <class T>
AVLTree<T>::AVLTree(T const &item)
{
    // TODO

    current_= AVLTNode<T>::create(item); //Crear un nuevo nodo con el valor item.
    root_=current_; //Asignar el nodo raíz al nodo actual.
    parent_=nullptr; //Asignar el nodo padre a nullptr.
    size=1; //Asignar el tamaño del árbol a 1.
    height_=0; //Asignar la altura del árbol a 0.

    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item() == item);
    assert(current_exists());
    assert(current() == item);
#ifndef __ONLY_BSTREE__
    assert(current_level() == 0);
    assert(height() == 0);
#endif
}

template <class T>
AVLTree<T>::AVLTree(std::istream &in) noexcept(false)
{
    // TODO

    std::string token; //Variable para almacenar el token leído.
    in >> token; //Leer el token del flujo de entrada.

    if (token == "["){ //Si el token es "[", significa que hay un nodo raíz.

        T value; //Variable para almacenar el valor del nodo raíz.
        in >> value; //Leer el valor del nodo raíz.
        create_root(value); //Crear el nodo raíz con el valor leído.
        auto lefttree=AVLTree<T>(in); //Crear el subárbol izquierdo.
        set_left(lefttree); //Asignar el subárbol izquierdo al nodo raíz.
        auto righttree=AVLTree<T>(in); //Crear el subárbol derecho.
        set_right(righttree); //Asignar el subárbol derecho al nodo raíz.
        in >> token; //Leer el siguiente token.

        if (token != "]"){ //Si el token no es "]" error.

            throw std::runtime_error("Wrong input format.");
        }
    }

    else if (token != "[]"){ //Si el token no es "[]", error.

        throw std::runtime_error("Wrong input format.");
    }
    
    //

    if (!is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (!is_a_balanced_tree())
        throw std::runtime_error("It is not an avl tree");
}

template <class T>
AVLTree<T>::~AVLTree()
{
    // TODO
    // Think if it is necessary to do something here regarding your representation.

    //No es necesario hacer nada aquí, ya que el destructor de AVLTNode se encargará de liberar la memoria.

    //
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create an perfectly balanced BSTree by inserting the median of
 *        an ordered sub sequence data[begin, end).
 * @param data is the ordered sequence of values.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of array data to use.
 * @pre 0 <= begin <= end <=data.size()
 * @pre begin==end || data[begin]<data[end];
 */
template <class T>
void create_inserting_median(std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             AVLTree<T> &tree)
{
    assert(begin <= end);
    assert(end <= data.size());
    assert(begin == end || data[begin] <= data[end - 1]);

    // TODO
    // Hint: if (end==begin) none thing must be done (it is an empty sub array)
    //  else, insert the median in the tree and (recursively) process
    //  the two sub sequences [begin, median_idx) and [median_idx+1, end)

    if (end != begin){ //Si el subárbol no está vacío, insertar el valor medio en el árbol.

        size_t median_idx = (int) begin + (end-begin)/2; //Calcular el índice medio.
        tree.insert(data.at(median_idx)); //Insertar el valor medio en el árbol.
        create_inserting_median(data, begin, median_idx, tree); //Recursividad para insertar el subárbol izquierdo.
        create_inserting_median(data, median_idx + 1, end, tree); //Recursividad para insertar el subárbol derecho.
    }
    //
}

template <class T>
AVLTree<T>
create_perfectly_balanced_bstree(std::vector<T> &data)
{
    AVLTree<T> tree;
    // TODO
    // Remember: the empty tree is perfectly balanced.
    // Remember: first, an ordered sequence (using < order) of values is needed.
    // Then you should use the above create_inserting_median function
    // on a empty tree to recursively create the perfectly balanced bstree.

    tree = AVLTree<T>(); //Crear un nuevo árbol vacío.
    std::sort(data.begin(), data.end()); //Ordenar el vector de datos.
    create_inserting_median(data, 0, data.size(), tree); //Insertar el valor medio en el árbol.
    //
    return tree;
}
#endif //__ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty() const
{
    // TODO

    return root_ == nullptr; //Si la raíz es nula, el árbol está vacío.
    //
}

template <class T>
T const &AVLTree<T>::item() const
{
    assert(!is_empty());
    // TODO: fixme

    return root_->item(); //Retornar el valor del nodo raíz.
    //
}

template <class T>
std::ostream &AVLTree<T>::fold(std::ostream &out) const
{
    // TODO

    if(is_empty()){ //Si el árbol está vacío, imprimir "[]".
    
        out << "[]";
    }
    else{ //Sino

        out << "[ " << item() << " "; //Imprimir el valor del nodo raíz.
        left().fold(out); //Imprimir el subárbol izquierdo.
        out << " "; 
        right().fold(out); //Imprimir el subárbol derecho.
        out << " ]"; //Cerrar el corchete.
    }

    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    // TODO

    return current_ != nullptr; //Si el nodo actual no es nulo, retornar true.
    //
}

template <class T>
T const &AVLTree<T>::current() const
{
    assert(current_exists());
    // TODO: fixme

    return current_->item(); //Retornar el valor del nodo actual.
    //
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    // TODO

    auto node = current_->parent(); //Asignar el nodo actual a una variable temporal.
    
    while (node != nullptr){ //Mientras el nodo padre no sea nulo.
        
        node = node->parent(); //Asignar el nodo padre a la variable temporal.
        level++; //Incrementar el nivel.
    }    

    //
    return level;
}

template <class T>
AVLTree<T> AVLTree<T>::left() const
{
    assert(!is_empty());
    AVLTree<T> subtree;
    // TODO
    // Hint: use the private AVLTree constructor given a node as root.

    subtree = AVLTree<T>(root_->left()); //Asignar el nodo izquierdo a la subárbol.
    //
    return subtree;
}

template <class T>
AVLTree<T> AVLTree<T>::right() const
{
    assert(!is_empty());
    AVLTree<T> subtree;
    // TODO
    // Hint: use the private AVLTree constructor given a node as root.

    subtree = AVLTree<T>(root_->right()); //Asignar el nodo derecho a la subárbol.
    //
    return subtree;
}

template <class T>
size_t AVLTree<T>::size() const
{
    size_t s = 0;
    // TODO
        
        if (!is_empty()){ //Si el nodo no es nulo, contar los nodos.

            s = right().size() + left().size() + 1; //Contar los nodos del subárbol izquierdo y derecho.
        }
    //
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = 0;
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: we want O(1) here.

    h = height_; //Asignar la altura del árbol a la variable h.

    if (is_empty()){ //Si el árbol está vacío, la altura es -1.

        h = -1; 
    }
    else{ //Sino

        h = root_->height(); //Asignar la altura del nodo raíz a la variable h.
    }
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
    int bf = 0;
    // TODO
    // Remember: this operation is only necessary for the AVLTree.

    if (root_ != nullptr) { //Si root existe
                int left_height, right_height;
                if(root_->left()){
                    left_height=root_->left()->height();
                }
                else{
                    left_height=-1;
                }
                if(root_->right()){
                    right_height=root_->right()->height();
                }
                else{
                    right_height=-1;
                }
                bf = left_height - right_height; //Devolvemos factor izquierdo menos factor derecho
            }
    //
    return bf;
}

template <class T>
bool AVLTree<T>::has(const T &k) const
{
#ifndef NDEBUG
    bool old_current_exists = current_exists();
    T old_current;
    if (old_current_exists)
        old_current = current();
#endif

    bool found = true;

    // TODO
    // Hint: you can reuse the search method for this but in this case you will
    //       need to use "const_cast" to remove constness of "this" and
    //       save/restore the old state of current before returning.

    auto actual_= current_; // Guardamos el nodo actual
    found= const_cast<AVLTree<T> *>(this)->search(k); // Buscamos el elemento k en el árbol
    const_cast<AVLTree<T> *>(this)->set_current_node(actual_); // Restauramos el nodo actual
    
    //

#ifndef NDEBUG
    assert(!old_current_exists || old_current == current());
#endif
    return found;
}

/**
 * @brief infix process of a node.
 * The Processor must allow to be used as a function with a parameter  (the
 * item to be processed) and returning true if the process must continue or
 * false if not.
 * @param node is the node to be processed.
 * @param p is the Processor.
 * @return true if all the tree was in-fix processed.
 */
template <class T, class Processor>
bool infix_process(typename AVLTNode<T>::Ref node, Processor &p)
{
    bool retVal = true;
    // TODO
    // Remember: if node is nullptr return true.

    if (node == nullptr){  //Si el nodo es nulo, retornar true.

        return true;
    }
    
    else { //Sino
        retVal= infix_process<T, Processor>(node->left(), p); //Recursividad para procesar el subárbol izquierdo.
        retVal= retVal && p(node->item()); //Procesar el nodo actual.
        retVal= retVal && infix_process<T, Processor>(node->right(), p); //Recursividad para procesar el subárbol derecho.
    }
    //
    return retVal;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    // TODO
    // Remember: a empty tree is a binary search tree.
    //
    // Remember: for a non empty binary search tree, the in-fix traversal from
    // the root node must follow an ordered sequence of items.
    //
    // Remember: use a lambda function with signature '(T v) -> bool' to
    //  implement the Processor.
    //

    T last = T{}; //Variable para almacenar el último valor procesado.

    auto lambda = [&last](T item){ //Procesar el nodo actual.

        if (item > last || last == T{}){ //Si el valor actual es mayor que el último valor procesado o el último valor procesado es nulo, asignar el valor actual al último valor procesado.

            last = item; //Asignar el valor actual al último valor procesado.
            return true;
        } 

        return false; 
    };

    is_bst = infix_process<T>(root_node(), lambda); //Recursividad para procesar el árbol en orden.
    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
    bool is_balanced = true;
#ifndef __ONLY_BSTREE__
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: a empty tree is balanced.
    //
    // Remember: A non empty tree is balanced if both children are balanced
    // and the absolute value of the balance factor of the tree is less or
    // equal to one.

    if (root_ != nullptr){ //Si la raíz no es nula, calcular el factor de equilibrio.

        is_balanced = std::abs(root_->balance_factor()) <= 1; //Calcular el factor de equilibrio.
    }
    //
#endif
    return is_balanced;
}

template <class T>
void AVLTree<T>::create_root(T const &v)
{
    assert(is_empty());
    // TODO

    root_ = AVLTNode<T>::create(v); //Crear un nuevo nodo con el valor v.
    current_ = root_; //Asignar el nodo raíz al nodo actual.
    parent_ = nullptr; //Asignar el nodo padre a nullptr.
    height_ = 0; //Asignar la altura del árbol a 0.

    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item() == v);
    assert(current_exists());
    assert(current() == v);
#ifndef __ONLY_BSTREE__
    assert(current_level() == 0);
    assert(height() == 0);
#endif
}

template <class T>
bool AVLTree<T>::search(T const &k)
{
    bool found = false;
    // TODO

    auto node = root_node(); //Asignar la raíz del árbol a una variable temporal.
    set_current_node(nullptr); //Asignar el nodo actual a nullptr.

    while (node != nullptr) { //Mientras el nodo no sea nulo, buscar el valor k.
    
        if (k == node->item()) { //Si el valor k es igual al valor del nodo actual, asignar el nodo actual a la variable found.
    
            set_current_node(node); //Asignar el nodo actual al nodo encontrado.
            found = true; //Asignar el valor encontrado a true.
            break; //Salir del bucle.
        } 
        
        else if (k < node->item()) { //Si el valor k es menor que el valor del nodo actual, buscar en el subárbol izquierdo.
        
            set_parent_node(node); //Asignar el nodo padre al nodo actual.
            node = node->left(); //Asignar el subárbol izquierdo al nodo actual.
        } 
        
        else { //Sino
        
            set_parent_node(node); //Asignar el nodo padre al nodo actual. 
            node = node->right(); //Asignar el subárbol derecho al nodo actual.
        }
    }
    //
    assert(!found || current() == k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const &k)
{
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    if (!search(k))
    {
        // TODO

        current_ = AVLTNode<T>::create(k); //Crear un nuevo nodo con el valor k.

        if (parent_ == nullptr) { //Si el nodo padre es nulo, asignar el nodo actual a la raíz.

            root_ = current_; //Asignar el nodo raíz al nodo actual.
            current_->set_parent(nullptr); //Asignar el nodo padre a nullptr.
        }
        
        else { //Sino

            current_->set_parent(parent_); //Asignar el nodo padre al nodo actual.

            if (parent_->item() > k) { //Si el valor del nodo padre es mayor que el valor k, asignar el subárbol izquierdo al nodo padre.

                parent_->set_left(current_); //Asignar el subárbol izquierdo al nodo padre.
            }
            
            else { //Sino

                parent_->set_right(current_); //Asignar el subárbol derecho al nodo padre.
            }
        }
        height_ = std::max(height_, current_level());
        size_++;
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
    }
    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    // check postconditions.
    assert(current_exists());
    assert(current() == k);
}

template <class T>
void AVLTree<T>::remove()
{
    // check preconditions.
    assert(current_exists());

#ifndef NDEBUG
    // the invariants only must be checked for the first recursive call.
    // We use a static variable to count the recursion levels.
    // see section "Static variables in a Function" in
    // ref https://www.geeksforgeeks.org/static-keyword-cpp/ for more info.
    static int recursion_count = 0;
    recursion_count++;
    if (recursion_count == 1)
    {
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());
    }
#endif // NDEBUG

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    // TODO
    //  Check which of cases 0,1,2,3 we have (see theory class slides).

    if (current_->left() == nullptr && current_->right() == nullptr) { //Caso 0: El nodo no tiene hijos.
        
        subtree = nullptr;
    }
    
    else if (current_->left() == nullptr) { //Caso 1: El nodo tiene solo un hijo derecho.

        subtree = current_->right();
    }
    
    else if (current_->right() == nullptr) { //Caso 2: El nodo tiene solo un hijo izquierdo.

        subtree = current_->left();
    }
    
    else { //Caso 3: El nodo tiene dos hijos.

        replace_with_subtree = false;
    }
    //

    if (replace_with_subtree)
    {
        // TODO
        // Manage cases 0,1,2
        // Remember: update subtree to parent links too.

        if (parent_ == nullptr){ //Caso 0: El nodo no tiene hijos.

            root_ = subtree;
        }
        
        else if (parent_->right() == current_){ //Caso 1: El nodo tiene solo un hijo derecho.
            
            parent_->set_right(subtree);
        }
        
        else{ //Caso 2: El nodo tiene solo un hijo izquierdo.

            parent_->set_left(subtree);
        }

        current_ = nullptr; //Asignar el nodo actual a nullptr.
        //
        assert(check_parent_chains());
        make_balanced();
        assert(check_parent_chains());
    }
    else
    {
        // TODO
        // Manage case 3.

        auto tmp = current_; //Crear un puntero al nodo actual.
        find_inorder_sucessor(); //Buscar el sucesor inorden.
        tmp->set_item(current_->item()); //Asignar el valor del nodo sucesor al nodo actual.
        remove(); //Eliminar el nodo sucesor.
        //
    }

#ifndef NDEBUG
    // We come back so the recursion count must be decreased.
    recursion_count--;
    assert(recursion_count >= 0);
    if (recursion_count == 0)
    {
        // Only check for the last return.
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());

        // Check postconditions.
        assert(!current_exists());
    }
#endif
}

template <class T>
AVLTree<T>::AVLTree(typename AVLTNode<T>::Ref const &root)
{
    // TODO

    root_ = root;
    current_ = root_;
    parent_ = nullptr;
    height_ = 0;
    size_ = 0;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(root_node() == root);
    assert(current_node() == root);
    assert(parent_node() == nullptr);
}

template <class T>
void AVLTree<T>::set_left(AVLTree<T> &subtree)
{
    assert(!is_empty());
    // TODO

    root_->set_left(subtree.root_node()); //Asignar el subárbol izquierdo al nodo raíz.

    if (!subtree.is_empty()) { //Si el subárbol no está vacío, asignar el nodo padre al subárbol.
        
        root_->left()->set_parent(root_); //Asignar el nodo padre al subárbol.
    }
    //
    assert(subtree.is_empty() || left().item() == subtree.item());
    assert(!subtree.is_empty() || left().is_empty());
}

template <class T>
void AVLTree<T>::set_right(AVLTree<T> &subtree)
{
    assert(!is_empty());
    // TODO
    // Remember to set parent's link of the subtree root to this.

    root_->set_right(subtree.root_node()); //Asignar el subárbol derecho al nodo raíz.

    if (!subtree.is_empty()) { //Si el subárbol no está vacío, asignar el nodo padre al subárbol.

        root_->right()->set_parent(root_); //Asignar el nodo padre al subárbol.
    }
    //
    assert(subtree.is_empty() || right().item() == subtree.item());
    assert(!subtree.is_empty() || right().is_empty());
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::current_node() const
{
    // TODO: fixme

    return current_; //Retornar el nodo actual.
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::current_node()
{
    // TODO: fixme

    return current_; //Retornar el nodo actual.
    //
}

template <class T>
void AVLTree<T>::set_current_node(typename AVLTNode<T>::Ref const &new_c)
{
    // TODO

    current_ = new_c; //Asignar el nuevo nodo al nodo actual.
    //
    assert(current_node() == new_c);
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::root_node() const
{
    // TODO: fixme
    
    return root_; //Retornar el nodo raíz.
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::root_node()
{
    // TODO: fixme
   
    return root_; //Retornar el nodo raíz.
    //
}

template <class T>
void AVLTree<T>::set_root_node(typename AVLTNode<T>::Ref const &new_root)
{
    // TODO

    root_ = new_root; //Asignar el nuevo nodo raíz al árbol.
    //
    assert(root_node() == new_root);
}

template <class T>
typename AVLTNode<T>::Ref const &AVLTree<T>::parent_node() const
{
    // TODO: fixme
    
    return parent_; //Retornar el nodo padre.
    //
}

template <class T>
typename AVLTNode<T>::Ref &AVLTree<T>::parent_node()
{
    // TODO: fixme
    
    return parent_;
    //
}

template <class T>
void AVLTree<T>::set_parent_node(typename AVLTNode<T>::Ref const &new_p)
{
    // TODO

    parent_ = new_p; //Asignar el nuevo nodo padre al árbol.
    //
    assert(parent_node() == new_p);
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
    assert(is_a_binary_search_tree());

#ifndef NDEBUG
    T old_curr = current();
#endif
    // TODO

    parent_ = current_; //Asignar el nodo padre al nodo actual.
    current_ = current_->right(); //Asignar el subárbol derecho al nodo actual.

    while (current_->left() != nullptr){ //Mientras el subárbol izquierdo no sea nulo.

        parent_ = current_; //Asignar el nodo padre al nodo actual.
        current_ = current_->left(); //Asignar el subárbol izquierdo al nodo actual.
    }
    //
    assert(current_exists() && current_node()->left() == nullptr);
#ifndef NDEBUG
    assert(current() > old_curr);
#endif
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::rotate(typename AVLTNode<T>::Ref &P, int dir)
{
    assert(P != nullptr);
    assert(dir == 0 || dir == 1);
    assert(P->child(1 - dir) != nullptr);
    auto N = P->child(1 - dir); // the child to promote.
#ifdef __DEBUG__
    if (__DEBUG__ > 1)
        std::clog << "Rotating to " << (dir == 0 ? "left" : "right") << " on key " << P->item() << std::endl;
#endif
    // TODO
    // Remember: this operation is only necessary for the AVLTree.
    // Remember: if P has not a parent (it is the tree's current root),
    // the promoted node N will be the new root of the tree.
    // Hint: you can see wikipedia: https://en.wikipedia.org/wiki/Tree_rotation

    typename AVLTNode<T>::Ref G;
    typename AVLTNode<T>::Ref CN;
    int gpDir;
    G = P->parent(); //Nodo padre del nodo P.
    N = P->child(1 - dir); //Nodo hijo del nodo P.
    CN = N->child(dir); //Nodo hijo del nodo N.
    P->set_child(1 - dir, CN); //Asignar el hijo del nodo P al nodo hijo del nodo N.

    if (CN != nullptr){ //Si el hijo del nodo N no es nulo

        CN->set_parent(P); //Asignar el nodo padre al nodo P.
    }

    N->set_child(dir, P); //Asignar el hijo del nodo N al nodo P.
    P->set_parent(N); //Asignar el nodo padre al nodo N.

    if (G != nullptr){ //Si el nodo padre no es nulo
    
        gpDir = (G->child(0) == P) ? 0 : 1; //Asignar el hijo del nodo padre al nodo P.
        G->set_child(gpDir, N); //Asignar el hijo del nodo padre al nodo N.
    }
    
    else{ //Sino

        set_root_node(N); //Asignar el nodo raíz al nodo N.
    }

    N->set_parent(G); //Asignar el nodo padre al nodo N.
    //
    return N;
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return; // for a BSTree there is no need to balance.
#else
    auto P = parent_node(); // the subtree root node.

    while (P)
    {
        // TODO
        // Check the subtree balance factor to do rotations if needed.

        typename AVLTNode<T>::Ref N; //Hijo del nodo padre.
        int bfP, bfN, dir; //Factor de equilibrio del nodo padre, hijo y dirección.
        P->update_height(); //Actualizar la altura del nodo padre.

        // First, update subtree root node height because we have just done
        // an insertion/deletion in the subtree.
        
        bfP = P->balance_factor(); //Factor de equilibrio del nodo padre.

        if (std::abs(bfP) > 1){ //Si el factor de equilibrio del nodo padre es mayor que 1, el árbol está desbalanceado.

            dir = (bfP < 0) ? 0 : 1; //Asignar la dirección del nodo padre.
            N = P->child(dir); //Asignar el hijo del nodo padre.
            bfN = N->balance_factor(); //Factor de equilibrio del hijo del nodo padre.

            if (bfP*bfN >= 0){ //Si el producto de los factores de equilibrio es mayor o igual a 0, el árbol está desbalanceado.

                P = rotate(P, 1 - dir); //Asignar el nodo padre al hijo del nodo padre.
            }
            
            else{ //Sino

                rotate(N, dir); //Asignar el hijo del nodo padre al nodo padre.
                P = rotate(P, 1 - dir); //Asignar el nodo padre al hijo del nodo padre.
            }
        }
        //

        // Second, compute balance factor.

        //

        // Third, check the balance factor to do rotations if needed.
        // Remember: update subtree_root if any rotation is done.

        //

        P = P->parent(); // going up.
    }
    // Update the cursor's parent_ node if needed.
    if (current_exists())
        set_parent_node(current_node()->parent());
    assert(!current_exists() || current_node()->parent() == parent_node());
#endif //__ONLY_BSTREE__
}

template <class T>
bool AVLTree<T>::check_parent_chains() const
{
#ifdef __ONLY_BSTREE__
    return true; // for a BSTree there is no need to check this.
#else
    if (!is_empty())
    {
        std::function<void(typename AVLTNode<T>::Ref, std::vector<typename AVLTNode<T>::Ref>)> go_down;
        go_down = [&go_down](typename AVLTNode<T>::Ref node, std::vector<typename AVLTNode<T>::Ref> branch) -> void
        {
            if (node->left() != nullptr || node->right() != nullptr)
            {
                branch.push_back(node);
                if (node->left())
                    // go down by the left
                    go_down(node->left(), branch);
                if (node->right())
                    // go down by the right
                    go_down(node->right(), branch);
            }
            else
            {
                // The node is a leaf node, so check the branch
                // to the tree root node.
                typename AVLTNode<T>::Ref parent = node->parent();
                int idx = static_cast<int>(branch.size()) - 1;
                while (parent && idx >= 0)
                {
                    assert(parent == branch[idx]);
                    --idx;
                    parent = parent->parent();
                }
                assert(idx == -1 && parent == nullptr);
            }
        };
        std::vector<typename AVLTNode<T>::Ref> branch;
        go_down(root_node(), branch);
    }
    return true;
#endif
}

template <class T>
std::tuple<int, int>
compute_min_max_branch_length(AVLTree<T> const &tree)
{
    int min_path_l = std::numeric_limits<int>::max();
    int max_path_l = 0;

    // TODO
    //  Hint: you can use a lambda function to recursive go down through the tree.
    //  A new recursion increase the level in the tree. When a subtree is empty
    //  you have achieved a the leaf of a branch and the current level is e
    //  the branch length ending in this leaf node so we can update
    //  the min/max length values according before returning.
    //  @see: https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
    //  or check_parent_chains() function the to study similar cases.

    if (tree.is_empty()){ //Si el árbol está vacío, asignar los valores de longitud mínima y máxima a -1.
        
        min_path_l = -1;
        max_path_l = -1;
    }

    else if (tree.left().is_empty() && tree.right().is_empty()){ //Si el árbol es una hoja, asignar los valores de longitud mínima y máxima a 0.

        min_path_l = 0;
        max_path_l = 0;
    }

    else{ //Sino

        std::function<void(AVLTree<T> const &, int)> traverse; //Declarar la función lambda.
        traverse = [&min_path_l, &max_path_l, &traverse](AVLTree<T> const &subtree, int level){ //Definir la función lambda.
            
            if (subtree.is_empty()){ //Si el subárbol está vacío, asignar los valores de longitud mínima y máxima a 0.

                return;
            }

            if (subtree.left().is_empty() && subtree.right().is_empty()){ //Si el subárbol es una hoja, asignar los valores de longitud mínima y máxima a 0.

                min_path_l = std::min(min_path_l, level); //Asignar el valor mínimo de longitud al nivel actual.
                max_path_l = std::max(max_path_l, level); //Asignar el valor máximo de longitud al nivel actual.
                return;
            }

            traverse(subtree.left(), level + 1); //Recursividad para procesar el subárbol izquierdo.
            traverse(subtree.right(), level + 1); //Recursividad para procesar el subárbol derecho.
        };

        traverse(tree, 0); //Llamar la función lambda con el árbol y el nivel 0.
    }
    //

    return std::make_tuple(min_path_l, max_path_l);
}
template <class T>
AVLTreeIterator<T> AVLTree<T>::begin() const
{
    typename AVLTNode<T>::Ref node;
    // TODO

    node = root_node(); //Asignar la raíz del árbol a una variable temporal.
    
    while (node && node->left() != nullptr) { //Mientras el nodo no sea nulo y el hijo izquierdo no sea nulo, asignar el hijo izquierdo al nodo.

        node = node->left(); //Asignar el hijo izquierdo al nodo.
    }
    //
    return AVLTreeIterator<T>(node);
}

template <class T>
AVLTreeIterator<T> AVLTree<T>::end() const
{
    return AVLTreeIterator<T>(nullptr);
}
