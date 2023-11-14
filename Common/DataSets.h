#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>

std::vector<int> generate_random_data(int n) {
    std::vector<int> data(n);
    std::generate(data.begin(), data.end(), std::rand);
    return data;
}

std::vector<int> generate_sorted_data(int n) {
    std::vector<int> data(n);
    std::iota(data.begin(), data.end(), 1);
    return data;
}

std::vector<int> generate_reversed_data(int n) {
    std::vector<int> data(n);
    std::iota(data.rbegin(), data.rend(), 1);
    return data;
}

std::vector<int> generate_constant_data(int n) {
    std::vector<int> data(n, 1);
    return data;
}

std::vector<int> generate_few_unique_data(int n) {
    std::vector<int> data(n);
    std::generate(data.begin(), data.end(), []() { return std::rand() % 10; });
    return data;
}
