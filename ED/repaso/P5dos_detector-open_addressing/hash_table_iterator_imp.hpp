/**
 * @file hash_table_iterator.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <hash_table_iterator.hpp>

template <class K, class V>
size_t HashTableIterator<K, V>::index() const
{
    // TODO

    return idx_; //Devolvemos el índice

    //
}

template <class K, class V>
const HashTable<K, V> *HashTableIterator<K, V>::table() const
{
    // TODO

    return ht_; //Devolvemos la tabla

    //
}

template <class K, class V>
HashTable<K, V> *HashTableIterator<K, V>::table()
{
    // TODO

    return ht_; //Devolvemos la tabla

    //
}

template <class K, class V>
HashTableIterator<K, V>::HashTableIterator()
{
    // TODO
    
    ht_ = nullptr; // Inicializamos la tabla a nullptr
    idx_ = 0; // Inicializamos el índice a 0

    //
    assert(table() == nullptr);
    assert(index() == 0);
    assert(!is_valid());
}

template <class K, class V>
HashTableIterator<K, V>::HashTableIterator(HashTable<K, V> *ht, size_t idx)
{
    assert(ht != nullptr);
    // TODO

    ht_ = ht; // Inicializamos la tabla a la pasada como parámetro
    idx_ = idx; // Inicializamos el índice a la pasada como parámetro

    //
    assert(table() == ht);
    assert(index() == idx);
}

template <class K, class V>
bool HashTableIterator<K, V>::is_valid() const
{
    // TODO
    // Remember: check that idx_ is in the table's range and the entry is valid.

    return ht_ != nullptr && idx_ < ht_->size() && ht_->entry(idx_).is_valid(); // Comprobamos que la tabla no es nullptr, que el índice está dentro del rango y que la entrada es válida
 
    //
}

template <class K, class V>
HashTableIterator<K, V> &
HashTableIterator<K, V>::operator++()
{
    assert(is_valid());
    // TODO

    do{ 

        ++idx_; // Aumentamos el índice
    }
    
    while (idx_ < ht_->size() && !ht_->entry(idx_).is_valid()); //Mientras el índice sea menor que el tamaño de la tabla y la entrada no sea válida, aumentamos el índice

    //
    return *this;
}

template <class K, class V>
HashTableIterator<K, V>
HashTableIterator<K, V>::operator++(int)
{
    assert(is_valid());
    HashTableIterator ret_v(*this);
    ++(*this);
    return ret_v;
}

template <class K, class V>
bool HashTableIterator<K, V>::operator==(HashTableIterator<K, V> const &other) const
{
    bool ret_v = false;
    // TODO

    ret_v = table() == other.table() && index() == other.index(); //Comprobamos que la tabla es la misma y que el índice es el mismo

    //
    return ret_v;
}
template <class K, class V>
bool HashTableIterator<K, V>::operator!=(HashTableIterator<K, V> const &other) const
{
    return !(*this == other);
}

template <class K, class V>
K const &
HashTableIterator<K, V>::key() const
{
    // TODO

    return ht_->entry(idx_).key(); //Devolvemos la clave de la entrada

    //
}

template <class K, class V>
V const &
HashTableIterator<K, V>::value() const
{
    // TODO

    return ht_->entry(idx_).value(); //Devolvemos el valor de la entrada

    //
}

template <class K, class V>
void HashTableIterator<K, V>::set_value(V const &v) const
{
    // TODO

    ht_->entry(idx_).set_value(v); //Establecemos el valor de la entrada

    //
}
