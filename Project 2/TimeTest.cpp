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
  for (int i = 0; i < size-1; i++) {
      table.initialAdd(rand() % 100001, rand() % 101);
  }
    table.add(rand() % 100001, rand() % 101);
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

template <typename T>
void DT_measure_time_int(const int TableSize, int (T::*operation)() const, const std::filesystem::path& output_csv) {
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

    if (!timingsCollector.save_file(output_csv)) {
        std::cerr << "Error saving timings to " << output_csv << std::endl;
    }
}

void LL_measure_time(int size) {
    std::vector<int> PriorityQueue(size);
    random_array(PriorityQueue.data(), size, 1, 1000); 

    int randomNum = std::rand() % 10001;
    int randomPriority = std::rand() % 101;

    std::vector<TestFunction> tests = {
            { "add", [&]() { insert(randomNum, randomPriority); } },  
            { "delete", [&]() { delete_p(randomPriority); } },
            { "size", [&]() { queue_size(); } },
            { "peek", [&]() { peek(randomPriority); } },  
            { "modify", [&]() { modify_priority(randomNum, std::rand() % 101, randomPriority); } },
    };

    for (const auto& test : tests) {
        std::string filename = "results/LL_" + test.name + std::to_string(size) + ".csv";
        std::ofstream results(filename);
        results << "Time[ns]\n";

        for (int j = 0; j < 100; j++) {
            std::vector<int> tab = PriorityQueue; 
            int priorytety[size];
            for (int k = 0; k < size; ++k) {
                priorytety[k] = rand() % 101;  
            }
            create(tab.data(), priorytety, size);  

            auto start = std::chrono::high_resolution_clock::now();
            test.func();              
            auto end = std::chrono::high_resolution_clock::now();

            long long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            results << std::fixed << std::setprecision(3) << time << "\n";

            // Zwalnianie pamięci
            clear_queue();
        }
        results.close();
        std::cout << "Wyniki zapisano do: " << filename << std::endl;
    }
}