#pragma once

#include <iterator>

namespace Sort
{

    // ����һ����Ϊ selection_sort ��ģ�庯��
    // ������һ��������ʷ�Χ�����磬�����������
    template<std::ranges::random_access_range Container>
    constexpr void selection_sort(Container& c)
    {
        // �������е�ÿ��Ԫ�ؽ���ѭ��
        for (auto i = std::begin(c); i != std::end(c); ++i)
        {
            // �ҵ��ӵ�ǰԪ�ص�����ĩβ����СԪ��
            auto min_element = std::min_element(i, std::end(c));
            // �����СԪ��С�ڵ�ǰԪ�أ��ͽ������ǵ�λ��
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