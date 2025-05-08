#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <numeric>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <thread>
#include <functional>

#include "include/DynamicTable.hpp"
#include "DynamicTable.cpp"
#include "include/LinkedList.hpp"
#include "LinkedList.cpp"

#include "include/TimeTest.hpp"
#include "TimeTest.cpp"

void testDynamicTable(int size) {
    std::ostringstream filename;
    filename << size << ".csv";

    int randomNumber = rand() % 10001;
    int randomPriority = rand() % 101;

    DT_measure_time(size, &DynamicTable::add, randomNumber, randomPriority, "results/DT_add" + filename.str());
    DT_measure_time(size, &DynamicTable::remove, randomNumber, 0, "results/DT_delete" + filename.str());
    DT_measure_time_int(size, &DynamicTable::getSize, "results/DT_size" + filename.str());
    DT_measure_time_int(size, &DynamicTable::peek, "results/DT_peek" + filename.str());
	DT_measure_time(size, &DynamicTable::modifyPriority, randomNumber, randomPriority, "results/DT_modify" + filename.str());
}

void testLinkedList(int size) {
    LL_measure_time(size);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    const int TableSizes[] = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000}; //

    for(int size : TableSizes){
        // testDynamicTable(size);
		// testLinkedList(size);
    }

    // int data[]      = { 10, 20, 30, 40, 50 };
    // int priority[]  = {  2,  5,  1,  4,  3 };
    // int n = sizeof(data) / sizeof(data[0]);

    // create(data, priority, n);
    // display();

    // insert(25, 6);      // higher priority than any existing node
    // display();

    // delete_p(4);        // expects the _correct_ delete_p implementation
    // display();

    // modify_priority(30, 1, 7);
    // display();

    // clear_queue();

    DynamicTable table;
    table.add(10, 2);   
    table.add(9, 2); 
    table.add(3, 98); 
    table.add(5, 4); 
    table.add(2, 2);
    table.print();
    table.modifyPriority(3, 1); 
    table.print();


    return 0;
}
