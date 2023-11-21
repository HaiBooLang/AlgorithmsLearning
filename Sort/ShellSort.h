#pragma once

#include <iterator>

namespace Sort {

    // 希尔排序
    // 希尔排序是插入排序的一种更高效的改进版本，也称为“缩小增量排序”，其基本思想是：先将整个待排序的记录序列分割成为若干子序列分别进行直接插入排序，待整个序列中的记录"基本有序"时，再对全体记录进行依次直接插入排序。
    // 希尔排序更高效的原因是它权衡了子数组的规模和有序性，排序之初，各个子数组都很短，排序之后子数组都是部分有序的，这两种情况都很适合插人排序。
    // 希尔排序的时间复杂度与增量序列的选取有关，例如，当增量序列为 1, 2, 4, 8,... 时，最坏时间复杂度为 O(n^2)，但如果使用 Hibbard 提出的增量序列 1, 3, 7, 15,...，则最坏时间复杂度为 O(n^(3/2))。
    // 希尔排序的空间复杂度为 O(1)，因为只需要常数级别的临时变量。
    // 希尔排序适用于大规模数据的排序，特别是当数据量在几千到几万之间时，效率较高。
    
    template<std::ranges::random_access_range Container, typename GapCalculator>
    constexpr void shell_sort(Container& c, GapCalculator&& gap_calculator)
    {
        // 获取容器的大小
        auto size = std::size(c);
        // 使用 gap_calculator 函数生成间隔序列
        auto gaps = gap_calculator(size);
        // 对每个间隔值进行一次希尔排序
        for (const auto& gap : gaps)
        {
            // 对每个间隔为 gap 的子序列进行插入排序
            for (auto i = std::next(c.begin(), gap); i != c.end(); ++i)
            {
                // 将 c[i] 插入到 c[i-gap], c[i-2*gap], c[i-3*gap]... 中
                for (auto j = i; j - c.begin() >= gap && *j < *(j - gap); j -= gap)
                {
                    std::swap(*j, *(j - gap));
                }
            }
        }
    }
}