#pragma once

#include "../Common/stub.h"
#include "../Common/MeasureTime.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "TestSort.h"
#include "QuickSort.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <functional>

namespace Sort
{
    // Shell's original sequence
    auto shell_sequence = [](int size)
    {
        std::vector<int> gaps;
        for (int gap = 1; gap < size; gap = gap * 2 + 1)
            gaps.push_back(gap);
        std::reverse(gaps.begin(), gaps.end());
        // for (const auto& gap : gaps)
        //{
        //     std::cout << gap << " ";
        // }
        return gaps;
    };

    // Knuth's sequence
    auto knuth_sequence = [](int size)
    {
        std::vector<int> gaps;
        for (int gap = 1; gap < size / 3; gap = gap * 3 + 1)
            gaps.push_back(gap);
        std::reverse(gaps.begin(), gaps.end());
        return gaps;
    };

    // Sedgewick's sequence
    auto sedgewick_sequence = [](int size)
    {
        std::vector<int> gaps;
        int k = 0;
        while (true)
        {
            int gap;
            if (k == 0)
            {
                gap = 1;
            }
            else
            {
                gap = std::pow(4, k) + 3 * std::pow(2, k - 1) + 1;
            }
            if (gap > size)
                break;
            gaps.push_back(gap);
            ++k;
        }
        std::reverse(gaps.begin(), gaps.end());
        return gaps;
    };

    // Hibbard's sequence
    auto hibbard_sequence = [](int size)
    {
        std::vector<int> gaps;
        int k = 1;
        while (true)
        {
            int gap = std::pow(2, k) - 1;
            if (gap > size)
                break;
            gaps.push_back(gap);
            ++k;
        }
        std::reverse(gaps.begin(), gaps.end());
        return gaps;
    };

    // Papernov & Stasevich sequence
    auto papernov_stasevich_sequence = [](int size)
    {
        std::vector<int> gaps;
        for (int k = 1;; ++k)
        {
            int gap = (1 << k) + 1;
            if (gap > size)
                break;
            gaps.push_back(gap);
        }
        if (gaps.empty() || gaps.back() != 1)
        {
            gaps.push_back(1);
        }
        std::reverse(gaps.begin(), gaps.end());
        return gaps;
    };

    // Pratt's sequence
    auto pratt_sequence = [](int size)
    {
        std::vector<int> gaps;
        for (int p = 0;; ++p)
        {
            for (int q = 0;; ++q)
            {
                int gap = std::pow(2, p) * std::pow(3, q);
                if (gap > size)
                    break;
                gaps.push_back(gap);
            }
            if (std::pow(2, p) > size)
                break;
        }
        std::reverse(gaps.begin(), gaps.end());
        return gaps;
    };

    void test_merge_sort()
    {

        auto data1 = generate_irregular_sorted_data(1000);
        auto data2 = generate_irregular_sorted_data(1000);

        auto result1 = merge_sort(data1, data2);
        assert(std::is_sorted(result1.begin(), result1.end()));

        auto data3 = generate_random_data(1000);
        down_top_merge_sort<int>(data3.begin(), data3.end());
        assert(std::is_sorted(data3.begin(), data3.end()));

        auto data4 = generate_random_data(1000);
        top_down_merge_sort<int>(data3.begin(), data3.end());
        assert(std::is_sorted(data3.begin(), data3.end()));

        std::cout << "Merge sort test passed successfully.\n"
                  << std::endl;
    }

    void test_selection_sort()
    {
        auto data = generate_random_data(1000);
        selection_sort(data);
        assert(std::is_sorted(data.begin(), data.end()));

        std::cout << "Selection sort test passed successfully.\n"
                  << std::endl;
    }

    void test_quick_sort()
    {
        auto data = generate_random_data(1000);
        quick_sort(data);
        assert(std::is_sorted(data.begin(), data.end()));

        std::cout << "Quick sort test passed successfully.\n"
                  << std::endl;
    }

    void test_sort(int size, int times)
    {
        test_quick_sort();
        test_selection_sort();
        test_merge_sort();

        std::vector<std::pair<std::string, std::function<void(std::vector<int> &)>>> functions =
            {
                {"shell sort 2x + 1", [](std::vector<int> &data)
                 { shell_sort(data, shell_sequence); }},
                {"shell sort 3x + 1", [](std::vector<int> &data)
                 { shell_sort(data, knuth_sequence); }},
                {"shell sort 4^k + 3*2^(k-1) + 1", [](std::vector<int> &data)
                 { shell_sort(data, sedgewick_sequence); }},
                {"shell sort 2^k - 1", [](std::vector<int> &data)
                 { shell_sort(data, hibbard_sequence); }},
                {"shell sort 2^k + 1", [](std::vector<int> &data)
                 { shell_sort(data, papernov_stasevich_sequence); }},
                {"shell sort 2^p * 3^q", [](std::vector<int> &data)
                 { shell_sort(data, pratt_sequence); }},
                {"selection sort", [](std::vector<int> &data)
                 { selection_sort(data); }},
                {"insertion sort", [](std::vector<int> &data)
                 { insertion_sort(data); }},
                {"down top merge sort", [](std::vector<int> &data)
                 { down_top_merge_sort<int>(data.begin(), data.end()); }},
                {"top down merge sort", [](std::vector<int> &data)
                 { top_down_merge_sort<int>(data.begin(), data.end()); }},
                {"quick sort", [](std::vector<int> &data)
                 { quick_sort(data); }}};

        compare_with_all_datasets(functions, size, times);
    }
}