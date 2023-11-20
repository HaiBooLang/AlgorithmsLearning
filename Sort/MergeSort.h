#pragma once

#include <vector>

namespace Sort
{

    // �鲢����
    template <typename T>
    std::vector<T> inplace_merge_sort(const std::vector<T>& c1, const std::vector<T>& c2) {
        std::vector<T> result;
        // Ԥ�����ڴ�
        result.reserve(c1.size() + c2.size());

        auto iter1 = c1.begin();
        auto iter2 = c2.begin();

        // ��������������Ԫ��ʱ
        while (iter1 != c1.end() && iter2 != c2.end()) {
            // �������1�ĵ�ǰԪ��С�ڻ��������2�ĵ�ǰԪ��
            if (*iter1 <= *iter2) {
                // ������1�ĵ�ǰԪ����ӵ������
                result.push_back(*iter1);
                ++iter1;
            }
            else {
                // ���򣬽�����2�ĵ�ǰԪ����ӵ������
                result.push_back(*iter2);
                ++iter2;
            }
        }

        // �������1����ʣ��Ԫ�أ���������ӵ������
        std::move(iter1, c1.end(), std::back_inserter(result));

        // �������2����ʣ��Ԫ�أ���������ӵ������
        std::move(iter2, c2.end(), std::back_inserter(result));

        return result;
    }

}

