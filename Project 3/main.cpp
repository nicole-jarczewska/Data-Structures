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
#include <cmath>

#include "include/HashTable.hpp"
#include "HashTable.cpp"
#include "include/HashFunctions.hpp"
#include "HashFunctions.cpp"

#include "include/TimeTest.hpp"
#include "TimeTest.cpp"

void test(int size, int scenario) {
    std::string s;
    if(scenario == 0) {
        s = "average";
    } else if(scenario == 1) {
         s = "optymisctic";
    } else if(scenario == -1) {
         s = "pesymistic";
    }

    std::ostringstream filename;
    filename << size << s << ".csv";

    measure_time<HashTable, int>(hashMod, size, &HashTable::insert, rand() % 10001, "results/MOD_insert" + filename.str());
    measure_time<HashTable, int>(hashMod, size, &HashTable::remove, rand() % 10001, "results/MOD_remove" + filename.str());
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    const int TableSizes[] = {10};
    const int Scenerios[] = {0}; //-1, 0, 1 

    for(int size : TableSizes){
        for(int scenario : Scenerios){
            test(size, scenario);
        }
    }

    return 0;
}
