#ifndef TABLE_H //zapobiega problemom związanym z wielokrotnym dołączaniem tego samego pliku nagłówkowego
#define TABLE_H

class Table {
public:
    Table();
    ~Table();
    void addFront(int e); //e - element
    void addBack(int e); 
    void removeFront(); 
    void removeBack(); 
    bool contains(int e) const;

private:
    int* array; // pointer to the table
    int capacity; // maximum capacity
    int size; // number of element the table currently contains

    void expand(); // double capacity
};

#endif
