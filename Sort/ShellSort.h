#pragma once

#include <iterator>

namespace Sort {

    // ����һ����Ϊ shell_sort ��ģ�庯��
    // ������һ��������ʷ�Χ�����磬�����������
    template<std::ranges::random_access_range Container>
    constexpr void shell_sort(Container& c) {
        // ��ȡ�����Ĵ�С
        int size = std::size(c);
        // ��ʼ�����ֵΪ 1
        int gap = 1;
        // ʹ�� 3x+1 ���м������ļ��ֵ
        while (gap < size / 3)
            gap = gap * 3 + 1;
        // �����ֵ���ڵ��� 1 ʱ������ϣ������
        while (gap >= 1)
        {
            // ��ÿ�����Ϊ gap �������н��в�������
            for (int i = gap; i < size; ++i)
            {
                // �� c[i] ���뵽 c[i-gap], c[i-2*gap], c[i-3*gap]... ��
                for (int j = i; j >= gap && c[j] < c[j - gap]; j -= gap)
                    std::swap(c[j], c[j - gap]);
            }
            // ��С���ֵ
            gap = gap / 3;
        }
    }

}