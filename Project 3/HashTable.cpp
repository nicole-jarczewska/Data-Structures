#include "include/HashTable.hpp"

HashTable::HashTable(int s, int (*h)(int, int)) : size(s), hashFunction(h) {
        table.resize(s, -1);
        used.resize(s, false);
}

HashTable::~HashTable() {
    clear();
}

bool HashTable::insert(int key) {
    int index = hashFunction(key, size);
    if (table[index] == -1) {
        table[index] = key;
        used[index] = true;
        return true;
    } else {
        return false;
    }
}

bool HashTable::remove(int key) {
    int index = hashFunction(key, size);
    if (table[index] == key) {
        table[index] = -1;
        used[index] = false;
        return true;
    } else {
        return false;
    }
}

void HashTable::load(int size) {
    for (int i = 0; i < size; ++i) {
        int key = rand() % 10001;
        insert(key);
    }
}

void HashTable::clear() {
    for (int i = 0; i < size; ++i) {
        table[i] = -1;
        used[i] = false;
    }
}