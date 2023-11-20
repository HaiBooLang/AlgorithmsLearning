#pragma once

#include <vector>

namespace Sort
{

    // 归并函数
    template <typename T>
    std::vector<T> inplace_merge_sort(const std::vector<T>& c1, const std::vector<T>& c2) {
        std::vector<T> result;
        // 预分配内存
        result.reserve(c1.size() + c2.size());

        auto iter1 = c1.begin();
        auto iter2 = c2.begin();

        // 当两个容器都有元素时
        while (iter1 != c1.end() && iter2 != c2.end()) {
            // 如果容器1的当前元素小于或等于容器2的当前元素
            if (*iter1 <= *iter2) {
                // 将容器1的当前元素添加到结果中
                result.push_back(*iter1);
                ++iter1;
            }
            else {
                // 否则，将容器2的当前元素添加到结果中
                result.push_back(*iter2);
                ++iter2;
            }
        }

        // 如果容器1还有剩余元素，将它们添加到结果中
        std::move(iter1, c1.end(), std::back_inserter(result));

        // 如果容器2还有剩余元素，将它们添加到结果中
        std::move(iter2, c2.end(), std::back_inserter(result));

        return result;
    }

}

