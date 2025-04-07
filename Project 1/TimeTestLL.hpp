#pragma once

struct TestFunction {
    std::string name;
    std::function<void()> func;
};


void measure_time(int size);