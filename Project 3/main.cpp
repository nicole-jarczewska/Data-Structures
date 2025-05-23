#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <filesystem>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "include/HashTable.hpp"
#include "HashTable.cpp"
#include "include/HashFunctions.hpp"
#include "HashFunctions.cpp"

#include "include/TimeTest.hpp"
#include "TimeTest.cpp"

void test(int size, int loadfactor, int scenario) {
    std::string s = "average";

    if(scenario == 1) {
         s = "optymisctic";
    } else if(scenario == -1) {
         s = "pesymistic";
    }

    std::ostringstream filename;
    filename << size << "_" << loadfactor << "%_" << s << ".csv";

    measure_time<HashTable, int>(hashMod, size, loadfactor, scenario, &HashTable::insert, rand() % 10001, "results/MOD_insert" + filename.str());
    measure_time<HashTable, int>(hashMod, size, loadfactor, scenario, &HashTable::remove, rand() % 10001, "results/MOD_remove" + filename.str());

    measure_time<HashTable, int>(fibonacci, size, loadfactor, scenario, &HashTable::insert, rand() % 10001, "results/FIB_insert" + filename.str());
    measure_time<HashTable, int>(fibonacci, size, loadfactor, scenario, &HashTable::remove, rand() % 10001, "results/FIB_remove" + filename.str());

    measure_time<HashTable, int>(square, size, loadfactor, scenario, &HashTable::insert, rand() % 10001, "results/SQR_insert" + filename.str());
    measure_time<HashTable, int>(square, size, loadfactor, scenario, &HashTable::remove, rand() % 10001, "results/SQR_remove" + filename.str());
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    const int Sizes[] = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000}; //10000, 20000, 50000, 100000, 200000, 500000, 1000000
    const int LoadFactors[] = {10, 25, 50, 75}; //as in: 10%, 25%, 50%, 75%
    const int Scenerios[] = {0}; //-1 - pesymistic, 0 - average, 1 - optymistic

    for(int size : Sizes){
        for(int loadfactor : LoadFactors){
            for(int scenario : Scenerios)
                test(size, loadfactor, scenario);
        }
    }

    // std::cout << "123" << std::endl;
    // std::cout << square(123, 100) << std::endl;

    return 0;
}
