#include <iostream>
#include <algorithm>
#include "DynamicTable.hpp"


//DynamicTable::DynamicTable() : array(nullptr), capacity(4), size(0) {} // creating an empty table

DynamicTable::DynamicTable() {
    capacity = 10;
    size = 0;
    array = new int[capacity];
}

DynamicTable::~DynamicTable() {
    delete[] array;
}

void DynamicTable::addBack(int element) {
    if (size == capacity) { 
        expand();
    }
    array[size + 1] = element;
    size++;
}

void DynamicTable::addFront(int element) {
    if (size == capacity) {
        expand();
    }
    for (int i = size; i > 0; --i) {
        array[i] = array[i - 1];
    }
    array[0] = element;
    size++;
}


void DynamicTable::removeBack(){
    if (size > 0){
        size--;
    }
}

void DynamicTable::removeFront(){
    if (size > 0){
        for (int i = 0; i < size - 1; i++){
            array [i] = array [i+1];
        }
        size--;
    }
}

int DynamicTable::contains(int element) const {
    for (int i = 0; i < size; i++) {
        if (array[i] == element) {
            return i;
        }
    }
    return -1; // not found
}

void DynamicTable::expand() { 
    capacity *= 2;

    int* newArray = new int[capacity];
    std::copy(array, array + size, newArray);
    delete[] array;
    array = newArray;
}


void DynamicTable::print() const {
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}
