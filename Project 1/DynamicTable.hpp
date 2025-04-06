#ifndef TABLE_H 
#define TABLE_H

class DynamicTable {
public:
    DynamicTable();
    ~DynamicTable();
    
    void addFront(int element);
    void addBack(int element); 
    void removeFront(); 
    void removeBack(); 
    int contains(int element) const;
    void print() const;

private:
    int* array; // pointer to the table
    int capacity; // maximum capacity
    int size; // number of element the table currently contains

    void expand(); // doubling capacity when the table is full
};

#endif
