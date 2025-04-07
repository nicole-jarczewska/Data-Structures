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


#include "DynamicTable.hpp"
#include "DynamicTable.cpp"
#include "LinkedList.hpp"
#include "LinkedList.cpp"
#include "TimeTestDT.hpp"
#include "TimeTestDT.cpp"

void testDynamicTable(int size) {
    std::ostringstream filename;
    filename << size << ".csv";

    int randomNum = rand() % 100001;

    measure_time_no_arg(size, &DynamicTable::removeBack, "results/removeBack_" + filename.str());
    measure_time_no_arg(size, &DynamicTable::removeFront, "results/removeFront_" + filename.str());
    measure_time_arg(size, &DynamicTable::addBack, randomNum, "results/addBack_" + filename.str());
    measure_time_arg(size, &DynamicTable::addFront, randomNum, "results/addFront_" + filename.str());
    measure_time_int(size, &DynamicTable::contains, randomNum, "results/contains_" + filename.str());
}

int main() {
    const int TableSizes[] = {10000, 50000, 100000, 500000, 1000000, 2000000, 5000000};

    for(int size : TableSizes){
        testDynamicTable(size);
    }


    int A[] = { 1,2,3};
	int size = sizeof(A) / sizeof(A[0]);

{
    /*
	std::cout << "Wejsciowa lista: ";
	create(A,size);
	display(first);
	std::cout << std::endl;

	std::cout << "Dodanie elementu na koniec: ";
	add_back(300);
	display(first);
	std::cout << std::endl;

	std::cout << "Dodanie elementu na wybrany index: ";
	append_index(first, 2, 10);
	display(first);
	std::cout << std::endl;

	std::cout << "Dodanie elementu na poczatek: ";
	add_front(23);
	display(first);
	std::cout << std::endl;

	std::cout << "Usuniecie pierwszego elementu: ";
	delete_first();
	display(first);
	std::cout << std::endl;

	std::cout << "Usuniecie ostatniego elementu: ";
	delete_last();
	display(first);
	std::cout << std::endl;

	std::cout << "Usuniecie z indexu: ";
	delete_index(first, 2);
	display(first);
    */
}

    //
    return 0;
}
