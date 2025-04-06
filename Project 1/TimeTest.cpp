#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>

#include "TimeTest.hpp"

class Timer
{
  public:
    void start() { start_time = std::chrono::high_resolution_clock::now(); }
    void stop() { end_time = std::chrono::high_resolution_clock::now(); }
    double milliseconds() const { return std::chrono::duration<double, std::milli>(end_time - start_time).count(); }
  private:
    std::chrono::high_resolution_clock::time_point start_time, end_time;
};

struct TimingData { double ms; };

using Timings = std::vector<TimingData>;

class TimingsCollector {
  public:
    void add_timing(double milliseconds) { timings.push_back({milliseconds}); }
    
    bool save_file(const std::filesystem::path& filepath) const {
        std::ofstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << std::endl;
            return false;
        }
        for (const auto& entry : timings)
            file << entry.ms << "\n";
        return true;
    }

    Timings get_timings() const { return timings; }

  private:
    Timings timings;
};

template <typename T>
void measure_time_no_arg(T* table, void (T::*operation)(), const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        T temp_table = *table;
        timer.start();
        (temp_table.*operation)();
        timer.stop();
        timingsCollector.add_timing(timer.milliseconds());
    }
    if (timingsCollector.get_timings().empty()) {
      std::cerr << "No timings collected. File will not be saved." << std::endl;
  } 
    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Failed to save." << std::endl;
}

template <typename T, typename Arg>
void measure_time_arg(T* table, void (T::*operation)(Arg), Arg arg, const std::filesystem::path& output_csv) {
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        T temp_table = *table;
        timer.start();
        (temp_table.*operation)(arg);
        timer.stop();
        timingsCollector.add_timing(timer.milliseconds());
    }

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
}

template <typename T, typename Arg>
void measure_time_bool(T* table, bool (T::*operation)(Arg), Arg arg, const std::filesystem::path& output_csv) {
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        T temp_table = *table;
        timer.start();
        (temp_table.*operation)(arg);
        timer.stop();
        timingsCollector.add_timing(timer.milliseconds());
    }

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
}