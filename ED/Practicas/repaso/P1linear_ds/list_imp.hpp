/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <sstream>
#include <stdexcept>
#include <cassert>

#include <list.hpp>

template <class T>
List<T>::List()
{
    // TODO
    // Remember: in an empty list, the dummy node is linked with itself.

    head_ = DNode<T>::create(); //Crea un nodo dummy
    tail_ = head_; //Asigna la cola a la cabeza
    head_->set_next(head_); //Asigna el siguiente nodo a la cabeza
    head_->set_prev(head_); //Asigna el nodo anterior a la cabeza
    size_ = 0; //Inicializa el tamaño a 0

    //
    assert(is_empty());
}

template <class T>
List<T>::List(std::istream &in) noexcept(false) : List()
{

    // TODO
    // Hint: use std::istringstream to convert from a "string" token value to a template
    // T type value.
    // Remember: throw std::runtime_error("Wrong input format.") exception when an input
    //  format error was found.

    std::string token; //String token
    in >> token; //Leemos el token

    if (token != "[") { // Si el inicio del formato es incorrecto
        throw std::runtime_error("Wrong input format.");
    }

    T value;

    while (in >> token && token != "]") { // Mientras haya tokens distintos al final del formato
        std::istringstream string(token); // Convierte token a string

        if (!(string >> value)) { // Si no se puede convertir a string
            throw std::runtime_error("Wrong input format.");
        }

        push_back(value); // Inserta el valor al final de la lista
    }

    if (token != "]") { // Si el final del formato es incorrecto
        throw std::runtime_error("Wrong input format.");
    }

    //
}

template <class T>
List<T>::~List()
{
    // Think. We are using smart pointers (shared_ptr) so the nodes will
    // released automatically when the references going off.
}

template <class T>
typename DNode<T>::Ref List<T>::dummy() const
{
    // TODO: recode with respect to your representation.

    return head_; //Devuelve la cabeza

    //
}

template <class T>
bool List<T>::is_empty() const
{
    // TODO: recode with respect to your representation.

    if(size() == 0){ //Si el tamaño es 0 esta vacio
        return true;
    }

    return false;

    //
}

template <class T>
size_t List<T>::size() const
{
    // TODO: recode with respect to your representation.

    return size_; //Devuelve el tamaño

    //
}

template <class T>
void List<T>::set_size(size_t new_size)
{
    // TODO

    size_ = new_size; //Asigna el nuevo tamaño

    //
    assert(size() == new_size);
}

template <class T>
typename List<T>::iterator List<T>::begin() const
{

    // TODO: recode with respect to your representation.

    return iterator(head_->next()); //Retorna el nodo del primer elemento

    //
}

template <class T>
typename List<T>::iterator List<T>::end() const
{
    // TODO: recode with respect to your representation.

    return iterator(tail_); //Retorna el nodo cola

    //
}

template <class T>
T const &List<T>::front() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    // Hint: use iterators.
    
    return (head_->next()->item()); //Devuelve el primer elemento

    //
}

template <class T>
T const &List<T>::back() const
{
    assert(!is_empty());

    // TODO: recode with respect to your representation.
    // Hint: use iterators.

    return (tail_->prev()->item()); //Devuelve el ultimo elemento

    //
}

template <class T>
void List<T>::fold(std::ostream &out) const
{
    // TODO

    out << "["; //Introduce el valor inicial del formato
    auto it = head_->next(); //Iterador al primer elemento
    
    while (it != tail_) { //Mientras no lleguemos al final
        out << " " << it->item(); // Añade el elemento a la salida.
        it = it->next(); // Pasa al siguiente nodo.
    }

    out << " ]"; //Introduce el valor final del formato

    //
}

template <class T>
void List<T>::hook(typename DNode<T>::Ref n, typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // REPASO
    // Remember updating the size.

    

    //
    assert(size() == old_size + 1);
}

