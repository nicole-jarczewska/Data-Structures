#include <iostream>
#include <algorithm>
#include "DynamicTable.h"


DynamicTable::DynamicTable() : array(nullptr), capacity(4), size(0) {} // creating an empty table

DynamicTable::~DynamicTable() {
    delete[] array;
}

void DynamicTable::addBack(int e) {
    if (size == capacity) { 
        expand();
    }
    array[size + 1] = e;
    size++;
}

void DynamicTable::addFront(int e) {
    if (size == capacity) {
        expand();
    }
    for (int i = size; i > 0; --i) {
        array[i] = array[i - 1];
    }
    array[0] = e;
    size++;
}


void DynamicTable::removeBack(){
    if (size > 0){
        array[size] = NULL;
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

bool DynamicTable::contains(int e) const {
    for (int i = 0; i < size; i++) {
        if (array[i] == e) {
            return true;
        }
    }
    return false;
}

void DynamicTable::expand() { 
    capacity *= 2;

    int* newArray = new int[capacity];
    std::copy(array, array + size, newArray);
    delete[] array;

    array = newArray;
}

