#pragma once

#include <iterator>

namespace Sort {

    // 定义一个名为 shell_sort 的模板函数
    // 它接受一个随机访问范围（例如，数组或向量）
    template<std::ranges::random_access_range Container>
    constexpr void shell_sort(Container& c) {
        // 获取容器的大小
        int size = std::size(c);
        // 初始化间隔值为 1
        int gap = 1;
        // 使用 3x+1 序列计算最大的间隔值
        while (gap < size / 3)
            gap = gap * 3 + 1;
        // 当间隔值大于等于 1 时，进行希尔排序
        while (gap >= 1)
        {
            // 对每个间隔为 gap 的子序列进行插入排序
            for (int i = gap; i < size; ++i)
            {
                // 将 c[i] 插入到 c[i-gap], c[i-2*gap], c[i-3*gap]... 中
                for (int j = i; j >= gap && c[j] < c[j - gap]; j -= gap)
                    std::swap(c[j], c[j - gap]);
            }
            // 缩小间隔值
            gap = gap / 3;
        }
    }

}