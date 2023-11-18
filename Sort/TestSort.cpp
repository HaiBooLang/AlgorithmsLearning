#pragma once

#include "../Common/stub.h"
#include "../Common/MeasureTime.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "TestSort.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <functional>

namespace Sort
{
    void test_sort() {

    }



    void test_selection_sort(int size, int times)
    {
        
        std::vector<std::pair<std::string, std::function<void(std::vector<int>&)>>> function = {
            {"shell sort", [](std::vector<int>& data) {shell_sort(data); } },
            {"selection sort", [](std::vector<int>& data) {selection_sort(data); } },
            {"insertion sort", [](std::vector<int>& data) {insertion_sort(data); } },
        };

        compare_with_all_datasets(function, 10000, 1);
        //std::mt19937 gen(std::random_device{}());
        //std::uniform_int_distribution<> dist(1, size);

        //std::vector<int> vec(size);

        //for (int i = 0; i < times; ++i)
        //{
        //    for (int& value : vec) {
        //        value = dist(gen);
        //    }

        //    Status::swap_count = 0;
        //    auto time = measure_time(selection_sort<std::vector<int>>, vec);
        //    std::cout << "SelectionSort One case time: " << time << " ns\n";
        //    assert(std::is_sorted(vec.begin(), vec.end()));
        //    std::cout << "SelectionSort Number of swaps: " << Status::swap_count << std::endl;
        //}
    }

}