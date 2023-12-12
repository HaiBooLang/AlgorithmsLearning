#pragma once

#include <iterator>

namespace Sort
{

    // 选择排序
    // 一种最简单的排序算法是这样的：首先，找到数组中最小的那个元素，其次，将它和数组的第一个元素交换位置（如果第一个元素就是最小元素那么它就和自己交换）。再次，在剩下的元素中找到最小的元素，将它与数组的第二个元素交换位置。如此往复，直到将整个数组排序。这种方法叫做选择排序，因为它在不断地选择剩余元素之中的最小者。
    // 选择排序有两个很鲜明的特点：运行时间和输入无关。为了找出最小的元素而扫描一遍数组并不能为下一遍扫描提供什么信息，而其他算法会更善于利用输人的初始状态。数据移动是最少的。每次交换都会改变两个数组元素的值，因此选择排序用了N次交换一一交换次数和数组的大小是线性关系。我们将研究的其他任何算法都不具备这个特征。
    // 选择排序的最好、最坏和平均时间复杂度都为 O(n^2)，因为无论输入序列的顺序如何，都需要进行 n(n-1)/2 次比较。
    // 选择排序的空间复杂度为 O(1)，因为只需要常数级别的临时变量。
    // 选择排序适用于数据量不大的场景，因为它的时间复杂度较高。

    template <std::ranges::random_access_range Container>
    inline void selection_sort(Container &c)
    {
        // 对容器中的每个元素进行循环
        for (auto i = std::begin(c); i != std::end(c); ++i)
        {
            // 找到从当前元素到容器末尾的最小元素
            auto min_element = std::min_element(i, std::end(c));
            // 如果最小元素小于当前元素，就交换它们的位置
            if (*min_element < *i)
            {
                std::iter_swap(i, min_element);
            }
        }
    }

    // 选择排序的另一种实现，接受迭代器作为参数，可以对任何支持迭代器的容器进行排序。

    template <std::random_access_iterator InputIt>
    inline void selection_sort(InputIt first, InputIt last)
    {
        for (auto i = first; i != last; ++i)
        {
            auto min_element = std::min_element(i, last);
            if (*min_element < *i)
            {
                std::iter_swap(i, min_element);
            }
        }
    }

}