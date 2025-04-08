#include <iostream>
#include <stdlib.h>
#include <cstdlib>
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

    int randomNumber = rand() % 1000001;
    int randomIndex = rand() % (size-1);

    DT_measure_time(size, &DynamicTable::addBack, randomNumber, 0, "results/DT_add_back_" + filename.str());
    DT_measure_time(size, &DynamicTable::addFront, randomNumber, 0, "results/DT_add_front_" + filename.str());
    DT_measure_time(size, &DynamicTable::addIndex, randomNumber, randomIndex, "results/DT_append_index_" + filename.str());
	DT_measure_time(size, &DynamicTable::removeFront, 0, 0, "results/DT_delete_first_" + filename.str());
	DT_measure_time(size, &DynamicTable::removeBack, 0, 0, "results/DT_delete_last_" + filename.str());
    DT_measure_time(size, &DynamicTable::removeIndex, 0, randomIndex, "results/DT_delete_index_" + filename.str());
    DT_measure_time_int(size, &DynamicTable::contains, randomNumber, "results/DT_find_value_" + filename.str());
}

void testLinkedList(int size) {
    LL_measure_time(size);
}

int main() {
    const int TableSizes[] = {10000, 50000, 100000, 500000, 1000000, 2000000, 5000000};

    for(int size : TableSizes){
        testDynamicTable(size);
		testLinkedList(size);
    }


    return 0;
}
