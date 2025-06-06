#pragma once

template <typename T, typename Arg>
void measure_time(int(*HashFunction)(int, int) , const int size, const int scenario, int (T::*operation)(Arg), Arg key, const std::filesystem::path& output_csv);
