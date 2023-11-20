#pragma once

#include <iterator>

namespace Sort {

    // ����һ����Ϊ shell_sort ��ģ�庯��
    // ������һ��������ʷ�Χ�����磬�������������һ�����ɼ�����еĺ���
    template<std::ranges::random_access_range Container, typename GapCalculator>
    constexpr void shell_sort(Container& c, GapCalculator&& gap_calculator) {
        // ��ȡ�����Ĵ�С
        auto size = std::size(c);
        // ʹ�� gap_calculator �������ɼ������
        auto gaps = gap_calculator(size);
        // ��ÿ�����ֵ����һ��ϣ������
        for (const auto& gap : gaps)
        {
            // ��ÿ�����Ϊ gap �������н��в�������
            for (auto i = std::next(c.begin(), gap); i != c.end(); ++i)
            {
                // �� c[i] ���뵽 c[i-gap], c[i-2*gap], c[i-3*gap]... ��
                for (auto j = i; j - c.begin() >= gap && *j < *(j - gap); j -= gap)
                    std::swap(*j, *(j - gap));
            }
        }
    }
}