#include "include/HashTable.hpp"

HashTable::HashTable(int s, int (*h)(int, int)) : size(s), hashFunction(h) {
    table = new int[size];
    used = new bool[size];
    clear();
}

HashTable::~HashTable() {
    delete[] table;
    delete[] used;
}

bool HashTable::insert(int key) {
    int index = hashFunction(key, size);

    for (int i = 0; i < size; ++i){

        if (used[index] && table[index] == key)
            return false;

        if (!used[index]){
            table[index] = key;
            used[index] = true;
            return true;
        }

        index = (index + 1) % size;
    }
    return false;
}

bool HashTable::remove(int key) {
    int index = hashFunction(key, size);

    for (int i = 0; i < size; ++i) {
        if (used[index] && table[index] == key) {
            used[index] = false;
            table[index] = -1;
            return true;
        }
        index = (index + 1) % size;
    }

    return false; // element not found
}


void HashTable::load(int size, int loadfactor, int scenario) {
    clear();
    float lf = size * (loadfactor/100.0);
    for (int i = 0; i < lf; ++i) {
        // int key = rand() % 10001;
        // if(scenario == 1) 
        int key = i;
        // else if(scenario == -1) key = i*size;
        insert(key);
    }
}

void HashTable::clear() {
    for (int i = 0; i < size; ++i) {
        table[i] = -1;
        used[i] = false;
    }
}