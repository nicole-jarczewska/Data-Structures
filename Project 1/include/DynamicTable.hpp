#pragma once

class DynamicTable {
public:
    DynamicTable();
    ~DynamicTable();
    
    void addFront(int element, int index);
    void addBack(int element, int index); 
    void addIndex(int element, int index); 
    void removeFront(int element, int index); 
    void removeBack(int element, int index);
    void removeIndex(int element, int index); 
    int contains(int element) const;
    void print() const;

private:
    int* array; // pointer to the table
    int capacity; // maximum capacity
    int size; // number of element the table currently contains

    void expand(); // doubling capacity when the table is full
};
