#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

#include "TimeTest.hpp"
#include "DynamicTable.hpp"

void load(const int size, DynamicTable& table) {
  std::ifstream inputFile("Dataset.txt");
  if (!inputFile) {
      std::cerr << "Failed to load the data\n";
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

template <typename T>
void measure_time_no_arg(const int TableSize, void (T::*operation)(), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        DynamicTable table;
        load(TableSize-1, table);
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
void measure_time_arg(const int TableSize, void (T::*operation)(Arg), Arg arg, const std::filesystem::path& output_csv) {
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        DynamicTable table;
        load(TableSize-1, table);
        timer.start();
        (table.*operation)(arg);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
    }

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
}

template <typename T, typename Arg>
void measure_time_int(const int TableSize, int (T::*operation)(Arg) const, Arg arg, const std::filesystem::path& output_csv) {
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        DynamicTable table;
        load(TableSize-1, table);
        timer.start();
        (table.*operation)(arg);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
    }

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
}