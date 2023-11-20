#pragma once

#include <iterator>

namespace Sort {

	template<std::ranges::random_access_range Container>
    constexpr void insertion_sort(Container& c) 
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
}