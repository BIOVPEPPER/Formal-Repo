/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
 
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    elems++;
    if (shouldResize()) {
        resizeTable();
    }
    unsigned h = hashes::hash(key, size);
    std::pair<K, V> target(key, value);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[h].begin(); it != table[h].end(); it++) {
        if (it->first == key) {
            it->second = value;
            return;
        }
    }
    table[h].push_front(target);
}



template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    unsigned h = hashes::hash(key, size);
    for (auto it = table[h].begin(); it != table[h].end(); ++it) {
        if (it->first == key) {
            table[h].erase(it);
            elems--;
            break;
        }
    }
}


template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    unsigned h = hashes::hash(key, size);
    for (auto const& elem : table[h]) {
        if (elem.first == key) {
            return elem.second;
        }
    }
    return V();
}


template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename std::list<std::pair<K, V>>::iterator it;
    size_t old_size = size;
    size = findPrime(2*old_size);
    std::list<std::pair<K, V>>* old_table = table;
    table = new std::list<std::pair<K, V>>[size];
    for (unsigned i = 0; i < old_size; i++) {
        it = old_table[i].begin();
        while(it != old_table[i].end()) {
            unsigned h = hashes::hash((*it).first, size);
            unsigned index = h;
            unsigned step = 1;
            while (table[index].size() != 0) {
                index = (index + step) % size;
                step++;
            }
            std::pair<K, V> target((*it).first, (*it).second);
            table[index].push_back(target);
            ++it;
        }
    }
    delete[] old_table;
}

