/**
 * @file hash_table_entry_imp.hpp
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
#include <hash_table_entry.hpp>

template <class K, class V>
HashTableEntry<K, V>::HashTableEntry()
{
    // TODO

    state_ = HashTableEntry<K, V>::EMPTY; //Cambiamos el estado a vacío

    //
    assert(is_empty());
}

template <class K, class V>
HashTableEntry<K, V>::HashTableEntry(const K &k, const V &v)
{
    // TODO

    data_ = std::make_pair(k, v); //Creamos el par con los datos pasados
    state_ = HashTableEntry<K, V>::VALID; //Cambiamos el estado a válido

    //
    assert(is_valid());
    assert(key() == k);
    assert(value() == v);
}

template <class K, class V>
bool HashTableEntry<K, V>::is_valid() const
{
    bool ret_val = false;
    // TODO

    if (state_ == VALID){ //Si el estado es válido

        ret_val = true;
    }

    else{ //Sino

        ret_val = false;
    }

    //
    return ret_val;
}

template <class K, class V>
bool HashTableEntry<K, V>::is_empty() const
{
    bool ret_val = false;
    // TODO

    if (state_ == EMPTY){ //Si el estado esta vacío

        ret_val = true;
    }

    else{ //Sino

        ret_val = false;
    }

    //
    return ret_val;
}

template <class K, class V>
bool HashTableEntry<K, V>::is_deleted() const
{
    bool ret_val = false;
    // TODO

    if (state_ == DELETED){ //Si el estado es eliminado

        ret_val = true;
    }

    else{ //Sino

        ret_val = false;
    }

    //
    return ret_val;
}

template <class K, class V>
K const &
HashTableEntry<K, V>::key() const
{
    assert(!is_empty());
    // TODO: recode according to your representation.

    return data_.first; //Devolvemos la clave del par

    //
}

template <class K, class V>
void HashTableEntry<K, V>::set(const K &k, const V &v)
{
    // TODO

    data_ = std::make_pair(k, v); //Creamos el par con los datos pasados
    state_ = VALID; //Cambiamos el estado a válido

    //
    assert(is_valid());
    assert(key() == k);
    assert(value() == v);
}

template <class K, class V>
V const &HashTableEntry<K, V>::value() const
{
    // TODO: recode according to your representation.

    return data_.second; //Devolvemos el valor del par

    //
}

template <class K, class V>
void HashTableEntry<K, V>::set_value(const V &new_v)
{
    assert(is_valid());

    // TODO: recode according to your representation.

    data_.second = new_v; //Cambiamos el valor del par

    //
    assert(is_valid());
    assert(value() == new_v);
}

template <class K, class V>
void HashTableEntry<K, V>::set_deleted()
{
    assert(is_valid());
    // TODO

    state_ = DELETED; //Cambiamos el estado a eliminado

    //
    assert(is_deleted());
}
