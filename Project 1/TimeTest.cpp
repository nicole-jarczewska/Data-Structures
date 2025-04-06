#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <experimental/filesystem>

#include "DynamicTable.hpp"

class Timer
{
  public:
    void start() { start_time = std::chrono::high_resolution_clock::now(); }
    void stop() { end_time = std::chrono::high_resolution_clock::now(); }
    double milliseconds() const { return std::chrono::duration<double, std::milli>(end_time - start_time).count(); }
  private:
    std::chrono::high_resolution_clock::time_point start_time, end_time;
};

struct TimingData { long N; double ms; };

using Timings = std::vector<TimingData>;

class TimingsCollector {
  public:
    void add_timing(long N, double milliseconds) { timings.push_back({N, milliseconds}); }
    
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

void measure_operation_timings(void (*operation)(DynamicTable&), const DynamicTable& original_tab, const std::filesystem::path& output_csv)
{
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        DynamicTable temp_tab = original_tab; // Copy for a clean start each time
        timer.start();
        operation(temp_tab); // running certain function
        timer.stop();
        timingsCollector.add_timing(temp_tab.getSize(), timer.milliseconds());
    }

    if (!timingsCollector.save_file(output_csv))
        std::cerr << "Error saving timings to " << output_csv << std::endl;
}