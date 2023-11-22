#pragma once

#include <iterator>

namespace Sort {

    // 插入排序
    // 插入排序是一种简单的排序算法，它的工作原理是通过构建有序序列，对于未排序数据，在已排序序列中从后向前扫描，找到相应位置并插入。
    // 插入排序的最好情况时间复杂度为 O(n)，即输入序列已经完全排序。最坏情况时间复杂度为 O(n^2)，即输入序列是逆序的。平均时间复杂度为 O(n^2)。
    // 插入排序的空间复杂度为 O(1)，因为只需要常数级别的临时变量。
    // 插入排序适用于数据量不大，或者输入数据部分有序的场景（插人排序能够立即发现每个元素都已经在合适的位置上）。

	template<std::ranges::random_access_range Container>
    void insertion_sort(Container& c) 
    {
        // 对容器中的每个元素进行循环
        for (auto i = std::begin(c); i != std::end(c); ++i)
        {
            // 保存当前元素的值
            auto key = *i;
            // 初始化另一个指向当前元素的迭代器
            auto j = i;
            // 从当前元素开始向前扫描，如果前一个元素大于当前元素的值，就将前一个元素向后移动一位
            while (j != std::begin(c) && *(j - 1) > key) 
            {
                *j = *(j - 1);
                --j;
            }

            // 如果 j 指向的位置不是初始的位置，就将保存的值插入到正确的位置
            if (j != i)
            {
                *j = key;
            }
        }
    }

    // 归并排序的另一种实现，接受迭代器作为参数，可以对任何支持随机访问迭代器的容器进行排序。

    template<typename InputIt>
    void insertion_sort(InputIt first, InputIt last) {
        if (first == last) return; // 如果范围为空，直接返回

        for (auto i = first + 1; i != last; ++i) {
            auto key = *i;
            auto j = i;

            // 从当前元素开始向前扫描，如果前一个元素大于当前元素的值，就将前一个元素向后移动一位
            while (j != first && *(j - 1) > key) {
                *j = *(j - 1);
                --j;
            }

            // 如果 j 指向的位置不是初始的位置，就将保存的值插入到正确的位置
            *j = key;
        }
    }
}