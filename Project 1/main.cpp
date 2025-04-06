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
#include "LinkedList.hpp"
#include "LinkedList.cpp"
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

    while (inputFile >> number && count < size){
        table.addBack(number);
        ++count;
    }

    inputFile.close();
}


int main() {
    DynamicTable table;
    const int TableSize = 100000;

    load(TableSize, table);
    

    //measure_time_no_arg(&table, &DynamicTable::removeBack, "results/removeBack.csv");
    //measure_time_no_arg(&table, &DynamicTable::removeFront, "results/removeFront.csv");
    //measure_time_arg(&table, &DynamicTable::addBack, 1, "results/addBack.csv");
    //measure_time_arg(&table, &DynamicTable::addFront, 1, "results/addFront.csv");
    //measure_time_int(&table, &DynamicTable::contains, 1, "contains.csv");

    int A[] = { 1,2,3};
	int size = sizeof(A) / sizeof(A[0]);


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


    //table.print();  
    return 0;
}
