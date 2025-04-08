#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

#include "include/TimeTest.hpp"
#include "include/DynamicTable.hpp"
#include "include/LinkedList.hpp"

class Timer
{
  public:
    void start() { start_time = std::chrono::high_resolution_clock::now(); }
    void stop() { end_time = std::chrono::high_resolution_clock::now(); }
    long long nanoseconds() const { 
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count(); 
    }
  
  private:
    std::chrono::high_resolution_clock::time_point start_time, end_time;
};

struct TimingData { double ns; };

using Timings = std::vector<TimingData>;

class TimingsCollector {
    public:
        void add_timing(double nanoseconds) { timings.push_back({nanoseconds}); }
        
        bool save_file(const std::filesystem::path& filepath) const {
            std::ofstream file(filepath);
            if (!file.is_open()) {
                std::cerr << "Failed to open file: " << filepath << std::endl;
                return false;
            }
            for (const auto& entry : timings)
                file << entry.ns << "\n";
            return true;
        }
    
        Timings get_timings() const { return timings; }
    
    private:
        Timings timings;
    };


void DT_load(const int size, DynamicTable& table) {
  std::ifstream inputFile("Dataset.txt");
  if (!inputFile) {
      std::cerr << "Failed to load the data\n";
      return;
  }

  int number;
  int count = 0;

  while (inputFile >> number && count < size){
      table.addBack(number, 0);
      ++count;
  }

  inputFile.close();
}


template <typename T>
void measure_time_no_arg(const int TableSize, void (T::*operation)(), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        DynamicTable table;
        DT_load(TableSize-1, table);
        timer.start();
        (table.*operation)();
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
    }
    const auto& timings = timingsCollector.get_timings();
    if (timings.empty()) {
        std::cerr << "No timings collected. File will not be saved." << std::endl;
    } else {
        if (!timingsCollector.save_file(output_csv)) {
            std::cerr << "Failed to save timings to " << output_csv << std::endl;
        }
    }  
}

template <typename T, typename Arg>
void DT_measure_time(const int TableSize, void (T::*operation)(Arg, Arg), Arg element, Arg index, const std::filesystem::path& output_csv) {
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        DynamicTable table;
        DT_load(TableSize-1, table);
        timer.start();
        (table.*operation)(element, index);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
    }

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
}

template <typename T, typename Arg>
void DT_measure_time_int(const int TableSize, int (T::*operation)(Arg) const, Arg element, const std::filesystem::path& output_csv) {
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        DynamicTable table;
        DT_load(TableSize-1, table);
        timer.start();
        (table.*operation)(element);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
    }

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
}

std::vector<int> LL_load(int size) {
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

void LL_measure_time(int size) {
    std::vector<int> original = LL_load(size);
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