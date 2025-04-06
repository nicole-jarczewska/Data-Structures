#include <iostream>
#include <algorithm>
#include "table.h"


Table::Table() : array(nullptr), capacity(4), size(0) {} // creating an empty table

Table::~Table() {
    delete[] array;
}

void Table::addBack(int e) {
    if (size == capacity) { 
        expand(); // doubling capacity when the table is full
    }
    array[size + 1] = e;
    size++;
}

void Table::addFront(int e) {
    if (size == capacity) {
        expand(); // doubling capacity when the table is full
    }
    for (int i = size; i > 0; --i) {
        array[i] = array[i - 1];
    }
    array[0] = e;
    size++;
}


void Table::removeBack(){
    if (size > 0){
        array[size] = NULL;
        size--;
    }
}

void Table::removeFront(){
    if (size > 0){
        for (int i = 0; i < size - 1; i++){
            array [i] = array [i+1];
        }
        size--;
    }
}

bool Table::contains(int e) const {
    for (int i = 0; i < size; i++) {
        if (array[i] == e) {
            return true;
        }
    }
    return false;
}

void Table::expand() {
    capacity *= 2;

    int* newArray = new int[capacity];
    std::copy(array, array + size, newArray);
    delete[] array;

    array = newArray;
}

