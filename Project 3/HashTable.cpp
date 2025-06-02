#include "include/HashTable.hpp"

HashTable::HashTable(int s, int (*h)(int, int)) : size(s), hashFunction(h) {
    table = new int[size];
    status = new CellStatus[size];
    clear();
}

HashTable::~HashTable() {
    delete[] table;
    delete[] status;
}

bool HashTable::insert(int key) {
    int index = hashFunction(key, size);
    for (int i = 0; i < size; ++i) {

        if (status[index] == EMPTY || status[index] == DELETED) {
            table[index] = key;
            status[index] = FILLED;
            return true;
        }

        if (status[index] == FILLED && table[index] == key) {
            return false;
        }
        index = (index + 1) % size;
    }
    return false;
}

bool HashTable::remove(int key) {
    int index = hashFunction(key, size);
    for (int i = 0; i < size; ++i) {
        if (status[index] == FILLED && table[index] == key) {
            status[index] = DELETED;
            table[index] = -1;
            return true;
        }

        if (status[index] == EMPTY) {
            return false;
        }
        index = (index + 1) % size;
    }
    return false;
}


void HashTable::load(int size, int loadfactor, int scenario) {
    clear();
    int lf = static_cast<int>(size * (loadfactor / 100.0));
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
        status[i] = EMPTY;
    }
}

int HashTable::count_filled() const {
    int count = 0;
    for (int i = 0; i < size; ++i)
        if (status[i] == FILLED) ++count;
    return count;
}