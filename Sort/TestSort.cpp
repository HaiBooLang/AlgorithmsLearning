#pragma once

#include "../stub.h"
#include "../MeasureTime.h"
#include "SelectionSort.h"
#include "TestSort.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>

namespace Sort
{

    void test_selection_sort(int size, int times)
    {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(1, size);

        std::vector<int> vec(size);

        for (int i = 0; i < times; ++i)
        {
            for (int& value : vec) {
                value = dist(gen);
            }

            std::swap_count = 0;
            auto time = measure_time(selection_sort<std::vector<int>>, vec);
            std::cout << "SelectionSort One case time: " << time << " ns\n";
            assert(std::is_sorted(vec.begin(), vec.end()));
            std::cout << "SelectionSort Number of swaps: " << std::swap_count << std::endl;
        }
    }

}