/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    elems++;
    if (shouldResize()) {
        resizeTable();
    }
    unsigned h = hashes::hash(key, size);
    unsigned i = 0;
    while (i < size) {
        unsigned index = (h + i * i) % size;
        if (should_probe[index] == false) {
            should_probe[index] = true;
            table[index] = new std::pair<K, V>(std::make_pair(key, value));
            break;
        } else if (table[index] != nullptr && table[index]->first == key) {
            table[index]->second = value;
            break;
        }
        i++;
    }
}




template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
    unsigned h = hashes::hash(key, size);
    unsigned i = 1; // Quadratic probing increment variable
    unsigned h_new = h;

    // Search for the key using quadratic probing
    while (should_probe[h_new]) {
        if ((*table[h_new]).first == key) {
            // Key found, remove the entry and update should_probe
            delete table[h_new];
            table[h_new] = nullptr;
            should_probe[h_new] = false;
            break;
        } else {
            // Key not found in the current slot, continue probing
            h_new = (h + i * i) % size;
            i++;
        }
    }
}


template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    unsigned h = hashes::hash(key, size);
    unsigned i = 1; // Quadratic probing increment variable
    unsigned h_new = h;

    // Search for the key using quadratic probing
    while (should_probe[h_new]) {
        if ((*table[h_new]).first == key) {
            // Key found, return the index
            return int(h_new);
        } else {
            // Key not found in the current slot, continue probing
            h_new = (h + i * i) % size;
            i++;
        }
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    size_t old_size = size;
    size = findPrime(2 * old_size);
    std::pair<K, V>** old_table = table;
    table = new std::pair<K, V>*[size];
    delete[] should_probe;
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }

    // Rehash the elements using quadratic probing
    for (unsigned i = 0; i < old_size; i++) {
        if (old_table[i] != NULL) {
            unsigned h = hashes::hash((*old_table[i]).first, size);
            unsigned j = 1; // Quadratic probing increment variable
            unsigned h_new = h;

            // Find an empty slot using quadratic probing
            while (should_probe[h_new]) {
                h_new = (h + j * j) % size;
                j++;
            }

            should_probe[h_new] = true;
            std::pair<K, V> target((*old_table[i]).first, (*old_table[i]).second);
            table[h_new] = new std::pair<K, V>(target);
        }
    }

    for (unsigned i = 0; i < old_size; i++) {
        delete old_table[i];
    }
    delete[] old_table;
}

