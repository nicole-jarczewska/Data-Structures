#include "include/Heap.hpp"

Heap::Heap() {
    capacity = 10;
    size = 0;
    array = new Element[capacity];
}

Heap::~Heap() {
    delete[] array;
}

void Heap::expand() {
    capacity *= 2;
    Element* newArray = new Element[capacity];
    std::copy(array, array + size, newArray);
    delete[] array;
    array = newArray;
}

void Heap::heapifyUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (array[index].priority <= array[parentIndex].priority)
            break;
        std::swap(array[index], array[parentIndex]);
        index = parentIndex;
    }
    return;
}

void Heap::heapifyDown(int index) {
    while (index < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && array[left].priority > array[largest].priority)
            largest = left;
        if (right < size && array[right].priority > array[largest].priority)
            largest = right;

        if (largest == index) break;

        std::swap(array[index], array[largest]);
        index = largest;
    }
    return;
}

void Heap::add(int value, int priority) {
    if (size == capacity) 
        expand();

    array[size++] = Element(value, priority);
    heapifyUp(size - 1);
    return;
}

void Heap::load(int desired_size) {
    if (size == capacity) 
        expand();

    for (int i = 0; i < desired_size; ++i)
    array[size++] = Element(rand() % 100001, rand() % 101);

    for (int i = size/ 2 - 1; i >= 0; i--)
        heapifyDown(i);

    return;
}

void Heap::remove(int value, int priority) {
    if (size == 0) return;
    array[0] = array[--size];
    heapifyDown(0); 
    return;
}

int Heap::peek() const {
    if (size == 0) {
        std::cout << "Queue is empty.\n";
        return -1;
    }
    return array[0].value; 
}

int Heap::getSize() const {
    return size;
}

void Heap::modifyPriority(int value, int newPriority) {
    int old_index = -1;
    while(old_index < size) {
        old_index++;
        if(array[old_index].value == value) {
            array[old_index].priority = newPriority;
            break;
        }
    }
    if (old_index == -1) return;

    int oldPriority = array[old_index].priority;
    array[old_index].priority = newPriority;

    if (newPriority > oldPriority) {
        heapifyUp(old_index);
    } else {
        heapifyDown(old_index);
    }
}

void Heap::print() const {
    int level = 0;
    int index = 0;

    while (index < size) { 
        for (int i = 0; i < pow(2,level); ++i) {
            if (index >= size) break;
            std::cout << "(" << array[index].value << ", " << array[index].priority << ") ";
            index++;
        }
        std::cout << std::endl;
        level++;
    }
    std::cout << std::endl;
    return;
}