#pragma once

#include <iterator>

namespace Sort {

    // ϣ������
    // ϣ�������ǲ��������һ�ָ���Ч�ĸĽ��汾��Ҳ��Ϊ����С�������򡱣������˼���ǣ��Ƚ�����������ļ�¼���зָ��Ϊ���������зֱ����ֱ�Ӳ������򣬴����������еļ�¼"��������"ʱ���ٶ�ȫ���¼��������ֱ�Ӳ�������
    // ϣ���������Ч��ԭ������Ȩ����������Ĺ�ģ�������ԣ�����֮�������������鶼�̣ܶ�����֮�������鶼�ǲ�������ģ���������������ʺϲ�������
    // ϣ�������ʱ�临�Ӷ����������е�ѡȡ�йأ����磬����������Ϊ 1, 2, 4, 8,... ʱ���ʱ�临�Ӷ�Ϊ O(n^2)�������ʹ�� Hibbard ������������� 1, 3, 7, 15,...�����ʱ�临�Ӷ�Ϊ O(n^(3/2))��
    // ϣ������Ŀռ临�Ӷ�Ϊ O(1)����Ϊֻ��Ҫ�����������ʱ������
    // ϣ�����������ڴ��ģ���ݵ������ر��ǵ��������ڼ�ǧ������֮��ʱ��Ч�ʽϸߡ�
    
    template<std::ranges::random_access_range Container, typename GapCalculator>
    constexpr void shell_sort(Container& c, GapCalculator&& gap_calculator)
    {
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
                {
                    std::swap(*j, *(j - gap));
                }
            }
        }
    }
}