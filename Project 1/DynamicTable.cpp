#include <iostream>
#include <algorithm>
#include "include/DynamicTable.hpp"


//DynamicTable::DynamicTable() : array(nullptr), capacity(4), size(0) {} // creating an empty table

DynamicTable::DynamicTable() {
    capacity = 4;
    size = 0;
    array = new int[capacity];
}

DynamicTable::~DynamicTable() {
    delete[] array;
}

void DynamicTable::addBack(int element, int index) {
    index = 0; 
    if (size == capacity) { 
        expand();
    }
    array[size] = element;
    size++;
}

void DynamicTable::addFront(int element, int index) {
    index = 0; 
    if (size == capacity) {
        expand();
    }
    for (int i = size; i > 0; --i) {
        array[i] = array[i - 1];
    }
    array[0] = element;
    size++;
}

void DynamicTable::addIndex(int element, int index) {
    if (index < 0 || index > size) 
        return;
    if (size == capacity) 
        expand();

    for (int i = size; i > index; --i) {
        array[i] = array[i - 1];
    }

    array[index] = element;
    size++;
}


void DynamicTable::removeBack(int element, int index){
    index = 0; 
    element = 0; 
    if (size > 0){
        size--;
    }
}

void DynamicTable::removeFront(int element, int index){
    index = 0; 
    element = 0; 
    if (size > 0){
        for (int i = 0; i < size - 1; i++){
            array [i] = array [i+1];
        }
        size--;
    }
}

void DynamicTable::removeIndex(int element, int index) {
    element = 0; 
    if (index < 0 || index >= size) 
        return;

    for (int i = index; i < size - 1; ++i) {
        array[i] = array[i + 1];
    }
    size--;
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
