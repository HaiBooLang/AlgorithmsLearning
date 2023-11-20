#pragma once

#include <iterator>

namespace Sort {

	template<std::ranges::random_access_range Container>
    constexpr void insertion_sort(Container& c) 
    {
        // �������е�ÿ��Ԫ�ؽ���ѭ��
        for (auto i = std::begin(c); i != std::end(c); ++i)
        {
            // ���浱ǰԪ�ص�ֵ
            auto key = *i;
            // ��ʼ����һ��ָ��ǰԪ�صĵ�����
            auto j = i;
            // �ӵ�ǰԪ�ؿ�ʼ��ǰɨ�裬���ǰһ��Ԫ�ش��ڵ�ǰԪ�ص�ֵ���ͽ�ǰһ��Ԫ������ƶ�һλ
            while (j != std::begin(c) && *(j - 1) > key) 
            {
                *j = *(j - 1);
                --j;
            }

            // ��� j ָ���λ�ò��ǳ�ʼ��λ�ã��ͽ������ֵ���뵽��ȷ��λ��
            if (j != i)
            {
                *j = key;
            }
        }
    }
}