#pragma once

#include <iterator>

namespace Sort
{

    // 定义一个名为 selection_sort 的模板函数
    // 它接受一个随机访问范围（例如，数组或向量）
    template<std::ranges::random_access_range Container>
    constexpr void selection_sort(Container& c)
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

    template<std::random_access_iterator InputIt>
    constexpr void selection_sort(InputIt first, InputIt last)
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