template <class T>
void List<T>::unhook(typename DNode<T>::Ref pos)
{
#ifndef NDEBUG
    auto old_size = size();
#endif
    // REPASO
    // Remember updating the size.



    //
    assert(size() == old_size - 1);
}

template <class T>
typename List<T>::iterator List<T>::insert(typename List<T>::iterator const &pos,
                                           T const &it)
{
#ifndef NDEBUG
    auto old_is_empty = is_empty();
    auto old_size = size();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in hook.

    auto new_node = DNode<T>::create(it); //Crea un nuevo nodo con it
    hook(new_node, pos.node()); //Conecta el nuevo nodo
    ret_v = iterator(new_node); //Asigna el nuevo nodo a ret_v

    //
    assert(!old_is_empty || (front() == it && back() == it));
    assert(old_is_empty || ret_v.next() == pos);
    assert(old_is_empty || old_pos_prev == ret_v.prev());
    assert(size() == (old_size + 1));
    return ret_v;
}

template <class T>
typename List<T>::iterator List<T>::remove(List<T>::iterator const &pos)
{
    assert(!is_empty());
#ifndef NDEBUG
    auto old_size = size();
    auto old_pos_next = pos.next();
    auto old_pos_prev = pos.prev();
#endif
    iterator ret_v;
    // TODO
    // Hint: delegate in unkook

    ret_v = pos.next(); //Asigna el siguiente nodo a ret_v
    unhook(pos.node()); //Desconecta el nodo

    //
    assert(ret_v == old_pos_next);
    assert(ret_v.prev() == old_pos_prev);
    assert(size() == (old_size - 1));
    return ret_v;
}

template <class T>
void List<T>::push_front(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // REPASO
    //  Hint: delegate in insert();



    //
    assert(front() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::push_back(T const &new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    //  Hint: delegate in insert();

    insert(end(), new_it); //Inserta el nuevo elemento al final

    //
    assert(back() == new_it);
    assert(size() == (old_size + 1));
}

template <class T>
void List<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
#endif
    // TODO
    // Hint: delegate in remove.

    remove(begin()); //Desconecta el primer nodo

    //
    assert(size() == (old_size - 1));
}

template <class T>
void List<T>::pop_back()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_end_prev_prev = end().prev().prev();
#endif
    // TODO
    // Hint: delegate in remove.

    remove(end().prev()); //Desconecta el último nodo

    //
    assert(is_empty() || end().prev() == old_end_prev_prev);
    assert(size() == (old_size - 1));
}

template <class T>
typename List<T>::iterator List<T>::find(T const &it, List<T>::iterator const &from) const
{
    iterator ret_v;
    // TODO

    ret_v = from; //Asigna el nodo de inicio a ret_v
    while (ret_v != end() && ret_v.item() != it) { //Mientras no lleguemos al final y no encontremos el elemento
        ret_v = ret_v.next(); //Pasamos al siguiente nodo
    }

    //
    assert(ret_v == end() || ret_v.item() == it);
    return ret_v;
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2,
                     iterator const &first, iterator const &last)
{
#ifndef NDEBUG
    size_t old_size = size();
    size_t old_l2_size = list2.size();
    auto old_range_size = first.distance(last);
#endif
    // TODO
    // Hint: if the range [first, last) is empty, nothing must be done.

    if (first == last) return; //Si el rango es vacío no se hace nada

    auto posNode = pos.node(); //Nodo de la posición
    auto prevPosNode = posNode->prev(); //Nodo anterior a la posición
    auto firstNode = first.node(); //Nodo del primer elemento
    auto prevFirstNode = firstNode->prev(); //Nodo anterior al primer elemento
    auto lastNode = last.node(); //Nodo del último elemento
    auto prevLastNode = lastNode->prev(); //Nodo anterior al último elemento

    prevFirstNode->set_next(lastNode); //Asigna el siguiente nodo al anterior al primer nodo
    lastNode->set_prev(prevFirstNode); //Asigna el nodo anterior al último nodo al anterior al primer nodo

    prevPosNode->set_next(firstNode); //Asigna el siguiente nodo al anterior a la posición
    firstNode->set_prev(prevPosNode); //Asigna el nodo anterior al primer nodo al anterior a la posición
    prevLastNode->set_next(posNode); //Asigna el siguiente nodo al anterior al último nodo
    posNode->set_prev(prevLastNode); //Asigna el nodo anterior al último nodo a la posición

    set_size(old_size + old_range_size); //Aumenta el tamaño
    list2.set_size(old_l2_size - old_range_size); //Disminuye el tamaño de la otra lista

    //
    assert(size() == (old_size + old_range_size));
    assert(list2.size() == (old_l2_size - old_range_size));
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2.size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [begin, end).

    splice(pos, list2, list2.begin(), list2.end()); //Introduce toda la lista en la lista actual

    //
    assert(size() == (old_size + old_list2_size));
    assert(list2.size() == 0);
    assert(list2.is_empty());
}

