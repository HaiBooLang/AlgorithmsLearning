#pragma once

#include "../Common/stub.h"
#include "../Common/MeasureTime.h"
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "TestSort.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>
#include <cassert>
#include <functional>

namespace Sort
{
	void test_sort() {
        test_merge_sort();

	}

    void test_merge_sort() {

        auto data1 = generate_irregular_sorted_data(1000);
        auto data2 = generate_irregular_sorted_data(1000);

        auto result1 = merge_sort(data1, data2);
        assert(std::is_sorted(result1.begin(), result1.end()));

        auto data3 = generate_random_data(1000);
        top_down_merge_sort<int>(data3.begin(), data3.end());
        assert(std::is_sorted(data3.begin(), data3.end()));

    }

	void test_selection_sort(int size, int times)
	{
        // Shell's original sequence
        auto shell_sequence = [](int size) {
            std::vector<int> gaps;
            for (int gap = 1; gap < size; gap = gap * 2 + 1)
                gaps.push_back(gap);
            std::reverse(gaps.begin(), gaps.end());
            //for (const auto& gap : gaps)
            //{
            //    std::cout << gap << " ";
            //}
            return gaps;
        };

        // Knuth's sequence
        auto knuth_sequence = [](int size) {
            std::vector<int> gaps;
            for (int gap = 1; gap < size / 3; gap = gap * 3 + 1)
                gaps.push_back(gap);
            std::reverse(gaps.begin(), gaps.end());
            return gaps;
        };

        // Sedgewick's sequence
        auto sedgewick_sequence = [](int size) {
            std::vector<int> gaps;
            int k = 0;
            while (true) {
                int gap;
                if (k == 0) {
                    gap = 1;
                }
                else {
                    gap = std::pow(4, k) + 3 * std::pow(2, k - 1) + 1;
                }
                if (gap > size) break;
                gaps.push_back(gap);
                ++k;
            }
            std::reverse(gaps.begin(), gaps.end());
            return gaps;
        };

        // Hibbard's sequence
        auto hibbard_sequence = [](int size) {
            std::vector<int> gaps;
            int k = 1;
            while (true) {
                int gap = std::pow(2, k) - 1;
                if (gap > size) break;
                gaps.push_back(gap);
                ++k;
            }
            std::reverse(gaps.begin(), gaps.end());
            return gaps;
        };

        // Papernov & Stasevich sequence
        auto papernov_stasevich_sequence = [](int size) {
            std::vector<int> gaps;
            for (int k = 1; ; ++k) {
                int gap = (1 << k) + 1;
                if (gap > size) break;
                gaps.push_back(gap);
            }
            if (gaps.empty() || gaps.back() != 1) {
                gaps.push_back(1);
            }
            std::reverse(gaps.begin(), gaps.end());
            return gaps;
        };

        // Pratt's sequence
        auto pratt_sequence = [](int size) {
            std::vector<int> gaps;
            for (int p = 0; ; ++p) {
                for (int q = 0; ; ++q) {
                    int gap = std::pow(2, p) * std::pow(3, q);
                    if (gap > size) break;
                    gaps.push_back(gap);
                }
                if (std::pow(2, p) > size) break;
            }
            std::reverse(gaps.begin(), gaps.end());
            return gaps;
        };


		std::vector<std::pair<std::string, std::function<void(std::vector<int>&)>>> function = {
            {"shell sort 2x + 1", [&shell_sequence](std::vector<int>& data) {shell_sort(data, shell_sequence); }},
            {"shell sort 3x + 1", [&knuth_sequence](std::vector<int>& data) {shell_sort(data, knuth_sequence); }},
            {"shell sort 4^k + 3*2^(k-1) + 1", [&sedgewick_sequence](std::vector<int>& data) {shell_sort(data, sedgewick_sequence); }},
            {"shell sort 2^k - 1", [&hibbard_sequence](std::vector<int>& data) {shell_sort(data, hibbard_sequence); }},
            {"shell sort 2^k + 1", [&papernov_stasevich_sequence](std::vector<int>& data) {shell_sort(data, papernov_stasevich_sequence); }},
			{"shell sort 2^p * 3^q", [&pratt_sequence](std::vector<int>& data) {shell_sort(data, pratt_sequence); }},
			{"selection sort", [](std::vector<int>& data) {selection_sort(data); } },
			{"insertion sort", [](std::vector<int>& data) {insertion_sort(data); } },
		};


		compare_with_all_datasets(function, 10000, 1);

	}

}