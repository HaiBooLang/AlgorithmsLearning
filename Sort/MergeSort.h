#pragma once

#include <vector>

namespace Sort
{

    // 归并函数
    template <typename T>
    std::vector<T> merge_sort(const std::vector<T>& c1, const std::vector<T>& c2) {
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

    // std::vector<typename std::iterator_traits<Iterator>::value_type>
    template <typename T>
    std::vector<T> merge_sort(typename std::vector<T>::iterator begin1, typename std::vector<T>::iterator end1, typename std::vector<T>::iterator begin2, typename std::vector<T>::iterator end2) {
        std::vector<T> result;
        result.reserve(std::distance(begin1, end1) + std::distance(begin2, end2));

        auto iter1 = begin1;
        auto iter2 = begin2;

        while (iter1 != end1 && iter2 != end2)
        {
            if (*iter1 >= *iter2)
            {
                result.push_back(*iter2);
                iter2++;
            }
            else
            {
                result.push_back(*iter1);
                iter1++;
            }

        }

        std::move(iter1, end1, std::back_inserter(result));
        std::move(iter2, end2, std::back_inserter(result));

        return result;
    }

    template <typename T>
    void inplace_merge_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator middle, typename std::vector<T>::iterator end) {
        std::vector<T> temp;
        temp.reserve(std::distance(begin, end));
        std::copy(begin, end, std::back_inserter(temp));

        auto left_iter = temp.begin();
        auto right_iter = temp.begin() + std::distance(begin, middle);

        for (auto i = begin; i != end; ++i)
        {
            if (left_iter >= temp.begin() + std::distance(begin, middle))
            {
                *i = *right_iter++;
            }
            else if (right_iter >= temp.end())
            {
                *i = *left_iter++;
            }
            else if (*left_iter < *right_iter)
            {
                *i = *left_iter++;
            }
            else if (*left_iter >= *right_iter)
            {
                *i = *right_iter++;
            }
        }
    }

    template <typename T>
    void top_down_merge_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
    {
        if (end <= begin + 1)
        {
            return;
        }

        auto middle = begin + std::distance(begin, end) / 2;

        std::sort(begin, std::next(middle));
        std::sort(middle, end);

        inplace_merge_sort<T>(begin, middle, end);

    }

}

