#include <iostream>
#include <chrono>
#include <vector>
#include <numeric>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>


#include "DynamicTable.hpp"
#include "DynamicTable.cpp"
#include "TimeTest.hpp"
#include "TimeTest.cpp"

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
    

   measure_time_no_arg(&table, &DynamicTable::removeBack, "removeBack.csv");
   measure_time_no_arg(&table, &DynamicTable::removeFront, "results/removeFront.csv");
   //measure_time_arg(&table, &DynamicTable::addBack, 1, "results/addBack.csv");
   //measure_time_arg(&table, &DynamicTable::addFront, 1, "results/addFront.csv");
   //measure_time_bool(&table, &DynamicTable::contains, 1, "contains.csv");

    //table.print();  
    return 0;
}
