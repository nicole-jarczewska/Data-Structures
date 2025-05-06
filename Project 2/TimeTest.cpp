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
    std::vector<int> priorities(size);
    random_array(PriorityQueue.data(), size, 1, 1000); 
    random_array(priorities.data(), size, 1, 100);

    int randomNum = std::rand() % 10001;
    int randomPriority = std::rand() % 101;


        std::vector<std::function<void(const std::vector<int>&, const std::vector<int>&)>> tests = {
            // INSERT
            [&](const std::vector<int>& data, const std::vector<int>& prio) {
                int index = rand() % size;
                insert(data[index], prio[index]);
            },

            // DELETE
            [&](const std::vector<int>& data, const std::vector<int>& prio) {
                int index = rand() % size;
                delete_p(prio[index]);
            },

            // QUEUE_SIZE
            [&](const std::vector<int>&, const std::vector<int>&) {
                queue_size();
            },

            // PEEK
            [&](const std::vector<int>&, const std::vector<int>& prio) {
                int index = rand() % size;
                peek(prio[index]);
            },

            // MODIFY_PRIORITY
            [&](const std::vector<int>& data, const std::vector<int>& prio) {
                int index = rand() % size;
                modify_priority(data[index], prio[index], prio[index] + 1);
            }
        };

        std::vector<std::string> test_names = { "add", "delete", "size", "peek", "modify" }; //

        for (int t = 0; t < tests.size(); ++t) {
            std::string filename = "results/LL_" + test_names[t] + std::to_string(size) + ".csv";
            std::ofstream results(filename);
            results << "Time[ns]\n";

            for (int j = 0; j < 100; j++) {
                // create(const_cast<int*>(PriorityQueue.data()), const_cast<int*>(priorities.data()), size);
                create_optimized(PriorityQueue.data(), priorities.data(), size);

                auto start = std::chrono::high_resolution_clock::now();
                tests[t](PriorityQueue, priorities);
                auto end = std::chrono::high_resolution_clock::now();

                long long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                results << std::fixed << std::setprecision(3) << time << "\n";

                clear_queue();
            }

            results.close();
            std::cout << "Wyniki zapisano do: " << filename << std::endl;
        }
}
