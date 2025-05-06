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
    const int TableSizes[] = {10000, 50000, 100000, 500000, 1000000, 2000000, 5000000}; //

    for(int size : TableSizes){
        testDynamicTable(size);
		testLinkedList(size);
    }


    return 0;
}
