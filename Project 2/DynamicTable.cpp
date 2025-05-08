#include "include/DynamicTable.hpp"

Element::Element(int value, int priority) : value(value), priority(priority) {}

DynamicTable::DynamicTable() {
    capacity = 10;
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
    // if (size == capacity) {
    //     expand();
    // }
    // array[size++] = Element(value, priority);
    // reorder(); 
    if (size == capacity) 
        expand();

    int new_index = 0;
    while(array[new_index].priority < priority && new_index < size) {
        new_index++;
    }
    for(int i = size; i > new_index; --i) {
        array[i] = array[i - 1];
    }

    array[new_index] = Element(value, priority);
    size++;
}

void DynamicTable::load(int desired_size) {
    if (size == capacity) 
        expand();

    for (int i = 0; i < desired_size; ++i)
    array[size++] = Element(rand() % 100001, rand() % 101);

    reorder();
    return;
}

void DynamicTable::remove(int value, int priority) {
    if (size == 0) return;
    size--;    
    return;
}

int DynamicTable::peek() const {
    if (size == 0) {
        std::cout << "Queue is empty.\n";
        return -1;
    }
    return array[size-1].value; 
}

int DynamicTable::getSize() const {
    return size;
}

void DynamicTable::modifyPriority(int value, int newPriority) {
    int old_index = -1;
    while(old_index < size) {
        old_index++;
        if(array[old_index].value == value) {
            array[old_index].priority = newPriority;
            break;
        }
    }
    if (old_index == -1) return;

    Element temp = array[old_index];

    for(int i = old_index; i<size; i++) {
        array[i] = array[i + 1];
    }
    size--;
    add(temp.value, temp.priority);
    return;
    // int new_index = 0;
    // while(array[new_index].priority < newPriority && new_index < size) {
    //     new_index++;
    // }
    // for(int i = size; i > new_index; i--) {
    //     array[i] = array[i - 1];
    // }

    // array[new_index] = temp;
    // size++;
}

void DynamicTable::print() const {
    std::cout << "[";
    for (int i = 0; i < size; ++i) {
        std::cout << "(" << array[i].value << ", " << array[i].priority << ")";
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << "]\n";
    return;
}