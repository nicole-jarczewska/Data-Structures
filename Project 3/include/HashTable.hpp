#pragma once

class HashTable{ 
public:
    HashTable(int s, int (*h)(int, int));
    ~HashTable();

    bool insert(int key);
    bool remove(int key);
    void load(int size, int loadfactor, int scenario);

    int *table;
    bool *used;
    int size;
    int (*hashFunction)(int, int);
    
private:
    void clear();
};
