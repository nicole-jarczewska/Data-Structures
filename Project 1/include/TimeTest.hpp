#pragma once

struct TestFunction {
    std::string name;
    std::function<void()> func;
};


void LL_measure_time(int size);

void DT_load(const int size, DynamicTable& table);

template <typename T>
void measure_time_no_arg(T* table, void (T::*operation)(), const std::filesystem::path& output_csv);

template <typename T, typename Arg>
void DT_measure_time(const int TableSize, void (T::*operation)(Arg, Arg), Arg element, Arg index, const std::filesystem::path& output_csv);

template <typename T, typename Arg>
void DT_measure_time_int(const int TableSize, int (T::*operation)(Arg) const, Arg arg, const std::filesystem::path& output_csv);