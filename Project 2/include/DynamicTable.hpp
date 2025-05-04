#pragma once

struct Element {
    int value;
    int priority;

    Element(int value, int piority);
    Element() : value(0), priority(0) {}
};

class DynamicTable { 
public:
    DynamicTable();
    ~DynamicTable();
    void add(int value, int priority);
    void initialAdd(int value, int priority); 
    void remove(int value, int priority);           
    int peek() const; 
    int getSize() const;   
    void modifyPriority(int value, int newPriority);
    void print() const;

private:
    Element* array;
    int capacity;
    int size;
    void expand();
    void reorder();
};