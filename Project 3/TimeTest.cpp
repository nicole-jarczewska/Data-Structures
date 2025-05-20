#include "include/TimeTest.hpp"
#include "include/HashTable.hpp"

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

template <typename T, typename Arg>
void measure_time(int(*HashFunction)(int, int), const int size, const int scenario, bool (T::*operation)(Arg), Arg key, const std::filesystem::path& output_csv) {
    Timer timer;
    TimingsCollector timingsCollector;
    const int repeats = 100;

    for (int i = 0; i < repeats; ++i) {
        T HashTable(size, HashFunction);
        HashTable.load(size, scenario);
        timer.start();
        (HashTable.*operation)(key);
        timer.stop();
        timingsCollector.add_timing(timer.nanoseconds());
    }

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
};