template <class T>
void List<T>::splice(iterator const &pos, List<T> &list2, iterator const &i)
{
#ifndef NDEBUG
    size_t old_size = size();
    auto old_list2_size = list2.size();
#endif
    // TODO
    // Hint: Delegate in splice the list2 range [i, i.next()).

    auto next = i; //Crea un iterador next.
    next = next.next(); //Avanza next al siguiente nodo.
    splice(pos, list2, i, next); //Llama a splice con el rango [i, next).


    //
    assert(size() == (old_size + 1));
    assert(list2.size() == (old_list2_size - 1));
}

template <class T>
template <class Compare>
void List<T>::merge(List<T> &other, Compare comp)
{
    // TODO
    // Remember: The nodes of the other list are spliced into this list.

    auto it1 = begin(); // Iterador al primer elemento
    auto it2 = other.begin(); // Iterador al primer elemento de la otra lista

    while (it1 != end() && it2 != other.end()) { // Mientras no lleguemos al final de ninguna lista
        
        if (comp(it1.node()->item(), it2.node()->item())) { // Si el elemento de la lista es menor que el de la otra lista
            it1 = it1.next(); // Pasa al siguiente nodo
        } else { // Si el elemento de la otra lista es menor o igual que el de la lista
            auto tmp = it2; // Asigna el nodo actual de la otra lista a tmp
            it2 = it2.next(); // Pasa al siguiente nodo en la otra lista
            splice(it1, other, tmp, it2); // Introduce el nodo tmp en la lista actual
        }
    }

    if (it2 != other.end()) { // Si no hemos llegado al final de la otra lista
        splice(end(), other, it2, other.end()); // Introduce el resto de la otra lista en la lista actual
    }

    // Asegúrate de que la otra lista esté vacía después de fusionar
    other.set_size(0);
    other.head_->set_next(other.head_);
    other.head_->set_prev(other.head_);

    //
}

template <class T>
template <class Compare>
void List<T>::sort(Compare comp)
{
    // TODO
    // Remember: we want a complexity in to N Log(N) so mergeSort algorithm is
    // a good candidate to sort the list.
    // Hint: Do a recursive implementation, splitting the list into two halves,
    // sorting recursively each part and merging the sorted lists to obtain
    // the full sorted list.

    // The empty list and a list with only one element are sorted by default.

    
    if (size() <= 1) return; //Si el tamaño es 0 o 1, la lista ya está ordenada

    List<T> tmp; // Lista temporal para almacenar la segunda mitad de la lista
    auto midpoint = begin(); // Iterador al primer elemento

    for (size_t i = 0; i < size() / 2; ++i) { // Mueve el iterador a la mitad de la lista
        midpoint = midpoint.next();
    }

    tmp.splice(tmp.begin(), *this, midpoint, end()); // Introduce la segunda mitad de la lista en la lista temporal
    sort(comp); // Ordena la primera mitad de la lista
    tmp.sort(comp); // Ordena la segunda mitad de la lista
    merge(tmp, comp); // Fusiona las dos mitades de la lista

    //
}
