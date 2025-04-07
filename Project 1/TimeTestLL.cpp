#include <iostream>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <sstream>
#include <functional>
#include <filesystem>

#include "LinkedList.hpp"
#include "TimeTestLL.hpp"

std::vector<int> loadDataFromTxt(int size) {
    std::ifstream file("Dataset.txt");
    std::vector<int> data;
    int value;

    while (file >> value) {
        data.push_back(value);
    }

    if (data.size() < size) {
        std::cerr << "Error: Not enough data in Dataset.txt!" << std::endl;
        std::exit(1);
    }

    return std::vector<int>(data.begin(), data.begin() + size);
}

void measure_time(int size) {
    std::vector<int> original = loadDataFromTxt(size);
    int randomNum = std::rand() % size;

    std::vector<TestFunction> tests = {
        { "add_back",    [=]() { add_back(randomNum); } },
        { "add_front",   [=]() { add_front(randomNum); } },
        { "append_index",[=]() { append_index(first, 1, randomNum); } },
        { "delete_first",[=]() { delete_first(); } },
        { "delete_last", [=]() { delete_last(); } },
        { "delete_index",[=]() { delete_index(first, randomNum); } },
        { "find_value",  [=]() { find_value(first, randomNum); } },
    };

    for (const auto& test : tests) {
        std::string filename = "results/LL_" + test.name + "_" + std::to_string(size) + ".csv";
        std::ofstream results(filename);
        results << "Time[ns]\n";
        int num_tests = 100;

        for (int j = 0; j < num_tests; j++) {
            std::vector<int> tab = original;
            create(tab.data(), size);

            auto start = std::chrono::high_resolution_clock::now();
            test.func();
            auto end = std::chrono::high_resolution_clock::now();

            long long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            results << std::fixed << std::setprecision(3) << time << "\n";

            // Free memory
            while (first != nullptr) {
                Node* tmp = first;
                first = first->next;
                delete tmp;
            }
        }

        results.close();
        std::cout << "saved to: " << filename << std::endl;
    }
}
