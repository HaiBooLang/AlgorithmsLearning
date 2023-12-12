/*
 * 文件名: MergeSort.h
 * 作者: HaiBooLang
 * 创建日期: 2023-11-19
 * 描述: 这个文件包含了归并排序算法的实现。
 */
#pragma once

#include <vector>

namespace Sort
{

    // 归并排序
    // 归并排序是一种采用分治策略的排序算法。它的基本思想是将两个或两个以上的有序表合并成一个新的有序表。
    // 归并排序的时间复杂度为 O(n log n)，无论是最好、最坏还是平均情况都是如此。空间复杂度为 O(n)，因为需要额外的空间来存储合并的结果。
    // 归并排序适用于数据量大，对稳定性有要求的场景，例如大规模数据的排序和处理。

    template <typename T>
    std::vector<T> merge_sort(const std::vector<T> &c1, const std::vector<T> &c2)
    {
        std::vector<T> result;
        // 预分配内存
        result.reserve(c1.size() + c2.size());

        auto iter1 = c1.begin();
        auto iter2 = c2.begin();

        // 当两个容器都有元素时
        while (iter1 != c1.end() && iter2 != c2.end())
        {
            // 如果容器1的当前元素小于或等于容器2的当前元素
            if (*iter1 <= *iter2)
            {
                // 将容器1的当前元素添加到结果中
                result.push_back(*iter1);
                ++iter1;
            }
            else
            {
                // 否则，将容器2的当前元素添加到结果中
                result.push_back(*iter2);
                ++iter2;
            }
        }

        // 如果容器1还有剩余元素，将它们添加到结果中
        std::copy(iter1, c1.end(), std::back_inserter(result));

        // 如果容器2还有剩余元素，将它们添加到结果中
        std::copy(iter2, c2.end(), std::back_inserter(result));

        return result;
    }

    // 归并排序的另一种实现，接受迭代器作为参数，可以对任何支持随机访问迭代器的容器进行排序。
    // std::vector<typename std::iterator_traits<Iterator>::value_type>

    template <typename T>
    std::vector<T> merge_sort(typename std::vector<T>::iterator begin1, typename std::vector<T>::iterator end1, typename std::vector<T>::iterator begin2, typename std::vector<T>::iterator end2)
    {
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

        std::copy(iter1, end1, std::back_inserter(result));
        std::copy(iter2, end2, std::back_inserter(result));

        return result;
    }

    // 原地归并排序
    // 原地归并排序是归并排序的一种变种，它试图在不使用额外空间的情况下进行排序。
    // 但是，由于需要进行复杂的元素交换，其时间复杂度为 O(n^2)，空间复杂度为 O(1)。
    // 原地归并排序适用于对空间使用有严格限制的场景。

    template <typename T>
    void inplace_merge_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator middle, typename std::vector<T>::iterator end)
    {
        // 创建一个临时向量来存储原始数据
        std::vector<T> temp;
        temp.reserve(std::distance(begin, end));
        std::copy(begin, end, std::back_inserter(temp));

        auto left_iter = temp.begin();
        auto right_iter = temp.begin() + std::distance(begin, middle);

        // 将两个有序的部分合并
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

    // 自顶向下的归并排序
    // 自顶向下的归并排序是一种递归的排序算法，它首先将数据集分解为两个相等的部分，然后对每个部分进行排序，最后将排序后的部分合并。
    // 自顶向下的归并排序的时间复杂度为 O(n log n)，空间复杂度为 O(n)，因为需要额外的空间来存储合并的结果。
    // 自顶向下的归并排序适用于数据量大，对稳定性有要求的场景，例如大规模数据的排序和处理。

    template <typename T>
    void top_down_merge_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
    {
        if (end <= begin + 1)
        {
            return;
        }

        auto middle = begin + std::distance(begin, end) / 2;

        top_down_merge_sort<T>(begin, middle);
        top_down_merge_sort<T>(middle, end);

        inplace_merge_sort<T>(begin, middle, end);
    }

    // 改进的自顶向下的归并排序函数
    // 这个版本的归并排序在处理小规模子数组时使用插入排序，因为对于小规模数据，插入排序的常数因子较小，效率更高。
    // 当子数组的大小小于或等于设定的阈值时，就使用插入排序。

    template <typename T>
    void top_down_merge_sort_improved(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
    {
        const int threshold = 16; // 设置阈值，当子数组大小小于这个值时，使用插入排序
        if (std::distance(begin, end) <= threshold)
        {
            insertion_sort(begin, end);
            return;
        }

        auto middle = begin + std::distance(begin, end) / 2;

        top_down_merge_sort<T>(begin, std::next(middle));
        top_down_merge_sort<T>(middle, end);

        inplace_merge_sort<T>(begin, middle, end);
    }

    // 自底向上的归并排序函数
    // 自底向上的归并排序是一种迭代的排序算法，它首先合并小的子数组，然后逐渐合并更大的子数组。
    // 这种方法不需要递归，因此在处理大规模数据时，可以避免递归导致的栈溢出问题。
    // 自底向上的归并排序比较适合用链表组织的数据。这种方法只需要重新组织链表链接就能将链表原地排序（不需要创建任何新的链表结点）。

    template <typename T>
    void down_top_merge_sort(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end)
    {
        if (begin == end)
            return; // 如果范围为空，直接返回

        auto len = std::distance(begin, end);

        // 外层循环控制每次合并的元素个数
        for (auto size = 1; size < len; size *= 2)
        {
            // 内层循环控制每次合并的起始位置
            for (auto left = begin; left < end; left += 2 * size)
            {
                auto middle = left + size;
                auto right = std::min(left + 2 * size, end);

                // 合并 [left, middle) 和 [middle, right)
                inplace_merge_sort<T>(left, middle, right);
            }
        }
    }
}
