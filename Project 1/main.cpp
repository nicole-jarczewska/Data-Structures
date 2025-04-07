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


#include "DynamicTable.hpp"
#include "DynamicTable.cpp"
#include "LinkedList.hpp"
#include "LinkedList.cpp"

#include "TimeTestDT.hpp"
#include "TimeTestDT.cpp"
#include "TimeTestLL.hpp"
#include "TimeTestLL.cpp"

void testDynamicTable(int size) {
    std::ostringstream filename;
    filename << size << ".csv";

    int randomNum = rand() % size;

    measure_time_arg(size, &DynamicTable::addBack, randomNum, "results/DT_addBack_" + filename.str());
    measure_time_arg(size, &DynamicTable::addFront, randomNum, "results/DT_addFront_" + filename.str());
	measure_time_no_arg(size, &DynamicTable::removeFront, "results/DT_removeFront_" + filename.str());
	measure_time_no_arg(size, &DynamicTable::removeBack, "results/DT_removeBack_" + filename.str());
    measure_time_int(size, &DynamicTable::contains, randomNum, "results/DT_contains_" + filename.str());
}

void testLinkedList(int size) {
    measure_time(size);
}

int main() {
    const int TableSizes[] = {10000, 50000, 100000, 500000, 1000000, 2000000, 5000000};

    for(int size : TableSizes){
        testDynamicTable(size);
		testLinkedList(size);
    }


    return 0;
}
