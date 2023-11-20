#pragma once

#include <iterator>

namespace Sort {

    // 定义一个名为 shell_sort 的模板函数
    // 它接受一个随机访问范围（例如，数组或向量）和一个生成间隔序列的函数
    template<std::ranges::random_access_range Container, typename GapCalculator>
    constexpr void shell_sort(Container& c, GapCalculator&& gap_calculator) {
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
                    std::swap(*j, *(j - gap));
            }
        }
    }
}