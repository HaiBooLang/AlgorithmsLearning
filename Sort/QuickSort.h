/*
 * 文件名: MergeSort.h
 * 作者: HaiBooLang
 * 创建日期: 2023-11-19
 * 描述: 这个文件包含了归并排序算法的实现。
 */
#pragma once

#include "InsertionSort.h"

namespace Sort
{

    // 快速排序
    // 快速排序是一种采用分治策略的排序算法。它的基本思想是选择一个枢轴元素，然后将数组重新排列，使得所有小于枢轴的元素都在枢轴之前，所有大于枢轴的元素都在枢轴之后。
    // 在这个过程中，枢轴元素到达其最终位置。然后，我们对枢轴左右两侧的子数组进行递归排序。
    // 快速排序的平均时间复杂度为 O(n log n)，但在最坏情况下（输入数组已经排序），时间复杂度为 O(n^2)。空间复杂度为 O(log n)，这是因为需要栈空间来处理递归调用。
    // 快速排序不是稳定的排序算法，但在处理大规模和随机数据时，它的平均性能非常好。

    template<typename InputIt>
    inline InputIt partition(InputIt begin, InputIt end)
    {
        // 选择第一个元素、中间元素和最后一个元素
        auto first = begin;
        auto middle = begin + std::distance(begin, end) / 2;
        auto last = end - 1;

        // 找到这三个元素的中值，并将其作为枢轴
        auto pivot_iter = std::max(std::min(first, middle), std::min(std::max(first, middle), last));
        auto pivot_value = *pivot_iter;
        std::iter_swap(begin, pivot_iter);

        auto left_iter = begin + 1;
        auto right_iter = end - 1;

        while (true) {
            // 从左向右找到第一个大于枢轴的元素
            while (left_iter <= right_iter && *left_iter <= pivot_value) ++left_iter;
            // 从右向左找到第一个小于或等于枢轴的元素
            while (left_iter <= right_iter && *right_iter > pivot_value) --right_iter;
            // 如果左右指针相遇，跳出循环
            if (left_iter >= right_iter) break;
            // 交换左右指针指向的元素
            std::iter_swap(left_iter, right_iter);
        }

        // 将枢轴元素放到正确的位置
        std::iter_swap(begin, right_iter);
        // 返回枢轴元素的位置
        return right_iter;
    }


	template <typename Container>
	inline void quick_sort(Container& container)
	{
		auto left_iter = c.begin();
		auto right_iter = c.end();

		// 如果待排序的序列的大小小于15，那么使用插入排序而不是快速排序
		if (std::distance(left_iter, right_iter) < 15)
        {
			insertion_sort(left_iter, right_iter);
			return;
		}

		// 对序列进行分区，返回枢轴的位置
		auto pivot_iter = partition(left_iter, right_iter);

		// 对枢轴左边的序列进行递归排序
        if (pivot_iter != left_iter)
        {
            quick_sort(left_iter, pivot_iter);
        }
		// 对枢轴右边的序列进行递归排序
		if (pivot_iter + 1 != right_iter)
        {
            quick_sort(pivot_iter + 1, right_iter);
        }

	}

}