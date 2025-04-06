#pragma once

void measure_operation_timings(void (*operation)(DynamicTable&), const DynamicTable& original_tab, const std::filesystem::path& output_csv);