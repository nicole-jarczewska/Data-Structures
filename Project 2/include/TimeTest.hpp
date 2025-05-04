#pragma once

struct TestFunction {
    std::string name;
    std::function<void()> func;
};


void LL_measure_time(int size);

void DT_load(const int size, DynamicTable& table);

template <typename T, typename Arg>
void DT_measure_time(const int TableSize, void (T::*operation)(Arg, Arg), Arg element, Arg index, const std::filesystem::path& output_csv);

template <typename T>
void DT_measure_time_int(const int TableSize, int (T::*operation)() const, const std::filesystem::path& output_csv);