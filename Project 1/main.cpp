#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <fstream>

#include "DynamicTable.hpp"
#include "DynamicTable.cpp"

void testDynamicTable() {
    
}

void load(const int size, DynamicTable& table) {
    std::ifstream inputFile("Dataset.txt");
    if (!inputFile) {
        std::cerr << "Failed to open numbers.txt\n";
        return;
    }

    int number;
    int count = 0;

    while (inputFile >> number && count < 1000){
        table.addBack(number);
        ++count;
    }

    inputFile.close();
}


int main() {
    DynamicTable table;
    const int TableSize = 1000;

    load(TableSize, table);

    table.print();  
    return 0;
}
