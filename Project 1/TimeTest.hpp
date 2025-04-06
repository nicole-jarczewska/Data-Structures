#pragma once

template <typename T>
void measure_time_no_arg(T* table, void (T::*operation)(), const std::filesystem::path& output_csv);

template <typename T, typename Arg>
void measure_time_arg(T* table, void (T::*operation)(Arg), Arg arg, const std::filesystem::path& output_csv);

template <typename T, typename Arg>
void measure_time_bool(T* table, bool (T::*operation)(Arg), Arg arg, const std::filesystem::path& output_csv);