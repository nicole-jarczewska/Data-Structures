#ifndef TABLE_H 
#define TABLE_H

class DynamicTable {
public:
    DynamicTable();
    ~DynamicTable();
    void addFront(int e); //e - element
    void addBack(int e); 
    void removeFront(); 
    void removeBack(); 
    bool contains(int e) const;

private:
    int* array; // pointer to the table
    int capacity; // maximum capacity
    int size; // number of element the table currently contains

    void expand(); // doubling capacity when the table is full
};

#endif
