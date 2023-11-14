#include <numeric>

#include "TestSearch.h"
#include "../MeasureTime.h"

namespace Search
{

    void test_seach(int size)
    {
        test_binary_search(size);
    }

    void test_binary_search(int size) {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(1, size);

        std::vector<int> data(size);
        for (int& value : data) {
            value = dist(gen);
        }

        std::sort(data.begin(), data.end());

        auto worst_case_time = measure_time(binary_search<std::vector<int>, int>, data, size + 1);
        std::cout << "BinarySearch Worst case time: " << worst_case_time << " ns\n";

        auto best_case_time = measure_time(binary_search<std::vector<int>, int>, data, data[size / 2]);
        std::cout << "BinarySearch Best case time: " << best_case_time << " ns\n";

        long long total_time = 0;
        for (int i = 0; i < 10; ++i) {
            int target = dist(gen);
            total_time += measure_time(binary_search<std::vector<int>, int>, data, target);
        }
        std::cout << "BinarySearch Average case time: " << total_time / 10 << " ns\n";
    }

}