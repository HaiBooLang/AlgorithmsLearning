#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>

inline std::vector<int> generate_random_data(int n) {
    std::vector<int> data(n);
    std::generate(data.begin(), data.end(), std::rand);
    return data;
}

inline std::vector<int> generate_sorted_data(int n) {
    std::vector<int> data(n);
    std::iota(data.begin(), data.end(), 1);
    return data;
}

inline std::vector<int> generate_irregular_sorted_data(int n) {
    std::vector<int> data(n);
    int current = 1;
    std::generate(data.begin(), data.end(), [&current]() {
        int value = current;
        current += (current % 2 == 0) ? 1 : 3;
        return value;
        });
    return data;
}

inline std::vector<int> generate_partially_sorted_data(int n) {
    std::vector<int> data(n);
    int i = 0;
    while (i < n) {
        int block_size = std::rand() % 10 + 10;
        if (i + block_size > n) {
            block_size = n - i;
        }
        if ((i / block_size) % 2 == 0) {
            std::iota(data.begin() + i, data.begin() + i + block_size, 1);
        } else {
            std::generate(data.begin() + i, data.begin() + i + block_size, std::rand);
        }
        i += block_size;
    }
    return data;
}

inline std::vector<int> generate_reversed_data(int n) {
    std::vector<int> data(n);
    std::iota(data.rbegin(), data.rend(), 1);
    return data;
}

inline std::vector<int> generate_constant_data(int n) {
    std::vector<int> data(n, 1);
    return data;
}

inline std::vector<int> generate_few_unique_data(int n) {
    std::vector<int> data(n);
    std::generate(data.begin(), data.end(), []() { return std::rand() % 10; });
    return data;
}
