#include "include/DynamicTable.hpp"

Element::Element(int value, int priority) : value(value), priority(priority) {}

DynamicTable::DynamicTable() {
    capacity = 4;
    size = 0;
    array = new Element[capacity];
}

DynamicTable::~DynamicTable() {
    delete[] array;
}

void DynamicTable::expand() {
    capacity *= 2;
    Element* newArray = new Element[capacity];
    std::copy(array, array + size, newArray);
    delete[] array;
    array = newArray;
}

void DynamicTable::reorder() {
    std::sort(array, array + size, [](const Element& a, const Element& b) {
        return a.priority < b.priority;
    });
}

void DynamicTable::add(int value, int priority) {
    if (size == capacity) {
        expand();
    }
    array[size++] = Element(value, priority);
    reorder();                                
}

void DynamicTable::initialAdd(int value, int priority) {
    if (size == capacity) {
        expand();
    }
    array[size++] = Element(value, priority);
}

void DynamicTable::remove(int value, int priority) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (array[i].value == value) {
            index = i;
            break;
        }
    }
    
    if (index != -1) {
        for (int i = index; i < size - 1; i++) {
            array[i] = array[i + 1];
        }
        size--;
        reorder();
    }
}

int DynamicTable::peek() const {
    if (size == 0) {
        std::cout << "Queue is empty.\n";
        return -1;
    }
    return array[0].value; 
}

int DynamicTable::getSize() const {
    return size;
}

void DynamicTable::modifyPriority(int value, int newPriority) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (array[i].value == value) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        array[index].priority = newPriority;
        reorder();
    }
}

void DynamicTable::print() const {
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        std::cout << "(" << array[i].value << ", " << array[i].priority << ")";
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";
}