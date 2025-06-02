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

    measure_time<HashTable, int>(hashMod, size, loadfactor, scenario, &HashTable::insert, rand() % size, "results/MOD_insert" + filename.str());
    measure_time<HashTable, int>(hashMod, size, loadfactor, scenario, &HashTable::remove, rand() % size, "results/MOD_remove" + filename.str());

    measure_time<HashTable, int>(fibonacci, size, loadfactor, scenario, &HashTable::insert, rand() % size, "results/FIB_insert" + filename.str());
    measure_time<HashTable, int>(fibonacci, size, loadfactor, scenario, &HashTable::remove, rand() % size, "results/FIB_remove" + filename.str());

    measure_time<HashTable, int>(bitMix, size, loadfactor, scenario, &HashTable::insert, rand() % size, "results/BIT_insert" + filename.str());
    measure_time<HashTable, int>(bitMix, size, loadfactor, scenario, &HashTable::remove, rand() % size, "results/BIT_remove" + filename.str());

    int fill = static_cast<int>(size * (loadfactor / 100.0));
    std::ostringstream filename2;
    filename2 << size << "_filled_" << loadfactor << ".csv";

    histograms(hashMod, size, fill, "histograms/DMOD_" + filename2.str());
    histograms(fibonacci, size, fill, "histograms/DFIB_" + filename2.str());
    histograms(bitMix, size, fill, "histograms/DBIT_" + filename2.str());  
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    const int Sizes[] = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000}; //10000, 20000, 50000, 100000, 200000, 500000, 10000001000, 2000, 5000, 10000, 20000, 50000,
    const int LoadFactors[] = {10, 25, 50, 75}; //as in: 10%, 25%, 50%, 75%
    const int Scenerios[] = {0}; //-1 - pesymistic, 0 - average, 1 - optymistic

    for(int size : Sizes){
        for(int loadfactor : LoadFactors){
            for(int scenario : Scenerios)
                test(size, loadfactor, scenario);
        }
    }

    return 0;
}
