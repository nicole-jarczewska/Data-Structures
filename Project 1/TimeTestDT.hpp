#pragma once

void load(const int size, DynamicTable& table);

template <typename T>
void measure_time_no_arg(T* table, void (T::*operation)(), const std::filesystem::path& output_csv);

template <typename T, typename Arg>
void measure_time_arg(T* table, void (T::*operation)(Arg), Arg arg, const std::filesystem::path& output_csv);

template <typename T, typename Arg>
void measure_time_int(T* table, int (T::*operation)(Arg) const, Arg arg, const std::filesystem::path& output_csv);