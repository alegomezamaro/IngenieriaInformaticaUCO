/**
 * @file hash_table_imp.hpp
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

#include <hash_table.hpp>
#include <hash_table_iterator.hpp>

template <class K, class V>
HashTable<K, V>::HashTable(size_t m,
                           const Key_to_uint64_t &key_to_int,
                           OACollisionResolution::Ref hash)
{
    assert(m == hash->m());
    // TODO

    table_.resize(m); //Redimensionar la tabla
    key_to_int_ = key_to_int; //Función de hash
    hash_ = hash; //Resolución de colisiones
    used_entries_ = 0; //Número de entradas ocupadas

    //
    assert(size() == m);
}

template <class K, class V>
size_t
HashTable<K, V>::size() const
{
    size_t ret_v = 0;
    // TODO

    ret_v = table_.size(); //Devolvemos el tamaño de la tabla

    //
    return ret_v;
}

template <class K, class V>
float HashTable<K, V>::load_factor() const
{
    float ret_v = 0.0f;
    // TODO

    ret_v = static_cast<float>(used_entries_) / static_cast<float>(size()); //Devolvemos el factor de carga

    //
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::begin() const
{
    HashTableIterator<K, V> ret_v;
    // TODO
    // Remember: the iterator should point to the first valid entry.
    // Hint: you must use const_cast to remove the const qualifier from this.

    size_t idx = 0; //Índice para recorrer la tabla
     
    while(idx < size() && !entry(idx).is_valid()){ //Mientras el índice sea menor que el tamaño de la tabla y la entrada no sea válida
    
        idx++; //Aumentamos el índice
     
        if(idx < size()){ //Si el índice es menor que el tamaño de la tabla
     
             ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), idx); //Creamos el iterador
        }      
 
        else{ //Sino
         
             ret_v = end(); //Creamos el iterador al final de la tabla
        }
    }
    
    //
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::end() const
{
    HashTableIterator<K, V> ret_v;
    // TODO
    // Remember: the iterator should point one position pass the end of the table.
    // Hint: you must use const_cast to remove the const qualifier from this.

    ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), size()); //Creamos el iterador al final de la tabla

    //
    assert(!ret_v.is_valid());
    return ret_v;
}

template <class K, class V>
size_t HashTable<K, V>::find_position(K const &k) const
{
    assert(load_factor() < 1.0f);
    size_t idx = 0;
    // TODO

    size_t iter= 0; //Para contar el número de iteraciones
    uint64_t key_int= key_to_int_(k); //Convertimos la clave a un entero
    idx= (*hash_)(key_int, iter); //Obtenemos el índice inicial usando la función hash
    size_t first_deleted = size(); //Para recordar la primera posición eliminada encontrada
    
    while (!entry(idx).is_empty()){ //Mientras la entrada no esté vacía
 
        if(entry(idx).is_valid() && entry(idx).key() == k){ //Si la entrada es válida y la clave coincide con la buscada
             
            return idx; //Devolvemos el índice
        }
         
        if(entry(idx).is_deleted() && first_deleted == size()){ //Si la entrada está eliminada y no hemos encontrado ninguna posición eliminada antes
             
            first_deleted = idx; //Guardamos la posición eliminada
        }
         
        iter++; //Aumentamos el número de iteraciones
        idx= (*hash_)(key_int, iter); //Obtenemos el nuevo índice usando la función hash
    }

    if(first_deleted != size()){ //Si hemos encontrado una posición eliminada
    
        return first_deleted; //Devolvemos la posición eliminada
    }

    //
    assert(0 <= idx && idx < size());
    return idx;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::find(K const &k) const
{
    HashTableIterator<K, V> ret_v = end();
    // TODO
    // Hint: use find_position.
    // Hint: you must use const_cast to remove the const qualifier from this.

    size_t idx = find_position(k);

    if (entry(idx).is_valid()){ //Si la entrada es válida
    
        ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V> *>(this), idx); //Creamos el iterador
    }
    
    else{ //Sino

        ret_v = end(); //Creamos el iterador al final de la tabla
    }

    //
    assert(ret_v == end() || (ret_v.is_valid() && ret_v.key() == k));
    return ret_v;
}

template <class K, class V>
HashTableIterator<K, V> HashTable<K, V>::insert(K const &k, V const &v)
{
    assert(load_factor() <= 0.5f);
    HashTableIterator<K, V> ret_v = end();
    const size_t current_size = size();
    // TODO
    // Remember: increment the number of used entries only when an
    //    empty entry was used.
    // Remember: you must call to rehash before inserting a new entry to avoid
    //    a load factor greater than 0.5.
    // Remember: if a rehashing was done (current_size != new size returned by
    //    rehash function), you need to find the new location of the inserted key.

    size_t idx= find_position(k); //Obtenemos la posición del índice donde se debe insertar la clave
    bool is_update= entry(idx).is_valid() && entry(idx).key() == k; //Comprobamos si la entrada ya es válida y si la clave coincide con la buscada

    if(!is_update && load_factor() >= 0.5f){ //Si la carga es mayor o igual a 0.5, rehash

        size_t new_size= rehash(); //Rehashing de la tabla
        
        if(current_size != new_size){ //Si se ha cambiado el tamaño de la tabla, recalcular la posición
        
            idx= find_position(k); //Recalculamos la posición con nueva tabla
        }
    }

    if(!is_update && entry(idx).is_empty()){ //Si la entrada está vacía y no es una actualización
        
        used_entries_++; //Aumentamos el número de entradas ocupadas
    }

    entry(idx).set(k, v); //Insertamos la clave y el valor en la entrada
    ret_v = HashTableIterator<K, V>(const_cast<HashTable<K, V>*>(this), idx); //Creamos el iterador

    //
    assert(ret_v.is_valid());
    assert(ret_v.key() == k);
    assert(ret_v.value() == v);
    assert(load_factor() <= 0.5f);
    return ret_v;
}

template <class K, class V>
void HashTable<K, V>::remove(HashTableIterator<K, V> &iter)
{
#ifndef NDEBUG
    assert(iter.is_valid());
    K old_k = iter.key();
#endif
    // TODO
    // Remember: we are using a mark to sign "deleted".

    if (iter.is_valid()) {//Comprobamos si el iterador es válido
     
        size_t pos = iter.index(); //Obtenemos la posición del iterador
        entry(pos).set_deleted(); //Solo marcamos como eliminado
        iter = end(); //Eliminamos el iterador
    }

    //
    assert(!iter.is_valid());
    assert(find(old_k) == end());
}

template <class K, class V>
size_t HashTable<K, V>::rehash()
{
    // TODO
    // Remember: rehash when load_factor > 0.5
    // Remember: we use a 2 factor to grown the current size.
    // Remember: a new hash function will be picked at random from the Universal Family.
    // Remember: reset the number of used entries to zero before inserting the old valid
    // entries in the new table.

    auto old_table = table_; //Guardamos la tabla antigua
    auto old_used = used_entries_; //Guardamos el número de entradas usadas
    size_t new_size = size() * 2; //Duplicamos el tamaño de la tabla
    used_entries_ = 0; //Reiniciamos el número de entradas usadas
    table_.clear(); //Limpiamos la tabla
    table_.resize(new_size); //Redimensionamos la tabla al nuevo tamaño
    hash_ = hash_->pick_at_new(new_size); //Elegimos una nueva función hash al azar de la familia universal
    
    for(size_t i= 0; i<old_table.size();i++){ //Recorrendo la tabla antigua
         
        if(old_table[i].is_valid()){ //Si la entrada es válida
 
            insert(old_table[i].key(), old_table[i].value()); //Insertamos la clave y el valor en la nueva tabla
        }
    }

    //
    assert(load_factor() <= 0.5);
    return size();
}

template <class K, class V>
HashTableEntry<K, V> const &HashTable<K, V>::entry(size_t idx) const
{
    assert(idx < size());
    // TODO: recode according to your representation.
    
    return table_[idx]; // Devuelve una referencia a la entrada en la posición idx

    //
}

template <class K, class V>
HashTableEntry<K, V> &HashTable<K, V>::entry(size_t idx)
{
    assert(idx < size());
    // TODO: recode according to your representation.
    
    return table_[idx]; // Devuelve una referencia a la entrada en la posición idx

    //
}
